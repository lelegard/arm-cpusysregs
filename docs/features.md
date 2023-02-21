# Arm features for A-Profile

Reference page: [Feature names in A-profile architecture](https://developer.arm.com/downloads/-/exploration-tools/feature-names-for-a-profile).

| Feature Name             | Year  | Optional | Mandatory | sysregs | Short description
| ------------------------ | ----- | -------- | --------- | :-----: | -----------------------
| FEAT_AA32BF16            | <2020 | Armv8.2  |           |   | AArch32 BFloat16 instructions
| FEAT_AA32HPD             | <2020 | Armv8.2  |           |   | AArch32 Hierarchical permission disables
| FEAT_AA32I8MM            | <2020 | Armv8.2  |           |   | AArch32 Int8 Matrix Multiplication
| FEAT_ABLE                | 2022  |          |           |   | Address Breakpoint Linking extension
| FEAT_ADERR               | 2022  |          |           |   | RASv2 Additional Error syndrome reporting, for Device memory
| FEAT_AdvSIMD             | <2020 |          |           |   | Advanced SIMD Extension
| FEAT_AES                 | <2020 | Armv8.0  |           | X | Advanced SIMD AES instructions
| FEAT_AFP                 | 2020  |          | Armv8.7   | X | Alternate floating-point behavior
| FEAT_AIE                 | 2022  |          |           |   | Memory Attribute Index Enhancement
| FEAT_AMUv1               | <2020 | Armv8.4  |           | X | Activity Monitors Extension
| FEAT_AMUv1p1             | <2020 | Armv8.6  |           | X | Activity Monitors Extension version 1.1
| FEAT_ANERR               | 2022  |          |           |   | RASv2 Additional Error syndrome reporting, for Normal memory
| FEAT_ASMv8p2             |       |          | Armv8.2   |   | BDC and REV64 alias instructions
| FEAT_B16B16              | 2022  |          |           |   | Non-widening BFloat16 to BFloat16 arithmetic for SVE2.1 and SME2.1
| FEAT_BBM                 | <2020 |          | Armv8.4   | X | Translation table break before make levels
| FEAT_BF16                | <2020 | Armv8.2  | Armv8.6   | X | AARch64 BFloat16 instructions
| FEAT_BRBE                | 2020  | Armv9.2  |           | X | Branch Record Buffer Extensions
| FEAT_BRBEv1p1            | 2021  | Armv9.3  |           | X | Branch Record Buffer Extensions version 1.1
| FEAT_BTI                 | <2020 | Armv8.5  |           | X | Branch target identification
| FEAT_CCIDX               | <2020 | Armv8.3  |           | X | Extended cache index
| FEAT_CHK                 | 2022  |          |           |   | Detect when Guarded Control Stacks are implemented
| FEAT_CLRBHB              | 2022  |          |           |   | A new instruction CLRBHB is added in HINT space
| FEAT_CMOW                | 2021  |          | Armv8.8   | X | Control for cache maintenance permission
| FEAT_CNTSC               | <2020 | Armv8.4  |           |   | Generic Counter Scaling
| FEAT_CONSTPACFIELD       | 2021  | Armv8.3  |           | X | PAC Algorithm enhancement
| FEAT_CP15SDISABLE2       | <2020 | Armv8.0  |           |   | CP15DISABLE2
| FEAT_CRC32               | <2020 | Armv8.0  | Armv8.1   | X | CRC32 instructions
| FEAT_CSSC                | 2022  |          |           |   | Common Short Sequence Compression scalar integer instructions
| FEAT_CSV2                | <2020 | Armv8.0  | Armv8.5   | X | Cache Speculation Variant 2
| FEAT_CSV2_1p1            | <2020 | Armv8.0  |           | X | Cache Speculation Variant 2 version 1.1
| FEAT_CSV2_1p2            | <2020 | Armv8.0  |           | X | Cache Speculation Variant 2 version 1.2
| FEAT_CSV2_2              |       | Armv8.0  |           | X | SCXTNUM_ELx registers
| FEAT_CSV2_3              | 2022  | Armv8.0  |           | X | New identification mechanism for Branch History information
| FEAT_CSV3                | <2020 | Armv8.0  | Armv8.5   | X | Cache Speculation Variant 3
| FEAT_D128                | 2022  |          |           |   | 128-bit Translation Tables, 56 bit PA
| FEAT_Debugv8p1           | <2020 |          |           |   | Debug with VHE
| FEAT_Debugv8p2           | <2020 | Armv8.2  |           | X | ARMv8.2 Debug
| FEAT_Debugv8p4           | <2020 |          | Armv8.4   | X | Debug relaxations and extensions version 8.4
| FEAT_Debugv8p8           | 2021  |          | Armv8.8   | X | Debug v8.8
| FEAT_Debugv8p9           | 2022  |          |           |   | Debug 2022
| FEAT_DGH                 | <2020 | Armv8.0  |           | X | Data Gathering Hint
| FEAT_DIT                 | <2020 |          | Armv8.4   | X | Data Independent Timing instructions
| FEAT_DoPD                | <2020 | Armv8.3  |           |   | Debug over Powerdown
| FEAT_DotProd             | <2020 | Armv8.2  | Armv8.4   | X | Advanced SIMD Int8 dot product instructions
| FEAT_DoubleFault         | <2020 |          | Armv8.4   | X | Double Fault Extension
| FEAT_DoubleFault2        | 2022  |          |           |   | Error exception routing extensions.
| FEAT_DoubleLock          | <2020 | Armv8.0  | not DoPD  | X | Double Lock
| FEAT_DPB                 | <2020 |          | Armv8.2   | X | DC CVAP instruction
| FEAT_DPB2                | <2020 | Armv8.2  | Armv8.5   | X | DC CVADP instruction
| FEAT_E0PD                | <2020 |          | Armv8.5   | X | Preventing EL0 access to halves of address maps
| FEAT_EBEP                | 2022  |          |           |   | Exception-based event profiling
| FEAT_EBF16               | 2020  | Armv9.2  |           | X | Additional instructions for the SME Extension
| FEAT_ECBHB               | 2022  |          |           |   | Imposes restrictions on branch hisory speculation around exceptions
| FEAT_ECV                 | <2020 |          | Armv8.6   | X | Enhanced counter virtualization
| FEAT_EPAC                | <2020 | Armv8.3  |           | X | Enhanced Pointer authentication
| FEAT_ETE                 | <2020 | Armv9.0  |           | X | Embedded Trace Extension
| FEAT_ETEv1p1             | <2020 | Armv9.1  |           | X | Embedded Trace Extension, version 1.1
| FEAT_ETEv1p2             | <2020 | Armv9.2  |           | X | Embedded Trace Extension, version 1.2
| FEAT_ETEv1p3             | 2022  |          |           |   | ETE support for v9.3
| FEAT_ETMv4               | <2020 |          |           |   | Embedded Trace Macrocell version4
| FEAT_ETMv4p1             | <2020 |          |           |   | Embedded Trace Macrocell version 4.1
| FEAT_ETMv4p2             | <2020 |          |           |   | Embedded Trace Macrocell version 4.2
| FEAT_ETMv4p3             | <2020 |          |           |   | Embedded Trace Macrocell version 4.3
| FEAT_ETMv4p4             | <2020 |          |           |   | Embedded Trace Macrocell version 4.3
| FEAT_ETMv4p5             | <2020 |          |           |   | Embedded Trace Macrocell version 4.4
| FEAT_ETMv4p6             | <2020 |          |           |   | Embedded Trace Macrocell version 4.5
| FEAT_ETS                 | <2020 | Armv8.0  | Armv8.7   | X | Enhanced Translation Synchronization
| FEAT_EVT                 | <2020 | Armv8.2  | Armv8.5   | X | Enhanced Virtualization Traps
| FEAT_ExS                 | <2020 | Armv8.5  |           | X | Disabling context synchronizing exception entry and exit
| FEAT_F32MM               | <2020 | Armv8.2  |           | X | SVE single-precision floating-point matrix multiply instruction
| FEAT_F64MM               | <2020 | Armv8.2  |           | X | SVE double-precision floating-point matrix multiply instruction
| FEAT_FCMA                | <2020 |          | Armv8.3   | X | Floating-point FCMLA and FCADD instructions
| FEAT_FGT                 | <2020 |          | Armv8.6   | X | Fine Grain Traps
| FEAT_FGT2                | 2022  |          |           |   | Fine-grained traps 2
| FEAT_FHM                 | <2020 | Armv8.2  | Armv8.4   | X | Half-precision floating-point FMLAL instructions
| FEAT_FlagM               | <2020 | Armv8.2  | Armv8.4   | X | Condition flag manipulation
| FEAT_FlagM2              | <2020 |          | Armv8.5   | X | Condition flag manipulation version 2
| FEAT_FP                  | <2020 |          |           | X | Floating point extension
| FEAT_FP16                | <2020 | Armv8.2  |           | X | Half-precision floating-point data processing
| FEAT_FPAC                | <2020 | Armv8.3  |           | X | Faulting on pointer authentication instructions
| FEAT_FPACCOMBINE         | <2020 | Armv8.3  |           | X | Faulting on combined pointer authentication instructions
| FEAT_FRINTTS             | <2020 |          | Armv8.5   | X | FRINT32Z, FRINT32X, FRINT64Z, and FRINT64X instructions
| FEAT_GCS                 | 2022  |          |           |   | Guarded Control Stack Extension
| FEAT_GICv3               | <2020 |          |           |   | Generic Interrupt Controller version 3
| FEAT_GICv3_NMI           | 2021  |          |           |   | Non-maskable Interrupts
| FEAT_GICv3_TDIR          | <2020 |          |           |   | Trapping Non-secure EL1 writes to ICV_DIR
| FEAT_GICv3p1             | <2020 |          |           |   | Generic Interrupt Controller version 3.1
| FEAT_GICv4               | <2020 |          |           |   | Generic Interrupt Controller version 4
| FEAT_GICv4p1             | <2020 |          |           |   | Generic Interrupt Controller version 4.1
| FEAT_GTG                 | <2020 |          |           |   | Guest translation granule size
| FEAT_HAFDBS              | <2020 | Armv8.1  |           | X | Hardware updates to access flag and dirty state in translation tables
| FEAT_HAFT                | 2022  |          |           |   | Hardware managed Access Flag for Table descriptors
| FEAT_HBC                 | 2021  |          | Armv8.8   | X | Hinted conditional branches
| FEAT_HCX                 | 2020  |          | Armv8.7   | X | Support for the HCRX_EL2 register
| FEAT_HPDS                | <2020 |          | Armv8.1   | X | Hierarchical permission disables in translation tables
| FEAT_HPDS2               | <2020 | Armv8.2  |           | X | Heirarchical permission disables in translation tables 2
| FEAT_HPMN0               | 2021  | Armv8.8  |           | X | Setting of MDCR_EL2.HPMN to zero
| FEAT_I8MM                | <2020 | Armv8.2  | Armv8.6   | X | Int8 Matrix Multiplication
| FEAT_IDST                | <2020 |          | Armv8.4   | X | ID space trap handling
| FEAT_IESB                | <2020 | Armv8.2  |           | X | Implicit Error synchronization event
| FEAT_ITE                 | 2022  |          |           |   | Instrumentation trace extension
| FEAT_IVIPT               | <2020 |          |           |   | The IVIPT Extension
| FEAT_JSCVT               | <2020 |          | Armv8.3   | X | JavaScript FJCVTS conversion instruction
| FEAT_LOR                 | <2020 |          | Armv8.1   | X | Limited ordering regions
| FEAT_LPA                 | <2020 | Armv8.2  |           | X | Large PA and IPA support
| FEAT_LPA2                | 2020  | Armv8.7  |           | X | Larger physical address for 4KB and 16KB translation granules
| FEAT_LRCPC               | <2020 |          | Armv8.3   | X | Load-acquire RCpc instructions
| FEAT_LRCPC2              | <2020 | Armv8.2  | Armv8.4   | X | Load-acquire RCpc instructions version 2
| FEAT_LRCPC3              | 2022  |          |           |   | Load-Acquire RCpc instructions version 3
| FEAT_LS64                | 2020  | Armv8.7  |           | X | Support for 64 byte loads/stores without return
| FEAT_LS64_ACCDATA        | 2020  | Armv8.7  |           | X | Support for 64-byte EL0 stores with return
| FEAT_LS64_V              | 2020  | Armv8.7  |           | X | Support for 64-byte stores with return
| FEAT_LSE                 | <2020 |          | Armv8.1   | X | Large System Extensions
| FEAT_LSE128              | 2022  |          |           |   | 128-bit Atomics
| FEAT_LSE2                | <2020 | Armv8.2  | Armv8.4   | X | Large System Extensions version 2
| FEAT_LSMAOC              | <2020 | Armv8.2  |           | X | Load/Store instruction multiple atomicity and ordering controls
| FEAT_LVA                 | <2020 | Armv8.2  |           | X | Large VA support
| FEAT_LVA3                | 2022  |          |           |   | 56-bit VA
| FEAT_MEC                 | 2022  |          |           |   | Memory Encryption Contexts
| FEAT_MOPS                | 2021  |          | Armv8.8   | X | Standardization of memory operations
| FEAT_MPAM                | <2020 |          |           | X | Memory Partitioning and Monitoring
| FEAT_MPAMv0p1            | <2020 |          |           |   | Memory Partitioning and Monitoring version 0.1
| FEAT_MPAMv1p1            | <2020 |          |           |   | Memory Partitioning and Monitoring version1.1
| FEAT_MTE                 | <2020 | Armv8.5  |           | X | Instruction-only Memory Tagging Extension
| FEAT_MTE2                | <2020 | Armv8.5  |           | X | Full Memory Tagging Extension
| FEAT_MTE3                | 2020  | Armv8.5  |           | X | MTE Asymmetric Fault Handling
| FEAT_MTE4                | 2022  |          |           |   | Support for memory tag checking
| FEAT_MTE_ASYM_FAULT      | 2022  |          |           |   | Asymmetric Tag Check Fault handling
| FEAT_MTE_ASYNC           | 2022  |          |           |   | Asynchronous Tag Check Fault handling
| FEAT_MTE_CANONICAL_TAGS  | 2022  |          |           |   | Support for Canonical tag checking
| FEAT_MTE_NO_ADDRESS_TAGS | 2022  |          |           |   | Support for Memory tagging with Address tagging disabled
| FEAT_MTE_PERM            | 2022  |          |           |   | Allocation tag access permission
| FEAT_MTE_STORE_ONLY      | 2022  |          |           |   | Support for Store-only Tag checking
| FEAT_MTE_TAGGED_FAR      | 2022  |          |           |   | Support for reporting of all non-address bits on a fault
| FEAT_MTPMU               | <2020 | Armv8.6  |           | X | Multi-threaded PMU Extensions
| FEAT_NMI                 | 2021  |          | Armv8.8   | X | Non-maskable Interrupts
| FEAT_nTLBPA              | <2020 | Armv8.0  |           | X | No intermediate caching by output address in TLB
| FEAT_NV                  | <2020 | Armv8.3  |           | X | Nested virtualization
| FEAT_NV2                 | <2020 | Armv8.4  |           | X | Enhanced support for nested virtualization
| FEAT_PACIMP              | <2020 | Armv8.3  |           | X | Pointer authentication - IMPLEMENTATION DEFINED algorithm
| FEAT_PACQARMA3           | 2021  | Armv8.3  |           | X | Pointer authentication - QARMA3 algorithm
| FEAT_PACQARMA5           | <2020 | Armv8.3  |           | X | Pointer authentication - QARMA5 algorithm
| FEAT_PAN                 | <2020 |          | Armv8.1   | X | Privileged access-never
| FEAT_PAN2                | <2020 | Armv8.1  | Armv8.2   | X | AT S1E1R and AT S1E1W instruction variants for PAN
| FEAT_PAN3                | 2020  | Armv8.1  | Armv8.7   | X | Support for SCTLR_ELx.EPAN
| FEAT_PAuth               | <2020 |          | Armv8.3   | X | Pointer authentication
| FEAT_PAuth2              | <2020 | Armv8.3  | Armv8.6   | X | Enhancements to pointer authentication
| FEAT_PCSRv8              | <2020 | Armv8.0  |           |   | PC Sample-base Profiling extension (not EL3 and EL2)
| FEAT_PCSRv8p2            | <2020 | Armv8.2  |           |   | PC Sample-based profiling version 8.2
| FEAT_PCSRv8p9            | 2022  |          |           |   | PCSR disable control
| FEAT_PIE                 | 2022  |          |           |   | Permission model enhancements
| FEAT_PMULL               | <2020 | Armv8.0  |           | X | Advanced SIMD PMULL instructions
| FEAT_PMUv3               | <2020 |          |           | X | PMU extension version 3
| FEAT_PMUv3p1             | <2020 | Armv8.1  |           | X | PMU extension version 3.1
| FEAT_PMUv3p4             | <2020 | Armv8.2  |           | X | PMU extension version 3.4
| FEAT_PMUv3p5             | <2020 | Armv8.5  |           | X | PMU extension version 3.5
| FEAT_PMUv3p7             | 2020  | Armv8.7  |           | X | Armv8.7 PMU Extensions
| FEAT_PMUv3p8             | 2021  | Armv8.8  |           | X | Armv8.8 PMU Extensions
| FEAT_PMUv3p9             | 2022  |          |           |   | EL0 access controls for PMU event counters
| FEAT_PMUv3_EDGE          | 2022  |          |           |   | PMU event edge detection
| FEAT_PMUv3_EXT32         | 2021  |          |           |   | Represents the original mostly 32-bit external interface to the Performance Monitors
| FEAT_PMUv3_EXT64         | 2021  |          |           |   | Optional 64-bit external interface to the Performance Monitors
| FEAT_PMUv3_ICNTR         | 2022  |          |           |   | PMU instruction counter
| FEAT_PMUv3_SS            | 2022  |          |           |   | PMU snapshot
| FEAT_PMUv3_TH            | 2021  | Armv8.8  |           | X | Event counting threshold
| FEAT_POE                 | 2022  |          |           |   | Permission model enhancements
| FEAT_PRFMSLC             | 2022  |          |           |   | Prefetching enhancements
| FEAT_RAS                 | <2020 |          |           | X | Reliability, Availability, and Serviceability (RAS) Extension
| FEAT_RASv1p1             | <2020 | Armv8.2  | Armv8.4   | X | Reliability, Availability, and Serviceability (RAS) Extension version 1.1
| FEAT_RASv2               | 2022  |          |           |   | Reliability, Availability, and Serviceability (RAS) Extension version 2
| FEAT_RDM                 | <2020 |          | Armv8.1   | X | Rounding double multiply accumulate
| FEAT_RME                 | 2020  | Armv9.2  |           | X | Realm Management Extension
| FEAT_RNG                 | <2020 | Armv8.5  |           | X | Random number generator
| FEAT_RNG_TRAP            | 2021  | Armv8.5  |           | X | Trapping support for RNDR and RNDRRS
| FEAT_RPRES               | 2020  | Armv8.7  |           | X | Increased precision of Reciprocal Estimate and Reciprocal Square Root Estimate
| FEAT_RPRFM               | 2022  |          |           |   | RPRFM range prefetch hint instruction
| FEAT_S1PIE               | 2022  |          |           |   | Permission model enhancements
| FEAT_S1POE               | 2022  |          |           |   | Permission model enhancements
| FEAT_S2FWB               | <2020 |          | Armv8.4   | X | Stage 2 forced write-back
| FEAT_S2PIE               | 2022  |          |           |   | Permission model enhancements
| FEAT_S2POE               | 2022  |          |           |   | Permission model enhancements
| FEAT_SB                  | <2020 | Armv8.0  | Armv8.5   | X | Speculation barrier
| FEAT_SCTLR2              | 2022  |          |           |   | Extension to SCTLR_ELx
| FEAT_SEBEP               | 2022  |          |           |   | Synchronous Exception-based event profiling
| FEAT_SEL2                | <2020 |          | Armv8.4   | X | Secure EL2
| FEAT_SHA1                | <2020 | Armv8.0  |           | X | Advanced SIMD SHA1 instructions
| FEAT_SHA256              | <2020 | Armv8.0  |           | X | Advanced SIMD SHA256 instructions
| FEAT_SHA3                | <2020 | Armv8.2  |           | X | Advanced SIMD EOR3, RAX1, XAR, and BCAX instructions
| FEAT_SHA512              | <2020 | Armv8.2  |           | X | Advanced SIMD SHA512 instructions
| FEAT_SM3                 | <2020 | Armv8.2  |           | X | Advanced SIMD SM3 instructions
| FEAT_SM4                 | <2020 | Armv8.2  |           | X | Advanced SIMD SM4 instructions
| FEAT_SME                 | <2020 | Armv9.2  |           | X | Scalable Matrix Extension
| FEAT_SME2                | 2022  |          |           |   | Scalable Matrix Extension versions SME2
| FEAT_SME2p1              | 2022  |          |           |   | Scalable Matrix Extension versions SME2.1
| FEAT_SME_F16F16          | 2022  |          |           |   | Non-widening half-precision FP16 to FP16 arithmetic for SME2.1
| FEAT_SME_F64F64          | 2020  | Armv9.2  |           | X | Additional instructions for the SME Extension
| FEAT_SME_FA64            | 2020  | Armv9.2  |           | X | Additional instructions for the SME Extension
| FEAT_SME_I16I64          | 2020  | Armv9.2  |           | X | Additional instructions for the SME Extension
| FEAT_SPE                 | <2020 |          |           | X | Statistical Profiling Extension
| FEAT_SPECRES             | <2020 | Armv8.0  | Armv8.5   | X | Speculation restriction instructions
| FEAT_SPECRES2            | 2022  |          |           |   | Adds new Clear Other Speculative Predictions instruction
| FEAT_SPE_FDS             | 2022  |          |           |   | SPE filtering by data source
| FEAT_SPEv1p1             | <2020 | Armv8.3  | Armv8.5   | X | Statistical Profiling Extensions version 1.1
| FEAT_SPEv1p2             | 2020  |          | Armv8.7   | X | Armv8.7 SPE
| FEAT_SPEv1p3             | 2021  |          | Armv8.8   | X | Armv8.8 Statistical Profiling Extensions
| FEAT_SPEv1p4             | 2022  |          |           |   | Addtional SPE events
| FEAT_SPMU                | 2022  |          |           |   | System PMU
| FEAT_SSBS                | <2020 | Armv8.0  |           | X | Speculative Store Bypass Safe Instruction
| FEAT_SSBS2               | <2020 | Armv8.0  |           | X | MRS and MSR instructions for SSBS
| FEAT_SVE                 | <2020 |          |           | X | Scalable Vector Extension
| FEAT_SVE2                | <2020 | Armv9.0  |           | X | SVE version 2
| FEAT_SVE2p1              | 2022  |          |           |   | Scalable Vector Extension version SVE2.1
| FEAT_SVE_AES             | <2020 | Armv9.0  |           | X | SVE AES instructions
| FEAT_SVE_BitPerm         | <2020 | Armv9.0  |           | X | SVE Bit Permute
| FEAT_SVE_PMULL128        | <2020 | Armv9.0  |           | X | SVE PMULL instructions
| FEAT_SVE_SHA3            | <2020 | Armv9.0  |           | X | SVE SHA-3 instructions
| FEAT_SVE_SM4             | <2020 | Armv9.0  |           | X | SVE SM4 instructions
| FEAT_SYSINSTR128         | 2022  |          |           |   | 128-bit System instructions
| FEAT_SYSREG128           | 2022  |          |           |   | 128-bit System registers
| FEAT_TCR2                | 2022  |          |           |   | Extension to TCR_ELx
| FEAT_THE                 | 2022  |          |           |   | Translation Hardening Extension
| FEAT_TIDCP1              | 2021  |          | Armv8.8   | X | EL0 use of IMPLEMENTATION DEFINED functionality
| FEAT_TLBIOS              | <2020 |          | Armv8.4   | X | TLB invalidate outer-shared instructions
| FEAT_TLBIRANGE           | <2020 |          | Armv8.4   | X | TLB range invalidate range instructions
| FEAT_TME                 | <2020 | Armv9.0  |           | X | Transactional Memory Extension
| FEAT_TRBE                | <2020 | Armv9.0  |           | X | Trace Buffer Extension
| FEAT_TRBE_EXT            | 2022  |          |           |   | Represents TRBE external mode
| FEAT_TRBE_MPAM           | 2022  |          |           |   | Trace Buffer MPAM extensions
| FEAT_TRF                 | <2020 | Armv8.4  |           | X | Self hosted Trace Extensions
| FEAT_TTCNP               | <2020 |          | Armv8.2   | X | Common not private translations
| FEAT_TTL                 | <2020 |          | Armv8.4   | X | Translation Table Level
| FEAT_TTST                | <2020 | Armv8.4  | Armv8.4   | X | Small translation tables
| FEAT_TWED                | <2020 |          |           | X | Delayed trapping of WFE
| FEAT_UAO                 | <2020 |          | Armv8.2   | X | Unprivileged Access Override control
| FEAT_VHE                 | <2020 |          | Armv8.1   | X | Virtualization Host Extensions
| FEAT_VMID16              | <2020 | Armv8.1  |           | X | 16-bit VMID
| FEAT_VPIPT               | <2020 | Armv8.2  |           | X | VMID-aware PIPT instruction cache
| FEAT_WFxT                | 2020  |          | Armv8.7   | X | WFE and WFI instructions with timeout
| FEAT_XNX                 | <2020 |          | Armv8.2   | X | Execute-never control distinction by Exception level at stage 2
| FEAT_XS                  | 2020  |          | Armv8.7   | X | XS attribute
