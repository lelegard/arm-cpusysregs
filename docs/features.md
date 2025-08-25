# Arm features for A-Profile

Reference page: [Feature names in A-profile architecture](https://developer.arm.com/downloads/-/exploration-tools/feature-names-for-a-profile).

The following table lists all known Arm features by name.
For each feature, the initial versions for which it was optional and
then mandatory are indicated (when known).

The `sysreg` column is checked when the feature is detected by the command `sysreg -s`.
When set to "n/a", the presence of the feature cannot be detected from software
(external debug interfaces features for instance).

The Python script `aarch/extract-arm-spec.py` automatically updates this table,
based on reference JSON and XML files on the Arm public web site. This script should
be executed each time an update of the Arm architecture is published. It preserves all
existing information in the table, adds new features, update minimum versions of the
Arm architecture for existing features.

<!-- Do not remove the markers AUTOGEN-BEGIN and AUTOGEN-END. -->
<!-- @AUTOGEN-BEGIN -->
Version: 2025-06

Total: 366 features, 331 detectable, 19 removed.

| Feature Name             | Optional | Mandatory | sysregs | Short description
| ------------------------ | -------- | --------- | :-----: | -----------------
| FEAT_AA32                |          |           |    X    | PE supports AArch32.
| FEAT_AA32BF16            | Armv8.2  |           |    X    | AArch32 BFloat16 instructions
| FEAT_AA32EL0             | Armv8.0  |           |    X    | Support for AArch32 at EL0
| FEAT_AA32EL1             | Armv8.0  |           |    X    | Support for AArch32 at EL1, removed in Armv9.0
| FEAT_AA32EL2             | Armv8.0  |           |    X    | Support for AArch32 at EL2, removed in Armv9.0
| FEAT_AA32EL3             | Armv8.0  |           |    X    | Support for AArch32 at EL3, removed in Armv9.0
| FEAT_AA32HPD             | Armv8.1  |           |    X    | AArch32 Hierarchical permission disables
| FEAT_AA32I8MM            | Armv8.1  |           |    X    | AArch32 Int8 Matrix Multiplication
| FEAT_AA64                |          |           |    X    | PE uses AArch64 after last reboot
| FEAT_AA64EL0             | Armv8.0  | Armv9.0   |    X    | Support for AArch64 at EL0
| FEAT_AA64EL1             | Armv8.0  | Armv9.0   |    X    | Support for AArch64 at EL1
| FEAT_AA64EL2             | Armv8.0  |           |    X    | Support for AArch64 at EL2
| FEAT_AA64EL3             | Armv8.0  |           |    X    | Support for AArch64 at EL3
| FEAT_ABLE                | Armv9.3  |           |    X    | Address Breakpoint Linking extension
| FEAT_ADERR               | Armv8.8  |           |    X    | Asynchronous Device Error Exceptions~
| FEAT_AdvSIMD             | Armv8.0  |           |    X    | Advanced SIMD Extension
| FEAT_AES                 | Armv8.0  |           |    X    | Advanced SIMD AES instructions
| FEAT_AFP                 | Armv8.6  | Armv8.7   |    X    | Alternate floating-point behavior
| FEAT_AIE                 | Armv8.8  |           |    X    | Memory Attribute Index Enhancement
| FEAT_AMU_EXT             |          |           |   n/a   | External Activity Monitors extension
| FEAT_AMU_EXT32           |          |           |   n/a   | AArch32 External Activity Monitors
| FEAT_AMU_EXT64           |          |           |   n/a   | AArch64 External Activity Monitors
| FEAT_AMU_EXTACR          | Armv8.4  |           |   n/a   | Activity Monitors External Control Register
| FEAT_AMUv1               | Armv8.3  |           |    X    | Activity Monitors Extension
| FEAT_AMUv1p1             | Armv8.5  |           |    X    | Activity Monitors Extension version 1.1
| FEAT_ANERR               | Armv8.8  |           |    X    | Asynchronous Normal Error Exceptions
| FEAT_Armv9_Crypto        |          |           |    X    | Armv9 Cryptographic Extension
| FEAT_ASID16              | Armv8.0  |           |    X    | 16 bits ASID
| FEAT_ASID2               | Armv9.4  | Armv9.5   |    X    | Support for concurrent use of two ASIDs
| FEAT_ASMv8p2             | Armv8.1  | Armv8.2   |   n/a   | BDC and REV64 alias instructions
| FEAT_ATS1A               | Armv8.8  |           |    X    | Address Translate Stage 1 instructions without Permissions Checks
| FEAT_BBM                 | Armv8.3  | Armv8.4   |    X    | Translation table break before make levels (removed)
| FEAT_BBML1               | Armv8.3  |           |    X    | Translation table break-before-make level 1
| FEAT_BBML2               | Armv8.3  |           |    X    | Translation table break-before-make level 2
| FEAT_BF16                | Armv8.2  | Armv8.6   |    X    | AARch64 BFloat16 instructions
| FEAT_BRBE                | Armv9.1  |           |    X    | Branch Record Buffer Extensions
| FEAT_BRBEv1p1            | Armv9.2  |           |    X    | Branch Record Buffer Extensions version 1.1
| FEAT_BTI                 | Armv8.4  | Armv8.5   |    X    | Branch target identification
| FEAT_BWE                 | Armv9.3  |           |    X    | Breakpoints and watchpoint enhancements
| FEAT_BWE2                | Armv9.4  |           |    X    | Breakpoints and watchpoint enhancements 2
| FEAT_CCIDX               | Armv8.2  |           |    X    | Extended cache index
| FEAT_CHK                 | Armv8.0  | Armv9.4   |   n/a   | CHKFEAT instruction, detect when certain features are enabled
| FEAT_CLRBHB              | Armv8.0  | Armv8.9   |    X    | Support for Clear Branch History instruction
| FEAT_CMOW                | Armv8.7  | Armv8.8   |    X    | Control for cache maintenance permission
| FEAT_CMPBR               | Armv9.5  | Armv9.6   |    X    | Compare and Branch instructions
| FEAT_CNTSC               | Armv8.3  |           |   n/a   | Generic Counter Scaling
| FEAT_CONSTPACFIELD       | Armv8.2  |           |    X    | PAC Algorithm enhancement
| FEAT_CP15SDISABLE2       | Armv8.0  |           |   n/a   | Signal which prevents writes to Secure CP15 registers
| FEAT_CPA                 | Armv9.4  | Armv9.5   |    X    | Checked Pointer Arithmetic instructions
| FEAT_CPA2                | Armv9.4  |           |    X    | CPA instructions can be enabled
| FEAT_CRC32               | Armv8.0  | Armv8.1   |    X    | CRC32 instructions
| FEAT_Crypto              |          |           |    X    | Cryptographic Extension
| FEAT_CSSC                | Armv8.7  | Armv8.9   |    X    | Common Short Sequence Compression scalar integer instructions
| FEAT_CSV2                | Armv8.0  | Armv8.5   |    X    | Cache Speculation Variant 2
| FEAT_CSV2_1p1            | Armv8.0  |           |    X    | Cache Speculation Variant 2 version 1.1
| FEAT_CSV2_1p2            | Armv8.0  |           |    X    | Cache Speculation Variant 2 version 1.2
| FEAT_CSV2_2              | Armv8.0  |           |    X    | SCXTNUM_ELx registers
| FEAT_CSV2_3              | Armv8.0  |           |    X    | New identification mechanism for Branch History information
| FEAT_CSV3                | Armv8.0  | Armv8.5   |    X    | Cache Speculation Variant 3
| FEAT_D128                | Armv9.3  |           |    X    | 128-bit Translation Tables, 56 bit PA
| FEAT_Debugv8p1           | Armv8.0  |           |    X    | Debug with VHE
| FEAT_Debugv8p2           | Armv8.1  | Armv8.2   |    X    | ARMv8.2 Debug
| FEAT_Debugv8p4           | Armv8.3  | Armv8.4   |    X    | Debug relaxations and extensions version 8.4
| FEAT_Debugv8p8           | Armv8.7  | Armv8.8   |    X    | Debug v8.8
| FEAT_Debugv8p9           | Armv8.8  | Armv8.9   |    X    | Debug v8.9
| FEAT_DGH                 | Armv8.0  |           |    X    | Data Gathering Hint
| FEAT_DIT                 | Armv8.3  | Armv8.4   |    X    | Data Independent Timing instructions
| FEAT_DoPD                | Armv8.2  |           |   n/a   | Debug over Powerdown
| FEAT_DotProd             | Armv8.1  |           |    X    | Advanced SIMD Int8 dot product instructions
| FEAT_DoubleFault         | Armv8.3  |           |    X    | Double Fault Extension
| FEAT_DoubleFault2        | Armv8.8  |           |    X    | Double Fault Extension v2
| FEAT_DoubleLock          | Armv8.0  |           |    X    | Double Lock
| FEAT_DPB                 | Armv8.1  | Armv8.2   |    X    | DC CVAP instruction
| FEAT_DPB2                | Armv8.1  | Armv8.5   |    X    | DC CVADP instruction
| FEAT_E0PD                | Armv8.4  | Armv8.5   |    X    | Preventing EL0 access to halves of address maps
| FEAT_E2H0                | Armv8.0  |           |    X    | Programming of HCR_EL2.E2H
| FEAT_E3DSE               | Armv9.4  |           |    X    | Delegated SError exception injection
| FEAT_EBEP                | Armv9.3  |           |    X    | Exception-based event profiling
| FEAT_EBF16               | Armv8.2  |           |    X    | AArch64 Extended BFloat16 instructions
| FEAT_ECBHB               | Armv8.0  | Armv8.9   |    X    | Exploitative control using branch history information
| FEAT_ECV                 | Armv8.5  | Armv8.6   |    X    | Enhanced counter virtualization
| FEAT_ECV_POFF            | Armv8.5  |           |    X    | Enhanced Counter Virtualization Physical Offset
| FEAT_EDHSR               |          |           |   n/a   | External Debug Halting Syndrome Register
| FEAT_EL0                 |          | Armv8.0   |    X    | Support for execution at EL0
| FEAT_EL1                 |          | Armv8.0   |    X    | Support for execution at EL1
| FEAT_EL2                 | Armv8.0  |           |    X    | Support for execution at EL2
| FEAT_EL3                 | Armv8.0  |           |    X    | Support for execution at EL3
| FEAT_EPAC                | Armv8.2  |           |    X    | Enhanced Pointer authentication
| FEAT_ETE                 | Armv9.0  |           |    X    | Embedded Trace Extension
| FEAT_ETEv1p1             | Armv9.0  |           |    X    | Embedded Trace Extension, version 1.1
| FEAT_ETEv1p2             | Armv9.1  |           |    X    | Embedded Trace Extension, version 1.2
| FEAT_ETEv1p3             | Armv9.3  |           |    X    | Embedded Trace Extension, version 1.3
| FEAT_ETMv4               | Armv8.0  |           |    X    | Embedded Trace Macrocell version 4
| FEAT_ETMv4p1             |          |           |    X    | Embedded Trace Macrocell version 4.1 (removed)
| FEAT_ETMv4p2             |          |           |    X    | Embedded Trace Macrocell version 4.2 (removed)
| FEAT_ETMv4p3             |          |           |    X    | Embedded Trace Macrocell version 4.3 (removed)
| FEAT_ETMv4p4             |          |           |    X    | Embedded Trace Macrocell version 4.3 (removed)
| FEAT_ETMv4p5             |          |           |    X    | Embedded Trace Macrocell version 4.4 (removed)
| FEAT_ETMv4p6             |          |           |    X    | Embedded Trace Macrocell version 4.5 (removed)
| FEAT_ETS                 | Armv8.0  | Armv8.7   |    X    | Enhanced Translation Synchronization (removed)
| FEAT_ETS2                | Armv8.0  | Armv8.8   |    X    | Enhanced Translation Synchronization v2
| FEAT_ETS3                | Armv8.0  | Armv9.5   |    X    | Enhanced Translation Synchronization
| FEAT_EVT                 | Armv8.2  |           |    X    | Enhanced Virtualization Traps
| FEAT_ExS                 | Armv8.4  |           |    X    | Disabling context synchronizing exception entry and exit
| FEAT_F32MM               | Armv8.2  |           |    X    | SVE single-precision floating-point matrix multiply instruction
| FEAT_F64MM               | Armv8.2  |           |    X    | SVE double-precision floating-point matrix multiply instruction
| FEAT_F8F16MM             | Armv9.2  |           |    X    | FP8 to Half-Precision Matrix Multiplication
| FEAT_F8F32MM             | Armv9.2  |           |    X    | FP8 to Single-Precision Matrix Multiplication
| FEAT_FAMINMAX            | Armv9.2  |           |    X    | Advanced SIMD, SVE2, and SME2 FAMIN and FAMAX instructions
| FEAT_FCMA                | Armv8.2  |           |    X    | Floating-point FCMLA and FCADD instructions
| FEAT_FGT                 | Armv8.5  |           |    X    | Fine Grain Traps
| FEAT_FGT2                | Armv8.8  |           |    X    | Fine Grain Traps 2
| FEAT_FGWTE3              | Armv9.4  |           |    X    | Fine-Grained Write Trap EL3
| FEAT_FHM                 | Armv8.1  |           |    X    | Half-precision floating-point FMLAL instructions
| FEAT_FlagM               | Armv8.1  | Armv8.4   |    X    | Condition flag manipulation
| FEAT_FlagM2              | Armv8.4  |           |    X    | Condition flag manipulation version 2
| FEAT_FP                  | Armv8.0  |           |    X    | Floating point extension
| FEAT_FP16                | Armv8.2  |           |    X    | Half-precision floating-point data processing
| FEAT_FP8                 | Armv9.2  |           |    X    | FP8 convert instructions
| FEAT_FP8DOT2             | Armv9.2  |           |    X    | FP8 to half-precision 2-way dot product
| FEAT_FP8DOT4             | Armv9.2  |           |    X    | FP8 to single-precision 4-way dot product
| FEAT_FP8FMA              | Armv9.2  |           |    X    | FP8 multiply-accumulate instructions
| FEAT_FPAC                | Armv8.2  |           |    X    | Faulting on pointer authentication instructions
| FEAT_FPACC_SPEC          | Armv8.2  |           |    X    | Faulting on combined pointer authentication instructions
| FEAT_FPACCOMBINE         | Armv8.2  |           |    X    | Faulting on combined pointer authentication instructions
| FEAT_FPMR                | Armv9.2  |           |    X    | Floating-point Mode Register
| FEAT_FPRCVT              | Armv9.5  | Armv9.6   |    X    | Floating-Point to/from Integer in Scalar FP register
| FEAT_FRINTTS             | Armv8.4  |           |    X    | FRINT32Z, FRINT32X, FRINT64Z, and FRINT64X instructions
| FEAT_GCS                 | Armv9.3  |           |    X    | Guarded Control Stack Extension
| FEAT_GICv3               |          |           |    X    | Generic Interrupt Controller version 3 (removed)
| FEAT_GICv3_NMI           |          |           |   n/a   | Non-maskable Interrupts (removed)
| FEAT_GICv3_TDIR          |          |           |   n/a   | Trapping Non-secure EL1 writes to ICV_DIR (removed)
| FEAT_GICv3p1             |          |           |   n/a   | Generic Interrupt Controller version 3.1 (removed)
| FEAT_GICv4               |          |           |    X    | Generic Interrupt Controller version 4 (removed)
| FEAT_GICv4p1             |          |           |    X    | Generic Interrupt Controller version 4.1 (removed)
| FEAT_GTG                 | Armv8.0  |           |    X    | Guest translation granule size
| FEAT_HACDBS              | Armv9.4  |           |    X    | Hardware accelerator for cleaning Dirty state
| FEAT_HAFDBS              | Armv8.0  |           |    X    | Hardware updates to access flag and dirty state in translation tables
| FEAT_HAFT                | Armv8.7  |           |    X    | Hardware managed Access Flag for Table descriptors
| FEAT_HBC                 | Armv8.7  | Armv8.8   |    X    | Hinted conditional branches
| FEAT_HCX                 | Armv8.6  |           |    X    | Support for the HCRX_EL2 register
| FEAT_HDBSS               | Armv9.4  |           |    X    | Hardware Dirty state tracking Structure
| FEAT_HPDS                | Armv8.0  | Armv8.1   |    X    | Hierarchical permission disables in translation tables
| FEAT_HPDS2               | Armv8.1  |           |    X    | Heirarchical permission disables in translation tables 2
| FEAT_HPMN0               | Armv8.5  |           |    X    | Setting of MDCR_EL2.HPMN to zero
| FEAT_I8MM                | Armv8.1  | Armv8.6   |    X    | Int8 Matrix Multiplication
| FEAT_IDST                | Armv8.3  | Armv8.4   |    X    | ID space trap handling
| FEAT_IDTE3               | Armv9.0  |           |    X    | Trapping ID register accesses to EL3
| FEAT_IESB                | Armv8.1  |           |    X    | Implicit Error synchronization event
| FEAT_ITE                 | Armv9.3  |           |    X    | Instrumentation trace extension
| FEAT_IVIPT               | Armv8.0  | Armv8.0   |   n/a   | The IVIPT Extension
| FEAT_JSCVT               | Armv8.2  |           |    X    | JavaScript FJCVTS conversion instruction
| FEAT_LOR                 | Armv8.0  | Armv8.1   |    X    | Limited ordering regions
| FEAT_LPA                 | Armv8.1  |           |    X    | Large PA and IPA support
| FEAT_LPA2                | Armv8.6  |           |    X    | Larger physical address for 4KB and 16KB translation granules
| FEAT_LRCPC               | Armv8.2  | Armv8.3   |    X    | Load-acquire RCpc instructions
| FEAT_LRCPC2              | Armv8.2  | Armv8.4   |    X    | Load-acquire RCpc instructions version 2
| FEAT_LRCPC3              | Armv8.2  |           |    X    | Load-Acquire RCpc instructions version 3
| FEAT_LS64                | Armv8.6  |           |    X    | Support for 64 byte loads/stores without return
| FEAT_LS64_ACCDATA        | Armv8.6  |           |    X    | Support for 64-byte EL0 stores with return
| FEAT_LS64_V              | Armv8.6  |           |    X    | Support for 64-byte stores with return
| FEAT_LS64WB              | Armv9.2  |           |    X    | LS64 for Write-back cacheable memory
| FEAT_LSE                 | Armv8.0  | Armv8.1   |    X    | Large System Extensions
| FEAT_LSE128              | Armv9.3  |           |    X    | 128-bit Atomics
| FEAT_LSE2                | Armv8.2  | Armv8.4   |    X    | Large System Extensions version 2
| FEAT_LSFE                | Armv9.3  |           |    X    | Large System Float Extension
| FEAT_LSMAOC              | Armv8.1  |           |    X    | Load/Store instruction multiple atomicity and ordering controls
| FEAT_LSUI                | Armv9.5  | Armv9.6   |    X    | Unprivileged Load Store
| FEAT_LUT                 | Armv9.2  |           |    X    | Lookup table instructions with 2-bit and 4-bit indices
| FEAT_LVA                 | Armv8.1  |           |    X    | Large VA support
| FEAT_LVA3                | Armv9.3  |           |    X    | 56-bit VA
| FEAT_MEC                 | Armv9.2  |           |    X    | Memory Encryption Contexts
| FEAT_MixedEnd            | Armv8.0  |           |    X    | Mixed-endian support
| FEAT_MixedEndEL0         | Armv8.0  |           |    X    | Mixed-endian support at EL0
| FEAT_MOPS                | Armv8.7  | Armv8.8   |    X    | Standardization of memory operations
| FEAT_MPAM                | Armv8.2  |           |    X    | Memory Partitioning and Monitoring
| FEAT_MPAM_MSC_DCTRL      | Armv9.5  |           |   n/a   | MPAM Default Resource Control
| FEAT_MPAM_MSC_DOMAINS    | Armv9.5  |           |   n/a   | MPAM Domains PARTID translation
| FEAT_MPAM_PE_BW_CTRL     | Armv9.3  |           |    X    | MPAM PE-side Bandwidth Controls
| FEAT_MPAMv0p1            | Armv8.5  |           |    X    | Memory Partitioning and Monitoring version 0.1
| FEAT_MPAMv1p0            | Armv8.2  |           |    X    | Memory Partitioning and Monitoring version 1.0
| FEAT_MPAMv1p1            | Armv8.5  |           |    X    | Memory Partitioning and Monitoring version 1.1
| FEAT_MTE                 | Armv8.4  |           |    X    | Instruction-only Memory Tagging Extension
| FEAT_MTE2                | Armv8.4  |           |    X    | Full Memory Tagging Extension
| FEAT_MTE3                | Armv8.5  |           |    X    | MTE Asymmetric Fault Handling
| FEAT_MTE4                | Armv8.7  |           |    X    | Enhanced Memory Tagging Extension
| FEAT_MTE_ASYM_FAULT      |          |           |    X    | Asymmetric Tag Check Fault handling
| FEAT_MTE_ASYNC           | Armv8.5  |           |    X    | Asynchronous Tag Check Fault handling
| FEAT_MTE_CANONICAL_TAGS  |          |           |    X    | Canonical Tag checking for Untagged memory
| FEAT_MTE_NO_ADDRESS_TAGS |          |           |    X    | Memory tagging with Address tagging disabled
| FEAT_MTE_PERM            | Armv8.7  |           |    X    | Allocation tag access permission
| FEAT_MTE_STORE_ONLY      |          |           |    X    | Support for Store-only Tag checking
| FEAT_MTE_TAGGED_FAR      |          |           |    X    | FAR_ELx on a Tag Check Fault
| FEAT_MTPMU               | Armv8.5  |           |    X    | Multi-threaded PMU Extensions
| FEAT_NMI                 | Armv8.7  | Armv8.8   |    X    | Non-maskable Interrupts
| FEAT_nTLBPA              | Armv8.0  |           |    X    | No intermediate caching by output address in TLB
| FEAT_NV                  | Armv8.2  |           |    X    | Nested virtualization
| FEAT_NV2                 | Armv8.3  |           |    X    | Enhanced support for nested virtualization
| FEAT_NV2p1               | Armv8.4  |           |    X    | Enhanced nested virtualization support
| FEAT_OCCMO               | Armv9.5  | Armv9.6   |    X    | Outer Cacheable Cache Maintenance Operation
| FEAT_PACIMP              | Armv8.2  |           |    X    | Pointer authentication - IMPLEMENTATION DEFINED algorithm
| FEAT_PACQARMA3           | Armv8.2  |           |    X    | Pointer authentication - QARMA3 algorithm
| FEAT_PACQARMA5           | Armv8.2  |           |    X    | Pointer authentication - QARMA5 algorithm
| FEAT_PAN                 | Armv8.0  | Armv8.1   |    X    | Privileged access-never
| FEAT_PAN2                | Armv8.1  | Armv8.2   |    X    | AT S1E1R and AT S1E1W instruction variants for PAN
| FEAT_PAN3                | Armv8.1  | Armv8.7   |    X    | Support for SCTLR_ELx.EPAN
| FEAT_PAuth               | Armv8.2  | Armv8.3   |    X    | Pointer authentication
| FEAT_PAuth2              | Armv8.2  | Armv8.6   |    X    | Enhancements to pointer authentication
| FEAT_PAuth_LR            | Armv9.4  |           |    X    | PSTATE.PACM (?)
| FEAT_PCDPHINT            | Armv9.0  |           |    X    | Producer-Consumer Data Placement Hints
| FEAT_PCSRv8              | Armv8.0  |           |   n/a   | PC Sample-base Profiling extension (not EL3 and EL2)
| FEAT_PCSRv8p2            | Armv8.1  |           |   n/a   | PC Sample-based profiling version 8.2
| FEAT_PCSRv8p9            | Armv8.8  |           |   n/a   | PCSR disable control
| FEAT_PFAR                | Armv8.8  |           |    X    | Physical fault address registers
| FEAT_PIE                 |          |           |   n/a   | Permission model enhancements (removed)
| FEAT_PMULL               | Armv8.0  |           |    X    | Advanced SIMD PMULL instructions
| FEAT_PMUv3               | Armv8.0  |           |    X    | PMU extension version 3
| FEAT_PMUv3_EDGE          | Armv8.8  |           |    X    | PMU event edge detection
| FEAT_PMUv3_EXT           | Armv8.0  |           |   n/a   | External interface to the Performance Monitors
| FEAT_PMUv3_EXT32         | Armv8.0  |           |   n/a   | Original mostly 32-bit external interface to the Performance Monitors
| FEAT_PMUv3_EXT64         | Armv8.8  |           |   n/a   | Optional 64-bit external interface to the Performance Monitors
| FEAT_PMUv3_EXTPMN        | Armv9.5  |           |   n/a   | Reserving PMU event counters for external agents
| FEAT_PMUv3_ICNTR         | Armv8.8  |           |    X    | PMU instruction counter
| FEAT_PMUv3_SME           | Armv9.4  |           |    X    | Performance Monitors extensions for SME
| FEAT_PMUv3_SS            | Armv8.8  |           |    X    | PMU snapshot
| FEAT_PMUv3_TH            | Armv8.7  |           |    X    | Event counting threshold
| FEAT_PMUv3_TH2           | Armv9.4  |           |    X    | Performance Monitors event counter linking extension
| FEAT_PMUv3p1             | Armv8.0  |           |    X    | PMU extension version 3.1
| FEAT_PMUv3p4             | Armv8.3  |           |    X    | PMU extension version 3.4
| FEAT_PMUv3p5             | Armv8.4  |           |    X    | PMU extension version 3.5
| FEAT_PMUv3p7             | Armv8.6  |           |    X    | Armv8.7 PMU Extensions
| FEAT_PMUv3p8             | Armv8.7  |           |    X    | Armv8.8 PMU Extensions
| FEAT_PMUv3p9             | Armv8.8  |           |    X    | EL0 access controls for PMU event counters
| FEAT_POE                 |          |           |   n/a   | Permission model enhancements (removed)
| FEAT_PoPS                | Armv9.5  |           |    X    | Point of Physical Storage
| FEAT_PRFMSLC             | Armv8.0  |           |    X    | SLC target support for PRFM instructions
| FEAT_RAS                 | Armv8.0  | Armv8.2   |    X    | Reliability, Availability, and Serviceability (RAS) Extension
| FEAT_RASSA_ACR           |          |           |   n/a   | Access Control Register
| FEAT_RASSA_GRP           |          |           |   n/a   | RAS groups
| FEAT_RASSAv1             |          |           |   n/a   | RAS System Architecture version 1
| FEAT_RASSAv1p1           | Armv8.2  |           |   n/a   | RAS System Architecture version 1.1
| FEAT_RASSAv2             | Armv8.8  |           |   n/a   | RAS System Architecture Extension v2
| FEAT_RASv1p1             | Armv8.2  | Armv8.4   |    X    | Reliability, Availability, and Serviceability (RAS) Extension version 1.1
| FEAT_RASv2               | Armv8.8  |           |    X    | Reliability, Availability, and Serviceability (RAS) Extension version 2
| FEAT_RDM                 | Armv8.0  |           |    X    | Rounding double multiply accumulate
| FEAT_RME                 | Armv9.1  |           |    X    | Realm Management Extension
| FEAT_RME_GDI             | Armv9.4  |           |    X    | RME Granular Data Isolation extension
| FEAT_RME_GPC2            | Armv9.4  |           |    X    | RME Granule Protection Check 2 Extension
| FEAT_RME_GPC3            | Armv9.5  |           |    X    | RME Granule Protection Check 3 Extension
| FEAT_RNG                 | Armv8.4  |           |    X    | Random number generator
| FEAT_RNG_TRAP            | Armv8.4  |           |    X    | Trapping support for RNDR and RNDRRS
| FEAT_RPRES               | Armv8.6  |           |    X    | Increased precision of Reciprocal Estimate and Reciprocal Square Root Estimate
| FEAT_RPRFM               | Armv8.0  |           |    X    | RPRFM range prefetch hint instruction
| FEAT_S1PIE               | Armv8.8  |           |    X    | Stage 1 permission indirections
| FEAT_S1POE               | Armv8.8  |           |    X    | Stage 1 permission overlays
| FEAT_S2FWB               | Armv8.3  | Armv8.4   |    X    | Stage 2 forced write-back
| FEAT_S2PIE               | Armv8.8  |           |    X    | Stage 2 permission indirections
| FEAT_S2POE               | Armv8.8  |           |    X    | Stage 1 permission overlays
| FEAT_S2TGran16K          | Armv8.5  |           |    X    | Support for 16KB memory translation granule size at stage 2
| FEAT_S2TGran4K           | Armv8.5  |           |    X    | Support for 4KB memory translation granule size at stage 2
| FEAT_S2TGran64K          | Armv8.5  |           |    X    | Support for 64KB memory translation granule size at stage 2
| FEAT_SB                  | Armv8.0  | Armv8.5   |    X    | Speculation barrier
| FEAT_SCTLR2              | Armv8.0  | Armv8.9   |    X    | Extension to SCTLR_ELx
| FEAT_SEBEP               | Armv9.3  |           |    X    | Synchronous Exception-based event profilin
| FEAT_Secure              | Armv8.0  |           |   n/a   | Support for Secure state
| FEAT_SEL2                | Armv8.3  | Armv8.4   |    X    | Secure EL2
| FEAT_SHA1                | Armv8.0  |           |    X    | Advanced SIMD SHA1 instructions
| FEAT_SHA256              | Armv8.0  |           |    X    | Advanced SIMD SHA256 instructions
| FEAT_SHA3                | Armv8.1  |           |    X    | Advanced SIMD EOR3, RAX1, XAR, and BCAX instructions
| FEAT_SHA512              | Armv8.1  |           |    X    | Advanced SIMD SHA512 instructions
| FEAT_SM3                 | Armv8.1  |           |    X    | Advanced SIMD SM3 instructions
| FEAT_SM4                 | Armv8.1  |           |    X    | Advanced SIMD SM4 instructions
| FEAT_SME                 | Armv9.2  |           |    X    | Scalable Matrix Extension
| FEAT_SME2                | Armv9.2  |           |    X    | Scalable Matrix Extension version 2
| FEAT_SME2p1              | Armv9.2  |           |    X    | Scalable Matrix Extension version 2.1
| FEAT_SME2p2              | Armv9.5  |           |    X    | Scalable Matrix Extension version 2.2
| FEAT_SME_B16B16          | Armv9.2  |           |    X    | Non-widening BFloat16 to BFloat16 arithmetic for SME2.1
| FEAT_SME_F16F16          | Armv9.2  |           |    X    | Non-widening half-precision FP16 to FP16 arithmetic for SME2.1
| FEAT_SME_F64F64          | Armv9.2  |           |    X    | Additional instructions for the SME Extension
| FEAT_SME_F8F16           | Armv9.2  |           |    X    | SME2 ZA-targeting FP8 multiply-accumulate, dot product, and outer product to half-precision inst
| FEAT_SME_F8F32           | Armv9.2  |           |    X    | SME2 ZA-targeting FP8 multiply-accumulate, dot product, and outer product to single-precision inst
| FEAT_SME_FA64            | Armv9.2  |           |    X    | Additional instructions for the SME Extension
| FEAT_SME_I16I64          | Armv9.2  |           |    X    | Additional instructions for the SME Extension
| FEAT_SME_LUTv2           | Armv9.2  |           |    X    | Lookup table instructions with 4-bit indices and 8-bit elements
| FEAT_SME_MOP4            | Armv9.4  |           |    X    | Quarter-tile outer product instructions
| FEAT_SME_TMOP            | Armv9.4  |           |    X    | Structured sparsity outer product instructions
| FEAT_SPE                 | Armv8.1  |           |    X    | Statistical Profiling Extension
| FEAT_SPE_ALTCLK          | Armv9.4  |           |    X    | Statistical Profiling alternate clock domain extension
| FEAT_SPE_CRR             |          |           |    X    | Call Return Branch Records
| FEAT_SPE_DPFZS           | Armv8.6  |           |    X    | Disable Cycle Counter on SPE Freeze
| FEAT_SPE_EFT             | Armv9.4  |           |    X    | Statistical Profiling extended filtering by type
| FEAT_SPE_EXC             | Armv9.5  |           |    X    | SPE Profiling exception extension
| FEAT_SPE_FDS             | Armv8.8  |           |    X    | SPE filtering by data source
| FEAT_SPE_FnE             |          |           |    X    | Statistical Profiling inverse event filter
| FEAT_SPE_FPF             | Armv9.4  |           |    X    | Statistical Profiling floating-point flag extension
| FEAT_SPE_LDS             |          |           |   ???   | Statistical Profiling data source packet generation
| FEAT_SPE_nVM             | Armv9.5  |           |    X    | Statistical Profiling physical addressing mode extension
| FEAT_SPE_PBT             |          |           |    X    | Statistical Profiling previous branch target
| FEAT_SPE_SME             | Armv9.2  |           |    X    | Statistical Profiling extensions for SME
| FEAT_SPECRES             | Armv8.0  | Armv8.5   |    X    | Speculation restriction instructions
| FEAT_SPECRES2            | Armv8.0  | Armv8.9   |    X    | Adds new Clear Other Speculative Predictions instruction
| FEAT_SpecSEI             | Armv8.0  |           |    X    | SError interrupt exceptions from speculative reads of memory
| FEAT_SPEv1p1             | Armv8.2  |           |    X    | Statistical Profiling Extensions version 1.1
| FEAT_SPEv1p2             | Armv8.6  |           |    X    | Statistical Profiling Extensions version 1.2
| FEAT_SPEv1p3             | Armv8.7  |           |    X    | Armv8.8 Statistical Profiling Extensions
| FEAT_SPEv1p4             | Armv8.8  |           |    X    | Addtional SPE events
| FEAT_SPEv1p5             | Armv9.5  |           |    X    | Statistical Profiling Extension version 1.5
| FEAT_SPMU                | Armv8.8  |           |    X    | System Performance Monitors Extension
| FEAT_SPMU2               | Armv9.4  |           |    X    | System Performance Monitors Extension version 2
| FEAT_SRMASK              | Armv9.5  | Armv9.6   |    X    | Bitwise System Register Write Masks
| FEAT_SSBS                | Armv8.0  |           |    X    | Speculative Store Bypass Safe Instruction
| FEAT_SSBS2               | Armv8.0  |           |    X    | MRS and MSR instructions for SSBS
| FEAT_SSVE_AES            | Armv9.5  |           |    X    | Streaming SVE Mode AES and 128-bit polynomial multiply long instructions
| FEAT_SSVE_BitPerm        | Armv9.4  |           |    X    | Streaming Scalable Vector Bit Permutes instructions
| FEAT_SSVE_F8F16MM        | Armv9.2  |           |    X    | FP8 to Half-Precision Matrix Multiplication in Streaming SVE mode (removed)
| FEAT_SSVE_F8F32MM        | Armv9.2  |           |    X    | FP8 to Single-Precision Matrix Multiplication in Streaming SVE mode (removed)
| FEAT_SSVE_FEXPA          | Armv9.4  |           |    X    | Streaming FEXPA instruction
| FEAT_SSVE_FP8DOT2        | Armv9.2  |           |    X    | SVE FP8 2-way dot product to half-precision inst in Streaming SVE
| FEAT_SSVE_FP8DOT4        | Armv9.2  |           |    X    | SVE2 FP8 4-way dot product to single-precision inst in Streaming SVE
| FEAT_SSVE_FP8FMA         | Armv9.2  |           |    X    | SVE2 FP8 multiply-accumulate to half-precision and single-precision inst in Streaming SVE
| FEAT_STEP2               | Armv9.4  | Armv9.5   |    X    | Enhanced Software Step Extension
| FEAT_SVE                 | Armv8.2  |           |    X    | Scalable Vector Extension
| FEAT_SVE2                | Armv9.0  |           |    X    | SVE version 2
| FEAT_SVE2p1              | Armv9.2  |           |    X    | Scalable Vector Extension version 2.1
| FEAT_SVE2p2              | Armv9.5  |           |    X    | Scalable Vector Extensions version 2.2
| FEAT_SVE_AES             | Armv9.0  |           |    X    | SVE AES instructions
| FEAT_SVE_AES2            | Armv9.5  |           |    X    | SVE multi-vector AES and 128-bit polynomial multiply long instructions
| FEAT_SVE_B16B16          | Armv9.2  |           |    X    | Non-widening BFloat16 to BFloat16 arithmetic for SVE2.1
| FEAT_SVE_BFSCALE         | Armv9.2  |           |    X    | BFloat16 Floating-Point Adjust Exponent
| FEAT_SVE_BitPerm         | Armv9.0  |           |    X    | SVE Bit Permute
| FEAT_SVE_F16F32MM        | Armv9.2  |           |    X    | SVE Half-Precision to Single-Precision Matrix Multiplication
| FEAT_SVE_PMULL128        | Armv9.0  |           |    X    | SVE PMULL instructions
| FEAT_SVE_SHA3            | Armv9.0  |           |    X    | SVE SHA-3 instructions
| FEAT_SVE_SM4             | Armv9.0  |           |    X    | SVE SM4 instructions
| FEAT_SYSINSTR128         | Armv9.3  |           |    X    | 128-bit System instructions
| FEAT_SYSREG128           | Armv9.3  |           |    X    | 128-bit System registers
| FEAT_TCR2                | Armv8.0  | Armv8.9   |    X    | Extension to TCR_ELx
| FEAT_TGran16K            | Armv8.0  |           |    X    | Support for 16KB memory translation granule size at stage 2
| FEAT_TGran4K             | Armv8.0  |           |    X    | Support for 4KB memory translation granule size at stage 2
| FEAT_TGran64K            | Armv8.0  |           |    X    | Support for 64KB memory translation granule size at stage 2
| FEAT_THE                 | Armv8.8  |           |    X    | Translation Hardening Extension
| FEAT_TIDCP1              | Armv8.7  | Armv8.8   |    X    | EL0 use of IMPLEMENTATION DEFINED functionality
| FEAT_TLBIOS              | Armv8.3  | Armv8.4   |    X    | TLB invalidate outer-shared instructions
| FEAT_TLBIRANGE           | Armv8.3  | Armv8.4   |    X    | TLB range invalidate range instructions
| FEAT_TLBIW               | Armv9.4  |           |    X    | TLBI VMALL for Dirty state
| FEAT_TME                 | Armv9.0  |           |    X    | Transactional Memory Extension
| FEAT_TRBE                | Armv9.0  |           |    X    | Trace Buffer Extension
| FEAT_TRBE_EXC            | Armv9.5  |           |    X    | Trace Buffer Profiling exception extension
| FEAT_TRBE_EXT            | Armv9.3  |           |    X    | Represents TRBE external mode
| FEAT_TRBE_MPAM           | Armv9.3  |           |    X    | Trace Buffer MPAM extensions
| FEAT_TRBEv1p1            | Armv9.5  |           |    X    | Trace Buffer Extension version 1.1
| FEAT_TRC_EXT             | Armv8.0  |           |   n/a   | Trace external registers
| FEAT_TRC_SR              | Armv8.0  |           |    X    | Trace System registers
| FEAT_TRF                 | Armv8.3  |           |    X    | Self hosted Trace Extensions
| FEAT_TTCNP               | Armv8.1  | Armv8.2   |    X    | Common not private translations
| FEAT_TTL                 | Armv8.3  | Armv8.4   |    X    | Translation Table Level
| FEAT_TTST                | Armv8.3  |           |    X    | Small translation tables
| FEAT_TWED                | Armv8.5  |           |    X    | Delayed trapping of WFE
| FEAT_UAO                 | Armv8.1  | Armv8.2   |    X    | Unprivileged Access Override control
| FEAT_UINJ                | Armv9.0  | Armv9.6   |    X    | Injection of Undefined Instruction exceptions
| FEAT_VHE                 | Armv8.0  |           |    X    | Virtualization Host Extensions
| FEAT_VMID16              | Armv8.0  |           |    X    | 16-bit VMID
| FEAT_VPIPT               | Armv8.2  |           |    X    | VMID-aware PIPT instruction cache (removed)
| FEAT_WFxT                | Armv8.6  | Armv8.7   |    X    | WFE and WFI instructions with timeout
| FEAT_XNX                 | Armv8.1  |           |    X    | Execute-never control distinction by Exception level at stage 2
| FEAT_XS                  | Armv8.6  | Armv8.7   |    X    | XS attribute
<!-- @AUTOGEN-END -->
