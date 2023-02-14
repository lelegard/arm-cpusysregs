//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// A class describing the features of an Arm64 processor.
//
//----------------------------------------------------------------------------

#pragma once
#include "regaccess.h"

//
// A class describing the features of an Arm64 processor.
//
class ArmFeatures
{
public:
    // Constructor.
    ArmFeatures();
    ArmFeatures(RegAccess&);

    // Load features from the system registers.
    bool load(RegAccess&);
    bool isLoaded() const { return _loaded; }

    // Load features using direct access to system registers in userland.
    // Linux: Mostly works thanks to mrs emulation. However, some fields are incorrectly reported.
    // macOS: Illegal instruction exception.
    void loadDirect();

    // Individual fields in the system registers.

    int ID_AA64ISAR0_EL1_RNDR() const { return (int)(_aa64isar0 >> 60) & 0x0F; }
    int ID_AA64ISAR0_EL1_TLB() const { return (int)(_aa64isar0 >> 56) & 0x0F; }
    int ID_AA64ISAR0_EL1_TS() const { return (int)(_aa64isar0 >> 52) & 0x0F; }
    int ID_AA64ISAR0_EL1_FHM() const { return (int)(_aa64isar0 >> 48) & 0x0F; }
    int ID_AA64ISAR0_EL1_DP() const { return (int)(_aa64isar0 >> 44) & 0x0F; }
    int ID_AA64ISAR0_EL1_SM4() const { return (int)(_aa64isar0 >> 40) & 0x0F; }
    int ID_AA64ISAR0_EL1_SM3() const { return (int)(_aa64isar0 >> 36) & 0x0F; }
    int ID_AA64ISAR0_EL1_SHA3() const { return (int)(_aa64isar0 >> 32) & 0x0F; }
    int ID_AA64ISAR0_EL1_RDM() const { return (int)(_aa64isar0 >> 28) & 0x0F; }
    int ID_AA64ISAR0_EL1_TME() const { return (int)(_aa64isar0 >> 24) & 0x0F; }
    int ID_AA64ISAR0_EL1_Atomic() const { return (int)(_aa64isar0 >> 20) & 0x0F; }
    int ID_AA64ISAR0_EL1_CRC32() const { return (int)(_aa64isar0 >> 16) & 0x0F; }
    int ID_AA64ISAR0_EL1_SHA2() const { return (int)(_aa64isar0 >> 12) & 0x0F; }
    int ID_AA64ISAR0_EL1_SHA1() const { return (int)(_aa64isar0 >> 8) & 0x0F; }
    int ID_AA64ISAR0_EL1_AES() const { return (int)(_aa64isar0 >> 4) & 0x0F; }

    int ID_AA64ISAR1_EL1_LS64() const { return (int)(_aa64isar1 >> 60) & 0x0F; }
    int ID_AA64ISAR1_EL1_XS() const { return (int)(_aa64isar1 >> 56) & 0x0F; }
    int ID_AA64ISAR1_EL1_I18MM() const { return (int)(_aa64isar1 >> 52) & 0x0F; }
    int ID_AA64ISAR1_EL1_DGH() const { return (int)(_aa64isar1 >> 48) & 0x0F; }
    int ID_AA64ISAR1_EL1_BF16() const { return (int)(_aa64isar1 >> 44) & 0x0F; }
    int ID_AA64ISAR1_EL1_SPECRES() const { return (int)(_aa64isar1 >> 40) & 0x0F; }
    int ID_AA64ISAR1_EL1_SB() const { return (int)(_aa64isar1 >> 36) & 0x0F; }
    int ID_AA64ISAR1_EL1_FRINTTS() const { return (int)(_aa64isar1 >> 32) & 0x0F; }
    int ID_AA64ISAR1_EL1_GPI() const { return (int)(_aa64isar1 >> 28) & 0x0F; }
    int ID_AA64ISAR1_EL1_GPA() const { return (int)(_aa64isar1 >> 24) & 0x0F; }
    int ID_AA64ISAR1_EL1_LRCPC() const { return (int)(_aa64isar1 >> 20) & 0x0F; }
    int ID_AA64ISAR1_EL1_FCMA() const { return (int)(_aa64isar1 >> 16) & 0x0F; }
    int ID_AA64ISAR1_EL1_JSCVT() const { return (int)(_aa64isar1 >> 12) & 0x0F; }
    int ID_AA64ISAR1_EL1_API() const { return (int)(_aa64isar1 >> 8) & 0x0F; }
    int ID_AA64ISAR1_EL1_APA() const { return (int)(_aa64isar1 >> 4) & 0x0F; }
    int ID_AA64ISAR1_EL1_DPB() const { return (int)(_aa64isar1) & 0x0F; }

    int ID_AA64ISAR2_EL1_PAC_frac() const { return (int)(_aa64isar2 >> 24) & 0x0F; }
    int ID_AA64ISAR2_EL1_BC() const { return (int)(_aa64isar2 >> 20) & 0x0F; }
    int ID_AA64ISAR2_EL1_MOPS() const { return (int)(_aa64isar2 >> 16) & 0x0F; }
    int ID_AA64ISAR2_EL1_APA3() const { return (int)(_aa64isar2 >> 12) & 0x0F; }
    int ID_AA64ISAR2_EL1_GPA3() const { return (int)(_aa64isar2 >> 8) & 0x0F; }
    int ID_AA64ISAR2_EL1_RPRES() const { return (int)(_aa64isar2 >> 4) & 0x0F; }
    int ID_AA64ISAR2_EL1_WFxT() const { return (int)(_aa64isar2) & 0x0F; }

