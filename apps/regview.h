//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Description of Arm64 system registers.
//
//----------------------------------------------------------------------------

#pragma once

#include "cpusysregs.h"
#include <string>
#include <list>
#include <map>

//
// A class with static fields to describe Arm64 system registers.
//
class RegView
{
public:
    // Description of one value in a bitfield in a register.
    struct Name {
        csr_u64_t   value;
        std::string name;
    };

    // Description of one bit-field in a register.
    struct BitField {
        std::string     name;    // bitfield name
        int             msb;     // most significant bit index
        int             lsb;     // least significant bit index
        std::list<Name> values;  // known values, end with a NULL name
    };

    // Define the properties and condition of existence of a register.
    enum {
        READ       = 0x0001,  // readable register
        WRITE      = 0x0002,  // writeable register
        NEED_PAC   = 0x0004,  // exist only with PAC
        NEED_PACGA = 0x0008,  // exist only with PACGA
    };

    // Description of one register with bitfields.
    struct Register {
        std::string         name;       // register name
        std::string         section;    // section in Arm arch ref manual
        int                 csr_index;  // CSR_REG_ or CSR_REG2_ value from cpusysregs.h
        int                 features;   // required features (bit mask)
        std::list<BitField> fields;     // known bitfields
    };

    // Descriptions of all known registers.
    static const std::list<Register> AllRegisters;

    // Get the description of register by its csr_index.
    static const Register& getRegister(int csr_index);

private:
    // A dummy empty description.
    static const Register EmptyRegister;

    // Map view of AllRegisters, indexed by CMD_REG_ values.
    static std::map<int, Register> AllRegistersByIndex;

    // Initialize AllRegistersByIndex.
    static void initializeAllRegistersByIndex();
};
