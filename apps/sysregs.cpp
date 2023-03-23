//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Userland application to play with the Arm64 CPU system registers.
//
//----------------------------------------------------------------------------

#include "cpusysregs.h"
#include "strutils.h"
#include "regaccess.h"
#include "regview.h"
#include "armfeatures.h"
#include "armpseudocode.h"

#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <list>


//----------------------------------------------------------------------------
// Command line options.
//----------------------------------------------------------------------------

class Options
{
public:
    // Constructor.
    Options(int argc, char* argv[]);

    // Command line options.
    std::string command;
    std::string read_register;
    std::string write_register;
    std::string display_register;
    csr_pair_t write_value;
    csr_pair_t display_value;
    bool all_registers;
    bool binary;
    bool force;
    bool list_registers;
    bool cpu_summary;
    bool direct_load;
    bool pac_summary;
    bool verbose;

    // Print help and exits.
    void usage() const;

    // Print a fatal error and exit.
    void fatal(const std::string& message) const;
};

void Options::usage() const
{
    std::cerr << std::endl
              << "Command line options:" << std::endl
              << std::endl
              << "  -a : read all supported Arm64 system registers" << std::endl
              << "  -b : display register value in binary (default: hex)" << std::endl
              << "  -d name value : display the value in the named register format" << std::endl
              << "  -f : force read/write register, even if not supposed to" << std::endl
              << "  -h : display this help text" << std::endl
              << "  -l : list all supported Arm64 system registers" << std::endl
              << "  -p : summary of supported PAC features" << std::endl
              << "  -r name : read the content of the named register" << std::endl
              << "  -s : summary of CPU features" << std::endl
              << "  -S : same as -s but read registers at EL0 (maybe partial, may fail)" << std::endl
              << "  -w name hex-value : write the value in the named register" << std::endl
              << "  -v : verbose, display register analysis and fields" << std::endl
              << std::endl;
    ::exit(EXIT_FAILURE);
}

void Options::fatal(const std::string& message) const
{
    std::cerr << command << ": " << message << std::endl;
    ::exit(EXIT_FAILURE);
}

Options::Options(int argc, char* argv[]) :
    command(argc < 1 ? "" : argv[0]),
    read_register(),
    write_register(),
    display_register(),
    write_value{0, 0},
    display_value{0, 0},
    all_registers(false),
    binary(false),
    force(false),
    list_registers(false),
    cpu_summary(false),
    direct_load(false),
    pac_summary(false),
    verbose(false)
{
    for (int i = 1; i < argc; ++i) {
        const std::string arg(argv[i]);
        if (arg == "--help" || arg == "-h") {
            usage();
        }
        else if (arg == "-r" && i+1 < argc) {
            read_register = argv[++i];
        }
        else if (arg == "-w" && i+2 < argc) {
            write_register = argv[++i];
            if (!DecodeHexa(write_value, argv[++i])) {
                fatal("invalid hexa value to write");
            }
        }
        else if (arg == "-d" && i+2 < argc) {
            display_register = argv[++i];
            if (!DecodeHexa(display_value, argv[++i])) {
                fatal("invalid hexa value to display");
            }
        }
        else if (arg == "-a") {
            all_registers = true;
        }
        else if (arg == "-b") {
            binary = true;
        }
        else if (arg == "-f") {
            force = true;
        }
        else if (arg == "-l") {
            list_registers = true;
        }
        else if (arg == "-p") {
            pac_summary = true;
        }
        else if (arg == "-s") {
            cpu_summary = true;
        }
        else if (arg == "-S") {
            cpu_summary = direct_load = true;
        }
        else if (arg == "-v") {
            verbose = true;
        }
        else {
            fatal("invalid option '" + arg + "', try --help");
        }
    }
}


//----------------------------------------------------------------------------
// List available registers
//----------------------------------------------------------------------------

void ListRegisters(const Options& opt, std::ostream& out)
{
    const std::string name_title("Register");
    const std::string doc_title("RTFM section");
    const std::string feature_title("Features");

    size_t name_width = name_title.length();
    size_t doc_width = doc_title.length();
    size_t feature_width = 30;

    for (const auto& desc : RegView::AllRegisters) {
        name_width = std::max(name_width, desc.name.length());
        doc_width = std::max(doc_width, desc.section.length());
    }

    out << std::endl
        << Pad(name_title, name_width, ' ') << "  " << Pad(doc_title, doc_width, ' ') << "  " << feature_title << std::endl
        << Pad("", name_width, '-') << "  " << Pad("", doc_width, '-') << "  " << Pad("", feature_width, '-') << std::endl;

    for (const auto& desc : RegView::AllRegisters) {
        out << Pad(desc.name, name_width, ' ') << "  "
            << Pad(desc.section, doc_width, ' ') << "  "
            << desc.featuresList() << std::endl;
    }
    out << std::endl;
}


