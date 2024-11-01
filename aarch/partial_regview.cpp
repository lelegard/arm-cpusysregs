    {
        "ID_AA64ISAR0_EL1", CSR_REGID_ID_AA64ISAR0_EL1, READ,
        {
            {"RNDR",   63, 60, {}},
            {"TLB",    59, 56, {}},
            {"TS",     55, 52, {}},
            {"FHM",    51, 48, {}},
            {"DP",     47, 44, {}},
            {"SM4",    43, 40, {}},
            {"SM3",    39, 36, {}},
            {"SHA3",   35, 32, {}},
            {"RDM",    31, 28, {}},
            {"TME",    27, 24, {}},
            {"Atomic", 23, 20, {}},
            {"CRC32",  19, 16, {}},
            {"SHA2",   15, 12, {}},
            {"SHA1",   11,  8, {}},
            {"AES",     7,  4, {}},
        }
    },
    {
        "ID_AA64ISAR1_EL1", CSR_REGID_ID_AA64ISAR1_EL1, READ,
        {
            {"LS64",    63, 60, {}},
            {"XS",      59, 56, {}},
            {"I8MM",    55, 52, {}},
            {"DGH",     51, 48, {}},
            {"BF16",    47, 44, {}},
            {"SPECRES", 43, 40, {}},
            {"SB",      39, 36, {}},
            {"FRINTTS", 35, 32, {}},
            {"GPI",     31, 28, {}},
            {"GPA",     27, 24, {}},
            {"LRCPC",   23, 20, {}},
            {"FCMA",    19, 16, {}},
            {"JSCVT",   15, 12, {}},
            {"API",     11,  8, {}},
            {"APA",      7,  4, {}},
            {"DPB",      3,  0, {}},
        }
    },
    {
        "ID_AA64ISAR2_EL1", CSR_REGID_ID_AA64ISAR2_EL1, READ,
        {
            {"ATS1A",        63, 60, {}},
            {"LUT",          59, 56, {}},
            {"CSSC",         55, 52, {}},
            {"RPRFM",        51, 48, {}},
            {"PCDPHINT",     47, 44, {}},
            {"PRFMSLC",      43, 40, {}},
            {"SYSINSTR_128", 39, 36, {}},
            {"SYSREG_128",   35, 32, {}},
            {"CLRBHB",       31, 28, {}},
            {"PAC_frac",     27, 24, {}},
            {"BC",           23, 20, {}},
            {"MOPS",         19, 16, {}},
            {"APA3",         15, 12, {}},
            {"GPA3",         11,  8, {}},
            {"RPRES",         7,  4, {}},
            {"WFxT",          3,  0, {}},
        }
    },
    {
        "ID_AA64ISAR3_EL1", CSR_REGID_ID_AA64ISAR3_EL1, READ,
        {
            {"FPRCVT",   31, 28, {}},
            {"LSUI",     27, 24, {}},
            {"OCCMO",    23, 20, {}},
            {"LSFE",     19, 16, {}},
            {"PACM",     15, 12, {}},
            {"TLBIW",    11,  8, {}},
            {"FAMINMAX",  7,  4, {}},
            {"CPA",       3,  0, {}},
        }
    },
    {
        "ID_AA64PFR0_EL1", CSR_REGID_ID_AA64PFR0_EL1, READ,
        {
            {"CSV3",    63, 60, {}},
            {"CSV2",    59, 56, {}},
            {"RME",     55, 52, {}},
            {"DIT",     51, 48, {}},
            {"AMU",     47, 44, {}},
            {"MPAM",    43, 40, {}},
            {"SEL2",    39, 36, {}},
            {"SVE",     35, 32, {}},
            {"RAS",     31, 28, {}},
            {"GIC",     27, 24, {}},
            {"AdvSIMD", 23, 20, {}},
            {"FP",      19, 16, {}},
            {"EL3",     15, 12, {}},
            {"EL2",     11,  8, {}},
            {"EL1",      7,  4, {}},
            {"EL0",      3,  0, {}},
        }
    },
    {
        "ID_AA64PFR1_EL1", CSR_REGID_ID_AA64PFR1_EL1, READ,
        {
            {"PFAR",      63, 60, {}},
            {"DF2",       59, 56, {}},
            {"MTEX",      55, 52, {}},
            {"THE",       51, 48, {}},
            {"GCS",       47, 44, {}},
            {"MTE_frac",  43, 40, {}},
            {"NMI",       39, 36, {}},
            {"CSV2_frac", 35, 32, {}},
            {"RNDR_trap", 31, 28, {}},
            {"SME",       27, 24, {}},
            {"MPAM_frac", 19, 16, {}},
            {"RAS_frac",  15, 12, {}},
            {"MTE",       11,  8, {}},
            {"SSBS",       7,  4, {}},
            {"BT",         3,  0, {}},
        }
    },
    {
        "ID_AA64PFR2_EL1", CSR_REGID_ID_AA64PFR2_EL1, READ,
        {
            {"FPMR",         35, 32, {}},
            {"UINJ",         19, 16, {}},
            {"MTEFAR",       11,  8, {}},
            {"MTESTOREONLY",  7,  4, {}},
            {"MTEPERM",       3,  0, {}},
        }
    },
    {
        "ID_AA64DFR0_EL1", CSR_REGID_ID_AA64DFR0_EL1, READ,
        {
            {"HPMN0",       63, 60, {}},
            {"ExtTrcBuff",  59, 56, {}},
            {"BRBE",        55, 52, {}},
            {"MTPMU",       51, 48, {}},
            {"TraceBuffer", 47, 44, {}},
            {"TraceFilt",   43, 40, {}},
            {"DoubleLock",  39, 36, {}},
            {"PMSVer",      35, 32, {}},
            {"CTX_CMPs",    31, 28, {}},
            {"SEBEP",       27, 24, {}},
            {"WRPs",        23, 20, {}},
            {"PMSS",        19, 16, {}},
            {"BRPs",        15, 12, {}},
            {"PMUVer",      11,  8, {}},
            {"TraceVer",     7,  4, {}},
            {"DebugVer",     3,  0, {}},
        }
    },
    {
        "ID_AA64DFR1_EL1", CSR_REGID_ID_AA64DFR1_EL1, READ,
        {
            {"ABL_CMPs", 63, 56, {}},
            {"DPFZS",    55, 52, {}},
            {"EBEP",     51, 48, {}},
            {"ITE",      47, 44, {}},
            {"ABLE",     43, 40, {}},
            {"PMICNTR",  39, 36, {}},
            {"SPMU",     35, 32, {}},
            {"CTX_CMPs", 31, 24, {}},
            {"WRPs",     23, 16, {}},
            {"BRPs",     15,  8, {}},
            {"SYSPMUID",  7,  0, {}},
        }
    },
    {
        "ID_AA64DFR2_EL1", CSR_REGID_ID_AA64DFR2_EL1, READ,
        {
            {"TRBE_EXC", 27, 24, {}},
            {"SPE_nVM",  23, 20, {}},
            {"SPE_EXC",  19, 16, {}},
            {"BWE",       7,  4, {}},
            {"STEP",      3,  0, {}},
        }
    },
    {
        "ID_AA64FPFR0_EL1", CSR_REGID_ID_AA64FPFR0_EL1, READ,
        {
            {"F8CVT",  31, 31, {}},
            {"F8FMA",  30, 30, {}},
            {"F8DP4",  29, 29, {}},
            {"F8DP2",  28, 28, {}},
            {"F8MM8",  27, 27, {}},
            {"F8MM4",  26, 26, {}},
            {"F8E4M3",  1,  1, {}},
            {"F8E5M2",  0,  0, {}},
        }
    },
    {
        "ID_AA64MMFR0_EL1", CSR_REGID_ID_AA64MMFR0_EL1, READ,
        {
            {"ECV",       63, 60, {}},
            {"FGT",       59, 56, {}},
            {"ExS",       47, 44, {}},
            {"TGran4_2",  43, 40, {}},
            {"TGran64_2", 39, 36, {}},
            {"TGran16_2", 35, 32, {}},
            {"TGran4",    31, 28, {}},
            {"TGran64",   27, 24, {}},
            {"TGran16",   23, 20, {}},
            {"BigEndEL0", 19, 16, {}},
            {"SNSMem",    15, 12, {}},
            {"BigEnd",    11,  8, {}},
            {"ASIDBits",   7,  4, {}},
            {"PARange",    3,  0, {}},
        }
    },
    {
        "ID_AA64MMFR1_EL1", CSR_REGID_ID_AA64MMFR1_EL1, READ,
        {
            {"ECBHB",    63, 60, {}},
            {"CMOW",     59, 56, {}},
            {"TIDCP1",   55, 52, {}},
            {"nTLBPA",   51, 48, {}},
            {"AFP",      47, 44, {}},
            {"HCX",      43, 40, {}},
            {"ETS",      39, 36, {}},
            {"TWED",     35, 32, {}},
            {"XNX",      31, 28, {}},
            {"SpecSEI",  27, 24, {}},
            {"PAN",      23, 20, {}},
            {"LO",       19, 16, {}},
            {"HPDS",     15, 12, {}},
            {"VH",       11,  8, {}},
            {"VMIDBits",  7,  4, {}},
            {"HAFDBS",    3,  0, {}},
        }
    },
    {
        "ID_AA64MMFR2_EL1", CSR_REGID_ID_AA64MMFR2_EL1, READ,
        {
            {"E0PD",    63, 60, {}},
            {"EVT",     59, 56, {}},
            {"BBM",     55, 52, {}},
            {"TTL",     51, 48, {}},
            {"FWB",     43, 40, {}},
            {"IDS",     39, 36, {}},
            {"AT",      35, 32, {}},
            {"ST",      31, 28, {}},
            {"NV",      27, 24, {}},
            {"CCIDX",   23, 20, {}},
            {"VARange", 19, 16, {}},
            {"IESB",    15, 12, {}},
            {"LSM",     11,  8, {}},
            {"UAO",      7,  4, {}},
            {"CnP",      3,  0, {}},
        }
    },
    {
        "ID_AA64MMFR3_EL1", CSR_REGID_ID_AA64MMFR3_EL1, READ,
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
        "ID_AA64MMFR4_EL1", CSR_REGID_ID_AA64MMFR4_EL1, READ,
        {
            {"SRMASK",  47, 44, {}},
            {"E3DSE",   39, 36, {}},
            {"RMEGDI",  31, 28, {}},
            {"E2H0",    27, 24, {}},
            {"NV_frac", 23, 20, {}},
            {"FGWTE3",  19, 16, {}},
            {"HACDBS",  15, 12, {}},
            {"ASID2",   11,  8, {}},
            {"EIESB",    7,  4, {}},
            {"PoPS",     3,  0, {}},
        }
    },
    {
        "ID_AA64SMFR0_EL1", CSR_REGID_ID_AA64SMFR0_EL1, READ,
        {
            {"FA64",     63, 63, {}},
            {"LUTv2",    60, 60, {}},
            {"SMEver",   59, 56, {}},
            {"I16I64",   55, 52, {}},
            {"F64F64",   48, 48, {}},
            {"I16I32",   47, 44, {}},
            {"B16B16",   43, 43, {}},
            {"F16F16",   42, 42, {}},
            {"F8F16",    41, 41, {}},
            {"F8F32",    40, 40, {}},
            {"I8I32",    39, 36, {}},
            {"F16F32",   35, 35, {}},
            {"B16F32",   34, 34, {}},
            {"BI32I32",  33, 33, {}},
            {"F32F32",   32, 32, {}},
            {"SF8FMA",   30, 30, {}},
            {"SF8DP4",   29, 29, {}},
            {"SF8DP2",   28, 28, {}},
            {"SF8MM8",   27, 27, {}},
            {"SF8MM4",   26, 26, {}},
            {"SBitPerm", 25, 25, {}},
            {"AES",      24, 24, {}},
            {"SFEXPA",   23, 23, {}},
            {"STMOP",    16, 16, {}},
            {"SMOP4",     0,  0, {}},
        }
    },
    {
        "ID_AA64ZFR0_EL1", CSR_REGID_ID_AA64ZFR0_EL1, READ,
        {
            {"F64MM",   59, 56, {}},
            {"F32MM",   55, 52, {}},
            {"F16MM",   51, 48, {}},
            {"I8MM",    47, 44, {}},
            {"SM4",     43, 40, {}},
            {"SHA3",    35, 32, {}},
            {"B16B16",  27, 24, {}},
            {"BF16",    23, 20, {}},
            {"BitPerm", 19, 16, {}},
            {"EltPerm", 15, 12, {}},
            {"AES",      7,  4, {}},
            {"SVEver",   3,  0, {}},
        }
    },
    {
        "ID_ISAR0_EL1", CSR_REGID_ID_ISAR0_EL1, READ,
        {
            {"Divide",    27, 24, {}},
            {"Debug",     23, 20, {}},
            {"Coproc",    19, 16, {}},
            {"CmpBranch", 15, 12, {}},
            {"BitField",  11,  8, {}},
            {"BitCount",   7,  4, {}},
            {"Swap",       3,  0, {}},
        }
    },
    {
        "ID_ISAR1_EL1", CSR_REGID_ID_ISAR1_EL1, READ,
        {
            {"Jazelle",   31, 28, {}},
            {"Interwork", 27, 24, {}},
            {"Immediate", 23, 20, {}},
            {"IfThen",    19, 16, {}},
            {"Extend",    15, 12, {}},
            {"Except_AR", 11,  8, {}},
            {"Except",     7,  4, {}},
            {"Endian",     3,  0, {}},
        }
    },
    {
        "ID_ISAR2_EL1", CSR_REGID_ID_ISAR2_EL1, READ,
        {
            {"Reversal",       31, 28, {}},
            {"PSR_AR",         27, 24, {}},
            {"MultU",          23, 20, {}},
            {"MultS",          19, 16, {}},
            {"Mult",           15, 12, {}},
            {"MultiAccessInt", 11,  8, {}},
            {"MemHint",         7,  4, {}},
            {"LoadStore",       3,  0, {}},
        }
    },
    {
        "ID_ISAR3_EL1", CSR_REGID_ID_ISAR3_EL1, READ,
        {
            {"T32EE",     31, 28, {}},
            {"TrueNOP",   27, 24, {}},
            {"T32Copy",   23, 20, {}},
            {"TabBranch", 19, 16, {}},
            {"SynchPrim", 15, 12, {}},
            {"SVC",       11,  8, {}},
            {"SIMD",       7,  4, {}},
            {"Saturate",   3,  0, {}},
        }
    },
    {
        "ID_ISAR4_EL1", CSR_REGID_ID_ISAR4_EL1, READ,
        {
            {"SWP_frac",       31, 28, {}},
            {"PSR_M",          27, 24, {}},
            {"SynchPrim_frac", 23, 20, {}},
            {"Barrier",        19, 16, {}},
            {"SMC",            15, 12, {}},
            {"Writeback",      11,  8, {}},
            {"WithShifts",      7,  4, {}},
            {"Unpriv",          3,  0, {}},
        }
    },
    {
        "ID_ISAR5_EL1", CSR_REGID_ID_ISAR5_EL1, READ,
        {
            {"VCMA",  31, 28, {}},
            {"RDM",   27, 24, {}},
            {"CRC32", 19, 16, {}},
            {"SHA2",  15, 12, {}},
            {"SHA1",  11,  8, {}},
            {"AES",    7,  4, {}},
            {"SEVL",   3,  0, {}},
        }
    },
    {
        "ID_ISAR6_EL1", CSR_REGID_ID_ISAR6_EL1, READ,
        {
            {"CLRBHB",  31, 28, {}},
            {"I8MM",    27, 24, {}},
            {"BF16",    23, 20, {}},
            {"SPECRES", 19, 16, {}},
            {"SB",      15, 12, {}},
            {"FHM",     11,  8, {}},
            {"DP",       7,  4, {}},
            {"JSCVT",    3,  0, {}},
        }
    },
    {
        "ID_MMFR0_EL1", CSR_REGID_ID_MMFR0_EL1, READ,
        {
            {"InnerShr", 31, 28, {}},
            {"FCSE",     27, 24, {}},
            {"AuxReg",   23, 20, {}},
            {"TCM",      19, 16, {}},
            {"ShareLvl", 15, 12, {}},
            {"OuterShr", 11,  8, {}},
            {"PMSA",      7,  4, {}},
            {"VMSA",      3,  0, {}},
        }
    },
    {
        "ID_MMFR1_EL1", CSR_REGID_ID_MMFR1_EL1, READ,
        {
            {"BPred",    31, 28, {}},
            {"L1TstCln", 27, 24, {}},
            {"L1Uni",    23, 20, {}},
            {"L1Hvd",    19, 16, {}},
            {"L1UniSW",  15, 12, {}},
            {"L1HvdSW",  11,  8, {}},
            {"L1UniVA",   7,  4, {}},
            {"L1HvdVA",   3,  0, {}},
        }
    },
    {
        "ID_MMFR2_EL1", CSR_REGID_ID_MMFR2_EL1, READ,
        {
            {"HWAccFlg", 31, 28, {}},
            {"WFIStall", 27, 24, {}},
            {"MemBarr",  23, 20, {}},
            {"UniTLB",   19, 16, {}},
            {"HvdTLB",   15, 12, {}},
            {"L1HvdRng", 11,  8, {}},
            {"L1HvdBG",   7,  4, {}},
            {"L1HvdFG",   3,  0, {}},
        }
    },
    {
        "ID_MMFR3_EL1", CSR_REGID_ID_MMFR3_EL1, READ,
        {
            {"Supersec",  31, 28, {}},
            {"CMemSz",    27, 24, {}},
            {"CohWalk",   23, 20, {}},
            {"PAN",       19, 16, {}},
            {"MaintBcst", 15, 12, {}},
            {"BPMaint",   11,  8, {}},
            {"CMaintSW",   7,  4, {}},
            {"CMaintVA",   3,  0, {}},
        }
    },
    {
        "ID_MMFR4_EL1", CSR_REGID_ID_MMFR4_EL1, READ,
        {
            {"EVT",     31, 28, {}},
            {"CCIDX",   27, 24, {}},
            {"LSM",     23, 20, {}},
            {"HPDS",    19, 16, {}},
            {"CnP",     15, 12, {}},
            {"XNX",     11,  8, {}},
            {"AC2",      7,  4, {}},
            {"SpecSEI",  3,  0, {}},
        }
    },
    {
        "ID_MMFR5_EL1", CSR_REGID_ID_MMFR5_EL1, READ,
        {
            {"nTLBPA",  7,  4, {}},
            {"ETS",     3,  0, {}},
        }
    },
    {
        "ID_PFR0_EL1", CSR_REGID_ID_PFR0_EL1, READ,
        {
            {"RAS",    31, 28, {}},
            {"DIT",    27, 24, {}},
            {"AMU",    23, 20, {}},
            {"CSV2",   19, 16, {}},
            {"State3", 15, 12, {}},
            {"State2", 11,  8, {}},
            {"State1",  7,  4, {}},
            {"State0",  3,  0, {}},
        }
    },
    {
        "ID_PFR1_EL1", CSR_REGID_ID_PFR1_EL1, READ,
        {
            {"GIC",            31, 28, {}},
            {"Virt_frac",      27, 24, {}},
            {"Sec_frac",       23, 20, {}},
            {"GenTimer",       19, 16, {}},
            {"Virtualization", 15, 12, {}},
            {"MProgMod",       11,  8, {}},
            {"Security",        7,  4, {}},
            {"ProgMod",         3,  0, {}},
        }
    },
    {
        "ID_PFR2_EL1", CSR_REGID_ID_PFR2_EL1, READ,
        {
            {"RAS_frac", 11,  8, {}},
            {"SSBS",      7,  4, {}},
            {"CSV3",      3,  0, {}},
        }
    },
    {
        "CTR_EL0", CSR_REGID_CTR_EL0, READ,
        {
            {"TminLine", 37, 32, {}},
            {"DIC",      29, 29, {}},
            {"IDC",      28, 28, {}},
            {"CWG",      27, 24, {}},
            {"ERG",      23, 20, {}},
            {"DminLine", 19, 16, {}},
            {"L1Ip",     15, 14, {}},
            {"IminLine",  3,  0, {}},
        }
    },
    {
        "TCR_EL1", CSR_REGID_TCR_EL1, READ,
        {
            {"MTX1",   61, 61, {}},
            {"MTX0",   60, 60, {}},
            {"DS",     59, 59, {}},
            {"TCMA1",  58, 58, {}},
            {"TCMA0",  57, 57, {}},
            {"E0PD1",  56, 56, {}},
            {"E0PD0",  55, 55, {}},
            {"NFD1",   54, 54, {}},
            {"NFD0",   53, 53, {}},
            {"TBID1",  52, 52, {}},
            {"TBID0",  51, 51, {}},
            {"HWU162", 50, 50, {}},
            {"HWU161", 49, 49, {}},
            {"HWU160", 48, 48, {}},
            {"HWU159", 47, 47, {}},
            {"HWU062", 46, 46, {}},
            {"HWU061", 45, 45, {}},
            {"HWU060", 44, 44, {}},
            {"HWU059", 43, 43, {}},
            {"HPD1",   42, 42, {}},
            {"HPD0",   41, 41, {}},
            {"HD",     40, 40, {}},
            {"HA",     39, 39, {}},
            {"TBI1",   38, 38, {}},
            {"TBI0",   37, 37, {}},
            {"AS",     36, 36, {}},
            {"IPS",    34, 32, {}},
            {"TG1",    31, 30, {}},
            {"SH1",    29, 28, {}},
            {"ORGN1",  27, 26, {}},
            {"IRGN1",  25, 24, {}},
            {"EPD1",   23, 23, {}},
            {"A1",     22, 22, {}},
            {"T1SZ",   21, 16, {}},
            {"TG0",    15, 14, {}},
            {"SH0",    13, 12, {}},
            {"ORGN0",  11, 10, {}},
            {"IRGN0",   9,  8, {}},
            {"EPD0",    7,  7, {}},
            {"T0SZ",    5,  0, {}},
        }
    },
    {
        "TCR2_EL1", CSR_REGID_TCR2_EL1, READ,
        {
            {"FNGNA1", 21, 21, {}},
            {"FNGNA0", 20, 20, {}},
            {"FNG1",   18, 18, {}},
            {"FNG0",   17, 17, {}},
            {"A2",     16, 16, {}},
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
        "TRCDEVARCH", CSR_REGID_TRCDEVARCH, READ,
        {
            {"ARCHITECT", 31, 21, {}},
            {"PRESENT",   20, 20, {}},
            {"REVISION",  19, 16, {}},
            {"ARCHVER",   15, 12, {}},
            {"ARCHPART",  11,  0, {}},
        }
    },
    {
        "PMMIR_EL1", CSR_REGID_PMMIR_EL1, READ,
        {
            {"SME",       28, 28, {}},
            {"EDGE",      27, 24, {}},
            {"THWIDTH",   23, 20, {}},
            {"BUS_WIDTH", 19, 16, {}},
            {"BUS_SLOTS", 15,  8, {}},
            {"SLOTS",      7,  0, {}},
        }
    },
    {
        "PMSIDR_EL1", CSR_REGID_PMSIDR_EL1, READ,
        {
            {"SME",       32, 32, {}},
            {"ALTCLK",    31, 28, {}},
            {"FPF",       27, 27, {}},
            {"EFT",       26, 26, {}},
            {"CRR",       25, 25, {}},
            {"PBT",       24, 24, {}},
            {"Format",    23, 20, {}},
            {"CountSize", 19, 16, {}},
            {"MaxSize",   15, 12, {}},
            {"Interval",  11,  8, {}},
            {"FDS",        7,  7, {}},
            {"FnE",        6,  6, {}},
            {"ERnd",       5,  5, {}},
            {"LDS",        4,  4, {}},
            {"ArchInst",   3,  3, {}},
            {"FL",         2,  2, {}},
            {"FT",         1,  1, {}},
            {"FE",         0,  0, {}},
        }
    },
    {
        "MPAMIDR_EL1", CSR_REGID_MPAMIDR_EL1, READ,
        {
            {"HAS_SDEFLT",   61, 61, {}},
            {"HAS_FORCE_NS", 60, 60, {}},
            {"SP4",          59, 59, {}},
            {"HAS_TIDR",     58, 58, {}},
            {"HAS_ALTSP",    57, 57, {}},
            {"HAS_BW_CTRL",  56, 56, {}},
            {"PMG_MAX",      39, 32, {}},
            {"VPMR_MAX",     20, 18, {}},
            {"HAS_HCR",      17, 17, {}},
            {"PARTID_MAX",   15,  0, {}},
        }
    },
    {
        "TRBIDR_EL1", CSR_REGID_TRBIDR_EL1, READ,
        {
            {"MaxBuffSize", 47, 32, {}},
            {"MPAM",        15, 12, {}},
            {"EA",          11,  8, {}},
            {"AddrMode",     7,  6, {}},
            {"F",            5,  5, {}},
            {"P",            4,  4, {}},
            {"Align",        3,  0, {}},
        }
    },
    {
        "MIDR_EL1", CSR_REGID_MIDR_EL1, READ,
        {
            {"Implementer",  31, 24, {}},
            {"Variant",      23, 20, {}},
            {"Architecture", 19, 16, {}},
            {"PartNum",      15,  4, {}},
            {"Revision",      3,  0, {}},
        }
    },
    {
        "MPIDR_EL1", CSR_REGID_MPIDR_EL1, READ,
        {
            {"Aff3", 39, 32, {}},
            {"U",    30, 30, {}},
            {"MT",   24, 24, {}},
            {"Aff2", 23, 16, {}},
            {"Aff1", 15,  8, {}},
            {"Aff0",  7,  0, {}},
        }
    },
    {
        "REVIDR_EL1", CSR_REGID_REVIDR_EL1, READ,
        {
            {"IMPLEMENTATION DEFINED", 63,  0, {}},
        }
    },
    {
        "TPIDRRO_EL0", CSR_REGID_TPIDRRO_EL0, READ,
        {
            {"ThreadID", 63,  0, {}},
        }
    },
    {
        "TPIDR_EL0", CSR_REGID_TPIDR_EL0, READ,
        {
            {"ThreadID", 63,  0, {}},
        }
    },
    {
        "TPIDR_EL1", CSR_REGID_TPIDR_EL1, READ,
        {
            {"ThreadID", 63,  0, {}},
        }
    },
    {
        "SCXTNUM_EL0", CSR_REGID_SCXTNUM_EL0, READ,
        {
            {"SCXTNUM", 63,  0, {}},
        }
    },
    {
        "SCXTNUM_EL1", CSR_REGID_SCXTNUM_EL1, READ,
        {
            {"SCXTNUM", 63,  0, {}},
        }
    },
    {
        "SCTLR_EL1", CSR_REGID_SCTLR_EL1, READ,
        {
            {"TIDCP",     63, 63, {}},
            {"SPINTMASK", 62, 62, {}},
            {"NMI",       61, 61, {}},
            {"EnTP2",     60, 60, {}},
            {"TCSO",      59, 59, {}},
            {"TCSO0",     58, 58, {}},
            {"EPAN",      57, 57, {}},
            {"EnALS",     56, 56, {}},
            {"EnAS0",     55, 55, {}},
            {"EnASR",     54, 54, {}},
            {"TME",       53, 53, {}},
            {"TME0",      52, 52, {}},
            {"TMT",       51, 51, {}},
            {"TMT0",      50, 50, {}},
            {"TWEDEL",    49, 46, {}},
            {"TWEDEn",    45, 45, {}},
            {"DSSBS",     44, 44, {}},
            {"ATA",       43, 43, {}},
            {"ATA0",      42, 42, {}},
            {"TCF",       41, 40, {}},
            {"TCF0",      39, 38, {}},
            {"ITFSB",     37, 37, {}},
            {"BT1",       36, 36, {}},
            {"BT0",       35, 35, {}},
            {"EnFPM",     34, 34, {}},
            {"MSCEn",     33, 33, {}},
            {"CMOW",      32, 32, {}},
            {"EnIA",      31, 31, {}},
            {"EnIB",      30, 30, {}},
            {"LSMAOE",    29, 29, {}},
            {"nTLSMD",    28, 28, {}},
            {"EnDA",      27, 27, {}},
            {"UCI",       26, 26, {}},
            {"EE",        25, 25, {}},
            {"E0E",       24, 24, {}},
            {"SPAN",      23, 23, {}},
            {"EIS",       22, 22, {}},
            {"IESB",      21, 21, {}},
            {"TSCXT",     20, 20, {}},
            {"WXN",       19, 19, {}},
            {"nTWE",      18, 18, {}},
            {"nTWI",      16, 16, {}},
            {"UCT",       15, 15, {}},
            {"DZE",       14, 14, {}},
            {"EnDB",      13, 13, {}},
            {"I",         12, 12, {}},
            {"EOS",       11, 11, {}},
            {"EnRCTX",    10, 10, {}},
            {"UMA",        9,  9, {}},
            {"SED",        8,  8, {}},
            {"ITD",        7,  7, {}},
            {"nAA",        6,  6, {}},
            {"CP15BEN",    5,  5, {}},
            {"SA0",        4,  4, {}},
            {"SA",         3,  3, {}},
            {"C",          2,  2, {}},
            {"A",          1,  1, {}},
            {"M",          0,  0, {}},
        }
    },
    {
        "SCTLR2_EL1", CSR_REGID_SCTLR2_EL1, READ,
        {
            {"CPTM0",     12, 12, {}},
            {"CPTM",      11, 11, {}},
            {"CPTA0",     10, 10, {}},
            {"CPTA",       9,  9, {}},
            {"EnPACM0",    8,  8, {}},
            {"EnPACM",     7,  7, {}},
            {"EnIDCP128",  6,  6, {}},
            {"EASE",       5,  5, {}},
            {"EnANERR",    4,  4, {}},
            {"EnADERR",    3,  3, {}},
            {"NMEA",       2,  2, {}},
        }
    },
    {
        "HCR_EL2", CSR_REGID_HCR_EL2, READ,
        {
            {"TWEDEL",   63, 60, {}},
            {"TWEDEn",   59, 59, {}},
            {"TID5",     58, 58, {}},
            {"DCT",      57, 57, {}},
            {"ATA",      56, 56, {}},
            {"TTLBOS",   55, 55, {}},
            {"TTLBIS",   54, 54, {}},
            {"EnSCXT",   53, 53, {}},
            {"TOCU",     52, 52, {}},
            {"AMVOFFEN", 51, 51, {}},
            {"TICAB",    50, 50, {}},
            {"TID4",     49, 49, {}},
            {"GPF",      48, 48, {}},
            {"FIEN",     47, 47, {}},
            {"FWB",      46, 46, {}},
            {"NV2",      45, 45, {}},
            {"AT",       44, 44, {}},
            {"NV1",      43, 43, {}},
            {"NV",       42, 42, {}},
            {"API",      41, 41, {}},
            {"APK",      40, 40, {}},
            {"TME",      39, 39, {}},
            {"MIOCNCE",  38, 38, {}},
            {"TEA",      37, 37, {}},
            {"TERR",     36, 36, {}},
            {"TLOR",     35, 35, {}},
            {"E2H",      34, 34, {}},
            {"ID",       33, 33, {}},
            {"CD",       32, 32, {}},
            {"RW",       31, 31, {}},
            {"TRVM",     30, 30, {}},
            {"HCD",      29, 29, {}},
            {"TDZ",      28, 28, {}},
            {"TGE",      27, 27, {}},
            {"TVM",      26, 26, {}},
            {"TTLB",     25, 25, {}},
            {"TPU",      24, 24, {}},
            {"TPCP",     23, 23, {}},
            {"TPC",      23, 23, {}},
            {"TSW",      22, 22, {}},
            {"TACR",     21, 21, {}},
            {"TIDCP",    20, 20, {}},
            {"TSC",      19, 19, {}},
            {"TID3",     18, 18, {}},
            {"TID2",     17, 17, {}},
            {"TID1",     16, 16, {}},
            {"TID0",     15, 15, {}},
            {"TWE",      14, 14, {}},
            {"TWI",      13, 13, {}},
            {"DC",       12, 12, {}},
            {"BSU",      11, 10, {}},
            {"FB",        9,  9, {}},
            {"VSE",       8,  8, {}},
            {"VI",        7,  7, {}},
            {"VF",        6,  6, {}},
            {"AMO",       5,  5, {}},
            {"IMO",       4,  4, {}},
            {"FMO",       3,  3, {}},
            {"PTW",       2,  2, {}},
            {"SWIO",      1,  1, {}},
            {"VM",        0,  0, {}},
        }
    },
    {
        "RNDR", CSR_REGID_RNDR, READ,
        {
            {"RNDR", 63,  0, {}},
        }
    },
    {
        "RNDRRS", CSR_REGID_RNDRRS, READ,
        {
            {"RNDRRS", 63,  0, {}},
        }
    },
    {
        "SCR_EL3", CSR_REGID_SCR_EL3, READ,
        {
            {"NSE",       62, 62, {}},
            {"HACDBSEn",  61, 61, {}},
            {"HDBSSEn",   60, 60, {}},
            {"FGTEn2",    59, 59, {}},
            {"EnDSE",     58, 58, {}},
            {"DSE",       57, 57, {}},
            {"EnIDCP128", 55, 55, {}},
            {"SRMASKEn",  54, 54, {}},
            {"PFAREn",    53, 53, {}},
            {"TWERR",     52, 52, {}},
            {"TMEA",      51, 51, {}},
            {"EnFPM",     50, 50, {}},
            {"MECEn",     49, 49, {}},
            {"GPF",       48, 48, {}},
            {"D128En",    47, 47, {}},
            {"AIEn",      46, 46, {}},
            {"PIEn",      45, 45, {}},
            {"SCTLR2En",  44, 44, {}},
            {"TCR2En",    43, 43, {}},
            {"RCWMASKEn", 42, 42, {}},
            {"EnTP2",     41, 41, {}},
            {"TRNDR",     40, 40, {}},
            {"GCSEn",     39, 39, {}},
            {"HXEn",      38, 38, {}},
            {"ADEn",      37, 37, {}},
            {"EnAS0",     36, 36, {}},
            {"AMVOFFEN",  35, 35, {}},
            {"TME",       34, 34, {}},
            {"TWEDEL",    33, 30, {}},
            {"TWEDEn",    29, 29, {}},
            {"ECVEn",     28, 28, {}},
            {"FGTEn",     27, 27, {}},
            {"ATA",       26, 26, {}},
            {"EnSCXT",    25, 25, {}},
            {"TID5",      23, 23, {}},
            {"TID3",      22, 22, {}},
            {"FIEN",      21, 21, {}},
            {"NMEA",      20, 20, {}},
            {"EASE",      19, 19, {}},
            {"EEL2",      18, 18, {}},
            {"API",       17, 17, {}},
            {"APK",       16, 16, {}},
            {"TERR",      15, 15, {}},
            {"TLOR",      14, 14, {}},
            {"TWE",       13, 13, {}},
            {"TWI",       12, 12, {}},
            {"ST",        11, 11, {}},
            {"RW",        10, 10, {}},
            {"SIF",        9,  9, {}},
            {"HCE",        8,  8, {}},
            {"SMD",        7,  7, {}},
            {"EA",         3,  3, {}},
            {"FIQ",        2,  2, {}},
            {"IRQ",        1,  1, {}},
            {"NS",         0,  0, {}},
        }
    },
    {
        "ID_AA64AFR0_EL1", CSR_REGID_ID_AA64AFR0_EL1, READ,
        {
            {"IMPLEMENTATION DEFINED", 31, 28, {}},
        }
    },
    {
        "ID_AA64AFR1_EL1", CSR_REGID_ID_AA64AFR1_EL1, READ,
        {
        }
    },
    {
        "TTBR0_EL1", CSR_REGID_TTBR0_EL1, READ,
        {
            {"BADDR",       87, 80, {}},
            {"ASID",        63, 48, {}},
            {"BADDR[42:0]", 47,  5, {}},
            {"SKL",          2,  1, {}},
            {"CnP",          0,  0, {}},
        }
    },
    {
        "TTBR1_EL1", CSR_REGID_TTBR1_EL1, READ,
        {
            {"BADDR",       87, 80, {}},
            {"ASID",        63, 48, {}},
            {"BADDR[42:0]", 47,  5, {}},
            {"SKL",          2,  1, {}},
            {"CnP",          0,  0, {}},
        }
    },
    {
        "MAIR_EL1", CSR_REGID_MAIR_EL1, READ,
        {
            {"Attr<n>", 63,  0, {}},
        }
    },
    {
        "MAIR2_EL1", CSR_REGID_MAIR2_EL1, READ,
        {
            {"Attr<n>", 63,  0, {}},
        }
    },
    {
        "PIR_EL1", CSR_REGID_PIR_EL1, READ,
        {
            {"Perm<m>", 63,  0, {}},
        }
    },
    {
        "PIRE0_EL1", CSR_REGID_PIRE0_EL1, READ,
        {
            {"Perm<m>", 63,  0, {}},
        }
    },
    {
        "CNTKCTL_EL1", CSR_REGID_CNTKCTL_EL1, READ,
        {
            {"CNTPMASK", 19, 19, {}},
            {"CNTVMASK", 18, 18, {}},
            {"EVNTIS",   17, 17, {}},
            {"EL1NVVCT", 16, 16, {}},
            {"EL1NVPCT", 15, 15, {}},
            {"EL1TVCT",  14, 14, {}},
            {"EL1TVT",   13, 13, {}},
            {"ECV",      12, 12, {}},
            {"EL1PTEN",  11, 11, {}},
            {"EL1PCTEN", 10, 10, {}},
            {"EL0PTEN",   9,  9, {}},
            {"EL0VTEN",   8,  8, {}},
            {"EVNTI",     7,  4, {}},
            {"EVNTDIR",   3,  3, {}},
            {"EVNTEN",    2,  2, {}},
            {"EL0VCTEN",  1,  1, {}},
            {"EL0PCTEN",  0,  0, {}},
        }
    },
    {
        "CNTPS_CTL_EL1", CSR_REGID_CNTPS_CTL_EL1, READ,
        {
            {"ISTATUS",  2,  2, {}},
            {"IMASK",    1,  1, {}},
            {"ENABLE",   0,  0, {}},
        }
    },
    {
        "CNTFRQ_EL0", CSR_REGID_CNTFRQ_EL0, READ,
        {
            {"ClockFreq", 31,  0, {}},
        }
    },
    {
        "CNTPCT_EL0", CSR_REGID_CNTPCT_EL0, READ,
        {
            {"PhysicalCount", 63,  0, {}},
        }
    },
    {
        "CNTVCT_EL0", CSR_REGID_CNTVCT_EL0, READ,
        {
            {"VirtualCount", 63,  0, {}},
        }
    },
    {
        "PMCCFILTR_EL0", CSR_REGID_PMCCFILTR_EL0, READ,
        {
            {"VS",  57, 56, {}},
            {"P",   31, 31, {}},
            {"U",   30, 30, {}},
            {"NSK", 29, 29, {}},
            {"NSU", 28, 28, {}},
            {"NSH", 27, 27, {}},
            {"M",   26, 26, {}},
            {"SH",  24, 24, {}},
            {"T",   23, 23, {}},
            {"RLK", 22, 22, {}},
            {"RLU", 21, 21, {}},
            {"RLH", 20, 20, {}},
        }
    },
    {
        "PMCCNTR_EL0", CSR_REGID_PMCCNTR_EL0, READ,
        {
            {"CCNT", 63,  0, {}},
        }
    },
    {
        "PMCR_EL0", CSR_REGID_PMCR_EL0, READ,
        {
            {"FZS",    32, 32, {}},
            {"IMP",    31, 24, {}},
            {"IDCODE", 23, 16, {}},
            {"N",      15, 11, {}},
            {"FZO",     9,  9, {}},
            {"LP",      7,  7, {}},
            {"LC",      6,  6, {}},
            {"DP",      5,  5, {}},
            {"X",       4,  4, {}},
            {"D",       3,  3, {}},
            {"C",       2,  2, {}},
            {"P",       1,  1, {}},
            {"E",       0,  0, {}},
        }
    },
    {
        "PMUSERENR_EL0", CSR_REGID_PMUSERENR_EL0, READ,
        {
            {"TID",  6,  6, {}},
            {"IR",   5,  5, {}},
            {"UEN",  4,  4, {}},
            {"ER",   3,  3, {}},
            {"CR",   2,  2, {}},
            {"SW",   1,  1, {}},
            {"EN",   0,  0, {}},
        }
    },
    {
        "APDAKEYHI_EL1", CSR_REGID_APDAKEYHI_EL1, READ,
        {
            {"APDAKeyHi", 63,  0, {}},
        }
    },
    {
        "APDAKEYLO_EL1", CSR_REGID_APDAKEYLO_EL1, READ,
        {
            {"APDAKeyLo", 63,  0, {}},
        }
    },
    {
        "APDBKEYHI_EL1", CSR_REGID_APDBKEYHI_EL1, READ,
        {
            {"APDBKeyHi", 63,  0, {}},
        }
    },
    {
        "APDBKEYLO_EL1", CSR_REGID_APDBKEYLO_EL1, READ,
        {
            {"APDBKeyLo", 63,  0, {}},
        }
    },
    {
        "APGAKEYHI_EL1", CSR_REGID_APGAKEYHI_EL1, READ,
        {
            {"APGAKeyHi", 63,  0, {}},
        }
    },
    {
        "APGAKEYLO_EL1", CSR_REGID_APGAKEYLO_EL1, READ,
        {
            {"APGAKeyLo", 63,  0, {}},
        }
    },
    {
        "APIAKEYHI_EL1", CSR_REGID_APIAKEYHI_EL1, READ,
        {
            {"APIAKeyHi", 63,  0, {}},
        }
    },
    {
        "APIAKEYLO_EL1", CSR_REGID_APIAKEYLO_EL1, READ,
        {
            {"APIAKeyLo", 63,  0, {}},
        }
    },
    {
        "APIBKEYHI_EL1", CSR_REGID_APIBKEYHI_EL1, READ,
        {
            {"APIBKeyHi", 63,  0, {}},
        }
    },
    {
        "APIBKEYLO_EL1", CSR_REGID_APIBKEYLO_EL1, READ,
        {
            {"APIBKeyLo", 63,  0, {}},
        }
    },
