//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Description of Arm64 system registers.
//
//----------------------------------------------------------------------------

#include "regview.h"
#include "strutils.h"

// Accessing the PAC key registers crashes macOS.
#if defined(__linux__)
    #define READ_PAC  RegView::READ
    #define WRITE_PAC RegView::WRITE
#elif defined(__APPLE__)
    #define READ_PAC  0
    #define WRITE_PAC 0
#endif

// Map view of AllRegisters, indexed by CMD_REG_ values and names.
std::map<int, RegView::Register> RegView::AllRegistersByIndex;
std::map<std::string, RegView::Register> RegView::AllRegistersByName;

// A dummy empty description.
const RegView::Register RegView::EmptyRegister {"", "", INVALID, 0, {}};

// Descriptions of all known registers.
const std::list<RegView::Register> RegView::AllRegisters {
    {
        "ID_AA64PFR0_EL1", "D17.2.67", CSR_REG_AA64PFR0, READ,
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
        "ID_AA64PFR1_EL1", "D17.2.68", CSR_REG_AA64PFR1, READ,
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
        "ID_AA64ISAR0_EL1", "D17.2.61", CSR_REG_AA64ISAR0, READ,
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
        "ID_AA64ISAR1_EL1", "D17.2.62", CSR_REG_AA64ISAR1, READ,
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
        "ID_AA64ISAR2_EL1", "D17.2.63", CSR_REG_AA64ISAR2, READ,
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
        "TCR_EL1", "D17.2.131", CSR_REG_TCR, READ,
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
        "APIAKEY_EL1", "D17.2.21/22", CSR_REG2_APIAKEY, READ_PAC | WRITE_PAC | NEED_PAC, {}
    },
    {
        "APIBKEY_EL1", "D17.2.23/24", CSR_REG2_APIBKEY, READ_PAC | WRITE_PAC | NEED_PAC, {}
    },
    {
        "APDAKEY_EL1", "D17.2.15/16", CSR_REG2_APDAKEY, READ_PAC | WRITE_PAC | NEED_PAC, {}
    },
    {
        "APDBKEY_EL1", "D17.2.17/18", CSR_REG2_APDBKEY, READ_PAC | WRITE_PAC | NEED_PAC, {}
    },
    {
        "APGAKEY_EL1", "D17.2.19/20", CSR_REG2_APGAKEY, READ_PAC | WRITE_PAC | NEED_PACGA, {}
    },
};


//----------------------------------------------------------------------------
// Register features field as a string
//----------------------------------------------------------------------------

std::string RegView::Register::featuresList() const
{
    std::list<std::string> res;
    if (features & RegView::READ) {
        res.push_back("read");
    }
    if (features & RegView::WRITE) {
        res.push_back("write");
    }
    if (features & RegView::NEED_PAC) {
        res.push_back("need PAC");
    }
    if (features & RegView::NEED_PACGA) {
        res.push_back("need PACGA");
    }
    return Join(res, ", ");
}


//----------------------------------------------------------------------------
// Initialize AllRegistersByIndex and AllRegistersByName.
//----------------------------------------------------------------------------

void RegView::initializeCache()
{
    if (AllRegistersByIndex.empty() || AllRegistersByName.empty()) {
        for (const auto& reg : AllRegisters) {
            AllRegistersByIndex[reg.csr_index] = reg;
            AllRegistersByName[ToUpper(reg.name)] = reg;
        }
    }
}


//----------------------------------------------------------------------------
// Get the description of register by its csr_index or name.
//----------------------------------------------------------------------------

const RegView::Register& RegView::getRegister(int csr_index)
{
    initializeCache();
    const auto iter(AllRegistersByIndex.find(csr_index));
    return iter == AllRegistersByIndex.end() ? EmptyRegister : iter->second;
}

const RegView::Register& RegView::getRegister(const std::string& name)
{
    initializeCache();
    const auto iter(AllRegistersByName.find(ToUpper(name)));
    return iter == AllRegistersByName.end() ? EmptyRegister : iter->second;
}
