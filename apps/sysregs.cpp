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

#include <iostream>
#include <cstddef>
#include <cstdlib>


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
    csr_pair_t write_value;
    bool all_registers;
    bool binary;
    bool force;
    bool list_registers;
    bool summary;
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
              << "  -f : force read/write register, even if not supposed to" << std::endl
              << "  -h : display this help text" << std::endl
              << "  -l : list all supported Arm64 system registers" << std::endl
              << "  -r name : read the content of the named register" << std::endl
              << "  -s : summary of CPU features" << std::endl
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
    write_value{0, 0},
    all_registers(false),
    binary(false),
    force(false),
    list_registers(false),
    summary(false),
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
        else if (arg == "-s") {
            summary = true;
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
// Read a register
//----------------------------------------------------------------------------

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
    else if (opt.verbose) {
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
// Display a summary of CPU features.
//----------------------------------------------------------------------------

void FeaturesSummary(const Options& opt, std::ostream& out)
{
    RegAccess regaccess(true, true);
    out << std::endl
        << "Summary: PAC: " << YesNo(regaccess.hasPAC())
        << ", PACGA: " << YesNo(regaccess.hasPACGA())
        << ", BTI: " << YesNo(regaccess.hasBTI())
        << ", RME: " << YesNo(regaccess.hasRME())
        << ", CSV2_2: " << YesNo(regaccess.hasCSV2_2())
        << std::endl << std::endl;
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
    if (!opt.write_register.empty()) {
        WriteRegister(opt, std::cout);
    }
    if (!opt.read_register.empty()) {
        ReadRegister(opt, std::cout);
    }
    if (opt.summary) {
        FeaturesSummary(opt, std::cout);
    }

    return EXIT_SUCCESS;
}