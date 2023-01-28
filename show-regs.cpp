//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Userland application to display the Arm64 CPU system registers.
//
//----------------------------------------------------------------------------

#include "cpusysregs.h"
#include "apputils.h"

#include <list>
#include <iostream>
#include <cstdio>
#include <cstddef>
#include <cstdlib>

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>


//----------------------------------------------------------------------------
// Description of Arm64 system registers using the "ID feature" scheme.
// See the Arm Architecture Reference Manual, section D17.1.3.
//----------------------------------------------------------------------------

// List of ID registers:
// — The AArch32 Auxiliary Feature register ID_AFR0_EL1.
// — The AArch32 Processor Feature registers ID_PFR0_EL1 and ID_PFR1_EL1.
// — The AArch32 Debug Feature register ID_DFR0_EL1.
// — The AArch32 Memory Model Feature registers ID_MMFR0_EL1, ID_MMFR1_EL1,
//   ID_MMFR2_EL1, ID_MMFR3_EL1, and ID_MMFR4_EL1.
// — The AArch32 Instruction Set Attribute registers ID_ISAR0_EL1, ID_ISAR1_EL1,
//   ID_ISAR2_EL1, ID_ISAR3_EL1, ID_ISAR4_EL1, and ID_ISAR5_EL1.
// — The AArch32 Media and VFP Feature registers MVFR0_EL1, MVFR1_EL1, and MVFR2_EL1.
// - The AArch64 Auxiliary Feature registers ID_AA64AFR0_EL1 and ID_AA64AFR1_EL1.
// - The AArch64 Processor Feature registers ID_AA64PFR0_EL1 and ID_AA64PFR1_EL1.
// - The AArch64 Debug Feature registers ID_AA64DFR0_EL1 and ID_AA64DFR1_EL1.
// - The AArch64 Memory Model Feature registers ID_AA64MMFR0_EL1, ID_AA64MMFR1_EL1,
//   and ID_AA64MMFR2_EL1.
// - The AArch64 Instruction Set Attribute registers ID_AA64ISAR0_EL1 and ID_AA64ISAR1_EL1.

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

// Define the condition of existence of a register.
// This is a bitmask. At least one condition is necessary for the register to exist.
#define ALWAYS      0x0000
#define NEED_PAC    0x0001
#define NEED_PACGA  0x0002
#define NEED_BTI    0x0004

// Description of one register with bitfields.
struct Register {
    std::string                  name;     // register name
    std::string                  section;  // section in Arm arch ref manual
    csr_u64_t csr_registers_t::* offset;   // offset in structure csr_registers_t
    int                          require;  // required features
    std::list<BitField>          fields;   // known bitfields
};

