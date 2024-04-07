# Arm features in the Apple M1 and M2 chips

**Contents:**

* [Checking the presence of Arm features on a CPU](#checking-the-presence-of-arm-features-on-a-cpu)
* [Complete list of Arm features in the Apple M1](#complete-list-of-arm-features-in-the-apple-m1)
* [Features comparison between the M1 and the M2](#features-comparison-between-the-m1-and-the-m2)

## Checking the presence of Arm features on a CPU

At a given level of Arm architecture, several features are mandatory or optional.
A CPU core may or may not implement them. In the Arm architecture reference manual,
they are usually named `FEAT_xxx`.

Using system registers (usually accessible at EL1 only), it is possible to check the
presence of each feature. Consequently, the exact list of features is known to the
kernel only. Userland applications cannot read these registers and cannot determine
the exact list of features.

Depending on the operating system, it is possible to query a limited subset of the
supported Arm features from userland using various commands or system calls:

- On Linux: use `cat /proc/cpuinfo` on the command line or the `getauxval()` library function.
- On macOS: use `sysctl`, either the command line tool or the system call of the same name.

The C++ class `UserFeatures` and the program `demo-userfeatures` in this project demonstrate this.

To get the complete list of features from userland, we need a specialized kernel
module (Linux) or kernel extension (macOS) to read all relevant system registers,
such as done in this project. The command line `sysregs` calls the kernel module
to fetch all relevant information and displays them.

## Complete list of Arm features in the Apple M1

The following table lists all Arm features which are implemented - or not - in the Apple M1,
based on the command `sysregs -s`.

~~~
FEAT_AA32BF16 ............ no	FEAT_FPAC ................ no	FEAT_PMUv3p9 ............. no
FEAT_AA32HPD ............. no	FEAT_FPACCOMBINE ......... no	FEAT_PRFMSLC ............. no
FEAT_AA32I8MM ............ no	FEAT_FRINTTS ............. yes	FEAT_RAS ................. yes
FEAT_AArch32 ............. no	FEAT_GCS ................. no	FEAT_RASv1p1 ............. no
FEAT_ABLE ................ no	FEAT_GICv3 ............... no	FEAT_RASv2 ............... no
FEAT_ADERR ............... no	FEAT_GICv4 ............... no	FEAT_RDM ................. yes
FEAT_AdvSIMD ............. yes	FEAT_GICv4p1 ............. no	FEAT_RME ................. no
FEAT_AES ................. yes	FEAT_GTG ................. yes	FEAT_RNG ................. no
FEAT_AFP ................. no	FEAT_HAFDBS .............. no	FEAT_RNG_TRAP ............ no
FEAT_AIE ................. no	FEAT_HAFT ................ no	FEAT_RPRES ............... no
FEAT_AMUv1 ............... no	FEAT_HBC ................. no	FEAT_RPRFM ............... no
FEAT_AMUv1p1 ............. no	FEAT_HCX ................. no	FEAT_S1PIE ............... no
FEAT_ANERR ............... no	FEAT_HPDS ................ yes	FEAT_S1POE ............... no
FEAT_B16B16 .............. no	FEAT_HPDS2 ............... yes	FEAT_S2FWB ............... yes
FEAT_BBM ................. no	FEAT_HPMN0 ............... no	FEAT_S2PIE ............... no
FEAT_BF16 ................ no	FEAT_I8MM ................ no	FEAT_S2POE ............... no
FEAT_BRBE ................ no	FEAT_IDST ................ yes	FEAT_SB .................. yes
FEAT_BRBEv1p1 ............ no	FEAT_IESB ................ yes	FEAT_SCTLR2 .............. no
FEAT_BTI ................. no	FEAT_ITE ................. no	FEAT_SEBEP ............... no
FEAT_CCIDX ............... no	FEAT_JSCVT ............... yes	FEAT_SEL2 ................ no
FEAT_CLRBHB .............. no	FEAT_LOR ................. yes	FEAT_SHA1 ................ yes
FEAT_CMOW ................ no	FEAT_LPA ................. no	FEAT_SHA256 .............. yes
FEAT_CONSTPACFIELD ....... no	FEAT_LPA2 ................ no	FEAT_SHA3 ................ yes
FEAT_CRC32 ............... yes	FEAT_LRCPC ............... yes	FEAT_SHA512 .............. yes
FEAT_CSSC ................ no	FEAT_LRCPC2 .............. yes	FEAT_SM3 ................. no
FEAT_CSV2 ................ yes	FEAT_LRCPC3 .............. no	FEAT_SM4 ................. no
FEAT_CSV2_1p1 ............ no	FEAT_LS64 ................ no	FEAT_SME ................. no
FEAT_CSV2_1p2 ............ no	FEAT_LS64_ACCDATA ........ no	FEAT_SME2 ................ no
FEAT_CSV2_2 .............. no	FEAT_LS64_V .............. no	FEAT_SME2p1 .............. no
FEAT_CSV2_3 .............. no	FEAT_LSE ................. yes	FEAT_SME_F16F16 .......... no
FEAT_CSV3 ................ yes	FEAT_LSE128 .............. no	FEAT_SME_F64F64 .......... no
FEAT_D128 ................ no	FEAT_LSE2 ................ yes	FEAT_SME_FA64 ............ no
FEAT_Debugv8p1 ........... yes	FEAT_LSMAOC .............. no	FEAT_SME_I16I64 .......... no
FEAT_Debugv8p2 ........... yes	FEAT_LVA ................. no	FEAT_SPE ................. no
FEAT_Debugv8p4 ........... yes	FEAT_LVA3 ................ no	FEAT_SPE_CRR ............. no
FEAT_Debugv8p8 ........... no	FEAT_MEC ................. no	FEAT_SPE_FDS ............. no
FEAT_Debugv8p9 ........... no	FEAT_MOPS ................ no	FEAT_SPECRES ............. yes
FEAT_DGH ................. no	FEAT_MPAM ................ no	FEAT_SPECRES2 ............ no
FEAT_DIT ................. yes	FEAT_MPAMv0p1 ............ no	FEAT_SPEv1p1 ............. no
FEAT_DotProd ............. yes	FEAT_MPAMv1p0 ............ no	FEAT_SPEv1p2 ............. no
FEAT_DoubleFault ......... no	FEAT_MPAMv1p1 ............ no	FEAT_SPEv1p3 ............. no
FEAT_DoubleFault2 ........ no	FEAT_MTE ................. no	FEAT_SPEv1p4 ............. no
FEAT_DoubleLock .......... yes	FEAT_MTE2 ................ no	FEAT_SPMU ................ no
FEAT_DPB ................. yes	FEAT_MTE3 ................ no	FEAT_SSBS ................ yes
FEAT_DPB2 ................ yes	FEAT_MTE4 ................ no	FEAT_SSBS2 ............... yes
FEAT_E0PD ................ yes	FEAT_MTE_CANONICAL_TAGS .. no	FEAT_SVE ................. no
FEAT_EBEP ................ no	FEAT_MTE_NO_ADDRESS_TAGS . no	FEAT_SVE2 ................ no
FEAT_EBF16 ............... no	FEAT_MTE_PERM ............ no	FEAT_SVE2p1 .............. no
FEAT_ECBHB ............... no	FEAT_MTE_STORE_ONLY ...... no	FEAT_SVE_AES ............. no
FEAT_ECV ................. no	FEAT_MTE_TAGGED_FAR ...... no	FEAT_SVE_BitPerm ......... no
FEAT_EPAC ................ yes	FEAT_MTPMU ............... no	FEAT_SVE_PMULL128 ........ no
FEAT_ETE ................. no	FEAT_NMI ................. no	FEAT_SVE_SHA3 ............ no
FEAT_ETEv1p1 ............. no	FEAT_nTLBPA .............. no	FEAT_SVE_SM4 ............. no
FEAT_ETEv1p2 ............. no	FEAT_NV .................. no	FEAT_SYSINSTR128 ......... no
FEAT_ETEv1p3 ............. no	FEAT_NV2 ................. no	FEAT_SYSREG128 ........... no
FEAT_ETMv4 ............... no	FEAT_PACIMP .............. yes	FEAT_TCR2 ................ no
FEAT_ETMv4p1 ............. no	FEAT_PACQARMA3 ........... no	FEAT_THE ................. no
FEAT_ETMv4p2 ............. no	FEAT_PACQARMA5 ........... no	FEAT_TIDCP1 .............. no
FEAT_ETMv4p3 ............. no	FEAT_PAN ................. yes	FEAT_TLBIOS .............. yes
FEAT_ETMv4p4 ............. no	FEAT_PAN2 ................ yes	FEAT_TLBIRANGE ........... yes
FEAT_ETMv4p5 ............. no	FEAT_PAN3 ................ no	FEAT_TME ................. no
FEAT_ETMv4p6 ............. no	FEAT_PAuth ............... yes	FEAT_TRBE ................ no
FEAT_ETS ................. no	FEAT_PAuth2 .............. no	FEAT_TRF ................. no
FEAT_EVT ................. yes	FEAT_PFAR ................ no	FEAT_TTCNP ............... yes
FEAT_ExS ................. yes	FEAT_PMULL ............... yes	FEAT_TTL ................. yes
FEAT_F32MM ............... no	FEAT_PMUv3 ............... no	FEAT_TTST ................ no
FEAT_F64MM ............... no	FEAT_PMUv3_EDGE .......... no	FEAT_TWED ................ no
FEAT_FCMA ................ yes	FEAT_PMUv3_ICNTR ......... no	FEAT_UAO ................. yes
FEAT_FGT ................. no	FEAT_PMUv3_SS ............ no	FEAT_VHE ................. yes
FEAT_FGT2 ................ no	FEAT_PMUv3_TH ............ no	FEAT_VMID16 .............. no
FEAT_FHM ................. yes	FEAT_PMUv3p1 ............. no	FEAT_VPIPT ............... no
FEAT_FlagM ............... yes	FEAT_PMUv3p4 ............. no	FEAT_WFxT ................ no
FEAT_FlagM2 .............. yes	FEAT_PMUv3p5 ............. no	FEAT_XNX ................. yes
FEAT_FP .................. yes	FEAT_PMUv3p7 ............. no	FEAT_XS .................. no
FEAT_FP16 ................ yes	FEAT_PMUv3p8 ............. no
~~~

## Complete list of Arm features in the Apple M3

The following table lists all Arm features which are implemented - or not - in the Apple M3,
based on the command `sysregs -s`.

~~~
FEAT_AA32BF16 ............ no	FEAT_FPAC ................ yes	FEAT_PMUv3p9 ............. no
FEAT_AA32HPD ............. no	FEAT_FPACCOMBINE ......... no	FEAT_PRFMSLC ............. no
FEAT_AA32I8MM ............ no	FEAT_FRINTTS ............. yes	FEAT_RAS ................. yes
FEAT_AArch32 ............. no	FEAT_GCS ................. no	FEAT_RASv1p1 ............. no
FEAT_ABLE ................ no	FEAT_GICv3 ............... no	FEAT_RASv2 ............... no
FEAT_ADERR ............... no	FEAT_GICv4 ............... no	FEAT_RDM ................. yes
FEAT_AdvSIMD ............. yes	FEAT_GICv4p1 ............. no	FEAT_RME ................. no
FEAT_AES ................. yes	FEAT_GTG ................. yes	FEAT_RNG ................. no
FEAT_AFP ................. yes	FEAT_HAFDBS .............. no	FEAT_RNG_TRAP ............ no
FEAT_AIE ................. no	FEAT_HAFT ................ no	FEAT_RPRES ............... yes
FEAT_AMUv1 ............... no	FEAT_HBC ................. no	FEAT_RPRFM ............... no
FEAT_AMUv1p1 ............. no	FEAT_HCX ................. yes	FEAT_S1PIE ............... no
FEAT_ANERR ............... no	FEAT_HPDS ................ yes	FEAT_S1POE ............... no
FEAT_B16B16 .............. no	FEAT_HPDS2 ............... yes	FEAT_S2FWB ............... yes
FEAT_BBM ................. no	FEAT_HPMN0 ............... no	FEAT_S2PIE ............... no
FEAT_BF16 ................ yes	FEAT_I8MM ................ no	FEAT_S2POE ............... no
FEAT_BRBE ................ no	FEAT_IDST ................ yes	FEAT_SB .................. yes
FEAT_BRBEv1p1 ............ no	FEAT_IESB ................ yes	FEAT_SCTLR2 .............. no
FEAT_BTI ................. yes	FEAT_ITE ................. no	FEAT_SEBEP ............... no
FEAT_CCIDX ............... no	FEAT_JSCVT ............... yes	FEAT_SEL2 ................ no
FEAT_CLRBHB .............. no	FEAT_LOR ................. yes	FEAT_SHA1 ................ yes
FEAT_CMOW ................ no	FEAT_LPA ................. no	FEAT_SHA256 .............. yes
FEAT_CONSTPACFIELD ....... no	FEAT_LPA2 ................ no	FEAT_SHA3 ................ yes
FEAT_CRC32 ............... yes	FEAT_LRCPC ............... yes	FEAT_SHA512 .............. yes
FEAT_CSSC ................ no	FEAT_LRCPC2 .............. yes	FEAT_SM3 ................. no
FEAT_CSV2 ................ yes	FEAT_LRCPC3 .............. no	FEAT_SM4 ................. no
FEAT_CSV2_1p1 ............ yes	FEAT_LS64 ................ no	FEAT_SME ................. no
FEAT_CSV2_1p2 ............ no	FEAT_LS64_ACCDATA ........ no	FEAT_SME2 ................ no
FEAT_CSV2_2 .............. no	FEAT_LS64_V .............. no	FEAT_SME2p1 .............. no
FEAT_CSV2_3 .............. no	FEAT_LSE ................. yes	FEAT_SME_F16F16 .......... no
FEAT_CSV3 ................ yes	FEAT_LSE128 .............. no	FEAT_SME_F64F64 .......... no
FEAT_D128 ................ no	FEAT_LSE2 ................ yes	FEAT_SME_FA64 ............ no
FEAT_Debugv8p1 ........... yes	FEAT_LSMAOC .............. no	FEAT_SME_I16I64 .......... no
FEAT_Debugv8p2 ........... yes	FEAT_LVA ................. no	FEAT_SPE ................. no
FEAT_Debugv8p4 ........... yes	FEAT_LVA3 ................ no	FEAT_SPE_CRR ............. no
FEAT_Debugv8p8 ........... no	FEAT_MEC ................. no	FEAT_SPE_FDS ............. no
FEAT_Debugv8p9 ........... no	FEAT_MOPS ................ no	FEAT_SPECRES ............. yes
FEAT_DGH ................. no	FEAT_MPAM ................ no	FEAT_SPECRES2 ............ no
FEAT_DIT ................. yes	FEAT_MPAMv0p1 ............ no	FEAT_SPEv1p1 ............. no
FEAT_DotProd ............. yes	FEAT_MPAMv1p0 ............ no	FEAT_SPEv1p2 ............. no
FEAT_DoubleFault ......... no	FEAT_MPAMv1p1 ............ no	FEAT_SPEv1p3 ............. no
FEAT_DoubleFault2 ........ no	FEAT_MTE ................. no	FEAT_SPEv1p4 ............. no
FEAT_DoubleLock .......... yes	FEAT_MTE2 ................ no	FEAT_SPMU ................ no
FEAT_DPB ................. yes	FEAT_MTE3 ................ no	FEAT_SSBS ................ yes
FEAT_DPB2 ................ yes	FEAT_MTE4 ................ no	FEAT_SSBS2 ............... yes
FEAT_E0PD ................ yes	FEAT_MTE_CANONICAL_TAGS .. no	FEAT_SVE ................. no
FEAT_EBEP ................ no	FEAT_MTE_NO_ADDRESS_TAGS . no	FEAT_SVE2 ................ no
FEAT_EBF16 ............... no	FEAT_MTE_PERM ............ no	FEAT_SVE2p1 .............. no
FEAT_ECBHB ............... no	FEAT_MTE_STORE_ONLY ...... no	FEAT_SVE_AES ............. no
FEAT_ECV ................. yes	FEAT_MTE_TAGGED_FAR ...... no	FEAT_SVE_BitPerm ......... no
FEAT_EPAC ................ yes	FEAT_MTPMU ............... no	FEAT_SVE_PMULL128 ........ no
FEAT_ETE ................. no	FEAT_NMI ................. no	FEAT_SVE_SHA3 ............ no
FEAT_ETEv1p1 ............. no	FEAT_nTLBPA .............. no	FEAT_SVE_SM4 ............. no
FEAT_ETEv1p2 ............. no	FEAT_NV .................. yes	FEAT_SYSINSTR128 ......... no
FEAT_ETEv1p3 ............. no	FEAT_NV2 ................. yes	FEAT_SYSREG128 ........... no
FEAT_ETMv4 ............... no	FEAT_PACIMP .............. yes	FEAT_TCR2 ................ no
FEAT_ETMv4p1 ............. no	FEAT_PACQARMA3 ........... no	FEAT_THE ................. no
FEAT_ETMv4p2 ............. no	FEAT_PACQARMA5 ........... no	FEAT_TIDCP1 .............. no
FEAT_ETMv4p3 ............. no	FEAT_PAN ................. yes	FEAT_TLBIOS .............. yes
FEAT_ETMv4p4 ............. no	FEAT_PAN2 ................ yes	FEAT_TLBIRANGE ........... yes
FEAT_ETMv4p5 ............. no	FEAT_PAN3 ................ yes	FEAT_TME ................. no
FEAT_ETMv4p6 ............. no	FEAT_PAuth ............... yes	FEAT_TRBE ................ no
FEAT_ETS ................. yes	FEAT_PAuth2 .............. yes	FEAT_TRF ................. no
FEAT_EVT ................. yes	FEAT_PFAR ................ no	FEAT_TTCNP ............... yes
FEAT_ExS ................. yes	FEAT_PMULL ............... yes	FEAT_TTL ................. yes
FEAT_F32MM ............... no	FEAT_PMUv3 ............... no	FEAT_TTST ................ no
FEAT_F64MM ............... no	FEAT_PMUv3_EDGE .......... no	FEAT_TWED ................ yes
FEAT_FCMA ................ yes	FEAT_PMUv3_ICNTR ......... no	FEAT_UAO ................. yes
FEAT_FGT ................. yes	FEAT_PMUv3_SS ............ no	FEAT_VHE ................. yes
FEAT_FGT2 ................ no	FEAT_PMUv3_TH ............ no	FEAT_VMID16 .............. no
FEAT_FHM ................. yes	FEAT_PMUv3p1 ............. no	FEAT_VPIPT ............... no
FEAT_FlagM ............... yes	FEAT_PMUv3p4 ............. no	FEAT_WFxT ................ no
FEAT_FlagM2 .............. yes	FEAT_PMUv3p5 ............. no	FEAT_XNX ................. yes
FEAT_FP .................. yes	FEAT_PMUv3p7 ............. no	FEAT_XS .................. no
FEAT_FP16 ................ yes	FEAT_PMUv3p8 ............. no
~~~

## Features comparison between the M1, M2, M3

The following table compares the features of the M1, M2, and M3 based on the output of
the command `sysctl hw.optional.arm`. Since the lists of features are not exactly
the same, the M1 and M2 chips must use distinct types of cores.

Specifically, we can notice that the M2 implements all missing security features
from the M1: BTI, PAuth2, FPAC.

| Feature      | Apple M1 | Apple M2 | Apple M3 |
| :----------- | :------: | :------: | :------: |
| FEAT_AES     | X        | X        | X        |
| FEAT_BF16    | -        | X        | X        |
| FEAT_BTI     | -        | X        | X        |
| FEAT_CSV2    | X        | X        | X        |
| FEAT_CSV3    | X        | X        | X        |
| FEAT_DIT     | X        | X        | X        |
| FEAT_DPB2    | X        | X        | X        |
| FEAT_DPB     | X        | X        | X        |
| FEAT_DotProd | X        | X        | X        |
| FEAT_ECV     | X        | X        | X        |
| FEAT_FCMA    | X        | X        | X        |
| FEAT_FHM     | X        | X        | X        |
| FEAT_FP16    | X        | X        | X        |
| FEAT_FPAC    | -        | X        | X        |
| FEAT_FRINTTS | X        | X        | X        |
| FEAT_FlagM2  | X        | X        | X        |
| FEAT_FlagM   | X        | X        | X        |
| FEAT_I8MM    | -        | X        | X        |
| FEAT_JSCVT   | X        | X        | X        |
| FEAT_LRCPC2  | X        | X        | X        |
| FEAT_LRCPC   | X        | X        | X        |
| FEAT_LSE2    | X        | X        | X        |
| FEAT_LSE     | X        | X        | X        |
| FEAT_PAuth2  | -        | X        | X        |
| FEAT_PAuth   | X        | X        | X        |
| FEAT_PMULL   | X        | X        | X        |
| FEAT_RDM     | X        | X        | X        |
| FEAT_SB      | X        | X        | X        |
| FEAT_SHA1    | X        | X        | X        |
| FEAT_SHA256  | X        | X        | X        |
| FEAT_SHA3    | X        | X        | X        |
| FEAT_SHA512  | X        | X        | X        |
| FEAT_SPECRES | -        | -        | -        |
| FEAT_SSBS    | X        | X        | X        |
| FP_SyncExceptions | X   | X        | X        |