//----------------------------------------------------------------------------
// Read or display a register
//----------------------------------------------------------------------------

void DisplayRegisterValue(const Options& opt, const RegView::Register& desc, const csr_pair_t& reg, std::ostream& out)
{
    if (opt.verbose) {
        out << std::endl;
        desc.display(out, reg);
        out << std::endl;
    }
    else if (opt.binary) {
        if (desc.isPair()) {
            out << ToBinary(reg.high) << std::endl;
        }
        out << ToBinary(reg.low) << std::endl;
    }
    else {
        out << desc.hexa(reg) << std::endl;
    }
}

void ReadRegister(const Options& opt, std::ostream& out)
{
    RegAccess regaccess(false, true);

    const auto& desc(RegView::getRegister(opt.read_register));
    if (!desc.isValid()) {
        opt.fatal("unknown register " + opt.read_register + ", try -l");
    }
    if (!opt.force && !desc.canRead(regaccess)) {
        opt.fatal("register " + opt.read_register + " is not readable on this CPU, try -f at your own risks");
    }

    csr_pair_t reg;
    if (!regaccess.read(desc.csr_index, reg)) {
        regaccess.printLastError(opt.command + ": error reading " + opt.read_register);
    }
    else {
        DisplayRegisterValue(opt, desc, reg, out);
    }
}

void DisplayRegister(const Options& opt, std::ostream& out)
{
    const auto& desc(RegView::getRegister(opt.display_register));
    if (!desc.isValid()) {
        opt.fatal("unknown register " + opt.display_register + ", try -l");
    }
    else {
        DisplayRegisterValue(opt, desc, opt.display_value, out);
    }
}


//----------------------------------------------------------------------------
// Write a register
//----------------------------------------------------------------------------

void WriteRegister(const Options& opt, std::ostream& out)
{
    RegAccess regaccess(false, true);

    const auto& desc(RegView::getRegister(opt.write_register));
    if (!desc.isValid()) {
        opt.fatal("unknown register " + opt.write_register + ", try -l");
    }
    if (!opt.force && !desc.canWrite(regaccess)) {
        opt.fatal("register " + opt.write_register + " is not writeable on this CPU, try -f at your own risks");
    }
    if (opt.verbose) {
        out << opt.command << ": writing " << desc.hexa(opt.write_value) << " " << desc.name << std::endl;
    }
    if (!regaccess.write(desc.csr_index, opt.write_value)) {
        regaccess.printLastError(opt.command + ": error writing " + opt.write_register);
    }
}


//----------------------------------------------------------------------------
// Read all registers
//----------------------------------------------------------------------------

void ReadAllRegisters(const Options& opt, std::ostream& out)
{
    size_t name_width = 0;
    if (!opt.verbose) {
        for (const auto& desc : RegView::AllRegisters) {
            name_width = std::max(name_width, desc.name.length());
        }
        out << std::endl;
    }

    // Loop on all registers.
    RegAccess regaccess(true, true);
    for (const auto& desc : RegView::AllRegisters) {
        csr_pair_t reg;
        // Check if this register is readable and compatible with the CPU features.
        if (desc.canRead(regaccess) && regaccess.read(desc.csr_index, reg)) {
            if (opt.verbose) {
                out << std::endl;
                desc.display(out, reg);
            }
            else {
                out << Pad(desc.name, name_width, ' ') << "  " << desc.hexa(reg) << std::endl;
            }
        }
    }
    out << std::endl;
}


//----------------------------------------------------------------------------
// Display a summary of PAC features.
//----------------------------------------------------------------------------

void PACLayout(ArmPseudoCode& code, std::ostream& out, bool upper, bool is_instr)
{
    const csr_u64_t address = upper ? ~0ull : 0;
    const int top = code.pacTopBit(address, is_instr);
    const int sel = code.pacSelBit(address, is_instr);
    const int bottom = code.pacBottomBit(address, is_instr);

    std::string layout;
    if (bottom < 55 && 55 < top) {
        layout = Format("%d:56,54:%d", top, bottom);
    }
    else {
        layout = Format("%d:%d", top == 55 ? 54 : top, bottom == 55 ? 56 : bottom);
    }

    out << Format("  %-5s (%s): PAC size: %2d bits, bit range: %11s (top: %2d, sel: %2d, bottom: %2d)",
                  is_instr ? "Instr" : "Data", upper ? "upper" : "lower",
                  code.pacSize(address, is_instr), layout.c_str(), top, sel, bottom)
        << std::endl;
}