    int ID_AA64PFR0_EL1_CSV3() const { return (int)(_aa64pfr0 >> 60) & 0x0F; }
    int ID_AA64PFR0_EL1_CSV2() const { return (int)(_aa64pfr0 >> 56) & 0x0F; }
    int ID_AA64PFR0_EL1_RME() const { return (int)(_aa64pfr0 >> 52) & 0x0F; }
    int ID_AA64PFR0_EL1_DIT() const { return (int)(_aa64pfr0 >> 48) & 0x0F; }
    int ID_AA64PFR0_EL1_AMU() const { return (int)(_aa64pfr0 >> 44) & 0x0F; }
    int ID_AA64PFR0_EL1_MPAM() const { return (int)(_aa64pfr0 >> 40) & 0x0F; }
    int ID_AA64PFR0_EL1_SEL2() const { return (int)(_aa64pfr0 >> 36) & 0x0F; }
    int ID_AA64PFR0_EL1_SVE() const { return (int)(_aa64pfr0 >> 32) & 0x0F; }
    int ID_AA64PFR0_EL1_RAS() const { return (int)(_aa64pfr0 >> 28) & 0x0F; }
    int ID_AA64PFR0_EL1_GIC() const { return (int)(_aa64pfr0 >> 24) & 0x0F; }
    int ID_AA64PFR0_EL1_AdvSIMD() const { return (int)(_aa64pfr0 >> 20) & 0x0F; }
    int ID_AA64PFR0_EL1_FP() const { return (int)(_aa64pfr0 >> 16) & 0x0F; }
    int ID_AA64PFR0_EL1_EL3() const { return (int)(_aa64pfr0 >> 12) & 0x0F; }
    int ID_AA64PFR0_EL1_EL2() const { return (int)(_aa64pfr0 >> 8) & 0x0F; }
    int ID_AA64PFR0_EL1_EL1() const { return (int)(_aa64pfr0 >> 4) & 0x0F; }
    int ID_AA64PFR0_EL1_EL0() const { return (int)(_aa64pfr0) & 0x0F; }

    int ID_AA64PFR1_EL1_NMI() const { return (int)(_aa64pfr1 >> 36) & 0x0F; }
    int ID_AA64PFR1_EL1_CSV2_frac() const { return (int)(_aa64pfr1 >> 32) & 0x0F; }
    int ID_AA64PFR1_EL1_RNDR_trap() const { return (int)(_aa64pfr1 >> 28) & 0x0F; }
    int ID_AA64PFR1_EL1_SME() const { return (int)(_aa64pfr1 >> 24) & 0x0F; }
    int ID_AA64PFR1_EL1_MPAM_frac() const { return (int)(_aa64pfr1 >> 16) & 0x0F; }
    int ID_AA64PFR1_EL1_RAS_frac() const { return (int)(_aa64pfr1 >> 12) & 0x0F; }
    int ID_AA64PFR1_EL1_MTE() const { return (int)(_aa64pfr1 >> 8) & 0x0F; }
    int ID_AA64PFR1_EL1_SSBS() const { return (int)(_aa64pfr1 >> 4) & 0x0F; }
    int ID_AA64PFR1_EL1_BT() const { return (int)(_aa64pfr1) & 0x0F; }

    int ID_AA64DFR0_EL1_HPMN0() const { return (int)(_aa64dfr0 >> 60) & 0x0F; }
    int ID_AA64DFR0_EL1_BRBE() const { return (int)(_aa64dfr0 >> 52) & 0x0F; }
    int ID_AA64DFR0_EL1_MTPMU() const { return (int)(_aa64dfr0 >> 48) & 0x0F; }
    int ID_AA64DFR0_EL1_TraceBuffer() const { return (int)(_aa64dfr0 >> 44) & 0x0F; }
    int ID_AA64DFR0_EL1_TraceFilt() const { return (int)(_aa64dfr0 >> 40) & 0x0F; }
    int ID_AA64DFR0_EL1_DoubleLock() const { return (int)(_aa64dfr0 >> 36) & 0x0F; }
    int ID_AA64DFR0_EL1_PMSVer() const { return (int)(_aa64dfr0 >> 32) & 0x0F; }
    int ID_AA64DFR0_EL1_CTX_CMPs() const { return (int)(_aa64dfr0 >> 28) & 0x0F; }
    int ID_AA64DFR0_EL1_WRPs() const { return (int)(_aa64dfr0 >> 20) & 0x0F; }
    int ID_AA64DFR0_EL1_BRPs() const { return (int)(_aa64dfr0 >> 12) & 0x0F; }
    int ID_AA64DFR0_EL1_PMUVer() const { return (int)(_aa64dfr0 >> 8) & 0x0F; }
    int ID_AA64DFR0_EL1_TraceVer() const { return (int)(_aa64dfr0 >> 4) & 0x0F; }
    int ID_AA64DFR0_EL1_DebugVer() const { return (int)(_aa64dfr0) & 0x0F; }

