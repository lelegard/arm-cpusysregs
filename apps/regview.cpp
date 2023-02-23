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
#include "armfeatures.h"
#include "strutils.h"

// Accessing the PAC key registers in macOS kernel crashes the system.
#if defined(__APPLE__)
    #define READ_PAC  0
    #define WRITE_PAC 0
#else
    #define READ_PAC  RegView::READ
    #define WRITE_PAC RegView::WRITE
#endif

// Map view of AllRegisters, indexed by CMD_REG_ values and names.
std::map<int, RegView::Register> RegView::AllRegistersByIndex;
std::map<std::string, RegView::Register> RegView::AllRegistersByName;

// A dummy empty description.
const RegView::Register RegView::EmptyRegister {"", "", INVALID, 0, {}};


//----------------------------------------------------------------------------
// Check CPU features
//----------------------------------------------------------------------------

bool RegView::Register::isSupported(RegAccess& ra) const
{
    ArmFeatures feat(ra);
    return (!(features & NEED_PAC) || feat.FEAT_PAuth()) &&
           (!(features & NEED_PACGA) || feat.hasPACGA()) &&
           (!(features & NEED_CSV2_2) || feat.FEAT_CSV2_2()) &&
           (!(features & NEED_RNG) || feat.FEAT_RNG()) &&
           (!(features & NEED_SVE) || feat.FEAT_SVE()) &&
           (!(features & NEED_SME) || feat.FEAT_SME()) &&
           (!(features & NEED_ETE) || feat.FEAT_ETE()) &&
           (!(features & NEED_PMUv3p4) || feat.FEAT_PMUv3p4()) &&
           (!(features & NEED_TCR2) || feat.FEAT_TCR2()) &&
           (!(features & NEED_AIE) || feat.FEAT_AIE());
}

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
    if (features & RegView::NEED_CSV2_2) {
        res.push_back("need CSV2_2");
    }
    if (features & RegView::NEED_RNG) {
        res.push_back("need RNG");
    }
    if (features & RegView::NEED_SVE) {
        res.push_back("need SVE");
    }
    if (features & RegView::NEED_SME) {
        res.push_back("need SME");
    }
    if (features & RegView::NEED_ETE) {
        res.push_back("need ETE");
    }
    if (features & RegView::NEED_PMUv3p4) {
        res.push_back("need PMU v3.4");
    }
    if (features & RegView::NEED_TCR2) {
        res.push_back("need TCR2");
    }
    if (features & RegView::NEED_AIE) {
        res.push_back("need AIE");
    }
    return Join(res, ", ");
}


//----------------------------------------------------------------------------
// Descriptions of all known registers.
//----------------------------------------------------------------------------

