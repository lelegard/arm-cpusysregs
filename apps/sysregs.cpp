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
    bool binary;
    bool force;
    bool list_registers;
    std::string read_register;
    
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
              << "  -b : display register value in binary (default: hex)" << std::endl
              << "  -f : force read/write register, even if not supposed to" << std::endl
              << "  -l : list all supported Arm64 system registers" << std::endl
              << "  -r name : read the content of a register" << std::endl
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
    binary(false),
    force(false),
    list_registers(false),
    read_register()
{
    for (int i = 1; i < argc; ++i) {
        const std::string arg(argv[i]);
        if (arg == "--help" || arg == "-h") {
            usage();
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
        else if (arg == "-r" && i+1 < argc) {
            read_register = argv[++i];
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
    const auto& desc(RegView::getRegister(opt.read_register));

    if (!desc.isValid()) {
        opt.fatal("unknown register " + opt.read_register + ", try -l");
    }
    if (!opt.force && !(desc.features & RegView::READ)) {
        opt.fatal("register " + opt.read_register + " is not readable on this CPU, try -f at your own risks");        
    }

    RegAccess regaccess;
    csr_pair_t reg;
    if (!regaccess.isOpen()) {
        regaccess.printLastError(opt.command);
    }
    else if (!regaccess.read(desc.csr_index, reg)) {
        regaccess.printLastError(opt.command + ": error reading " + opt.read_register);
    }
    else if (opt.binary) {
        if (desc.isPair()) {
            out << ToBinary(reg.high) << std::endl;
        }
        out << ToBinary(reg.low) << std::endl;
    }
    else {
        if (desc.isPair()) {
            out << ToString(reg) << std::endl;
        }
        else {
            out << ToString(reg.low) << std::endl;
        }
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
    if (!opt.read_register.empty()) {
        ReadRegister(opt, std::cout);
    }

    return EXIT_SUCCESS;
}