    int ID_AA64MMFR0_EL1_ECV() const { return (int)(_aa64mmfr0 >> 60) & 0x0F; }
    int ID_AA64MMFR0_EL1_FGT() const { return (int)(_aa64mmfr0 >> 56) & 0x0F; }
    int ID_AA64MMFR0_EL1_ExS() const { return (int)(_aa64mmfr0 >> 44) & 0x0F; }
    int ID_AA64MMFR0_EL1_TGran4_2() const { return (int)(_aa64mmfr0 >> 40) & 0x0F; }
    int ID_AA64MMFR0_EL1_TGran64_2() const { return (int)(_aa64mmfr0 >> 36) & 0x0F; }
    int ID_AA64MMFR0_EL1_TGran16_2() const { return (int)(_aa64mmfr0 >> 32) & 0x0F; }
    int ID_AA64MMFR0_EL1_TGran4() const { return (int)(_aa64mmfr0 >> 28) & 0x0F; }
    int ID_AA64MMFR0_EL1_TGran64() const { return (int)(_aa64mmfr0 >> 24) & 0x0F; }
    int ID_AA64MMFR0_EL1_TGran16() const { return (int)(_aa64mmfr0 >> 20) & 0x0F; }
    int ID_AA64MMFR0_EL1_BigEndEL0() const { return (int)(_aa64mmfr0 >> 16) & 0x0F; }
    int ID_AA64MMFR0_EL1_SNSMem() const { return (int)(_aa64mmfr0 >> 12) & 0x0F; }
    int ID_AA64MMFR0_EL1_BigEnd() const { return (int)(_aa64mmfr0 >> 8) & 0x0F; }
    int ID_AA64MMFR0_EL1_ASIDBits() const { return (int)(_aa64mmfr0 >> 4) & 0x0F; }
    int ID_AA64MMFR0_EL1_PARange() const { return (int)(_aa64mmfr0) & 0x0F; }

    int ID_AA64MMFR1_EL1_CMOW() const { return (int)(_aa64mmfr1 >> 56) & 0x0F; }
    int ID_AA64MMFR1_EL1_TIDCP1() const { return (int)(_aa64mmfr1 >> 52) & 0x0F; }
    int ID_AA64MMFR1_EL1_nTLBPA() const { return (int)(_aa64mmfr1 >> 48) & 0x0F; }
    int ID_AA64MMFR1_EL1_AFP() const { return (int)(_aa64mmfr1 >> 44) & 0x0F; }
    int ID_AA64MMFR1_EL1_HCX() const { return (int)(_aa64mmfr1 >> 40) & 0x0F; }
    int ID_AA64MMFR1_EL1_ETS() const { return (int)(_aa64mmfr1 >> 36) & 0x0F; }
    int ID_AA64MMFR1_EL1_TWED() const { return (int)(_aa64mmfr1 >> 32) & 0x0F; }
    int ID_AA64MMFR1_EL1_XNX() const { return (int)(_aa64mmfr1 >> 28) & 0x0F; }
    int ID_AA64MMFR1_EL1_SpecSEI() const { return (int)(_aa64mmfr1 >> 24) & 0x0F; }
    int ID_AA64MMFR1_EL1_PAN() const { return (int)(_aa64mmfr1 >> 20) & 0x0F; }
    int ID_AA64MMFR1_EL1_LO() const { return (int)(_aa64mmfr1 >> 16) & 0x0F; }
    int ID_AA64MMFR1_EL1_HPDS() const { return (int)(_aa64mmfr1 >> 12) & 0x0F; }
    int ID_AA64MMFR1_EL1_VH() const { return (int)(_aa64mmfr1 >> 8) & 0x0F; }
    int ID_AA64MMFR1_EL1_VMIDBits() const { return (int)(_aa64mmfr1 >> 4) & 0x0F; }
    int ID_AA64MMFR1_EL1_HAFDBS() const { return (int)(_aa64mmfr1) & 0x0F; }

    int ID_AA64MMFR2_EL1_E0PD() const { return (int)(_aa64mmfr2 >> 60) & 0x0F; }
    int ID_AA64MMFR2_EL1_EVT() const { return (int)(_aa64mmfr2 >> 56) & 0x0F; }
    int ID_AA64MMFR2_EL1_BBM() const { return (int)(_aa64mmfr2 >> 52) & 0x0F; }
    int ID_AA64MMFR2_EL1_TTL() const { return (int)(_aa64mmfr2 >> 48) & 0x0F; }
    int ID_AA64MMFR2_EL1_FWB() const { return (int)(_aa64mmfr2 >> 40) & 0x0F; }
    int ID_AA64MMFR2_EL1_IDS() const { return (int)(_aa64mmfr2 >> 36) & 0x0F; }
    int ID_AA64MMFR2_EL1_AT() const { return (int)(_aa64mmfr2 >> 32) & 0x0F; }
    int ID_AA64MMFR2_EL1_ST() const { return (int)(_aa64mmfr2 >> 28) & 0x0F; }
    int ID_AA64MMFR2_EL1_NV() const { return (int)(_aa64mmfr2 >> 24) & 0x0F; }
    int ID_AA64MMFR2_EL1_CCIDX() const { return (int)(_aa64mmfr2 >> 20) & 0x0F; }
    int ID_AA64MMFR2_EL1_VARange() const { return (int)(_aa64mmfr2 >> 16) & 0x0F; }
    int ID_AA64MMFR2_EL1_IESB() const { return (int)(_aa64mmfr2 >> 12) & 0x0F; }
    int ID_AA64MMFR2_EL1_LSM() const { return (int)(_aa64mmfr2 >> 8) & 0x0F; }
    int ID_AA64MMFR2_EL1_UAO() const { return (int)(_aa64mmfr2 >> 4) & 0x0F; }
    int ID_AA64MMFR2_EL1_CnP() const { return (int)(_aa64mmfr2) & 0x0F; }

