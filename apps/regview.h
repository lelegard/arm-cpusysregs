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
#include "regaccess.h"
#include <ostream>
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
        READ         = 0x00000001,  // readable register
        WRITE        = 0x00000002,  // writeable register
        NEED_PAC     = 0x00000004,  // exist only with PAC
        NEED_PACGA   = 0x00000008,  // exist only with PACGA
        NEED_CSV2_2  = 0x00000010,  // exist only with CSV2_2
        NEED_RNG     = 0x00000020,  // exist only with RNG
        NEED_SVE     = 0x00000040,  // exist only with SVE
        NEED_SME     = 0x00000080,  // exist only with SME
        NEED_ETE     = 0x00000100,  // exist only with ETE
        NEED_PMUv3   = 0x00000200,  // exist only with PMUv3p4
        NEED_PMUv3p4 = 0x00000400,  // exist only with PMUv3p4
        NEED_TCR2    = 0x00000800,  // exist only with TCR2
        NEED_SCTLR2  = 0x00001000,  // exist only with SCTLR2
        NEED_AIE     = 0x00002000,  // exist only with AIE
        NEED_S1PIE   = 0x00004000,  // exist only with S1PIE
        NEED_SPE     = 0x00008000,  // exist only with SPE
        NEED_MPAM    = 0x00010000,  // exist only with MPAM
        NEED_TRBE    = 0x00020000,  // exist only with TRBE
    };

    // Description of one register with bitfields.
    class Register
    {
    public:
        std::string         name;       // register name
        int                 csr_index;  // CSR_REGID_ or CSR_REGID2_ value from cpusysregs.h
        int                 features;   // required features (bit mask)
        std::list<BitField> fields;     // known bitfields

        // Get a string version of the features field.
        std::string featuresList() const;

        // Check if the register description is valid.
        bool isValid() const { return csr_index != INVALID; }

        // Check if the register is in fact a pair of registers (e.g. PAK key)
        bool isPair() const { return csr_regid_is_pair(csr_index); }

        // Format an hexa value of the register.
        std::string hexa(csr_u64_t value) const;
        std::string hexa(const csr_pair_t& value) const;

        // Display a detailed descriptions of one register value.
        void display(std::ostream& out, csr_u64_t value) const;
        void display(std::ostream& out, const csr_pair_t& value) const;

        // Check if the register is supported on this CPU.
        bool isSupported(RegAccess&) const;
        bool canRead(RegAccess&) const;
        bool canWrite(RegAccess&) const;
    };

    // This value of 'csr_index' fields indicates an invalid register description.
    static constexpr int INVALID = ~0;

    // Descriptions of all known registers.
    static const std::list<Register> AllRegisters;

    // Get the description of register by its csr_index or name (case insensitive).
    static const Register& getRegister(int csr_index);
    static const Register& getRegister(const std::string& name);

private:
    // A dummy empty description.
    static const Register EmptyRegister;

    // Map view of AllRegisters, indexed by CMD_REG_ values and names.
    static std::map<int, Register> AllRegistersByIndex;
    static std::map<std::string, Register> AllRegistersByName;

    // Initialize AllRegistersByIndex and AllRegistersByName.
    static void initializeCache();
};