// Descriptions of registers which are returned by the kernel module.
const std::list<Register> AllRegisters {
    {
        "ID_AA64PFR0_EL1", "D17.2.67", &csr_registers_t::id_aa64pfr0_el1, ALWAYS,
        {
            {"CSV3",    63, 60, {{0, "undefined"}, {1, "safe"}}},
            {"CSV2",    59, 56, {{0, "none"}, {1, "CSV2"}, {2, "CSV2_2"}, {3, "CSV2_3"}}},
            {"RME",     55, 52, {{0, "none"}, {1, "RMEv1"}}},
            {"DIT",     51, 48, {{0, "none"}, {1, "DIT"}}},
            {"AMU",     47, 44, {{0, "none"}, {1, "AMUv1p1"}}},
            {"MPAM",    43, 40, {{0, "v0"}, {1, "v1"}}},
            {"SEL2",    39, 36, {{0, "none"}, {1, "Secure EL2"}}},
            {"SVE",     35, 32, {{0, "none"}, {1, "SVE"}}},
            {"RAS",     31, 28, {{0, "none"}, {1, "RAS"}, {2, "RASv1p1"}}},
            {"GIC",     27, 24, {{0, "none"}, {1, "3.0+4.0"}, {3, "4.1"}}},
            {"AdvSIMD", 23, 20, {{0, "basic"}, {1, "basic+FP16"}, {15, "none"}}},
            {"FP",      19, 16, {{0, "FP"}, {1, "FP+FP16"}, {15, "none"}}},
            {"EL3",     15, 12, {{0, "none"}, {1, "AArch64-only"}, {2, "AArch64+32"}}},
            {"EL2",     11,  8, {{0, "none"}, {1, "AArch64-only"}, {2, "AArch64+32"}}},
            {"EL2",      7,  4, {{1, "AArch64-only"}, {2, "AArch64+32"}}},
            {"EL0",      3,  0, {{1, "AArch64-only"}, {2, "AArch64+32"}}},
        }
    },
    {
        "ID_AA64PFR1_EL1", "D17.2.68", &csr_registers_t::id_aa64pfr1_el1, ALWAYS,
        {
            {"NMI",       39, 36, {{0, "none"}, {1, "NMI"}}},
            {"CSV2_frac", 35, 32, {{0, "none"}, {1, "CSV2_1p1"}, {2, "CSV2_1p2"}}},
            {"RNDR_trap", 31, 28, {{0, "none"}, {1, "RNG_TRAP"}}},
            {"SME",       27, 24, {{0, "none"}, {1, "SME"}}},
            {"MPAM_frac", 19, 16, {{0, "v.0"}, {1, "v.1"}}},
            {"RAS_frac",  15, 12, {{0, "none"}, {1, "VARv1p1"}}},
            {"MTE",       11,  8, {{0, "none"}, {1, "MTE"}, {2, "MTE2"}, {3, "MTE3"}}},
            {"SSBS",       7,  4, {{0, "none"}, {1, "SSBS"}, {2, "SSBS2"}}},
            {"BT",         3,  0, {{0, "none"}, {1, "BTI"}}},
        }
    },
    {
        "ID_AA64ISAR0_EL1", "D17.2.61", &csr_registers_t::id_aa64isar0_el1, ALWAYS,
        {
            {"RNDR",   63, 60, {{0, "none"}, {1, "RNG"}}},
            {"TLB",    59, 56, {{0, "none"}, {1, "TLBIOS"}, {2, "TLBIOS+TLBIRANGE"}}},
            {"TS",     55, 52, {{0, "none"}, {1, "FlagM"}, {2, "FlagM2"}}},
            {"FHM",    51, 48, {{0, "none"}, {1, "FHM"}}},
            {"DP",     47, 44, {{0, "none"}, {1, "DotProd"}}},
            {"SM4",    43, 40, {{0, "none"}, {1, "SM4"}}},
            {"SM3",    39, 36, {{0, "none"}, {1, "SM3"}}},
            {"SHA3",   35, 32, {{0, "none"}, {1, "SHA3"}}},
            {"RDM",    31, 28, {{0, "none"}, {1, "RDM"}}},
            {"TME",    27, 24, {{0, "none"}, {1, "TME"}}},
            {"Atomic", 23, 20, {{0, "none"}, {2, "LSE"}}},
            {"CRC32",  19, 16, {{0, "none"}, {1, "CRC32"}}},
            {"SHA2",   15, 12, {{0, "none"}, {1, "SHA256"}, {2, "SHA256+SHA512"}}},
            {"SHA1",   11,  8, {{0, "none"}, {1, "SHA1"}}},
            {"AES",     7,  4, {{0, "none"}, {1, "AES"}, {2, "AES+PMULL"}}},
        }
    },
    {
        "ID_AA64ISAR1_EL1", "D17.2.62", &csr_registers_t::id_aa64isar1_el1, ALWAYS,
        {
            {"LS64",    63, 60, {{0, "none"}, {1, "LS64"}, {2, "LS64+LS64_V"}, {3, "LS64+LS64_V+LS64_ACCDATA"}}},
            {"XS",      59, 56, {{0, "none"}, {1, "XS"}}},
            {"I8MM",    55, 52, {{0, "none"}, {1, "I8MM"}}},
            {"DGH",     51, 48, {{0, "none"}, {1, "BF16"}, {2, "EBF16"}}},
            {"BF16",    47, 44, {{0, "none"}, {1, "AMUv1p1"}}},
            {"SPECRES", 43, 40, {{0, "none"}, {1, "SHA256v1"}}},
            {"SB",      39, 36, {{0, "none"}, {1, "SB"}}},
            {"FRINTTS", 35, 32, {{0, "none"}, {1, "FRINTTS"}}},
            {"GPI",     31, 28, {{0, "none"}, {1, "PACIMP"}}},
            {"GPA",     27, 24, {{0, "none"}, {1, "PACQARMA5"}}},
            {"LRCPC",   23, 20, {{0, "none"}, {1, "LRCPC"}, {2, "LRCPC2"}}},
            {"FCMA",    19, 16, {{0, "none"}, {1, "FCMA"}}},
            {"JSCVT",   15, 12, {{0, "none"}, {1, "JSCVT"}}},
            {"API",     11,  8, {{0, "none"}, {1, "IMP PAuth"}, {2, "IMP PAuth+EPAC"}, {3, "IMP PAuth+EPAC+PAuth2"},
                                 {4, "IMP PAuth+EPAC+PAuth2+FPAC"}, {5, "IMP PAuth+EPAC+PAuth2+FPAC+FPACCOMBINE"}}},
            {"APA",      7,  4, {{0, "none"}, {1, "QARMA5 PAuth"}, {2, "QARMA5 PAuth+EPAC"}, {3, "QARMA5 PAuth+EPAC+PAuth2"},
                                 {4, "QARMA5 PAuth+EPAC+PAuth2+FPAC"}, {5, "QARMA5 PAuth+EPAC+PAuth2+FPAC+FPACCOMBINE"}}},
            {"DPB",      3,  0, {{0, "none"}, {1, "DPB"}, {2, "DPB2"}}},
        }
    },
    {
        "ID_AA64ISAR2_EL1", "D17.2.63", &csr_registers_t::id_aa64isar2_el1, ALWAYS,
        {
            {"PAC_frac", 27, 24, {{0, "none"}, {1, "ConstPACField"}}},
            {"BC",       23, 20, {{0, "none"}, {1, "HBC"}}},
            {"MOPS",     19, 16, {{0, "none"}, {1, "MOPS"}}},
            {"APA3",     15, 12, {{0, "none"}, {1, "QARMA3 PAuth"}, {2, "QARMA3 PAuth+EPAC"}, {3, "QARMA3 PAuth+EPAC+PAuth2"},
                                  {4, "QARMA3 PAuth+EPAC+PAuth2+FPAC"}, {5, "QARMA3 PAuth+EPAC+PAuth2+FPAC+FPACCOMBINE"}}},
            {"GPA3",     11,  8, {{0, "none"}, {1, "PACQARMA3"}}},
            {"RPRES",     7,  4, {{0, "none"}, {1, "RPRES"}}},
            {"WFxT",      3,  0, {{0, "none"}, {1, "WFxT"}}},
        }
    },
    {
        "TCR_EL1,", "D17.2.131", &csr_registers_t::tcr_el1, ALWAYS,
        {
            {"IPS",   34, 32, {{0, "32 bits, 4GB"}, {1, "36 bits, 64 GB"}, {2, "40 bits, 1 TB"}, {3, "42 bits, 4 TB"},
                               {4, "44 bits, 16 TB"}, {5, "48 bits, 256 TB"}, {6, "52 bits, 4 PB"}}},
            {"TG1",   31, 30, {{1, "16 kB"}, {2, "4 kB"}, {3, "64 kB"}}},
            {"SH1",   29, 28, {{0, "Non shareable"}, {2, "Outer shareable"}, {3, "Inner shareable"}}},
            {"ORGN1", 27, 26, {{0, "Normal memory, Outer Non-cacheable"},
                               {1, "Normal memory, Outer Write-Back Read-Allocate Write-Allocate Cacheable"},
                               {2, "Normal memory, Outer Write-Through Read-Allocate No Write-Allocate Cacheable"},
                               {3, "Normal memory, Outer Write-Back Read-Allocate No Write-Allocate Cacheable"}}},
            {"IRGN1", 25, 24, {{0, "Normal memory, Inner Non-cacheable"},
                               {1, "Normal memory, Inner Write-Back Read-Allocate Write-Allocate Cacheable"},
                               {2, "Normal memory, Inner Write-Through Read-Allocate No Write-Allocate Cacheable"},
                               {3, "Normal memory, Inner Write-Back Read-Allocate No Write-Allocate Cacheable"}}},
            {"EPD1",  23, 23, {{0, "Translation table walks using TTBR1_EL1"},
                               {1, "TLB miss using TTBR1_EL1 generates a Translation fault"}}},
            {"A1",    22, 22, {{0, "TTBR0_EL1.ASID defines the ASID"},
                               {1, "TTBR1_EL1.ASID defines the ASID"}}},
            {"T1SZ",  21, 16, {}},
            {"TG0",   15, 14, {{0, "4 kB"}, {1, "64 kB"}, {2, "16 kB"}}},
            {"SH0",   13, 12, {{0, "Non shareable"}, {2, "Outer shareable"}, {3, "Inner shareable"}}},
            {"ORGN0", 11, 10, {{0, "Normal memory, Outer Non-cacheable"},
                               {1, "Normal memory, Outer Write-Back Read-Allocate Write-Allocate Cacheable"},
                               {2, "Normal memory, Outer Write-Through Read-Allocate No Write-Allocate Cacheable"},
                               {3, "Normal memory, Outer Write-Back Read-Allocate No Write-Allocate Cacheable"}}},
            {"IRGN0",  9,  8, {{0, "Normal memory, Inner Non-cacheable"},
                               {1, "Normal memory, Inner Write-Back Read-Allocate Write-Allocate Cacheable"},
                               {2, "Normal memory, Inner Write-Through Read-Allocate No Write-Allocate Cacheable"},
                               {3, "Normal memory, Inner Write-Back Read-Allocate No Write-Allocate Cacheable"}}},
            {"EPD0",   7,  7, {{0, "Translation table walks using TTBR0_EL1"},
                               {1, "TLB miss using TTBR0_EL1 generates a Translation fault"}}},
            {"T0SZ",   5,  0, {}},
        }
    },
    {
        "APIAKEYHI_EL1", "D17.2.21", &csr_registers_t::apiakeyhi_el1, NEED_PAC, {}
    },
    {
        "APIAKEYLO_EL1", "D17.2.22", &csr_registers_t::apiakeylo_el1, NEED_PAC, {}
    },
    {
        "APIBKEYHI_EL1", "D17.2.23", &csr_registers_t::apibkeyhi_el1, NEED_PAC, {}
    },
    {
        "APIBKEYLO_EL1", "D17.2.24", &csr_registers_t::apibkeylo_el1, NEED_PAC, {}
    },
    {
        "APDAKEYHI_EL1", "D17.2.15", &csr_registers_t::apdakeyhi_el1, NEED_PAC, {}
    },
    {
        "APDAKEYLO_EL1", "D17.2.16", &csr_registers_t::apdakeylo_el1, NEED_PAC, {}
    },
    {
        "APDBKEYHI_EL1", "D17.2.17", &csr_registers_t::apdbkeyhi_el1, NEED_PAC, {}
    },
    {
        "APDBKEYLO_EL1", "D17.2.18", &csr_registers_t::apdbkeylo_el1, NEED_PAC, {}
    },
    {
        "APGAKEYHI_EL1", "D17.2.19", &csr_registers_t::apgakeyhi_el1, NEED_PACGA, {}
    },
    {
        "APGAKEYLO_EL1", "D17.2.20", &csr_registers_t::apgakeylo_el1, NEED_PACGA, {}
    },
};