const std::list<RegView::Register> RegView::AllRegisters {
    /* --------
     * Template for copy/paste on new registers:
    {
        "", "D17.2.", CSR_REGID_, READ,
        {
            {"",    63, 60, {{0, "none"}, {1, ""}}},
            {"",    59, 56, {{0, "none"}, {1, ""}}},
            {"",    55, 52, {{0, "none"}, {1, ""}}},
            {"",    51, 48, {{0, "none"}, {1, ""}}},
            {"",    47, 44, {{0, "none"}, {1, ""}}},
            {"",    43, 40, {{0, "none"}, {1, ""}}},
            {"",    39, 36, {{0, "none"}, {1, ""}}},
            {"",    35, 32, {{0, "none"}, {1, ""}}},
            {"",    31, 28, {{0, "none"}, {1, ""}}},
            {"",    27, 24, {{0, "none"}, {1, ""}}},
            {"",    23, 20, {{0, "none"}, {1, ""}}},
            {"",    19, 16, {{0, "none"}, {1, ""}}},
            {"",    15, 12, {{0, "none"}, {1, ""}}},
            {"",    11,  8, {{0, "none"}, {1, ""}}},
            {"",     7,  4, {{0, "none"}, {1, ""}}},
            {"",     3,  0, {{0, "none"}, {1, ""}}},
        }
    },
    -------- */
    {
        "APDAKEY_EL1", "D17.2.15/16", CSR_REGID2_APDAKEY, READ_PAC | WRITE_PAC | NEED_PAC, {}
    },
    {
        "APDBKEY_EL1", "D17.2.17/18", CSR_REGID2_APDBKEY, READ_PAC | WRITE_PAC | NEED_PAC, {}
    },
    {
        "APGAKEY_EL1", "D17.2.19/20", CSR_REGID2_APGAKEY, READ_PAC | WRITE_PAC | NEED_PACGA, {}
    },
    {
        "APIAKEY_EL1", "D17.2.21/22", CSR_REGID2_APIAKEY, READ_PAC | WRITE_PAC | NEED_PAC, {}
    },
    {
        "APIBKEY_EL1", "D17.2.23/24", CSR_REGID2_APIBKEY, READ_PAC | WRITE_PAC | NEED_PAC, {}
    },
    {
        "CTR_EL0", "D17.2.34", CSR_REGID_CTR, READ,
        {
            {"TminLine", 37, 32, {}},
            {"DIC",      29, 29, {}},
            {"IDC",      28, 28, {}},
            {"CWG",      27, 24, {}},
            {"ERG",      23, 20, {}},
            {"DminLine", 19, 16, {}},
            {"L1Ip",     15, 14, {{0, "VPIPT"}, {1, "AIVIVT"}, {2, "VIPT"}, {3, "PIPT"}}},
            {"IminLine",  3,  0, {}},
        }
    },
    {
        "HCR_EL2", "D17.2.48", CSR_REGID_HCR, 0, {
            {"TWEDEL",   63, 60, {}},
            {"TWEDEn",   59, 59, {}},
            {"TID5",     58, 58, {{0, "none"}, {1, "trap"}}},
            {"DCT",      57, 57, {{0, "untagged"}, {1, "tagged"}}},
            {"ATA",      56, 56, {{0, "forbidden"}, {1, "allowed"}}},
            {"TTLBOS",   55, 55, {{0, "none"}, {1, "trap"}}},
            {"TTLBIS",   54, 54, {{0, "none"}, {1, "trap"}}},
            {"EnSCXT",   53, 53, {{0, "none"}, {1, "trap"}}},
            {"TOCU",     52, 52, {{0, "none"}, {1, "trap"}}},
            {"AMVOFFEN", 51, 51, {{0, "disabled"}, {1, "enabled"}}},
            {"TICAB",    50, 50, {{0, "none"}, {1, "trap"}}},
            {"TID4",     49, 49, {{0, "none"}, {1, "trap"}}},
            {"GPF",      48, 48, {{0, "none"}, {1, "trap"}}},
            {"FIEN",     47, 47, {{0, "trap"}, {1, "none"}}},
            {"FWB",      46, 46, {}},
            {"NV2",      45, 45, {}},
            {"AT",       44, 44, {{0, "none"}, {1, "trap"}}},
            {"NV1",      43, 43, {}},
            {"NV",       42, 42, {}},
            {"API",      41, 41, {{0, "trap"}, {1, "none"}}},
            {"APK",      40, 40, {{0, "trap"}, {1, "none"}}},
            {"TME",      39, 39, {{0, "undefined"}, {1, "normal"}}},
            {"MIOCNCE",  38, 38, {}},
            {"TEA",      37, 37, {}},
            {"TERR",     36, 36, {{0, "none"}, {1, "trap"}}},
            {"TLOR",     35, 35, {{0, "none"}, {1, "trap"}}},
            {"E2H",      34, 34, {{0, "disabled"}, {1, "enabled"}}},
            {"ID",       33, 33, {}},
            {"CD",       32, 32, {}},
            {"RW",       31, 31, {}},
            {"TRVM",     30, 30, {{0, "none"}, {1, "trap"}}},
            {"HCD",      29, 29, {{0, "none"}, {1, "undefined"}}},
            {"TDZ",      28, 28, {}},
            {"TGE",      27, 27, {}},
            {"TVM",      26, 26, {{0, "none"}, {1, "trap"}}},
            {"TTLB",     25, 25, {{0, "none"}, {1, "trap"}}},
            {"TPU",      24, 24, {{0, "none"}, {1, "trap"}}},
            {"TPCP",     23, 23, {{0, "none"}, {1, "trap"}}},
            {"TSW",      22, 22, {}},
            {"TACR",     21, 21, {{0, "none"}, {1, "trap"}}},
            {"TIDCP",    20, 20, {{0, "none"}, {1, "trap"}}},
            {"TSC",      19, 19, {{0, "none"}, {1, "trap"}}},
            {"TID3",     18, 18, {{0, "none"}, {1, "trap"}}},
            {"TID2",     17, 17, {{0, "none"}, {1, "trap"}}},
            {"TID1",     16, 16, {{0, "none"}, {1, "trap"}}},
            {"TID0",     15, 15, {{0, "none"}, {1, "trap"}}},
            {"TWE",      14, 14, {{0, "none"}, {1, "trap"}}},
            {"TWI",      13, 13, {{0, "none"}, {1, "trap"}}},
            {"DC",       12, 12, {}},
            {"BSU",      11, 10, {{0, "none"}, {1, "inner shareable"}, {2, "outer shareable"}, {3, "full system"}}},
            {"FB",        9,  9, {}},
            {"VSE",       8,  8, {}},
            {"VI",        7,  7, {{0, "none"}, {1, "IRQ pending"}}},
            {"VF",        6,  6, {{0, "none"}, {1, "IRQ pending"}}},
            {"AMO",       5,  5, {}},
            {"IMO",       4,  4, {}},
            {"FMO",       3,  3, {}},
            {"PTW",       2,  2, {}},
            {"SWIO",      1,  1, {}},
            {"VM",        0,  0, {{0, "disabled"}, {1, "enabled"}}},
        }
    },
    {
        "ID_AA64AFR0_EL1", "D17.2.57", CSR_REGID_AA64AFR0, READ, {}
    },
    {
        "ID_AA64AFR1_EL1", "D17.2.58", CSR_REGID_AA64AFR1, READ, {}
    },
    {
        "ID_AA64DFR0_EL1", "D17.2.59", CSR_REGID_AA64DFR0, READ,
        {
            {"HPMN0",       63, 60, {{0, "none"}, {1, "HPMN0"}}},
            {"BRBE",        55, 52, {{0, "none"}, {1, "BRBE"}, {2, "BRBEv1p1"}}},
            {"MTPMU",       51, 48, {}},
            {"TraceBuffer", 47, 44, {{0, "none"}, {1, "TRBE"}}},
            {"TraceFilt",   43, 40, {{0, "none"}, {1, "TRBF"}}},
            {"DoubleLock",  39, 36, {{0, "DoubleLock"}, {15, "none"}}},
            {"PMSVer",      35, 32, {}},
            {"CTX_CMPs",    31, 28, {}},
            {"WRPs",        23, 20, {}},
            {"BRPs",        15, 12, {}},
            {"PMUVer",      11,  8, {}},
            {"TraceVer",     7,  4, {}},
            {"DebugVer",     3,  0, {}},
        }
    },
    {
        "ID_AA64DFR1_EL1", "D17.2.60", CSR_REGID_AA64DFR1, READ, {}
    },
    {
        "ID_AA64ISAR0_EL1", "D17.2.61", CSR_REGID_AA64ISAR0, READ,
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
        "ID_AA64ISAR1_EL1", "D17.2.62", CSR_REGID_AA64ISAR1, READ,
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
        "ID_AA64ISAR2_EL1", "D17.2.63", CSR_REGID_AA64ISAR2, READ,
        {
            {"CSSC",         55, 52, {{0, "none"}, {1, "CSSC"}}},
            {"RPRFM",        51, 48, {{0, "none"}, {1, "RPRFM"}}},
            {"PRFMSLC",      43, 40, {{0, "none"}, {1, "PRFMSLC"}}},
            {"SYSINSTR_128", 39, 36, {{0, "none"}, {1, "SYSINSTR_128"}}},
            {"SYSREG_128",   35, 32, {{0, "none"}, {1, "SYSREG_128"}}},
            {"CLRBHB",       31, 28, {{0, "none"}, {1, "CLRBHB"}}},
            {"PAC_frac",     27, 24, {{0, "none"}, {1, "ConstPACField"}}},
            {"BC",           23, 20, {{0, "none"}, {1, "HBC"}}},
            {"MOPS",         19, 16, {{0, "none"}, {1, "MOPS"}}},
            {"APA3",         15, 12, {{0, "none"}, {1, "QARMA3 PAuth"}, {2, "QARMA3 PAuth+EPAC"},
                                      {3, "QARMA3 PAuth+EPAC+PAuth2"}, {4, "QARMA3 PAuth+EPAC+PAuth2+FPAC"},
                                      {5, "QARMA3 PAuth+EPAC+PAuth2+FPAC+FPACCOMBINE"}}},
            {"GPA3",         11,  8, {{0, "none"}, {1, "PACQARMA3"}}},
            {"RPRES",         7,  4, {{0, "none"}, {1, "RPRES"}}},
            {"WFxT",          3,  0, {{0, "none"}, {1, "WFxT"}}},
        }
    },
    {
        "ID_AA64MMFR0_EL1", "D17.2.64", CSR_REGID_AA64MMFR0, READ,
        {
            {"ECV",       63, 60, {{0, "none"}}},
            {"FGT",       59, 56, {{0, "none"}}},
            {"ExS",       47, 44, {{0, "none"}}},
            {"TGran4_2",  43, 40, {{0, "none"}}},
            {"TGran64_2", 39, 36, {{0, "none"}}},
            {"TGran16_2", 35, 32, {{0, "none"}}},
            {"TGran4",    31, 28, {{0, "none"}}},
            {"TGran64",   27, 24, {{0, "none"}}},
            {"TGran16",   23, 20, {{0, "none"}}},
            {"BigEndEL0", 19, 16, {{0, "none"}, {1, "mixed"}}},
            {"SNSMem",    15, 12, {{0, "none"}, {1, "distinct"}}},
            {"BigEnd",    11,  8, {{0, "none"}, {1, "mixed"}}},
            {"ASIDBits",   7,  4, {{0, "8 bits"}, {1, "16 bits"}}},
            {"PARange",    3,  0, {{0, "32 bits, 4GB"}, {1, "36 bits, 64GB"}, {2, "40 bits, 1TB"}, {3, "42 bits, 4TB"},
                                   {4, "44 bits, 16TB"}, {5, "48 bits, 256TB"}, {6, "52 bits, 4PBB"}}},
        }
    },
    {
        "ID_AA64MMFR1_EL1", "D17.2.65", CSR_REGID_AA64MMFR1, READ,
        {
            {"ECBHB",    63, 60, {{0, "none"}, {1, "ECBHB"}}},
            {"CMOW",     59, 56, {{0, "none"}, {1, "CMOW"}}},
            {"TIDCP1",   55, 52, {{0, "none"}, {1, "TIDCP1"}}},
            {"nTLBPA",   51, 48, {}},
            {"AFP",      47, 44, {{0, "none"}, {1, "AFP"}}},
            {"HCX",      43, 40, {{0, "none"}, {1, "HCX"}}},
            {"ETS",      39, 36, {{0, "none"}, {1, "ETS"}}},
            {"TWED",     35, 32, {{0, "none"}, {1, "TWED"}}},
            {"XNX",      31, 28, {{0, "none"}, {1, "XNX"}}},
            {"SpecSEI",  27, 24, {}},
            {"PAN",      23, 20, {{0, "none"}, {1, "PAN"}, {2, "PAN2"}, {3, "PAN3"}}},
            {"LO",       19, 16, {{0, "none"}, {1, "LOR"}}},
            {"HPDS",     15, 12, {{0, "none"}, {1, "HPDS"}, {2, "HPDS2"}}},
            {"VH",       11,  8, {{0, "none"}, {1, "VHE"}}},
            {"VMIDBits",  7,  4, {{0, "8 bits"}, {2, "16 bits"}}},
            {"HAFDBS",    3,  0, {{0, "none"}}},
        }
    },
    {
        "ID_AA64MMFR2_EL1", "D17.2.66", CSR_REGID_AA64MMFR2, READ,
        {
            {"E0PD",    63, 60, {{0, "none"}, {1, "E0PD"}}},
            {"EVT",     59, 56, {{0, "none"}}},
            {"BBM",     55, 52, {}},
            {"TTL",     51, 48, {{0, "none"}, {1, "TTL"}}},
            {"FWB",     43, 40, {{0, "none"}, {1, "S2FWB"}}},
            {"IDS",     39, 36, {{0, "none"}, {1, "IDST"}}},
            {"AT",      35, 32, {{0, "none"}, {1, "LSE2"}}},
            {"ST",      31, 28, {}},
            {"NV",      27, 24, {}},
            {"CCIDX",   23, 20, {{0, "32-bit"}, {1, "64-bit"}}},
            {"VARange", 19, 16, {{0, "48-bit VA"}, {1, "52-bit VA"}}},
            {"IESB",    15, 12, {{0, "none"}, {1, "IESB"}}},
            {"LSM",     11,  8, {{0, "none"}, {1, "LSMAOC"}}},
            {"UAO",      7,  4, {{0, "none"}, {1, "UAO"}}},
            {"CnP",      3,  0, {{0, "none"}, {1, "TTCNP"}}},
        }
    },
    {
        "ID_AA64MMFR3_EL1", "N/A", CSR_REGID_AA64MMFR3, READ,
        {
            {"Spec_FPACC", 63, 60, {}},
            {"ADERR",      59, 56, {}},
            {"SDERR",      55, 52, {}},
            {"ANERR",      47, 44, {}},
            {"SNERR",      43, 40, {}},
            {"D128_2",     39, 36, {}},
            {"D128",       35, 32, {}},
            {"MEC",        31, 28, {}},
            {"AIE",        27, 24, {}},
            {"S2POE",      23, 20, {}},
            {"S1POE",      19, 16, {}},
            {"S2PIE",      15, 12, {}},
            {"S1PIE",      11,  8, {}},
            {"SCTLRX",      7,  4, {}},
            {"TCRX",        3,  0, {}},
        }
    },
    {
        "ID_AA64MMFR4_EL1", "N/A", CSR_REGID_AA64MMFR4, READ,
        {
            {"EIESB",  7,  4, {}},
        }
    },
    {
        "ID_AA64PFR0_EL1", "D17.2.67", CSR_REGID_AA64PFR0, READ,
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
        "ID_AA64PFR1_EL1", "D17.2.68", CSR_REGID_AA64PFR1, READ,
        {
            {"PFAR",      63, 60, {{0, "none"}, {1, "PFAR"}}},
            {"DF2",       59, 56, {{0, "none"}, {1, "DoubleFault2"}}},
            {"MTEX",      55, 52, {}},
            {"THE",       51, 48, {{0, "none"}, {1, "THE"}}},
            {"GCS",       47, 44, {{0, "none"}, {1, "GCS"}}},
            {"MTE_frac",  43, 40, {}},
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
        "ID_AA64PFR2_EL1", "N/A", CSR_REGID_AA64PFR2, READ,
        {
            {"MTEFAR",       11,  8, {{0, "none"}, {1, "MTE4"}}},
            {"MTESTOREONLY",  7,  4, {{0, "none"}, {1, "MTE_STORE_ONLY"}}},
            {"MTEPERM",       3,  0, {{0, "none"}, {1, "MTE_PERM"}}},
        }
    },
    {
        "ID_AA64SMFR0_EL1", "D17.2.69", CSR_REGID_AA64SMFR0, READ | NEED_SME,
        {
            {"FA64",   63, 63, {{0, "none"}, {1, "SME_FA64"}}},
            {"SMEver", 59, 56, {}},
            {"I16I64", 55, 52, {{0, "none"}, {15, "SME_I16I64"}}},
            {"F64F64", 48, 48, {{0, "none"}, {1, "SME_F16F64"}}},
            {"I8I32",  39, 36, {}},
            {"F16F32", 35, 35, {}},
            {"B16F32", 34, 34, {}},
            {"F32F32", 32, 32, {}},
        }
    },
    {
        "ID_AA64ZFR0_EL1", "D17.2.70", CSR_REGID_AA64ZFR0, READ | NEED_SVE,
        {
            {"F64MM",   59, 56, {{0, "none"}, {1, "F64MM"}}},
            {"F32MM",   55, 52, {{0, "none"}, {1, "F32MM"}}},
            {"I8MM",    47, 44, {{0, "none"}, {1, "I8MM"}}},
            {"SM4",     43, 40, {{0, "none"}, {1, "SVE_SM4"}}},
            {"SHA3",    35, 32, {{0, "none"}, {1, "SVE_SHA3"}}},
            {"BF16",    23, 20, {{0, "none"}, {1, "BF16"}, {2, "EBF16"}}},
            {"BitPerm", 19, 16, {{0, "none"}, {1, "SVE_BitPerm"}}},
            {"AES",      7,  4, {{0, "none"}, {1, "SVE_AES"}, {2, "SVE_AES+SVE_AES"}}},
            {"SVEver",   3,  0, {{0, "none"}, {1, "SVE2"}}},
        }
    },
    {
        "MAIR_EL1", "D17.2.97", CSR_REGID_MAIR, READ,
        {
            {"Attr7", 63, 56, {}},
            {"Attr6", 55, 48, {}},
            {"Attr5", 47, 40, {}},
            {"Attr4", 39, 32, {}},
            {"Attr3", 31, 24, {}},
            {"Attr2", 23, 16, {}},
            {"Attr1", 15,  8, {}},
            {"Attr0",  7,  0, {}},
        }
    },
    {
        "MAIR2_EL1", "N/A", CSR_REGID_MAIR2, READ | NEED_AIE,
        {
            {"Attr7", 63, 56, {}},
            {"Attr6", 55, 48, {}},
            {"Attr5", 47, 40, {}},
            {"Attr4", 39, 32, {}},
            {"Attr3", 31, 24, {}},
            {"Attr2", 23, 16, {}},
            {"Attr1", 15,  8, {}},
            {"Attr0",  7,  0, {}},
        }
    },
    {
        "MIDR_EL1", "D17.2.100", CSR_REGID_MIDR, READ,
        {
            {"Implementer",  31, 24, {{0x41, "Arm"}, {0x61, "Apple"}, {0xC0, "Ampere"}}},
            {"Variant",      23, 20, {}},
            {"Architecture", 19, 16, {{1, "v4"}, {2, "v4T"}, {3, "v5"}, {4, "v5T"}, {5, "v5TE"},
                                      {6, "v5TEJ"}, {7, "v6"}, {15, "By features"}}},
            {"PartNum",      15,  4, {}},
            {"Revision",      3,  0, {}},
        }
    },
    {
        "MPIDR_EL1", "D17.2.101", CSR_REGID_MPIDR, READ,
        {
            {"Aff3", 39, 32, {}},
            {"U",    30, 30, {{0, "Multiprocessor"}, {1, "Uniprocessor"}}},
            {"MT",   24, 24, {{0, "Independent perf."}, {1, "Interdependent perf."}}},
            {"Aff2", 23, 16, {}},
            {"Aff1", 15,  8, {}},
            {"Aff0",  7,  0, {}},
        }
    },
    {
        "REVIDR_EL1", "D17.2.106", CSR_REGID_REVIDR, READ, {}
    },
    {
        "RNDR", "D17.2.111", CSR_REGID_RNDR, READ | NEED_RNG, {}
    },
    {
        "RNDRRS", "D17.2.112", CSR_REGID_RNDRRS, READ | NEED_RNG, {}
    },
    {
        "SCR_EL3", "D17.2.117", CSR_REGID_SCR, 0,
        {
            {"NSE",       62, 62, {}},
            {"FGTEn2",    59, 59, {{0, "trap"}, {1, "none"}}},
            {"EnIDCP128", 55, 55, {}},
            {"PFAREn",    53, 53, {}},
            {"TWERR",     52, 52, {}},
            {"TMEA",      51, 51, {}},
            {"MECEn",     49, 49, {}},
            {"GPF",       48, 48, {{0, "none"}, {1, "exception"}}},
            {"D128En",    47, 47, {}},
            {"AIEn",      46, 46, {}},
            {"PIEn",      45, 45, {}},
            {"SCTLR2En",  44, 44, {}},
            {"TCR2En",    43, 43, {}},
            {"RCWMASKEn", 42, 42, {}},
            {"EnTP2",     41, 41, {{0, "trap"}, {1, "none"}}},
            {"TRNDR",     40, 40, {{0, "none"}, {1, "trap"}}},
            {"GCSEn",     39, 39, {}},
            {"HXEn",      38, 38, {{0, "trap"}, {1, "none"}}},
            {"ADEn",      37, 37, {{0, "trap"}, {1, "none"}}},
            {"EnAS0",     36, 36, {{0, "trap"}, {1, "none"}}},
            {"AMVOFFEN",  35, 35, {{0, "trap"}, {1, "none"}}},
            {"TME",       34, 34, {{0, "undefined"}, {1, "none"}}},
            {"TWEDEL",    33, 30, {}},
            {"TWEDEn",    29, 29, {{0, "imp"}, {1, "twedel"}}},
            {"ECVEn",     28, 28, {{0, "trap"}, {1, "none"}}},
            {"FGTEn",     27, 27, {{0, "trap"}, {1, "none"}}},
            {"ATA",       26, 26, {{0, "trap"}, {1, "none"}}},
            {"EnSCXT",    25, 25, {{0, "trap"}, {1, "none"}}},
            {"FIEN",      21, 21, {{0, "trap"}, {1, "none"}}},
            {"NMEA",      20, 20, {}},
            {"EASE",      19, 19, {{0, "exception"}, {1, "interrupt"}}},
            {"EEL2",      18, 18, {{0, "disabled"}, {1, "enabled"}}},
            {"API",       17, 17, {{0, "trap"}, {1, "none"}}},
            {"APK",       16, 16, {{0, "trap"}, {1, "none"}}},
            {"TERR",      15, 15, {{0, "none"}, {1, "trap"}}},
            {"TLOR",      14, 14, {{0, "none"}, {1, "trap"}}},
            {"TWE",       13, 13, {{0, "none"}, {1, "trap"}}},
            {"TWI",       12, 12, {{0, "none"}, {1, "trap"}}},
            {"ST",        11, 11, {{0, "trap"}, {1, "none"}}},
            {"RW",        10, 10, {{0, "aarch32"}, {1, "aarch64"}}},
            {"SIF",        9,  9, {{0, "permitted"}, {1, "not permitted"}}},
            {"HCE",        8,  8, {{0, "undefined"}, {1, "enabled"}}},
            {"SMD",        7,  7, {{0, "enabled"}, {1, "undefined"}}},
            {"EA",         3,  3, {{0, "none"}, {1, "el3"}}},
            {"FIQ",        2,  2, {{0, "none"}, {1, "el3"}}},
            {"IRQ",        1,  1, {{0, "none"}, {1, "el3"}}},
            {"NS",         0,  0, {}},
        }
    },
    {
        "SCTLR_EL1", "D17.2.118", CSR_REGID_SCTLR, READ | WRITE,
        {
            {"TIDCP",     63, 63, {{0, "none"}, {1, "trap EL0 access to system registers"}}},
            {"SPINTMASK", 62, 62, {{0, "none"}, {1, "SPINTMASK"}}},
            {"NMI",       61, 61, {{0, "none"}, {1, "NMI"}}},
            {"EnTP2",     60, 60, {{0, "none"}, {1, "EnTP2"}}},
            {"EPAN",      57, 57, {{0, "none"}, {1, "EPAN"}}},
            {"EnALS",     56, 56, {{0, "none"}, {1, "EnALS"}}},
            {"EnAS0",     55, 55, {{0, "none"}, {1, "EnAS0"}}},
            {"EnASR",     54, 54, {{0, "none"}, {1, "EnASR"}}},
            {"TME",       53, 53, {{0, "none"}, {1, "TME"}}},
            {"TME0",      52, 52, {{0, "none"}, {1, "TME0"}}},
            {"TMT",       51, 51, {{0, "none"}, {1, "TMT"}}},
            {"TMT0",      50, 50, {{0, "none"}, {1, "TMT0"}}},
            {"TWEDEL",    49, 46, {{0, "none"}, {1, "TWEDEL"}}},
            {"TWEDEn",    45, 45, {{0, "none"}, {1, "TWEDEn"}}},
            {"DSSBS",     44, 44, {{0, "none"}, {1, "DSSBS"}}},
            {"ATA",       43, 43, {{0, "none"}, {1, "ATA"}}},
            {"ATA0",      42, 42, {{0, "none"}, {1, "ATA0"}}},
            {"TCF",       41, 40, {{0, "none"}, {1, "TCF"}}},
            {"TCF0",      39, 38, {{0, "none"}, {1, "TCF0"}}},
            {"ITFSB",     37, 37, {{0, "none"}, {1, "ITFSB"}}},
            {"BT1",       36, 36, {{0, "BTI at EL1: PACIxSP is compatible with BTYPE:11"},
                                   {1, "BTI at EL1: PACIxSP NOT compatible with BTYPE:11"}}},
            {"BT0",       35, 35, {{0, "BTI at EL0: PACIxSP is compatible with BTYPE:11"},
                                   {1, "BTI at EL0: PACIxSP NOT compatible with BTYPE:11"}}},
            {"MSCEn",     33, 33, {{0, "none"}, {1, "MSCEn"}}},
            {"CMOW",      32, 32, {{0, "none"}, {1, "CMOW"}}},
            {"EnIA",      31, 31, {{0, "PACIA key NOT enabled"}, {1, "PACIA key enabled"}}},
            {"EnIB",      30, 30, {{0, "PACIB key NOT enabled"}, {1, "PACIB key enabled"}}},
            {"LSMAOE",    29, 29, {{0, "none"}, {1, "LSMAOE"}}},
            {"nTLSMD",    28, 28, {{0, "none"}, {1, "nTLSMD"}}},
            {"EnDA",      27, 27, {{0, "PACDA key NOT enabled"}, {1, "PACDA key enabled"}}},
            {"UCI",       26, 26, {{0, "none"}, {1, "UCI"}}},
            {"EE",        25, 25, {{0, "TT EL1 is little endian"}, {1, "TT EL1 is big endian"}}},
            {"E0E",       24, 24, {{0, "EL0 data access is little endian"}, {1, "EL0 data access is big endian"}}},
            {"SPAN",      23, 23, {{0, "none"}, {1, "SPAN"}}},
            {"EIS",       22, 22, {{0, "none"}, {1, "EIS"}}},
            {"IESB",      21, 21, {{0, "none"}, {1, "IESB"}}},
            {"TSCTX",     20, 20, {{0, "none"}, {1, "TSCTX"}}},
            {"WXN",       19, 19, {{0, "none"}, {1, "WXN"}}},
            {"nTWE",      18, 18, {{0, "none"}, {1, "nTWE"}}},
            {"nTWI",      16, 16, {{0, "none"}, {1, "nTWI"}}},
            {"UCT",       15, 15, {{0, "none"}, {1, "UCT"}}},
            {"DZE",       14, 14, {{0, "none"}, {1, "DZE"}}},
            {"EnDB",      13, 13, {{0, "PACDB key NOT enabled"}, {1, "PACDB key enabled"}}},
            {"I",         12, 12, {{0, "none"}, {1, "I"}}},
            {"EOS",       11, 11, {{0, "none"}, {1, "EOS"}}},
            {"EnRCTX",    10, 10, {{0, "none"}, {1, "EnRCTX"}}},
            {"UMA",        9,  9, {{0, "none"}, {1, "UMA"}}},
            {"SED",        8,  8, {{0, "none"}, {1, "SED"}}},
            {"ITD",        7,  7, {{0, "none"}, {1, "ITD"}}},
            {"nAA",        6,  6, {{0, "none"}, {1, "nAA"}}},
            {"CP15BEN",    5,  5, {{0, "none"}, {1, "CP15BEN"}}},
            {"SA0",        4,  4, {{0, "none"}, {1, "SA0"}}},
            {"SA",         3,  3, {{0, "none"}, {1, "SA"}}},
            {"C",          2,  2, {{0, "none"}, {1, "C"}}},
            {"A",          1,  1, {{0, "none"}, {1, "A"}}},
            {"M",          0,  0, {{0, "none"}, {1, "M"}}},
        }
    },
    {
        "SCXTNUM_EL0", "D17.2.121", CSR_REGID_SCXTNUM_EL0, READ | WRITE | NEED_CSV2_2, {}
    },
    {
        "SCXTNUM_EL1", "D17.2.122", CSR_REGID_SCXTNUM_EL1, READ | WRITE | NEED_CSV2_2, {}
    },
    {
        "TCR_EL1", "D17.2.131", CSR_REGID_TCR, READ,
        {
            {"MTX1",   61, 61, {{0, "none"}, {1, "logical address tag"}}},
            {"MTX0",   60, 60, {{0, "none"}, {1, "logical address tag"}}},
            {"DS",     59, 59, {{0, "48-bit addresses"}, {1, "52-bit addresses"}}},
            {"TCMA1",  58, 58, {{0, "none"}, {1, "unchecked"}}},
            {"TCMA0",  57, 57, {{0, "none"}, {1, "unchecked"}}},
            {"E0PD1",  56, 56, {{0, "none"}, {1, "fault"}}},
            {"E0PD0",  55, 55, {{0, "none"}, {1, "fault"}}},
            {"NFD1",   54, 54, {{0, "none"}, {1, "stage 1 disabled"}}},
            {"NFD0",   53, 53, {{0, "none"}, {1, "stage 1 disabled"}}},
            {"TBID1",  52, 52, {{0, "instr+data"}, {1, "data"}}},
            {"TBID0",  51, 51, {{0, "instr+data"}, {1, "data"}}},
            {"HWU162", 50, 50, {{0, "bit62-reserved"}, {1, "bit62-impl-def"}}},
            {"HWU161", 49, 49, {{0, "bit61-reserved"}, {1, "bit61-impl-def"}}},
            {"HWU160", 48, 48, {{0, "bit60-reserved"}, {1, "bit60-impl-def"}}},
            {"HWU159", 47, 47, {{0, "bit59-reserved"}, {1, "bit59-impl-def"}}},
            {"HWU062", 46, 46, {{0, "bit62-reserved"}, {1, "bit62-impl-def"}}},
            {"HWU061", 45, 45, {{0, "bit61-reserved"}, {1, "bit61-impl-def"}}},
            {"HWU060", 44, 44, {{0, "bit60-reserved"}, {1, "bit60-impl-def"}}},
            {"HWU059", 43, 43, {{0, "bit59-reserved"}, {1, "bit59-impl-def"}}},
            {"HPD1",   42, 42, {{0, "enabled"}, {1, "disabled"}}},
            {"HPD0",   41, 41, {{0, "enabled"}, {1, "disabled"}}},
            {"HD",     40, 40, {{0, "disabled"}, {1, "enabled"}}},
            {"HA",     39, 39, {{0, "disabled"}, {1, "enabled"}}},
            {"TBI1",   38, 38, {{0, "used"}, {1, "ignored"}}},
            {"TBI0",   37, 37, {{0, "used"}, {1, "ignored"}}},
            {"AS",     36, 36, {{0, "ignored"}, {1, "used"}}},
            {"IPS",    34, 32, {{0, "32 bits, 4GB"}, {1, "36 bits, 64 GB"}, {2, "40 bits, 1 TB"}, {3, "42 bits, 4 TB"},
                                {4, "44 bits, 16 TB"}, {5, "48 bits, 256 TB"}, {6, "52 bits, 4 PB"}}},
            {"TG1",    31, 30, {{1, "16 kB"}, {2, "4 kB"}, {3, "64 kB"}}},
            {"SH1",    29, 28, {{0, "Non shareable"}, {2, "Outer shareable"}, {3, "Inner shareable"}}},
            {"ORGN1",  27, 26, {{0, "Normal memory, Outer Non-cacheable"},
                                {1, "Normal memory, Outer Write-Back Read-Allocate Write-Allocate Cacheable"},
                                {2, "Normal memory, Outer Write-Through Read-Allocate No Write-Allocate Cacheable"},
                                {3, "Normal memory, Outer Write-Back Read-Allocate No Write-Allocate Cacheable"}}},
            {"IRGN1",  25, 24, {{0, "Normal memory, Inner Non-cacheable"},
                                {1, "Normal memory, Inner Write-Back Read-Allocate Write-Allocate Cacheable"},
                                {2, "Normal memory, Inner Write-Through Read-Allocate No Write-Allocate Cacheable"},
                                {3, "Normal memory, Inner Write-Back Read-Allocate No Write-Allocate Cacheable"}}},
            {"EPD1",   23, 23, {{0, "Translation table walks using TTBR1_EL1"},
                                {1, "TLB miss using TTBR1_EL1 generates a Translation fault"}}},
            {"A1",     22, 22, {{0, "TTBR0_EL1.ASID defines the ASID"},
                                {1, "TTBR1_EL1.ASID defines the ASID"}}},
            {"T1SZ",   21, 16, {}},
            {"TG0",    15, 14, {{0, "4 kB"}, {1, "64 kB"}, {2, "16 kB"}}},
            {"SH0",    13, 12, {{0, "Non shareable"}, {2, "Outer shareable"}, {3, "Inner shareable"}}},
            {"ORGN0",  11, 10, {{0, "Normal memory, Outer Non-cacheable"},
                                {1, "Normal memory, Outer Write-Back Read-Allocate Write-Allocate Cacheable"},
                                {2, "Normal memory, Outer Write-Through Read-Allocate No Write-Allocate Cacheable"},
                                {3, "Normal memory, Outer Write-Back Read-Allocate No Write-Allocate Cacheable"}}},
            {"IRGN0",   9,  8, {{0, "Normal memory, Inner Non-cacheable"},
                                {1, "Normal memory, Inner Write-Back Read-Allocate Write-Allocate Cacheable"},
                                {2, "Normal memory, Inner Write-Through Read-Allocate No Write-Allocate Cacheable"},
                                {3, "Normal memory, Inner Write-Back Read-Allocate No Write-Allocate Cacheable"}}},
            {"EPD0",    7,  7, {{0, "Translation table walks using TTBR0_EL1"},
                                {1, "TLB miss using TTBR0_EL1 generates a Translation fault"}}},
            {"T0SZ",    5,  0, {}},
        }
    },
    {
        "TCR2_EL1", "N/A", CSR_REGID_TCR2, READ | NEED_TCR2,
        {
            {"DisCH1", 15, 15, {}},
            {"DisCH0", 14, 14, {}},
            {"HAFT",   11, 11, {}},
            {"PTTWI",  10, 10, {}},
            {"D128",    5,  5, {}},
            {"AIE",     4,  4, {}},
            {"POE",     3,  3, {}},
            {"E0POE",   2,  2, {}},
            {"PIE",     1,  1, {}},
            {"PnCH",    0,  0, {}},
        }
    },
    {
        "TPIDRRO_EL0", "D17.2.143", CSR_REGID_TPIDRRO_EL0, READ | WRITE, {}
    },
    {
        "TPIDR_EL0", "D17.2.139", CSR_REGID_TPIDR_EL0, READ | WRITE, {}
    },
    {
        "TPIDR_EL1", "D17.2.140", CSR_REGID_TPIDR_EL1, READ | WRITE, {}
    },
    {
        "TTBR0_EL1", "D17.2.144", CSR_REGID_TTBR0_EL1, READ,
        {
            {"ASID",  63, 48, {}},
            {"BADDR", 47,  1, {}},
            {"CnP",    0,  0, {{0, "differ"}, {1, "common"}}},
        }
    },
    {
        "TTBR1_EL1", "D17.2.147", CSR_REGID_TTBR1_EL1, READ,
        {
            {"ASID",  63, 48, {}},
            {"BADDR", 47,  1, {}},
            {"CnP",    0,  0, {{0, "differ"}, {1, "common"}}},
        }
    },
    {
        "TRCDEVARCH", "D17.4.23", CSR_REGID_TRCDEVARCH, READ | NEED_ETE,
        {
            {"ARCHITECT", 31, 21, {}},
            {"PRESENT",   20, 20, {{0, "not present"}, {1, "present"}}},
            {"REVISION",  19, 16, {{0, "ETEv1.0"}, {1, "ETEv1.1"}, {2, "ETEv1.2"}}},
            {"ARCHVER",   15, 12, {{5, "ETEv1"}}},
            {"ARCHPART",  11,  0, {{0xA13, "Arm PE trace architecture"}}},
        }
    },
    {
        "PMMIR_EL1", "D17.5.12", CSR_REGID_PMMIR, READ | NEED_PMUv3p4,
        {
            {"THWIDTH",   23, 20, {}},
            {"BUS_WIDTH", 19, 16, {}},
            {"BUS_SLOTS", 15,  8, {}},
            {"SLOTS",      7,  0, {}},
        }
    },
};


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


//----------------------------------------------------------------------------
// Format an hexa value of the register.
//----------------------------------------------------------------------------

std::string RegView::Register::hexa(csr_u64_t value) const
{
    return ToHexa(value);
}

std::string RegView::Register::hexa(const csr_pair_t& value) const
{
    return isPair() ? ToHexa(value) : ToHexa(value.low);
}


//----------------------------------------------------------------------------
// Display a detailed descriptions of one register value.
//----------------------------------------------------------------------------

void RegView::Register::display(std::ostream& out, csr_u64_t value) const
{
    csr_pair_t pair;
    pair.high = 0;
    pair.low = value;
    display(out, pair);
}

void RegView::Register::display(std::ostream& out, const csr_pair_t& value) const
{
    // Print the register content as a suite of 4-bit binary values.
    out << name << ": ";
    if (isPair()) {
        out << ToBinary(value.high) << std::endl << std::string(name.length() + 2, ' ');
    }
    out << ToBinary(value.low) << std::endl << std::endl;
    out << "  Arch. Ref. Manual section " << section << std::endl;

    // Print the details of the register content.
    if (fields.empty()) {
        // No bitfield defined, just display the value in hexadecimal.
        out << "  Value: " << hexa(value) << std::endl;
    }
    else {
        // Print the various bit fields.
        size_t name_width = 0;
        for (const auto& bf : fields) {
            name_width = std::max(name_width, bf.name.length());
        }
        for (const auto& bf : fields) {
            // Value of the bitfield.
            const csr_u64_t bfval = bf.lsb >= 64 ?
                ((value.high << (127 - bf.msb)) >> (63 - bf.msb + bf.lsb)) :
                ((value.low << (63 - bf.msb)) >> (63 - bf.msb + bf.lsb));
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
            out << "  " << Pad(bf.name + ":", name_width + 1, ' ')
                << " " << Format("0x%0*llX", hexwidth, bfval) << " (" << name << ")" << std::endl;
        }
    }
}


//----------------------------------------------------------------------------
// Check if the register is supported on this CPU.
//----------------------------------------------------------------------------

bool RegView::Register::canRead(RegAccess& ra) const
{
    return (features & RegView::READ) && isSupported(ra);
}

bool RegView::Register::canWrite(RegAccess& ra) const
{
    return (features & RegView::WRITE) && isSupported(ra);
}
