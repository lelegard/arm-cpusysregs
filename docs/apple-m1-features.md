# Arm features in the Apple M1 and M2 chips

**Contents:**

* [Checking the presence of Arm features on a CPU](#checking-the-presence-of-arm-features-on-a-cpu)
* [Complete list of Arm features in the Apple M1](#complete-list-of-arm-features-in-the-apple-m1)
  * [Features comparison between the M1 and the M2](#features-comparison-between-the-m1-and-the-m2)

## Checking the presence of Arm features on a CPU

At a given level of Arm architecture, several features are mandatory or optional. A CPU core may or may not implement them. In the Arm architecture reference manual, they are usually named `FEAT_xxx`.

Using system registers (usually accessible at EL1 only), it is possible to check the presence of each feature. Consequently, the exact list of features is known to the kernel only. Userland applications cannot read these registers and cannot determine the exact list of features.

Depending on the operating system, it is possible to query a limited subset of the supported Arm features from userland using various commands or system calls:

- On Linux: use `cat /proc/cpuinfo` on the command line or the `getauxval()` library function.
- On macOS: use `sysctl`, either the command line tool or the system call of the same name.

The C++ class `UserFeatures` and the program `demo-userfeatures` in this project demonstrate this.

To get the complete list of features from userland, we need a specialized kernel module (Linux) or kernel extension (macOS) to read all relevant system registers, such as done in this project. The command line `sysregs` calls the kernel module to fetch all relevant information and displays them.

## Complete list of Arm features in the Apple M1

The following table lists all Arm features which are implemented - or not - in the Apple M1, based on the command `sysregs -s`.

~~~
FEAT_ADERR ........ no     FEAT_GCS .......... no     FEAT_RME .......... no
FEAT_AES .......... yes    FEAT_HAFDBS ....... no     FEAT_RNG .......... no
FEAT_AFP .......... no     FEAT_HAFT ......... no     FEAT_RNG_TRAP ..... no
FEAT_AIE .......... no     FEAT_HBC .......... no     FEAT_RPRES ........ no
FEAT_AMUv1 ........ no     FEAT_HCX .......... no     FEAT_RPRFM ........ no
FEAT_AMUv1p1 ...... no     FEAT_HPDS ......... yes    FEAT_S1PIE ........ no
FEAT_ANERR ........ no     FEAT_HPDS2 ........ yes    FEAT_S1POE ........ no
FEAT_BBM .......... no     FEAT_HPMN0 ........ no     FEAT_S2FWB ........ yes
FEAT_BF16 ......... no     FEAT_I8MM ......... no     FEAT_S2PIE ........ no
FEAT_BRBE ......... no     FEAT_IDST ......... yes    FEAT_S2POE ........ no
FEAT_BRBEv1p1 ..... no     FEAT_IESB ......... yes    FEAT_SB ........... yes
FEAT_BTI .......... no     FEAT_JSCVT ........ yes    FEAT_SCTLR2 ....... no
FEAT_CCIDX ........ no     FEAT_LOR .......... yes    FEAT_SEL2 ......... no
FEAT_CLRBHB ....... no     FEAT_LPA .......... no     FEAT_SHA1 ......... yes
FEAT_CMOW ......... no     FEAT_LPA2 ......... no     FEAT_SHA256 ....... yes
FEAT_CONSTPACFIELD  no     FEAT_LRCPC ........ yes    FEAT_SHA3 ......... yes
FEAT_CRC32 ........ yes    FEAT_LRCPC2 ....... yes    FEAT_SHA512 ....... yes
FEAT_CSSC ......... no     FEAT_LS64 ......... no     FEAT_SM3 .......... no
FEAT_CSV2 ......... yes    FEAT_LS64_ACCDATA . no     FEAT_SM4 .......... no
FEAT_CSV2_1p1 ..... no     FEAT_LS64_V ....... no     FEAT_SME .......... no
FEAT_CSV2_1p2 ..... no     FEAT_LSE .......... yes    FEAT_SME_F64F64 ... no
FEAT_CSV2_2 ....... no     FEAT_LSE2 ......... yes    FEAT_SME_FA64 ..... no
FEAT_CSV2_3 ....... no     FEAT_LSMAOC ....... no     FEAT_SME_I16I64 ... no
FEAT_CSV3 ......... yes    FEAT_LVA .......... no     FEAT_SPE .......... no
FEAT_Debugv8p2 .... yes    FEAT_LVA3 ......... no     FEAT_SPECRES ...... yes
FEAT_Debugv8p4 .... yes    FEAT_MEC .......... no     FEAT_SPEv1p1 ...... no
FEAT_Debugv8p8 .... no     FEAT_MOPS ......... no     FEAT_SPEv1p2 ...... no
FEAT_DGH .......... no     FEAT_MPAM ......... no     FEAT_SPEv1p3 ...... no
FEAT_DIT .......... yes    FEAT_MTE .......... no     FEAT_SSBS ......... yes
FEAT_DotProd ...... yes    FEAT_MTE2 ......... no     FEAT_SSBS2 ........ yes
FEAT_DoubleFault .. no     FEAT_MTE3 ......... no     FEAT_SVE .......... no
FEAT_DoubleFault2 . no     FEAT_MTE4 ......... no     FEAT_SVE2 ......... no
FEAT_DoubleLock ... yes    FEAT_MTPMU ........ no     FEAT_SVE_AES ...... no
FEAT_DPB .......... yes    FEAT_NMI .......... no     FEAT_SVE_BitPerm .. no
FEAT_DPB2 ......... yes    FEAT_nTLBPA ....... no     FEAT_SVE_PMULL128 . no
FEAT_E0PD ......... yes    FEAT_NV ........... no     FEAT_SVE_SHA3 ..... no
FEAT_EBF16 ........ no     FEAT_NV2 .......... no     FEAT_SVE_SM4 ...... no
FEAT_ECBHB ........ no     FEAT_PACIMP ....... yes    FEAT_SYSINSTR128 .. no
FEAT_ECV .......... no     FEAT_PACQARMA3 .... no     FEAT_SYSREG128 .... no
FEAT_EPAC ......... yes    FEAT_PACQARMA5 .... no     FEAT_TCR2 ......... no
FEAT_ETE .......... no     FEAT_PAN .......... yes    FEAT_THE .......... no
FEAT_ETEv1p1 ...... no     FEAT_PAN2 ......... yes    FEAT_TIDCP1 ....... no
FEAT_ETEv1p2 ...... no     FEAT_PAN3 ......... no     FEAT_TLBIOS ....... yes
FEAT_ETS .......... no     FEAT_PAuth ........ yes    FEAT_TLBIRANGE .... yes
FEAT_EVT .......... yes    FEAT_PAuth2 ....... no     FEAT_TME .......... no
FEAT_ExS .......... yes    FEAT_PFAR ......... no     FEAT_TRBE ......... no
FEAT_F32MM ........ no     FEAT_PMULL ........ yes    FEAT_TRF .......... no
FEAT_F64MM ........ no     FEAT_PMUv3 ........ no     FEAT_TTCNP ........ yes
FEAT_FCMA ......... yes    FEAT_PMUv3p1 ...... no     FEAT_TTL .......... yes
FEAT_FGT .......... no     FEAT_PMUv3p4 ...... no     FEAT_TTST ......... no
FEAT_FHM .......... yes    FEAT_PMUv3p5 ...... no     FEAT_TWED ......... no
FEAT_FlagM ........ yes    FEAT_PMUv3p7 ...... no     FEAT_UAO .......... yes
FEAT_FlagM2 ....... yes    FEAT_PMUv3p8 ...... no     FEAT_VHE .......... yes
FEAT_FP ........... yes    FEAT_PMUv3_TH ..... no     FEAT_VMID16 ....... no
FEAT_FP16 ......... yes    FEAT_PRFMSLC ...... no     FEAT_VPIPT ........ no
FEAT_FPAC ......... no     FEAT_RAS .......... yes    FEAT_WFxT ......... no
FEAT_FPACCOMBINE .. no     FEAT_RASv1p1 ...... no     FEAT_XNX .......... yes
FEAT_FRINTTS ...... yes    FEAT_RDM .......... yes    FEAT_XS ........... no
~~~

## Features comparison between the M1 and the M2

The following table compares the features of the M1 and M2 based on the output of the command `sysctl hw.optional.arm`. Since the lists of features are not exactly the same, the two chips must use distinct types of cores.

Specifically, we can notice that the M2 implements all missing security features from the M1: BTI, PAuth2, FPAC.

| Feature      | Apple M1 | Apple M2
| :----------- | :------: | :------:
| FEAT_AES     | X        | X
| FEAT_BF16    | -        | X
| FEAT_BTI     | -        | X
| FEAT_CSV2    | X        | X
| FEAT_CSV3    | X        | X
| FEAT_DIT     | X        | X
| FEAT_DPB2    | X        | X
| FEAT_DPB     | X        | X
| FEAT_DotProd | X        | X
| FEAT_ECV     | X        | X
| FEAT_FCMA    | X        | X
| FEAT_FHM     | X        | X
| FEAT_FP16    | X        | X
| FEAT_FPAC    | -        | X
| FEAT_FRINTTS | X        | X
| FEAT_FlagM2  | X        | X
| FEAT_FlagM   | X        | X
| FEAT_I8MM    | -        | X
| FEAT_JSCVT   | X        | X
| FEAT_LRCPC2  | X        | X
| FEAT_LRCPC   | X        | X
| FEAT_LSE2    | X        | X
| FEAT_LSE     | X        | X
| FEAT_PAuth2  | -        | X
| FEAT_PAuth   | X        | X
| FEAT_PMULL   | X        | X
| FEAT_RDM     | X        | X
| FEAT_SB      | X        | X
| FEAT_SHA1    | X        | X
| FEAT_SHA256  | X        | X
| FEAT_SHA3    | X        | X
| FEAT_SHA512  | X        | X
| FEAT_SPECRES | -        | -
| FEAT_SSBS    | X        | X
| FP_SyncExceptions | X   | X
