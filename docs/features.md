# Arm features for A-Profile

Reference page: [Feature names in A-profile architecture](https://developer.arm.com/downloads/-/exploration-tools/feature-names-for-a-profile).

The following table lists all known Arm features by name.
For each feature, the initial versions for which it was optional and then mandatory are indicated (when known).
The `sysreg` column is checked when the feature is detected by the command `sysreg -s`.

| Feature Name             | Optional | Mandatory | sysregs | Short description
| ------------------------ | -------- | --------- | :-----: | -----------------------
| FEAT_AA32BF16            | Armv8.2  |           |   | AArch32 BFloat16 instructions
| FEAT_AA32HPD             | Armv8.2  |           |   | AArch32 Hierarchical permission disables
| FEAT_AA32I8MM            | Armv8.2  |           |   | AArch32 Int8 Matrix Multiplication
| FEAT_ABLE                |          |           |   | Address Breakpoint Linking extension
| FEAT_ADERR               |          |           | X | RASv2 Additional Error syndrome reporting, for Device memory
| FEAT_AdvSIMD             |          |           |   | Advanced SIMD Extension
| FEAT_AES                 | Armv8.0  |           | X | Advanced SIMD AES instructions
| FEAT_AFP                 |          | Armv8.7   | X | Alternate floating-point behavior
| FEAT_AIE                 |          |           | X | Memory Attribute Index Enhancement
| FEAT_AMUv1               | Armv8.4  |           | X | Activity Monitors Extension
| FEAT_AMUv1p1             | Armv8.6  |           | X | Activity Monitors Extension version 1.1
| FEAT_ANERR               |          |           | X | RASv2 Additional Error syndrome reporting, for Normal memory
| FEAT_ASMv8p2             |          | Armv8.2   |   | BDC and REV64 alias instructions
| FEAT_B16B16              |          |           |   | Non-widening BFloat16 to BFloat16 arithmetic for SVE2.1 and SME2.1
| FEAT_BBM                 |          | Armv8.4   | X | Translation table break before make levels
| FEAT_BF16                | Armv8.2  | Armv8.6   | X | AARch64 BFloat16 instructions
| FEAT_BRBE                | Armv9.2  |           | X | Branch Record Buffer Extensions
| FEAT_BRBEv1p1            | Armv9.3  |           | X | Branch Record Buffer Extensions version 1.1
| FEAT_BTI                 | Armv8.5  |           | X | Branch target identification
| FEAT_CCIDX               | Armv8.3  |           | X | Extended cache index
| FEAT_CHK                 |          |           |   | Detect when Guarded Control Stacks are implemented
| FEAT_CLRBHB              |          |           | X | A new instruction CLRBHB is added in HINT space
| FEAT_CMOW                |          | Armv8.8   | X | Control for cache maintenance permission
| FEAT_CNTSC               | Armv8.4  |           |   | Generic Counter Scaling
| FEAT_CONSTPACFIELD       | Armv8.3  |           | X | PAC Algorithm enhancement
| FEAT_CP15SDISABLE2       | Armv8.0  |           |   | CP15DISABLE2
| FEAT_CRC32               | Armv8.0  | Armv8.1   | X | CRC32 instructions
| FEAT_CSSC                |          |           | X | Common Short Sequence Compression scalar integer instructions
| FEAT_CSV2                | Armv8.0  | Armv8.5   | X | Cache Speculation Variant 2
| FEAT_CSV2_1p1            | Armv8.0  |           | X | Cache Speculation Variant 2 version 1.1
| FEAT_CSV2_1p2            | Armv8.0  |           | X | Cache Speculation Variant 2 version 1.2
| FEAT_CSV2_2              | Armv8.0  |           | X | SCXTNUM_ELx registers
| FEAT_CSV2_3              | Armv8.0  |           | X | New identification mechanism for Branch History information
| FEAT_CSV3                | Armv8.0  | Armv8.5   | X | Cache Speculation Variant 3
| FEAT_D128                |          |           |   | 128-bit Translation Tables, 56 bit PA
| FEAT_Debugv8p1           |          |           |   | Debug with VHE
| FEAT_Debugv8p2           | Armv8.2  |           | X | ARMv8.2 Debug
| FEAT_Debugv8p4           |          | Armv8.4   | X | Debug relaxations and extensions version 8.4
| FEAT_Debugv8p8           |          | Armv8.8   | X | Debug v8.8
| FEAT_Debugv8p9           |          |           |   | Debug 2022
| FEAT_DGH                 | Armv8.0  |           | X | Data Gathering Hint
| FEAT_DIT                 |          | Armv8.4   | X | Data Independent Timing instructions
| FEAT_DoPD                | Armv8.3  |           |   | Debug over Powerdown
| FEAT_DotProd             | Armv8.2  | Armv8.4   | X | Advanced SIMD Int8 dot product instructions
| FEAT_DoubleFault         |          | Armv8.4   | X | Double Fault Extension
| FEAT_DoubleFault2        |          |           | X | Error exception routing extensions.
| FEAT_DoubleLock          | Armv8.0  | not DoPD  | X | Double Lock
| FEAT_DPB                 |          | Armv8.2   | X | DC CVAP instruction
| FEAT_DPB2                | Armv8.2  | Armv8.5   | X | DC CVADP instruction
| FEAT_E0PD                |          | Armv8.5   | X | Preventing EL0 access to halves of address maps
| FEAT_EBEP                |          |           |   | Exception-based event profiling
| FEAT_EBF16               | Armv9.2  |           | X | Additional instructions for the SME Extension
| FEAT_ECBHB               |          |           | X | Imposes restrictions on branch hisory speculation around exceptions
| FEAT_ECV                 |          | Armv8.6   | X | Enhanced counter virtualization
| FEAT_EPAC                | Armv8.3  |           | X | Enhanced Pointer authentication
| FEAT_ETE                 | Armv9.0  |           | X | Embedded Trace Extension
| FEAT_ETEv1p1             | Armv9.1  |           | X | Embedded Trace Extension, version 1.1
| FEAT_ETEv1p2             | Armv9.2  |           | X | Embedded Trace Extension, version 1.2
| FEAT_ETEv1p3             |          |           |   | ETE support for v9.3
| FEAT_ETMv4               |          |           |   | Embedded Trace Macrocell version4
| FEAT_ETMv4p1             |          |           |   | Embedded Trace Macrocell version 4.1
| FEAT_ETMv4p2             |          |           |   | Embedded Trace Macrocell version 4.2
| FEAT_ETMv4p3             |          |           |   | Embedded Trace Macrocell version 4.3
| FEAT_ETMv4p4             |          |           |   | Embedded Trace Macrocell version 4.3
| FEAT_ETMv4p5             |          |           |   | Embedded Trace Macrocell version 4.4
| FEAT_ETMv4p6             |          |           |   | Embedded Trace Macrocell version 4.5
| FEAT_ETS                 | Armv8.0  | Armv8.7   | X | Enhanced Translation Synchronization
| FEAT_EVT                 | Armv8.2  | Armv8.5   | X | Enhanced Virtualization Traps
| FEAT_ExS                 | Armv8.5  |           | X | Disabling context synchronizing exception entry and exit
| FEAT_F32MM               | Armv8.2  |           | X | SVE single-precision floating-point matrix multiply instruction
| FEAT_F64MM               | Armv8.2  |           | X | SVE double-precision floating-point matrix multiply instruction
| FEAT_FCMA                |          | Armv8.3   | X | Floating-point FCMLA and FCADD instructions
| FEAT_FGT                 |          | Armv8.6   | X | Fine Grain Traps
| FEAT_FGT2                |          |           |   | Fine-grained traps 2
| FEAT_FHM                 | Armv8.2  | Armv8.4   | X | Half-precision floating-point FMLAL instructions
| FEAT_FlagM               | Armv8.2  | Armv8.4   | X | Condition flag manipulation
| FEAT_FlagM2              |          | Armv8.5   | X | Condition flag manipulation version 2
| FEAT_FP                  |          |           | X | Floating point extension
| FEAT_FP16                | Armv8.2  |           | X | Half-precision floating-point data processing
| FEAT_FPAC                | Armv8.3  |           | X | Faulting on pointer authentication instructions
| FEAT_FPACCOMBINE         | Armv8.3  |           | X | Faulting on combined pointer authentication instructions
| FEAT_FRINTTS             |          | Armv8.5   | X | FRINT32Z, FRINT32X, FRINT64Z, and FRINT64X instructions
| FEAT_GCS                 |          |           | X | Guarded Control Stack Extension
| FEAT_GICv3               |          |           |   | Generic Interrupt Controller version 3
| FEAT_GICv3_NMI           |          |           |   | Non-maskable Interrupts
| FEAT_GICv3_TDIR          |          |           |   | Trapping Non-secure EL1 writes to ICV_DIR
| FEAT_GICv3p1             |          |           |   | Generic Interrupt Controller version 3.1
| FEAT_GICv4               |          |           |   | Generic Interrupt Controller version 4
| FEAT_GICv4p1             |          |           |   | Generic Interrupt Controller version 4.1
| FEAT_GTG                 |          |           |   | Guest translation granule size
| FEAT_HAFDBS              | Armv8.1  |           | X | Hardware updates to access flag and dirty state in translation tables
| FEAT_HAFT                |          |           |   | Hardware managed Access Flag for Table descriptors
| FEAT_HBC                 |          | Armv8.8   | X | Hinted conditional branches
| FEAT_HCX                 |          | Armv8.7   | X | Support for the HCRX_EL2 register
| FEAT_HPDS                |          | Armv8.1   | X | Hierarchical permission disables in translation tables
| FEAT_HPDS2               | Armv8.2  |           | X | Heirarchical permission disables in translation tables 2
| FEAT_HPMN0               | Armv8.8  |           | X | Setting of MDCR_EL2.HPMN to zero
| FEAT_I8MM                | Armv8.2  | Armv8.6   | X | Int8 Matrix Multiplication
| FEAT_IDST                |          | Armv8.4   | X | ID space trap handling
| FEAT_IESB                | Armv8.2  |           | X | Implicit Error synchronization event
| FEAT_ITE                 |          |           |   | Instrumentation trace extension
| FEAT_IVIPT               |          |           |   | The IVIPT Extension
| FEAT_JSCVT               |          | Armv8.3   | X | JavaScript FJCVTS conversion instruction
| FEAT_LOR                 |          | Armv8.1   | X | Limited ordering regions
| FEAT_LPA                 | Armv8.2  |           | X | Large PA and IPA support
| FEAT_LPA2                | Armv8.7  |           | X | Larger physical address for 4KB and 16KB translation granules
| FEAT_LRCPC               |          | Armv8.3   | X | Load-acquire RCpc instructions
| FEAT_LRCPC2              | Armv8.2  | Armv8.4   | X | Load-acquire RCpc instructions version 2
| FEAT_LRCPC3              |          |           |   | Load-Acquire RCpc instructions version 3
| FEAT_LS64                | Armv8.7  |           | X | Support for 64 byte loads/stores without return
| FEAT_LS64_ACCDATA        | Armv8.7  |           | X | Support for 64-byte EL0 stores with return
| FEAT_LS64_V              | Armv8.7  |           | X | Support for 64-byte stores with return
| FEAT_LSE                 |          | Armv8.1   | X | Large System Extensions
| FEAT_LSE128              |          |           |   | 128-bit Atomics
| FEAT_LSE2                | Armv8.2  | Armv8.4   | X | Large System Extensions version 2
| FEAT_LSMAOC              | Armv8.2  |           | X | Load/Store instruction multiple atomicity and ordering controls
| FEAT_LVA                 | Armv8.2  |           | X | Large VA support
| FEAT_LVA3                |          |           |   | 56-bit VA
| FEAT_MEC                 |          |           | X | Memory Encryption Contexts
| FEAT_MOPS                |          | Armv8.8   | X | Standardization of memory operations
| FEAT_MPAM                |          |           | X | Memory Partitioning and Monitoring
| FEAT_MPAMv0p1            |          |           |   | Memory Partitioning and Monitoring version 0.1
| FEAT_MPAMv1p1            |          |           |   | Memory Partitioning and Monitoring version1.1
| FEAT_MTE                 | Armv8.5  |           | X | Instruction-only Memory Tagging Extension
| FEAT_MTE2                | Armv8.5  |           | X | Full Memory Tagging Extension
| FEAT_MTE3                | Armv8.5  |           | X | MTE Asymmetric Fault Handling
| FEAT_MTE4                |          |           | X | Support for memory tag checking
| FEAT_MTE_ASYM_FAULT      |          |           |   | Asymmetric Tag Check Fault handling
| FEAT_MTE_ASYNC           |          |           |   | Asynchronous Tag Check Fault handling
| FEAT_MTE_CANONICAL_TAGS  |          |           |   | Support for Canonical tag checking
| FEAT_MTE_NO_ADDRESS_TAGS |          |           |   | Support for Memory tagging with Address tagging disabled
| FEAT_MTE_PERM            |          |           |   | Allocation tag access permission
| FEAT_MTE_STORE_ONLY      |          |           |   | Support for Store-only Tag checking
| FEAT_MTE_TAGGED_FAR      |          |           |   | Support for reporting of all non-address bits on a fault
| FEAT_MTPMU               | Armv8.6  |           | X | Multi-threaded PMU Extensions
| FEAT_NMI                 |          | Armv8.8   | X | Non-maskable Interrupts
| FEAT_nTLBPA              | Armv8.0  |           | X | No intermediate caching by output address in TLB
| FEAT_NV                  | Armv8.3  |           | X | Nested virtualization
| FEAT_NV2                 | Armv8.4  |           | X | Enhanced support for nested virtualization
| FEAT_PACIMP              | Armv8.3  |           | X | Pointer authentication - IMPLEMENTATION DEFINED algorithm
| FEAT_PACQARMA3           | Armv8.3  |           | X | Pointer authentication - QARMA3 algorithm
| FEAT_PACQARMA5           | Armv8.3  |           | X | Pointer authentication - QARMA5 algorithm
| FEAT_PAN                 |          | Armv8.1   | X | Privileged access-never
| FEAT_PAN2                | Armv8.1  | Armv8.2   | X | AT S1E1R and AT S1E1W instruction variants for PAN
| FEAT_PAN3                | Armv8.1  | Armv8.7   | X | Support for SCTLR_ELx.EPAN
| FEAT_PAuth               |          | Armv8.3   | X | Pointer authentication
| FEAT_PAuth2              | Armv8.3  | Armv8.6   | X | Enhancements to pointer authentication
| FEAT_PCSRv8              | Armv8.0  |           |   | PC Sample-base Profiling extension (not EL3 and EL2)
| FEAT_PCSRv8p2            | Armv8.2  |           |   | PC Sample-based profiling version 8.2
| FEAT_PCSRv8p9            |          |           |   | PCSR disable control
| FEAT_PFAR                |          |           | X | Physical fault address registers
| FEAT_PIE                 |          |           |   | Permission model enhancements
| FEAT_PMULL               | Armv8.0  |           | X | Advanced SIMD PMULL instructions
| FEAT_PMUv3               |          |           | X | PMU extension version 3
| FEAT_PMUv3p1             | Armv8.1  |           | X | PMU extension version 3.1
| FEAT_PMUv3p4             | Armv8.2  |           | X | PMU extension version 3.4
| FEAT_PMUv3p5             | Armv8.5  |           | X | PMU extension version 3.5
| FEAT_PMUv3p7             | Armv8.7  |           | X | Armv8.7 PMU Extensions
| FEAT_PMUv3p8             | Armv8.8  |           | X | Armv8.8 PMU Extensions
| FEAT_PMUv3p9             |          |           |   | EL0 access controls for PMU event counters
| FEAT_PMUv3_EDGE          |          |           |   | PMU event edge detection
| FEAT_PMUv3_EXT32         |          |           |   | Original mostly 32-bit external interface to the Performance Monitors
| FEAT_PMUv3_EXT64         |          |           |   | Optional 64-bit external interface to the Performance Monitors
| FEAT_PMUv3_ICNTR         |          |           |   | PMU instruction counter
| FEAT_PMUv3_SS            |          |           |   | PMU snapshot
| FEAT_PMUv3_TH            | Armv8.8  |           | X | Event counting threshold
| FEAT_POE                 |          |           |   | Permission model enhancements
| FEAT_PRFMSLC             |          |           | X | Prefetching enhancements
| FEAT_RAS                 |          |           | X | Reliability, Availability, and Serviceability (RAS) Extension
| FEAT_RASv1p1             | Armv8.2  | Armv8.4   | X | Reliability, Availability, and Serviceability (RAS) Extension version 1.1
| FEAT_RASv2               |          |           |   | Reliability, Availability, and Serviceability (RAS) Extension version 2
| FEAT_RDM                 |          | Armv8.1   | X | Rounding double multiply accumulate
| FEAT_RME                 | Armv9.2  |           | X | Realm Management Extension
| FEAT_RNG                 | Armv8.5  |           | X | Random number generator
| FEAT_RNG_TRAP            | Armv8.5  |           | X | Trapping support for RNDR and RNDRRS
| FEAT_RPRES               | Armv8.7  |           | X | Increased precision of Reciprocal Estimate and Reciprocal Square Root Estimate
| FEAT_RPRFM               |          |           | X | RPRFM range prefetch hint instruction
| FEAT_S1PIE               |          |           | X | Permission model enhancements
| FEAT_S1POE               |          |           | X | Permission model enhancements
| FEAT_S2FWB               |          | Armv8.4   | X | Stage 2 forced write-back
| FEAT_S2PIE               |          |           | X | Permission model enhancements
| FEAT_S2POE               |          |           | X | Permission model enhancements
| FEAT_SB                  | Armv8.0  | Armv8.5   | X | Speculation barrier
| FEAT_SCTLR2              |          |           | X | Extension to SCTLR_ELx
| FEAT_SEBEP               |          |           |   | Synchronous Exception-based event profiling
| FEAT_SEL2                |          | Armv8.4   | X | Secure EL2
| FEAT_SHA1                | Armv8.0  |           | X | Advanced SIMD SHA1 instructions
| FEAT_SHA256              | Armv8.0  |           | X | Advanced SIMD SHA256 instructions
| FEAT_SHA3                | Armv8.2  |           | X | Advanced SIMD EOR3, RAX1, XAR, and BCAX instructions
| FEAT_SHA512              | Armv8.2  |           | X | Advanced SIMD SHA512 instructions
| FEAT_SM3                 | Armv8.2  |           | X | Advanced SIMD SM3 instructions
| FEAT_SM4                 | Armv8.2  |           | X | Advanced SIMD SM4 instructions
| FEAT_SME                 | Armv9.2  |           | X | Scalable Matrix Extension
| FEAT_SME2                |          |           |   | Scalable Matrix Extension versions SME2
| FEAT_SME2p1              |          |           |   | Scalable Matrix Extension versions SME2.1
| FEAT_SME_F16F16          |          |           |   | Non-widening half-precision FP16 to FP16 arithmetic for SME2.1
| FEAT_SME_F64F64          | Armv9.2  |           | X | Additional instructions for the SME Extension
| FEAT_SME_FA64            | Armv9.2  |           | X | Additional instructions for the SME Extension
| FEAT_SME_I16I64          | Armv9.2  |           | X | Additional instructions for the SME Extension
| FEAT_SPE                 | Armv8.2  |           | X | Statistical Profiling Extension
| FEAT_SPECRES             | Armv8.0  | Armv8.5   | X | Speculation restriction instructions
| FEAT_SPECRES2            |          |           |   | Adds new Clear Other Speculative Predictions instruction
| FEAT_SPE_FDS             |          |           |   | SPE filtering by data source
| FEAT_SPEv1p1             | Armv8.3  | Armv8.5   | X | Statistical Profiling Extensions version 1.1
| FEAT_SPEv1p2             |          | Armv8.7   | X | Armv8.7 SPE
| FEAT_SPEv1p3             |          | Armv8.8   | X | Armv8.8 Statistical Profiling Extensions
| FEAT_SPEv1p4             |          |           |   | Addtional SPE events
| FEAT_SPMU                |          |           |   | System PMU
| FEAT_SSBS                | Armv8.0  |           | X | Speculative Store Bypass Safe Instruction
| FEAT_SSBS2               | Armv8.0  |           | X | MRS and MSR instructions for SSBS
| FEAT_SVE                 |          |           | X | Scalable Vector Extension
| FEAT_SVE2                | Armv9.0  |           | X | SVE version 2
| FEAT_SVE2p1              |          |           |   | Scalable Vector Extension version SVE2.1
| FEAT_SVE_AES             | Armv9.0  |           | X | SVE AES instructions
| FEAT_SVE_BitPerm         | Armv9.0  |           | X | SVE Bit Permute
| FEAT_SVE_PMULL128        | Armv9.0  |           | X | SVE PMULL instructions
| FEAT_SVE_SHA3            | Armv9.0  |           | X | SVE SHA-3 instructions
| FEAT_SVE_SM4             | Armv9.0  |           | X | SVE SM4 instructions
| FEAT_SYSINSTR128         |          |           | X | 128-bit System instructions
| FEAT_SYSREG128           |          |           | X | 128-bit System registers
| FEAT_TCR2                |          |           | X | Extension to TCR_ELx
| FEAT_THE                 |          |           | X | Translation Hardening Extension
| FEAT_TIDCP1              |          | Armv8.8   | X | EL0 use of IMPLEMENTATION DEFINED functionality
| FEAT_TLBIOS              |          | Armv8.4   | X | TLB invalidate outer-shared instructions
| FEAT_TLBIRANGE           |          | Armv8.4   | X | TLB range invalidate range instructions
| FEAT_TME                 | Armv9.0  |           | X | Transactional Memory Extension
| FEAT_TRBE                | Armv9.0  |           | X | Trace Buffer Extension
| FEAT_TRBE_EXT            |          |           |   | Represents TRBE external mode
| FEAT_TRBE_MPAM           |          |           |   | Trace Buffer MPAM extensions
| FEAT_TRF                 | Armv8.4  |           | X | Self hosted Trace Extensions
| FEAT_TTCNP               |          | Armv8.2   | X | Common not private translations
| FEAT_TTL                 |          | Armv8.4   | X | Translation Table Level
| FEAT_TTST                | Armv8.4  | Armv8.4   | X | Small translation tables
| FEAT_TWED                | Armv8.6  |           | X | Delayed trapping of WFE
| FEAT_UAO                 |          | Armv8.2   | X | Unprivileged Access Override control
| FEAT_VHE                 |          | Armv8.1   | X | Virtualization Host Extensions
| FEAT_VMID16              | Armv8.1  |           | X | 16-bit VMID
| FEAT_VPIPT               | Armv8.2  |           | X | VMID-aware PIPT instruction cache
| FEAT_WFxT                |          | Armv8.7   | X | WFE and WFI instructions with timeout
| FEAT_XNX                 |          | Armv8.2   | X | Execute-never control distinction by Exception level at stage 2
| FEAT_XS                  |          | Armv8.7   | X | XS attribute