//----------------------------------------------------------------------------
// Program entry point
//----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    // Open the pseudo-device for the kernel module.
    const int csr_fd = open(CSR_DEVICE_PATH, O_RDONLY);
    if (csr_fd < 0) {
        perror(CSR_DEVICE_PATH);
        return EXIT_FAILURE;
    }

    // Read all system registers.
    csr_registers_t regs;
    if (ioctl(csr_fd, CSR_IOCTL_GET_REGS, &regs) < 0) {
        perror("ioctl get regs");
        return EXIT_FAILURE;
    }
    close(csr_fd);

    // CPU features.
    const int features =
        (CSR_HAS_PAC(regs.id_aa64isar1_el1, regs.id_aa64isar2_el1) ? NEED_PAC : 0) |
        (CSR_HAS_PACGA(regs.id_aa64isar1_el1, regs.id_aa64isar2_el1) ? NEED_PACGA : 0) |
        (CSR_HAS_BTI(regs.id_aa64pfr1_el1) ? NEED_BTI : 0);

    // Loop on all supported registers.
    for (const auto& desc : AllRegisters) {

        // If the CPU does not have the required feature for this register, skip it.
        if (desc.require != 0 && (desc.require & features) == 0) {
            continue;
        }

        // Extract the register value from the structure.
        const csr_u64_t regval = regs.*desc.offset;

        // Print the register content as a suite of 4-bit binary values.
        std::cout << std::endl
                  << desc.name << ": " << ToBinary(regval) << std::endl
                  << std::endl
                  << "  Arch. Ref. Manual section " << desc.section << std::endl;

        // Print the details of the register content.
        if (desc.fields.empty()) {
            // No bitfield defined, just display the value in hexadecimal.
            std::cout << "  Value: " << ToString(regval) << std::endl;
        }
        else {
            // Print the various bit fields.
            for (const auto& bf : desc.fields) {
                // Value of the bitfield.
                const csr_u64_t bfval = (regval << (63 - bf.msb)) >> (63 - bf.msb + bf.lsb);
                // Look for a name for this value.
                std::string name(bf.values.empty() ? Format("%lld", bfval) : "reserved");
                for (const auto& nm : bf.values) {
                    if (nm.value == bfval) {
                        name = nm.name;
                        break;
                    }
                }
                // Print the bitfield description.
                const int hexwidth = (bf.msb - bf.lsb) / 4 + 1;
                std::cout << "  " << bf.name << ": " << Format("0x%*llX", hexwidth, bfval) << " (" << name << ")" << std::endl;
            }
        }
    }
    std::cout << std::endl;

    // Summary of CPU features.
    std::cout << "Summary: PAC: " << YesNo(CSR_HAS_PAC(regs.id_aa64isar1_el1, regs.id_aa64isar2_el1))
              << ", PACGA: " << YesNo(CSR_HAS_PACGA(regs.id_aa64isar1_el1, regs.id_aa64isar2_el1))
              << ", BTI: " << YesNo(CSR_HAS_BTI(regs.id_aa64pfr1_el1))
              << ", RME: " << YesNo(CSR_HAS_RME(regs.id_aa64pfr0_el1))
              << std::endl << std::endl;

    return EXIT_SUCCESS;
}