    int ID_AA64SMFR0_EL1_FA64() const { return (int)(_aa64smfr0 >> 63) & 0x01; }
    int ID_AA64SMFR0_EL1_SMEver() const { return (int)(_aa64smfr0 >> 56) & 0x0F; }
    int ID_AA64SMFR0_EL1_I16I64() const { return (int)(_aa64smfr0 >> 52) & 0x0F; }
    int ID_AA64SMFR0_EL1_F64F64() const { return (int)(_aa64smfr0 >> 48) & 0x01; }
    int ID_AA64SMFR0_EL1_I8I32() const { return (int)(_aa64smfr0 >> 36) & 0x0F; }
    int ID_AA64SMFR0_EL1_F16F32() const { return (int)(_aa64smfr0 >> 25) & 0x01; }
    int ID_AA64SMFR0_EL1_B16F32() const { return (int)(_aa64smfr0 >> 34) & 0x01; }
    int ID_AA64SMFR0_EL1_F32F32() const { return (int)(_aa64smfr0 >> 32) & 0x01; }

    int ID_AA64ZFR0_EL1_F64MM() const { return (int)(_aa64zfr0 >> 56) & 0x0F; }
    int ID_AA64ZFR0_EL1_F32MM() const { return (int)(_aa64zfr0 >> 52) & 0x0F; }
    int ID_AA64ZFR0_EL1_I8MM() const { return (int)(_aa64zfr0 >> 44) & 0x0F; }
    int ID_AA64ZFR0_EL1_SM4() const { return (int)(_aa64zfr0 >> 40) & 0x0F; }
    int ID_AA64ZFR0_EL1_SHA3() const { return (int)(_aa64zfr0 >> 32) & 0x0F; }
    int ID_AA64ZFR0_EL1_BF16() const { return (int)(_aa64zfr0 >> 20) & 0x0F; }
    int ID_AA64ZFR0_EL1_BitPerm() const { return (int)(_aa64zfr0 >> 16) & 0x0F; }
    int ID_AA64ZFR0_EL1_AES() const { return (int)(_aa64zfr0 >> 4) & 0x0F; }
    int ID_AA64ZFR0_EL1_SVEver() const { return (int)(_aa64zfr0) & 0x0F; }

    int CTR_EL0_TminLine() const { return (int)(_ctr >> 32) & 0x3F; }
    int CTR_EL0_DIC() const { return (int)(_ctr >> 29) & 0x01; }
    int CTR_EL0_IDC() const { return (int)(_ctr >> 28) & 0x01; }
    int CTR_EL0_CWG() const { return (int)(_ctr >> 24) & 0x0F; }
    int CTR_EL0_ERG() const { return (int)(_ctr >> 20) & 0x0F; }
    int CTR_EL0_DminLine() const { return (int)(_ctr >> 16) & 0x0F; }
    int CTR_EL0_L1Ip() const { return (int)(_ctr >> 14) & 0x03; }
    int CTR_EL0_IminLine() const { return (int)(_ctr) & 0x0F; }

    int TCR_EL1_TCMA1() const { return (int)(_tcr >> 58) & 0x01; }
    int TCR_EL1_TCMA0() const { return (int)(_tcr >> 57) & 0x01; }
    int TCR_EL1_TBID1() const { return (int)(_tcr >> 52) & 0x01; }
    int TCR_EL1_TBID0() const { return (int)(_tcr >> 51) & 0x01; }
    int TCR_EL1_TBI1() const { return (int)(_tcr >> 38) & 0x01; }
    int TCR_EL1_TBI0() const { return (int)(_tcr >> 37) & 0x01; }
    int TCR_EL1_AS() const { return (int)(_tcr >> 36) & 0x01; }
    int TCR_EL1_T1SZ() const { return (int)(_tcr >> 16) & 0x3F; }
    int TCR_EL1_T0SZ() const { return (int)(_tcr) & 0x3F; }

    int TRCDEVARCH_ARCHITECT() const { return (int)(_trcdevarch >> 21) & 0x07FF; }
    int TRCDEVARCH_PRESENT() const { return (int)(_trcdevarch >> 20) & 0x01; }
    int TRCDEVARCH_REVISION() const { return (int)(_trcdevarch >> 16) & 0x0F; }
    int TRCDEVARCH_ARCHVER() const { return (int)(_trcdevarch >> 12) & 0x0F; }
    int TRCDEVARCH_ARCHPART() const { return (int)(_trcdevarch) & 0x0FFF; }