void PointerAuthenticationSummary(const Options& opt, std::ostream& out)
{
    RegAccess regaccess(true, true);
    ArmFeatures feat(regaccess);

    out << std::endl
        << "Summary: PAC: " << YesNo(feat.FEAT_PAuth())
        << ", PACGA: " << YesNo(feat.hasPACGA())
        << std::endl
        << "PAuth: " << YesNo(feat.FEAT_PAuth())
        << ", PAuth2: " << YesNo(feat.FEAT_PAuth2())
        << ", EPAC: " << YesNo(feat.FEAT_EPAC())
        << ", FPAC: " << YesNo(feat.FEAT_FPAC())
        << ", FPACCOMBINE: " << YesNo(feat.FEAT_FPACCOMBINE())
        << ", CONSTPACFIELD: " << YesNo(feat.FEAT_CONSTPACFIELD())
        << std::endl
        << "Algorithms: QARMA3: " << YesNo(feat.FEAT_PACQARMA3())
        << ", QARMA5: " << YesNo(feat.FEAT_PACQARMA5())
        << ", implementation-defined: " << YesNo(feat.FEAT_PACIMP())
        << std::endl
        << "Memory tagging: " << YesNo(feat.addressTaggingEnabled()) << std::endl;
    if (feat.FEAT_PAuth()) {
        ArmPseudoCode code(regaccess);
        out << "Detailed PAC layout:" << std::endl
            << "  TCR_EL1: TBI0=" << feat.TCR_EL1_TBI0()
            << ", TBID0=" << feat.TCR_EL1_TBID0()
            << ", T0SZ=" << feat.TCR_EL1_T0SZ()
            << ", TBI1=" << feat.TCR_EL1_TBI1()
            << ", TBID1=" << feat.TCR_EL1_TBID1()
            << ", T1SZ=" << feat.TCR_EL1_T1SZ()
            << std::endl;
        PACLayout(code, out, false, false);
        PACLayout(code, out, true, false);
        PACLayout(code, out, false, true);
        PACLayout(code, out, true, true);
    }
    out << std::endl;
}


//----------------------------------------------------------------------------
// Descriptions of all Arm features.
//----------------------------------------------------------------------------

class Feature
{
public:
    std::string name;                  // Feature name
    bool (ArmFeatures::*get)() const;  // Method to get that feature
};

const std::list<Feature> AllArmFeatures {
    // Automatically generated file:
#if !defined(WINDOWS) // @@@ not yet implemented
    #include "_armfeatures.h"
#endif // @@@ not yet implemented
};


//----------------------------------------------------------------------------
// Display a summary of CPU features.
//----------------------------------------------------------------------------

void FeaturesSummary(const Options& opt, std::ostream& out)
{
    ArmFeatures features;
    if (opt.direct_load) {
        // Read system registers at EL0 (direct MRS instructions).
        features.loadDirect();
    }
    else {
        // Read system registers at EL1 (call the kernel module).
        RegAccess regaccess(true, true);
        features.load(regaccess);
    }

    size_t name_width = 0;
    for (const auto& feat : AllArmFeatures) {
        name_width = std::max(name_width, feat.name.length());
    }
    for (const auto& feat : AllArmFeatures) {
        out << Pad(feat.name + " ", name_width + 2) << " " << YesNo((features.*feat.get)()) << std::endl;
    }
}


//----------------------------------------------------------------------------
// Program entry point
//----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    const Options opt(argc, argv);

    if (opt.list_registers) {
        ListRegisters(opt, std::cout);
    }
    if (opt.all_registers) {
        ReadAllRegisters(opt, std::cout);
    }
    if (!opt.display_register.empty()) {
        DisplayRegister(opt, std::cout);
    }
    if (!opt.write_register.empty()) {
        WriteRegister(opt, std::cout);
    }
    if (!opt.read_register.empty()) {
        ReadRegister(opt, std::cout);
    }
    if (opt.pac_summary) {
        PointerAuthenticationSummary(opt, std::cout);
    }
    if (opt.cpu_summary) {
        FeaturesSummary(opt, std::cout);
    }

    return EXIT_SUCCESS;
}