    int PMMIR_THWIDTH() const { return (int)(_pmmir >> 20) & 0x0F; }
    int PMMIR_BUS_WIDTH() const { return (int)(_pmmir >> 16) & 0x0F; }
    int PMMIR_BUS_SLOTS() const { return (int)(_pmmir >> 8) & 0x0FF; }
    int PMMIR_SLOTS() const { return (int)(_pmmir) & 0x0FF; }

    // Processor features, using same names as Arm Architecture Reference Manual.
    // Implemented level: Armv9-A (ref manual rev I.a)

    bool FEAT_AES() const { return ID_AA64ISAR0_EL1_AES() >= 1; }
    bool FEAT_AFP() const { return ID_AA64MMFR1_EL1_AFP() >= 1; }
    bool FEAT_AMUv1() const { return ID_AA64PFR0_EL1_AMU() >= 1; }
    bool FEAT_AMUv1p1() const { return ID_AA64PFR0_EL1_AMU() >= 2; }
    bool FEAT_BBM() const { return ID_AA64MMFR2_EL1_BBM() >= 1; }
    bool FEAT_BF16() const { return ID_AA64ISAR1_EL1_BF16() >= 1 || ID_AA64ZFR0_EL1_BF16() >= 1; }
    bool FEAT_BRBE() const { return ID_AA64DFR0_EL1_BRBE() >= 1; }
    bool FEAT_BRBEv1p1() const { return ID_AA64DFR0_EL1_BRBE() >= 2; }
    bool FEAT_BTI() const { return ID_AA64PFR1_EL1_BT() >= 1; }
    bool FEAT_CCIDX() const { return ID_AA64MMFR2_EL1_CCIDX() >= 1; }
    bool FEAT_CMOW() const { return ID_AA64MMFR1_EL1_CMOW() >= 1; }
    //   FEAT_CNTSC => see CNTID, I5.7.8, not a system register
    bool FEAT_CONSTPACFIELD() const { return ID_AA64ISAR2_EL1_PAC_frac() >= 1; }
    bool FEAT_CRC32() const { return ID_AA64ISAR0_EL1_CRC32() >= 1; }
    bool FEAT_CSV2() const { return ID_AA64PFR0_EL1_CSV2() >= 1; }
    bool FEAT_CSV2_1p1() const { return ID_AA64PFR1_EL1_CSV2_frac() >= 1; }
    bool FEAT_CSV2_1p2() const { return ID_AA64PFR1_EL1_CSV2_frac() >= 2; }
    bool FEAT_CSV2_2() const { return ID_AA64PFR0_EL1_CSV2() >= 2; }
    bool FEAT_CSV2_3() const { return ID_AA64PFR0_EL1_CSV2() >= 3; }
    bool FEAT_CSV3() const { return ID_AA64PFR0_EL1_CSV3() >= 1; }
    bool FEAT_Debugv8p2() const { return ID_AA64DFR0_EL1_DebugVer() >= 8; }
    bool FEAT_Debugv8p4() const { return ID_AA64DFR0_EL1_DebugVer() >= 9; }
    bool FEAT_Debugv8p8() const { return ID_AA64DFR0_EL1_DebugVer() >= 10; }
    bool FEAT_DGH() const { return ID_AA64ISAR1_EL1_DGH() >= 1; }
    bool FEAT_DIT() const { return ID_AA64PFR0_EL1_DIT() >= 1; }
    //   FEAT_DoPD => see EDDEVID, H9.2.20, external debug register
    bool FEAT_DotProd() const { return ID_AA64ISAR0_EL1_DP() >= 1; }
    bool FEAT_DoubleFault() const { return ID_AA64PFR0_EL1_RAS() >= 2; }
    bool FEAT_DoubleLock() const { return ID_AA64DFR0_EL1_DoubleLock() != 15; }
    bool FEAT_DPB() const { return ID_AA64ISAR1_EL1_DPB() >= 1; }
    bool FEAT_DPB2() const { return ID_AA64ISAR1_EL1_DPB() >= 2; }
    bool FEAT_E0PD() const { return ID_AA64MMFR2_EL1_E0PD() >= 1; }
    bool FEAT_EBF16() const { return ID_AA64ISAR1_EL1_BF16() >= 2 || ID_AA64ZFR0_EL1_BF16() >= 2; }
    bool FEAT_ECV() const { return ID_AA64MMFR0_EL1_ECV() >= 1; }
    bool FEAT_EPAC() const { return ID_AA64ISAR1_EL1_API() >= 2 || ID_AA64ISAR1_EL1_APA() >= 2 || ID_AA64ISAR2_EL1_APA3() >= 2; }
    bool FEAT_ETE() const { return ID_AA64DFR0_EL1_TraceVer() >= 1; }
    bool FEAT_ETEv1p1() const { return TRCDEVARCH_REVISION() >= 1; }
    bool FEAT_ETEv1p2() const { return TRCDEVARCH_REVISION() >= 2; }
    bool FEAT_ETS() const { return ID_AA64MMFR1_EL1_ETS() >= 1; }
    bool FEAT_EVT() const { return ID_AA64MMFR2_EL1_EVT() >= 1; }
    bool FEAT_ExS() const { return ID_AA64MMFR0_EL1_ExS() >= 1; }
    bool FEAT_F32MM() const { return ID_AA64ZFR0_EL1_F32MM() >= 1; }
    bool FEAT_F64MM() const { return ID_AA64ZFR0_EL1_F64MM() >= 1; }
    bool FEAT_FCMA() const { return ID_AA64ISAR1_EL1_FCMA() >= 1; }
    bool FEAT_FGT() const { return ID_AA64MMFR0_EL1_FGT() >= 1; }
    bool FEAT_FHM() const { return ID_AA64ISAR0_EL1_FHM() >= 1; }
    bool FEAT_FlagM() const { return ID_AA64ISAR0_EL1_TS() >= 1; }
    bool FEAT_FlagM2() const { return ID_AA64ISAR0_EL1_TS() >= 2; }
    bool FEAT_FP() const { return ID_AA64PFR0_EL1_FP() < 15; }
    bool FEAT_FP16() const { return ID_AA64PFR0_EL1_FP() >= 1 && ID_AA64PFR0_EL1_FP() < 15; }
    bool FEAT_FPAC() const { return ID_AA64ISAR1_EL1_API() >= 4 || ID_AA64ISAR1_EL1_APA() >= 4 || ID_AA64ISAR2_EL1_APA3() >= 4; }
    bool FEAT_FPACCOMBINE() const { return ID_AA64ISAR1_EL1_API() >= 5 || ID_AA64ISAR1_EL1_APA() >= 5 || ID_AA64ISAR2_EL1_APA3() >= 5; }
    bool FEAT_FRINTTS() const { return ID_AA64ISAR1_EL1_FRINTTS() >= 1; }
    bool FEAT_HAFDBS() const { return ID_AA64MMFR1_EL1_HAFDBS() >= 1; }
    bool FEAT_HBC() const { return ID_AA64ISAR2_EL1_BC() >= 1; }
    bool FEAT_HCX() const { return ID_AA64MMFR1_EL1_HCX() >= 1; }
    bool FEAT_HPDS() const { return ID_AA64MMFR1_EL1_HPDS() >= 1; }
    bool FEAT_HPDS2() const { return ID_AA64MMFR1_EL1_HPDS() >= 2; }
    bool FEAT_HPMN0() const { return ID_AA64DFR0_EL1_HPMN0() >= 1; }
    bool FEAT_I8MM() const { return ID_AA64ZFR0_EL1_I8MM() >= 1; }
    bool FEAT_IDST() const { return ID_AA64MMFR2_EL1_IDS() >= 1; }
    bool FEAT_IESB() const { return ID_AA64MMFR2_EL1_IESB() >= 1; }
    bool FEAT_JSCVT() const { return ID_AA64ISAR1_EL1_JSCVT() >= 1; }
    bool FEAT_LOR() const { return ID_AA64MMFR1_EL1_LO() >= 1; }
    bool FEAT_LPA() const { return ID_AA64MMFR0_EL1_PARange() >= 6; }
    bool FEAT_LPA2() const { return ID_AA64MMFR0_EL1_TGran4_2() >= 3 || ID_AA64MMFR0_EL1_TGran16_2() >= 3; }
    bool FEAT_LRCPC() const { return ID_AA64ISAR1_EL1_LRCPC() >= 1; }
    bool FEAT_LRCPC2() const { return ID_AA64ISAR1_EL1_LRCPC() >= 2; }
    bool FEAT_LS64() const { return ID_AA64ISAR1_EL1_LS64() >= 1; }
    bool FEAT_LS64_V() const { return ID_AA64ISAR1_EL1_LS64() >= 2; }
    bool FEAT_LS64_ACCDATA() const { return ID_AA64ISAR1_EL1_LS64() >= 3; }
    bool FEAT_LSE() const { return ID_AA64ISAR0_EL1_Atomic() >= 2; }
    bool FEAT_LSE2() const { return ID_AA64MMFR2_EL1_AT() >= 1; }
    bool FEAT_LVA() const { return ID_AA64MMFR2_EL1_VARange() >= 1; }
    bool FEAT_LSMAOC() const { return ID_AA64MMFR2_EL1_LSM() >= 1; }
    bool FEAT_MOPS() const { return ID_AA64ISAR2_EL1_MOPS() >= 1; }
    bool FEAT_MPAM() const { return ID_AA64PFR0_EL1_MPAM() >= 1 || ID_AA64PFR1_EL1_MPAM_frac() >= 1; }
    bool FEAT_MTE() const { return ID_AA64PFR1_EL1_MTE() >= 1; }
    bool FEAT_MTE2() const { return ID_AA64PFR1_EL1_MTE() >= 2; }
    bool FEAT_MTE3() const { return ID_AA64PFR1_EL1_MTE() >= 3; }
    bool FEAT_MTPMU() const { return ID_AA64DFR0_EL1_MTPMU() >= 1; }
    bool FEAT_NMI() const { return ID_AA64PFR1_EL1_NMI() >= 1; }
    bool FEAT_nTLBPA() const { return ID_AA64MMFR1_EL1_nTLBPA() >= 1; }
    bool FEAT_NV() const { return ID_AA64MMFR2_EL1_NV() >= 1; }
    bool FEAT_NV2() const { return ID_AA64MMFR2_EL1_NV() >= 2; }
    bool FEAT_PACIMP() const { return ID_AA64ISAR1_EL1_GPI() >= 1 || ID_AA64ISAR1_EL1_API() >= 1; }
    bool FEAT_PACQARMA3() const { return ID_AA64ISAR2_EL1_GPA3() >= 1 || ID_AA64ISAR2_EL1_APA3() >= 1; }
    bool FEAT_PACQARMA5() const { return ID_AA64ISAR1_EL1_GPA() >= 1 || ID_AA64ISAR1_EL1_APA() >= 1; }
    bool FEAT_PAN() const { return ID_AA64MMFR1_EL1_PAN() >= 1; }
    bool FEAT_PAN2() const { return ID_AA64MMFR1_EL1_PAN() >= 2; }
    bool FEAT_PAN3() const { return ID_AA64MMFR1_EL1_PAN() >= 3; }
    bool FEAT_PAuth() const { return ID_AA64ISAR1_EL1_API() >= 1 || ID_AA64ISAR1_EL1_APA() >= 1 || ID_AA64ISAR2_EL1_APA3() >= 1; }
    bool FEAT_PAuth2() const { return ID_AA64ISAR1_EL1_API() >= 3 || ID_AA64ISAR1_EL1_APA() >= 3 || ID_AA64ISAR2_EL1_APA3() >= 3; }
    //   FEAT_PCSRv8p2 => see EDDEVID, H9.2.20, external debug register
    bool FEAT_PMUv3() const { return ID_AA64DFR0_EL1_PMUVer() >= 1 && ID_AA64DFR0_EL1_PMUVer() < 15; }
    bool FEAT_PMUv3p1() const { return ID_AA64DFR0_EL1_PMUVer() >= 4 && ID_AA64DFR0_EL1_PMUVer() < 15; }
    bool FEAT_PMUv3p4() const { return ID_AA64DFR0_EL1_PMUVer() >= 5 && ID_AA64DFR0_EL1_PMUVer() < 15; }
    bool FEAT_PMUv3p5() const { return ID_AA64DFR0_EL1_PMUVer() >= 6 && ID_AA64DFR0_EL1_PMUVer() < 15; }
    bool FEAT_PMUv3p7() const { return ID_AA64DFR0_EL1_PMUVer() >= 7 && ID_AA64DFR0_EL1_PMUVer() < 15; }
    bool FEAT_PMUv3p8() const { return ID_AA64DFR0_EL1_PMUVer() >= 8 && ID_AA64DFR0_EL1_PMUVer() < 15; }
    bool FEAT_PMUv3_TH() const { return PMMIR_THWIDTH() >= 1; }
    bool FEAT_PMULL() const { return ID_AA64ISAR0_EL1_AES() >= 2; }
    bool FEAT_RAS() const { return ID_AA64PFR0_EL1_RAS() >= 1; }
    bool FEAT_RASv1p1() const { return ID_AA64PFR1_EL1_RAS_frac() >= 1; }
    bool FEAT_RDM() const { return ID_AA64ISAR0_EL1_RDM() >= 1; }
    bool FEAT_RME() const { return ID_AA64PFR0_EL1_RME() >= 1; }
    bool FEAT_RNG() const { return ID_AA64ISAR0_EL1_RNDR() >= 1; }
    bool FEAT_RNG_TRAP() const { return ID_AA64PFR1_EL1_RNDR_trap() >= 1; }
    bool FEAT_RPRES() const { return ID_AA64ISAR2_EL1_RPRES() >= 1; }
    bool FEAT_S2FWB() const { return ID_AA64MMFR2_EL1_FWB() >= 1; }
    bool FEAT_SB() const { return ID_AA64ISAR1_EL1_SB() >= 1; }
    bool FEAT_SEL2() const { return ID_AA64PFR0_EL1_SEL2() >= 1; }
    bool FEAT_SHA1() const { return ID_AA64ISAR0_EL1_SHA1() >= 1; }
    bool FEAT_SHA256() const { return ID_AA64ISAR0_EL1_SHA2() >= 1; }
    bool FEAT_SHA512() const { return ID_AA64ISAR0_EL1_SHA2() >= 2; }
    bool FEAT_SHA3() const { return ID_AA64ISAR0_EL1_SHA3() >= 1; }
    bool FEAT_SM3() const { return ID_AA64ISAR0_EL1_SM3() >= 1; }
    bool FEAT_SM4() const { return ID_AA64ISAR0_EL1_SM4() >= 1; }
    bool FEAT_SME() const { return ID_AA64PFR1_EL1_SME() >= 1; }
    bool FEAT_SME_FA64() const { return ID_AA64SMFR0_EL1_FA64() >= 1; }
    bool FEAT_SME_F64F64() const { return ID_AA64SMFR0_EL1_F64F64() >= 1; }
    bool FEAT_SME_I16I64() const { return ID_AA64SMFR0_EL1_I16I64() >= 1; }
    bool FEAT_SPE() const { return ID_AA64DFR0_EL1_PMSVer() >= 1; }
    bool FEAT_SPEv1p1() const { return ID_AA64DFR0_EL1_PMSVer() >= 2; }
    bool FEAT_SPEv1p2() const { return ID_AA64DFR0_EL1_PMSVer() >= 3; }
    bool FEAT_SPEv1p3() const { return ID_AA64DFR0_EL1_PMSVer() >= 4; }
    bool FEAT_SPECRES() const { return ID_AA64ISAR1_EL1_SPECRES() >= 1; }
    bool FEAT_SSBS() const { return ID_AA64PFR1_EL1_SSBS() >= 1; }
    bool FEAT_SSBS2() const { return ID_AA64PFR1_EL1_SSBS() >= 2; }
    bool FEAT_SVE() const { return ID_AA64PFR0_EL1_SVE() >= 1; }
    bool FEAT_SVE2() const { return ID_AA64ZFR0_EL1_SVEver() >= 1; }
    bool FEAT_SVE_AES() const { return ID_AA64ZFR0_EL1_AES() >= 1; }
    bool FEAT_SVE_BitPerm() const { return ID_AA64ZFR0_EL1_BitPerm() >= 1; }
    bool FEAT_SVE_PMULL128() const { return ID_AA64ZFR0_EL1_AES() >= 2; }
    bool FEAT_SVE_SHA3() const { return ID_AA64ZFR0_EL1_SHA3() >= 1; }
    bool FEAT_SVE_SM4() const { return ID_AA64ZFR0_EL1_SM4() >= 1; }
    bool FEAT_TIDCP1() const { return ID_AA64MMFR1_EL1_TIDCP1() >= 1; }
    bool FEAT_TLBIOS() const { return ID_AA64ISAR0_EL1_TLB() >= 1; }
    bool FEAT_TLBIRANGE() const { return ID_AA64ISAR0_EL1_TLB() >= 2; }
    bool FEAT_TME() const { return ID_AA64ISAR0_EL1_TME() >= 1; }
    bool FEAT_TRBE() const { return ID_AA64DFR0_EL1_TraceBuffer() >= 1; }
    bool FEAT_TRF() const { return ID_AA64DFR0_EL1_TraceFilt() >= 1; }
    bool FEAT_TTCNP() const { return ID_AA64MMFR2_EL1_CnP() >= 1; }
    bool FEAT_TTL() const { return ID_AA64MMFR2_EL1_TTL() >= 1; }
    bool FEAT_TTST() const { return ID_AA64MMFR2_EL1_ST() >= 1; }
    bool FEAT_TWED() const { return ID_AA64MMFR1_EL1_TWED() >= 1; }
    bool FEAT_UAO() const { return ID_AA64MMFR2_EL1_UAO() >= 1; }
    bool FEAT_VHE() const { return ID_AA64MMFR1_EL1_VH() >= 1 || ID_AA64DFR0_EL1_DebugVer() >= 7; }
    bool FEAT_VMID16() const { return ID_AA64MMFR1_EL1_VMIDBits() == 2; }
    bool FEAT_VPIPT() const { return CTR_EL0_L1Ip() == 0; }
    bool FEAT_WFxT() const { return ID_AA64ISAR2_EL1_WFxT() >= 2; }
    bool FEAT_XNX() const { return ID_AA64MMFR1_EL1_XNX() >= 1; }
    bool FEAT_XS() const { return ID_AA64ISAR1_EL1_XS() >= 1; }

    // Synthetic features of the processor.

    // Supports PACGA in addition to PACIx and PACDx.
    bool hasPACGA() const { return ID_AA64ISAR1_EL1_GPI() >= 1 || ID_AA64ISAR1_EL1_GPA() >= 1 || ID_AA64ISAR2_EL1_GPA3() >= 1; }

    // Check if address tagging is enabled. Variant when two VA ranges are used.
    bool addressTaggingEnabled() const { return FEAT_MTE() && TCR_EL1_TBI0(); }
    bool AddressTaggingEnabled0() const { return FEAT_MTE() && TCR_EL1_TBI0(); } // lower VA range
    bool AddressTaggingEnabled1() const { return FEAT_MTE() && TCR_EL1_TBI1(); } // upper VA range

private:
    bool      _loaded;
    csr_u64_t _aa64isar0;
    csr_u64_t _aa64isar1;
    csr_u64_t _aa64isar2;
    csr_u64_t _aa64pfr0;
    csr_u64_t _aa64pfr1;
    csr_u64_t _aa64dfr0;
    csr_u64_t _aa64mmfr0;
    csr_u64_t _aa64mmfr1;
    csr_u64_t _aa64mmfr2;
    csr_u64_t _aa64smfr0;
    csr_u64_t _aa64zfr0;
    csr_u64_t _ctr;
    csr_u64_t _tcr;
    csr_u64_t _trcdevarch;
    csr_u64_t _pmmir;
};
