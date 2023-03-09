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

    // Clear contents of all loaded registers.
    void clear();

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

    int ID_AA64ISAR2_EL1_CSSC() const { return (int)(_aa64isar2 >> 52) & 0x0F; }
    int ID_AA64ISAR2_EL1_RPRFM() const { return (int)(_aa64isar2 >> 48) & 0x0F; }
    int ID_AA64ISAR2_EL1_PRFMSLC() const { return (int)(_aa64isar2 >> 40) & 0x0F; }
    int ID_AA64ISAR2_EL1_SYSINSTR_128() const { return (int)(_aa64isar2 >> 36) & 0x0F; }
    int ID_AA64ISAR2_EL1_SYSREG_128() const { return (int)(_aa64isar2 >> 32) & 0x0F; }
    int ID_AA64ISAR2_EL1_CLRBHB() const { return (int)(_aa64isar2 >> 28) & 0x0F; }
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

    int ID_AA64PFR1_EL1_PFAR() const { return (int)(_aa64pfr1 >> 60) & 0x0F; }
    int ID_AA64PFR1_EL1_DF2() const { return (int)(_aa64pfr1 >> 56) & 0x0F; }
    int ID_AA64PFR1_EL1_MTEX() const { return (int)(_aa64pfr1 >> 52) & 0x0F; }
    int ID_AA64PFR1_EL1_THE() const { return (int)(_aa64pfr1 >> 48) & 0x0F; }
    int ID_AA64PFR1_EL1_GCS() const { return (int)(_aa64pfr1 >> 44) & 0x0F; }
    int ID_AA64PFR1_EL1_MTE_frac() const { return (int)(_aa64pfr1 >> 40) & 0x0F; }
    int ID_AA64PFR1_EL1_NMI() const { return (int)(_aa64pfr1 >> 36) & 0x0F; }
    int ID_AA64PFR1_EL1_CSV2_frac() const { return (int)(_aa64pfr1 >> 32) & 0x0F; }
    int ID_AA64PFR1_EL1_RNDR_trap() const { return (int)(_aa64pfr1 >> 28) & 0x0F; }
    int ID_AA64PFR1_EL1_SME() const { return (int)(_aa64pfr1 >> 24) & 0x0F; }
    int ID_AA64PFR1_EL1_MPAM_frac() const { return (int)(_aa64pfr1 >> 16) & 0x0F; }
    int ID_AA64PFR1_EL1_RAS_frac() const { return (int)(_aa64pfr1 >> 12) & 0x0F; }
    int ID_AA64PFR1_EL1_MTE() const { return (int)(_aa64pfr1 >> 8) & 0x0F; }
    int ID_AA64PFR1_EL1_SSBS() const { return (int)(_aa64pfr1 >> 4) & 0x0F; }
    int ID_AA64PFR1_EL1_BT() const { return (int)(_aa64pfr1) & 0x0F; }

    int ID_AA64PFR2_EL1_MTEFAR() const { return (int)(_aa64pfr2 >> 8) & 0x0F; }
    int ID_AA64PFR2_EL1_MTESTOREONLY() const { return (int)(_aa64pfr2 >> 4) & 0x0F; }
    int ID_AA64PFR2_EL1_MTEPERM() const { return (int)(_aa64pfr2) & 0x0F; }

    int ID_AA64DFR0_EL1_HPMN0() const { return (int)(_aa64dfr0 >> 60) & 0x0F; }
    int ID_AA64DFR0_EL1_ExtTrcBuff() const { return (int)(_aa64dfr0 >> 56) & 0x0F; }
    int ID_AA64DFR0_EL1_BRBE() const { return (int)(_aa64dfr0 >> 52) & 0x0F; }
    int ID_AA64DFR0_EL1_MTPMU() const { return (int)(_aa64dfr0 >> 48) & 0x0F; }
    int ID_AA64DFR0_EL1_TraceBuffer() const { return (int)(_aa64dfr0 >> 44) & 0x0F; }
    int ID_AA64DFR0_EL1_TraceFilt() const { return (int)(_aa64dfr0 >> 40) & 0x0F; }
    int ID_AA64DFR0_EL1_DoubleLock() const { return (int)(_aa64dfr0 >> 36) & 0x0F; }
    int ID_AA64DFR0_EL1_PMSVer() const { return (int)(_aa64dfr0 >> 32) & 0x0F; }
    int ID_AA64DFR0_EL1_CTX_CMPs() const { return (int)(_aa64dfr0 >> 28) & 0x0F; }
    int ID_AA64DFR0_EL1_SEBEP() const { return (int)(_aa64dfr0 >> 24) & 0x0F; }
    int ID_AA64DFR0_EL1_WRPs() const { return (int)(_aa64dfr0 >> 20) & 0x0F; }
    int ID_AA64DFR0_EL1_PMSS() const { return (int)(_aa64dfr0 >> 16) & 0x0F; }
    int ID_AA64DFR0_EL1_BRPs() const { return (int)(_aa64dfr0 >> 12) & 0x0F; }
    int ID_AA64DFR0_EL1_PMUVer() const { return (int)(_aa64dfr0 >> 8) & 0x0F; }
    int ID_AA64DFR0_EL1_TraceVer() const { return (int)(_aa64dfr0 >> 4) & 0x0F; }
    int ID_AA64DFR0_EL1_DebugVer() const { return (int)(_aa64dfr0) & 0x0F; }

    int ID_AA64DFR1_EL1_ABL_CMPs() const { return (int)(_aa64dfr1 >> 56) & 0xFF; }
    int ID_AA64DFR1_EL1_EBEP() const { return (int)(_aa64dfr1 >> 48) & 0x0F; }
    int ID_AA64DFR1_EL1_ITE() const { return (int)(_aa64dfr1 >> 44) & 0x0F; }
    int ID_AA64DFR1_EL1_ABLE() const { return (int)(_aa64dfr1 >> 40) & 0x0F; }
    int ID_AA64DFR1_EL1_PMICNTR() const { return (int)(_aa64dfr1 >> 36) & 0x0F; }
    int ID_AA64DFR1_EL1_SPMU() const { return (int)(_aa64dfr1 >> 32) & 0x0F; }
    int ID_AA64DFR1_EL1_CTX_CMPs() const { return (int)(_aa64dfr1 >> 24) & 0xFF; }
    int ID_AA64DFR1_EL1_WRPs() const { return (int)(_aa64dfr1 >> 16) & 0xFF; }
    int ID_AA64DFR1_EL1_BRPs() const { return (int)(_aa64dfr1 >> 8) & 0xFF; }
    int ID_AA64DFR1_EL1_SYSPMUID() const { return (int)(_aa64dfr1) & 0xFF; }

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

    int ID_AA64MMFR1_EL1_ECBHB() const { return (int)(_aa64mmfr1 >> 60) & 0x0F; }
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

    int ID_AA64MMFR3_EL1_Spec_FPACC() const { return (int)(_aa64mmfr3 >> 60) & 0x0F; }
    int ID_AA64MMFR3_EL1_ADERR() const { return (int)(_aa64mmfr3 >> 56) & 0x0F; }
    int ID_AA64MMFR3_EL1_SDERR() const { return (int)(_aa64mmfr3 >> 52) & 0x0F; }
    int ID_AA64MMFR3_EL1_ANERR() const { return (int)(_aa64mmfr3 >> 44) & 0x0F; }
    int ID_AA64MMFR3_EL1_SNERR() const { return (int)(_aa64mmfr3 >> 40) & 0x0F; }
    int ID_AA64MMFR3_EL1_D128_2() const { return (int)(_aa64mmfr3 >> 36) & 0x0F; }
    int ID_AA64MMFR3_EL1_D128() const { return (int)(_aa64mmfr3 >> 32) & 0x0F; }
    int ID_AA64MMFR3_EL1_MEC() const { return (int)(_aa64mmfr3 >> 28) & 0x0F; }
    int ID_AA64MMFR3_EL1_AIE() const { return (int)(_aa64mmfr3 >> 24) & 0x0F; }
    int ID_AA64MMFR3_EL1_S2POE() const { return (int)(_aa64mmfr3 >> 20) & 0x0F; }
    int ID_AA64MMFR3_EL1_S1POE() const { return (int)(_aa64mmfr3 >> 16) & 0x0F; }
    int ID_AA64MMFR3_EL1_S2PIE() const { return (int)(_aa64mmfr3 >> 12) & 0x0F; }
    int ID_AA64MMFR3_EL1_S1PIE() const { return (int)(_aa64mmfr3 >> 8) & 0x0F; }
    int ID_AA64MMFR3_EL1_SCTLRX() const { return (int)(_aa64mmfr3 >> 4) & 0x0F; }
    int ID_AA64MMFR3_EL1_TCRX() const { return (int)(_aa64mmfr3) & 0x0F; }

    int ID_AA64MMFR4_EL1_EIESB() const { return (int)(_aa64mmfr4 >> 4) & 0x0F; }

    int ID_AA64SMFR0_EL1_FA64() const { return (int)(_aa64smfr0 >> 63) & 0x01; }
    int ID_AA64SMFR0_EL1_SMEver() const { return (int)(_aa64smfr0 >> 56) & 0x0F; }
    int ID_AA64SMFR0_EL1_I16I64() const { return (int)(_aa64smfr0 >> 52) & 0x0F; }
    int ID_AA64SMFR0_EL1_F64F64() const { return (int)(_aa64smfr0 >> 48) & 0x01; }
    int ID_AA64SMFR0_EL1_I16I32() const { return (int)(_aa64smfr0 >> 44) & 0x0F; }
    int ID_AA64SMFR0_EL1_B16B16() const { return (int)(_aa64smfr0 >> 43) & 0x01; }
    int ID_AA64SMFR0_EL1_F16F16() const { return (int)(_aa64smfr0 >> 42) & 0x01; }
    int ID_AA64SMFR0_EL1_I8I32() const { return (int)(_aa64smfr0 >> 36) & 0x0F; }
    int ID_AA64SMFR0_EL1_F16F32() const { return (int)(_aa64smfr0 >> 25) & 0x01; }
    int ID_AA64SMFR0_EL1_B16F32() const { return (int)(_aa64smfr0 >> 34) & 0x01; }
    int ID_AA64SMFR0_EL1_BI32I32() const { return (int)(_aa64smfr0 >> 33) & 0x01; }
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

    int ID_ISAR0_EL1_Divide() const { return (int)(_isar0 >> 24) & 0x0F; }
    int ID_ISAR0_EL1_Debug() const { return (int)(_isar0 >> 20) & 0x0F; }
    int ID_ISAR0_EL1_Coproc() const { return (int)(_isar0 >> 16) & 0x0F; }
    int ID_ISAR0_EL1_CmpBranch() const { return (int)(_isar0 >> 12) & 0x0F; }
    int ID_ISAR0_EL1_BitField() const { return (int)(_isar0 >> 8) & 0x0F; }
    int ID_ISAR0_EL1_BitCount() const { return (int)(_isar0 >> 4) & 0x0F; }
    int ID_ISAR0_EL1_Swap() const { return (int)(_isar0) & 0x0F; }

    int ID_ISAR1_EL1_Jazelle() const { return (int)(_isar1 >> 28) & 0x0F; }
    int ID_ISAR1_EL1_Interwork() const { return (int)(_isar1 >> 24) & 0x0F; }
    int ID_ISAR1_EL1_Immediate() const { return (int)(_isar1 >> 20) & 0x0F; }
    int ID_ISAR1_EL1_IfThen() const { return (int)(_isar1 >> 16) & 0x0F; }
    int ID_ISAR1_EL1_Extend() const { return (int)(_isar1 >> 12) & 0x0F; }
    int ID_ISAR1_EL1_Except_AR() const { return (int)(_isar1 >> 8) & 0x0F; }
    int ID_ISAR1_EL1_Except() const { return (int)(_isar1 >> 4) & 0x0F; }
    int ID_ISAR1_EL1_Endian() const { return (int)(_isar1) & 0x0F; }

    int ID_ISAR2_EL1_Reversal() const { return (int)(_isar2 >> 28) & 0x0F; }
    int ID_ISAR2_EL1_PSR_AR() const { return (int)(_isar2 >> 24) & 0x0F; }
    int ID_ISAR2_EL1_MultU() const { return (int)(_isar2 >> 20) & 0x0F; }
    int ID_ISAR2_EL1_MultS() const { return (int)(_isar2 >> 16) & 0x0F; }
    int ID_ISAR2_EL1_Mult() const { return (int)(_isar2 >> 12) & 0x0F; }
    int ID_ISAR2_EL1_MultiAccessInt() const { return (int)(_isar2 >> 8) & 0x0F; }
    int ID_ISAR2_EL1_MemHint() const { return (int)(_isar2 >> 4) & 0x0F; }
    int ID_ISAR2_EL1_LoadStore() const { return (int)(_isar2) & 0x0F; }

    int ID_ISAR3_EL1_T32EE() const { return (int)(_isar3 >> 28) & 0x0F; }
    int ID_ISAR3_EL1_TrueNOP() const { return (int)(_isar3 >> 24) & 0x0F; }
    int ID_ISAR3_EL1_T32Copy() const { return (int)(_isar3 >> 20) & 0x0F; }
    int ID_ISAR3_EL1_TabBranch() const { return (int)(_isar3 >> 16) & 0x0F; }
    int ID_ISAR3_EL1_SynchPrim() const { return (int)(_isar3 >> 12) & 0x0F; }
    int ID_ISAR3_EL1_SVC() const { return (int)(_isar3 >> 8) & 0x0F; }
    int ID_ISAR3_EL1_SIMD() const { return (int)(_isar3 >> 4) & 0x0F; }
    int ID_ISAR3_EL1_Saturate() const { return (int)(_isar3) & 0x0F; }

    int ID_ISAR4_EL1_SWP_frac() const { return (int)(_isar4 >> 28) & 0x0F; }
    int ID_ISAR4_EL1_PSR_M() const { return (int)(_isar4 >> 24) & 0x0F; }
    int ID_ISAR4_EL1_SynchPrim_frac() const { return (int)(_isar4 >> 20) & 0x0F; }
    int ID_ISAR4_EL1_Barrier() const { return (int)(_isar4 >> 16) & 0x0F; }
    int ID_ISAR4_EL1_SMC() const { return (int)(_isar4 >> 12) & 0x0F; }
    int ID_ISAR4_EL1_Writeback() const { return (int)(_isar4 >> 8) & 0x0F; }
    int ID_ISAR4_EL1_WithShifts() const { return (int)(_isar4 >> 4) & 0x0F; }
    int ID_ISAR4_EL1_Unpriv() const { return (int)(_isar4) & 0x0F; }

    int ID_ISAR5_EL1_VCMA() const { return (int)(_isar5 >> 28) & 0x0F; }
    int ID_ISAR5_EL1_RDM() const { return (int)(_isar5 >> 24) & 0x0F; }
    int ID_ISAR5_EL1_CRC32() const { return (int)(_isar5 >> 16) & 0x0F; }
    int ID_ISAR5_EL1_SHA2() const { return (int)(_isar5 >> 12) & 0x0F; }
    int ID_ISAR5_EL1_SHA1() const { return (int)(_isar5 >> 8) & 0x0F; }
    int ID_ISAR5_EL1_AES() const { return (int)(_isar5 >> 4) & 0x0F; }
    int ID_ISAR5_EL1_SEVL() const { return (int)(_isar5) & 0x0F; }

    int ID_ISAR6_EL1_I8MM() const { return (int)(_isar6 >> 24) & 0x0F; }
    int ID_ISAR6_EL1_BF16() const { return (int)(_isar6 >> 20) & 0x0F; }
    int ID_ISAR6_EL1_SPECRES() const { return (int)(_isar6 >> 16) & 0x0F; }
    int ID_ISAR6_EL1_SB() const { return (int)(_isar6 >> 12) & 0x0F; }
    int ID_ISAR6_EL1_FHM() const { return (int)(_isar6 >> 8) & 0x0F; }
    int ID_ISAR6_EL1_DP() const { return (int)(_isar6 >> 4) & 0x0F; }
    int ID_ISAR6_EL1_JSCVT() const { return (int)(_isar6) & 0x0F; }

    int ID_MMFR0_EL1_InnerShr() const { return (int)(_mmfr0 >> 28) & 0x0F; }
    int ID_MMFR0_EL1_FCSE() const { return (int)(_mmfr0 >> 24) & 0x0F; }
    int ID_MMFR0_EL1_AuxReg() const { return (int)(_mmfr0 >> 20) & 0x0F; }
    int ID_MMFR0_EL1_TCM() const { return (int)(_mmfr0 >> 16) & 0x0F; }
    int ID_MMFR0_EL1_ShareLvl() const { return (int)(_mmfr0 >> 12) & 0x0F; }
    int ID_MMFR0_EL1_OuterShr() const { return (int)(_mmfr0 >> 8) & 0x0F; }
    int ID_MMFR0_EL1_PMSA() const { return (int)(_mmfr0 >> 4) & 0x0F; }
    int ID_MMFR0_EL1_VMSA() const { return (int)(_mmfr0) & 0x0F; }

    int ID_MMFR1_EL1_BPred() const { return (int)(_mmfr1 >> 28) & 0x0F; }
    int ID_MMFR1_EL1_L1TstCln() const { return (int)(_mmfr1 >> 24) & 0x0F; }
    int ID_MMFR1_EL1_L1Uni() const { return (int)(_mmfr1 >> 20) & 0x0F; }
    int ID_MMFR1_EL1_L1Hvd() const { return (int)(_mmfr1 >> 16) & 0x0F; }
    int ID_MMFR1_EL1_L1UniSW() const { return (int)(_mmfr1 >> 12) & 0x0F; }
    int ID_MMFR1_EL1_L1HvdSW() const { return (int)(_mmfr1 >> 8) & 0x0F; }
    int ID_MMFR1_EL1_L1UniVA() const { return (int)(_mmfr1 >> 4) & 0x0F; }
    int ID_MMFR1_EL1_L1HvdVA() const { return (int)(_mmfr1) & 0x0F; }

    int ID_MMFR2_EL1_HWAccFlg() const { return (int)(_mmfr2 >> 28) & 0x0F; }
    int ID_MMFR2_EL1_WFIStall() const { return (int)(_mmfr2 >> 24) & 0x0F; }
    int ID_MMFR2_EL1_MemBarr() const { return (int)(_mmfr2 >> 20) & 0x0F; }
    int ID_MMFR2_EL1_UniTLB() const { return (int)(_mmfr2 >> 16) & 0x0F; }
    int ID_MMFR2_EL1_HvdTLB() const { return (int)(_mmfr2 >> 12) & 0x0F; }
    int ID_MMFR2_EL1_L1HvdRng() const { return (int)(_mmfr2 >> 8) & 0x0F; }
    int ID_MMFR2_EL1_L1HvdBG() const { return (int)(_mmfr2 >> 4) & 0x0F; }
    int ID_MMFR2_EL1_L1HvdFG() const { return (int)(_mmfr2) & 0x0F; }

    int ID_MMFR3_EL1_Supersec() const { return (int)(_mmfr3 >> 28) & 0x0F; }
    int ID_MMFR3_EL1_CMemSz() const { return (int)(_mmfr3 >> 24) & 0x0F; }
    int ID_MMFR3_EL1_CohWalk() const { return (int)(_mmfr3 >> 20) & 0x0F; }
    int ID_MMFR3_EL1_PAN() const { return (int)(_mmfr3 >> 16) & 0x0F; }
    int ID_MMFR3_EL1_MaintBcst() const { return (int)(_mmfr3 >> 12) & 0x0F; }
    int ID_MMFR3_EL1_BPMaint() const { return (int)(_mmfr3 >> 8) & 0x0F; }
    int ID_MMFR3_EL1_CMaintSW() const { return (int)(_mmfr3 >> 4) & 0x0F; }
    int ID_MMFR3_EL1_CMaintVA() const { return (int)(_mmfr3) & 0x0F; }

    int ID_MMFR4_EL1_EVT() const { return (int)(_mmfr4 >> 28) & 0x0F; }
    int ID_MMFR4_EL1_CCIDX() const { return (int)(_mmfr4 >> 24) & 0x0F; }
    int ID_MMFR4_EL1_LSM() const { return (int)(_mmfr4 >> 20) & 0x0F; }
    int ID_MMFR4_EL1_HPDS() const { return (int)(_mmfr4 >> 16) & 0x0F; }
    int ID_MMFR4_EL1_CnP() const { return (int)(_mmfr4 >> 12) & 0x0F; }
    int ID_MMFR4_EL1_XNX() const { return (int)(_mmfr4 >> 8) & 0x0F; }
    int ID_MMFR4_EL1_AC2() const { return (int)(_mmfr4 >> 4) & 0x0F; }
    int ID_MMFR4_EL1_SpecSEI() const { return (int)(_mmfr4) & 0x0F; }

    int ID_MMFR5_EL1_nTLBPA() const { return (int)(_mmfr5 >> 4) & 0x0F; }
    int ID_MMFR5_EL1_ETS() const { return (int)(_mmfr5) & 0x0F; }

    int ID_PFR0_EL1_RAS() const { return (int)(_pfr0 >> 28) & 0x0F; }
    int ID_PFR0_EL1_DIT() const { return (int)(_pfr0 >> 24) & 0x0F; }
    int ID_PFR0_EL1_AMU() const { return (int)(_pfr0 >> 20) & 0x0F; }
    int ID_PFR0_EL1_CSV2() const { return (int)(_pfr0 >> 16) & 0x0F; }
    int ID_PFR0_EL1_State3() const { return (int)(_pfr0 >> 12) & 0x0F; }
    int ID_PFR0_EL1_State2() const { return (int)(_pfr0 >> 8) & 0x0F; }
    int ID_PFR0_EL1_State1() const { return (int)(_pfr0 >> 4) & 0x0F; }
    int ID_PFR0_EL1_State0() const { return (int)(_pfr0) & 0x0F; }

    int ID_PFR1_EL1_GIC() const { return (int)(_pfr1 >> 28) & 0x0F; }
    int ID_PFR1_EL1_Virt_frac() const { return (int)(_pfr1 >> 24) & 0x0F; }
    int ID_PFR1_EL1_Sec_frac() const { return (int)(_pfr1 >> 20) & 0x0F; }
    int ID_PFR1_EL1_GenTimer() const { return (int)(_pfr1 >> 16) & 0x0F; }
    int ID_PFR1_EL1_Virtualization() const { return (int)(_pfr1 >> 12) & 0x0F; }
    int ID_PFR1_EL1_MProgMod() const { return (int)(_pfr1 >> 8) & 0x0F; }
    int ID_PFR1_EL1_Security() const { return (int)(_pfr1 >> 4) & 0x0F; }
    int ID_PFR1_EL1_ProgMod() const { return (int)(_pfr1) & 0x0F; }

    int ID_PFR2_EL1_RAS_frac() const { return (int)(_pfr2 >> 8) & 0x0F; }
    int ID_PFR2_EL1_SSBS() const { return (int)(_pfr2 >> 4) & 0x0F; }
    int ID_PFR2_EL1_CSV3() const { return (int)(_pfr2) & 0x0F; }

    int CTR_EL0_TminLine() const { return (int)(_ctr >> 32) & 0x3F; }
    int CTR_EL0_DIC() const { return (int)(_ctr >> 29) & 0x01; }
    int CTR_EL0_IDC() const { return (int)(_ctr >> 28) & 0x01; }
    int CTR_EL0_CWG() const { return (int)(_ctr >> 24) & 0x0F; }
    int CTR_EL0_ERG() const { return (int)(_ctr >> 20) & 0x0F; }
    int CTR_EL0_DminLine() const { return (int)(_ctr >> 16) & 0x0F; }
    int CTR_EL0_L1Ip() const { return (int)(_ctr >> 14) & 0x03; }
    int CTR_EL0_IminLine() const { return (int)(_ctr) & 0x0F; }

    int TCR_EL1_MTX1() const { return (int)(_tcr >> 61) & 0x01; }
    int TCR_EL1_MTX0() const { return (int)(_tcr >> 60) & 0x01; }
    int TCR_EL1_DS() const { return (int)(_tcr >> 59) & 0x01; }
    int TCR_EL1_TCMA1() const { return (int)(_tcr >> 58) & 0x01; }
    int TCR_EL1_TCMA0() const { return (int)(_tcr >> 57) & 0x01; }
    int TCR_EL1_E0PD1() const { return (int)(_tcr >> 56) & 0x01; }
    int TCR_EL1_E0PD0() const { return (int)(_tcr >> 55) & 0x01; }
    int TCR_EL1_NFD1() const { return (int)(_tcr >> 54) & 0x01; }
    int TCR_EL1_NFD0() const { return (int)(_tcr >> 53) & 0x01; }
    int TCR_EL1_TBID1() const { return (int)(_tcr >> 52) & 0x01; }
    int TCR_EL1_TBID0() const { return (int)(_tcr >> 51) & 0x01; }
    int TCR_EL1_HPD1() const { return (int)(_tcr >> 42) & 0x01; }
    int TCR_EL1_HPD0() const { return (int)(_tcr >> 41) & 0x01; }
    int TCR_EL1_HD() const { return (int)(_tcr >> 40) & 0x01; }
    int TCR_EL1_HA() const { return (int)(_tcr >> 39) & 0x01; }
    int TCR_EL1_TBI1() const { return (int)(_tcr >> 38) & 0x01; }
    int TCR_EL1_TBI0() const { return (int)(_tcr >> 37) & 0x01; }
    int TCR_EL1_AS() const { return (int)(_tcr >> 36) & 0x01; }
    int TCR_EL1_IPS() const { return (int)(_tcr >> 32) & 0x07; }
    int TCR_EL1_TG1() const { return (int)(_tcr >> 30) & 0x03; }
    int TCR_EL1_SH1() const { return (int)(_tcr >> 28) & 0x03; }
    int TCR_EL1_ORGN1() const { return (int)(_tcr >> 26) & 0x03; }
    int TCR_EL1_IRGN1() const { return (int)(_tcr >> 24) & 0x03; }
    int TCR_EL1_EPD1() const { return (int)(_tcr >> 23) & 0x01; }
    int TCR_EL1_A1() const { return (int)(_tcr >> 22) & 0x01; }
    int TCR_EL1_T1SZ() const { return (int)(_tcr >> 16) & 0x3F; }
    int TCR_EL1_TG0() const { return (int)(_tcr >> 14) & 0x03; }
    int TCR_EL1_SH0() const { return (int)(_tcr >> 12) & 0x03; }
    int TCR_EL1_ORGN0() const { return (int)(_tcr >> 10) & 0x03; }
    int TCR_EL1_IRGN0() const { return (int)(_tcr >> 8) & 0x03; }
    int TCR_EL1_EPD0() const { return (int)(_tcr >> 7) & 0x01; }
    int TCR_EL1_T0SZ() const { return (int)(_tcr) & 0x3F; }

    int TCR2_EL1_DisCH1() const { return (int)(_tcr2 >> 15) & 0x01; }
    int TCR2_EL1_DisCH0() const { return (int)(_tcr2 >> 14) & 0x01; }
    int TCR2_EL1_HAFT() const { return (int)(_tcr2 >> 11) & 0x01; }
    int TCR2_EL1_PTTWI() const { return (int)(_tcr2 >> 10) & 0x01; }
    int TCR2_EL1_D128() const { return (int)(_tcr2 >> 5) & 0x01; }
    int TCR2_EL1_AIE() const { return (int)(_tcr2 >> 4) & 0x01; }
    int TCR2_EL1_POE() const { return (int)(_tcr2 >> 3) & 0x01; }
    int TCR2_EL1_E0POE() const { return (int)(_tcr2 >> 2) & 0x01; }
    int TCR2_EL1_PIE() const { return (int)(_tcr2 >> 1) & 0x01; }
    int TCR2_EL1_PnCH() const { return (int)(_tcr2) & 0x01; }

    int TRCDEVARCH_ARCHITECT() const { return (int)(_trcdevarch >> 21) & 0x07FF; }
    int TRCDEVARCH_PRESENT() const { return (int)(_trcdevarch >> 20) & 0x01; }
    int TRCDEVARCH_REVISION() const { return (int)(_trcdevarch >> 16) & 0x0F; }
    int TRCDEVARCH_ARCHVER() const { return (int)(_trcdevarch >> 12) & 0x0F; }
    int TRCDEVARCH_ARCHPART() const { return (int)(_trcdevarch) & 0x0FFF; }

    int PMMIR_EDGE() const { return (int)(_pmmir >> 24) & 0x0F; }
    int PMMIR_THWIDTH() const { return (int)(_pmmir >> 20) & 0x0F; }
    int PMMIR_BUS_WIDTH() const { return (int)(_pmmir >> 16) & 0x0F; }
    int PMMIR_BUS_SLOTS() const { return (int)(_pmmir >> 8) & 0xFF; }
    int PMMIR_SLOTS() const { return (int)(_pmmir) & 0xFF; }

    int PMSIDR_CRR() const { return (int)(_pmsidr >> 25) & 0x01; }
    int PMSIDR_PBT() const { return (int)(_pmsidr >> 24) & 0x01; }
    int PMSIDR_Format() const { return (int)(_pmsidr >> 20) & 0x0F; }
    int PMSIDR_CountSize() const { return (int)(_pmsidr >> 16) & 0x0F; }
    int PMSIDR_MaxSize() const { return (int)(_pmsidr >> 12) & 0x0F; }
    int PMSIDR_Interval() const { return (int)(_pmsidr >> 8) & 0x0F; }
    int PMSIDR_FDS() const { return (int)(_pmsidr >> 7) & 0x01; }
    int PMSIDR_FNE() const { return (int)(_pmsidr >> 6) & 0x01; }
    int PMSIDR_ERnd() const { return (int)(_pmsidr >> 5) & 0x01; }
    int PMSIDR_LDS() const { return (int)(_pmsidr >> 4) & 0x01; }
    int PMSIDR_ArchInst() const { return (int)(_pmsidr >> 3) & 0x01; }
    int PMSIDR_FL() const { return (int)(_pmsidr >> 2) & 0x01; }
    int PMSIDR_FT() const { return (int)(_pmsidr >> 1) & 0x01; }
    int PMSIDR_FE() const { return (int)(_pmsidr) & 0x01; }

    // Processor features, using same names as Arm Architecture Reference Manual.
    // Implemented level: Armv9-A (ref manual rev I.a)

    bool FEAT_AArch32() const { return ID_AA64PFR0_EL1_EL1() >= 2 || ID_AA64PFR0_EL1_EL0() >= 2; }
    bool FEAT_AA32BF16() const { return ID_ISAR6_EL1_BF16() >= 1; }
    bool FEAT_AA32HPD() const { return ID_MMFR4_EL1_HPDS() >= 1; }
    bool FEAT_AA32I8MM() const { return ID_ISAR6_EL1_I8MM() >= 1; }
    bool FEAT_ABLE() const { return ID_AA64DFR1_EL1_ABLE() >= 1; }
    bool FEAT_ADERR() const { return ID_AA64MMFR3_EL1_ADERR() >= 2 || ID_AA64MMFR3_EL1_SDERR() >= 2; }
    bool FEAT_AdvSIMD() const { return ID_AA64PFR0_EL1_AdvSIMD() < 15; }
    bool FEAT_AES() const { return ID_AA64ISAR0_EL1_AES() >= 1; }
    bool FEAT_AFP() const { return ID_AA64MMFR1_EL1_AFP() >= 1; }
    bool FEAT_AIE() const { return ID_AA64MMFR3_EL1_AIE() >= 1; }
    bool FEAT_AMUv1() const { return ID_AA64PFR0_EL1_AMU() >= 1; }
    bool FEAT_AMUv1p1() const { return ID_AA64PFR0_EL1_AMU() >= 2; }
    bool FEAT_ANERR() const { return ID_AA64MMFR3_EL1_ANERR() >= 2 || ID_AA64MMFR3_EL1_SNERR() >= 2; }
    bool FEAT_B16B16() const { return ID_AA64SMFR0_EL1_B16B16() >= 1; }
    bool FEAT_BBM() const { return ID_AA64MMFR2_EL1_BBM() >= 1; }
    bool FEAT_BF16() const { return ID_AA64ISAR1_EL1_BF16() >= 1 || ID_AA64ZFR0_EL1_BF16() >= 1; }
    bool FEAT_BRBE() const { return ID_AA64DFR0_EL1_BRBE() >= 1; }
    bool FEAT_BRBEv1p1() const { return ID_AA64DFR0_EL1_BRBE() >= 2; }
    bool FEAT_BTI() const { return ID_AA64PFR1_EL1_BT() >= 1; }
    bool FEAT_CCIDX() const { return ID_AA64MMFR2_EL1_CCIDX() >= 1; }
    bool FEAT_CLRBHB() const { return ID_AA64ISAR2_EL1_CLRBHB() >= 1; }
    bool FEAT_CMOW() const { return ID_AA64MMFR1_EL1_CMOW() >= 1; }
    bool FEAT_CONSTPACFIELD() const { return ID_AA64ISAR2_EL1_PAC_frac() >= 1; }
    bool FEAT_CRC32() const { return ID_AA64ISAR0_EL1_CRC32() >= 1; }
    bool FEAT_CSSC() const { return ID_AA64ISAR2_EL1_CSSC() >= 1; }
    bool FEAT_CSV2() const { return ID_AA64PFR0_EL1_CSV2() >= 1; }
    bool FEAT_CSV2_1p1() const { return ID_AA64PFR1_EL1_CSV2_frac() >= 1; }
    bool FEAT_CSV2_1p2() const { return ID_AA64PFR1_EL1_CSV2_frac() >= 2; }
    bool FEAT_CSV2_2() const { return ID_AA64PFR0_EL1_CSV2() >= 2; }
    bool FEAT_CSV2_3() const { return ID_AA64PFR0_EL1_CSV2() >= 3; }
    bool FEAT_CSV3() const { return ID_AA64PFR0_EL1_CSV3() >= 1; }
    bool FEAT_D128() const { return ID_AA64MMFR3_EL1_D128() >= 1; }
    bool FEAT_Debugv8p1() const { return ID_AA64DFR0_EL1_DebugVer() >= 7; }
    bool FEAT_Debugv8p2() const { return ID_AA64DFR0_EL1_DebugVer() >= 8; }
    bool FEAT_Debugv8p4() const { return ID_AA64DFR0_EL1_DebugVer() >= 9; }
    bool FEAT_Debugv8p8() const { return ID_AA64DFR0_EL1_DebugVer() >= 10; }
    bool FEAT_Debugv8p9() const { return ID_AA64DFR0_EL1_DebugVer() >= 11; }
    bool FEAT_DGH() const { return ID_AA64ISAR1_EL1_DGH() >= 1; }
    bool FEAT_DIT() const { return ID_AA64PFR0_EL1_DIT() >= 1; }
    bool FEAT_DotProd() const { return ID_AA64ISAR0_EL1_DP() >= 1; }
    bool FEAT_DoubleFault() const { return ID_AA64PFR0_EL1_RAS() >= 2; }
    bool FEAT_DoubleFault2() const { return ID_AA64PFR1_EL1_DF2() >= 1; }
    bool FEAT_DoubleLock() const { return ID_AA64DFR0_EL1_DoubleLock() != 15; }
    bool FEAT_DPB() const { return ID_AA64ISAR1_EL1_DPB() >= 1; }
    bool FEAT_DPB2() const { return ID_AA64ISAR1_EL1_DPB() >= 2; }
    bool FEAT_E0PD() const { return ID_AA64MMFR2_EL1_E0PD() >= 1; }
    bool FEAT_EBEP() const { return ID_AA64DFR1_EL1_EBEP() >= 1; }
    bool FEAT_EBF16() const { return ID_AA64ISAR1_EL1_BF16() >= 2 || ID_AA64ZFR0_EL1_BF16() >= 2; }
    bool FEAT_ECBHB() const { return ID_AA64MMFR1_EL1_ECBHB() >= 1; }
    bool FEAT_ECV() const { return ID_AA64MMFR0_EL1_ECV() >= 1; }
    bool FEAT_EPAC() const { return ID_AA64ISAR1_EL1_API() >= 2 || ID_AA64ISAR1_EL1_APA() >= 2 || ID_AA64ISAR2_EL1_APA3() >= 2; }
    bool FEAT_ETE() const { return ID_AA64DFR0_EL1_TraceVer() >= 1; }
    bool FEAT_ETEv1p1() const { return TRCDEVARCH_REVISION() >= 1; }
    bool FEAT_ETEv1p2() const { return TRCDEVARCH_REVISION() >= 2; }
    bool FEAT_ETEv1p3() const { return TRCDEVARCH_REVISION() >= 3; }
    // About ETMv4, see Arm Embedded Trace Macrocell Architecture Specification ETMv4.0 to ETMv4.6
    bool FEAT_ETMv4() const { return TRCDEVARCH_ARCHITECT() == 0b01000111011 && TRCDEVARCH_PRESENT() == 1 && TRCDEVARCH_ARCHVER() == 0b0100 && TRCDEVARCH_ARCHPART() == 0b101000010011; }
    bool FEAT_ETMv4p1() const { return FEAT_ETMv4() && TRCDEVARCH_REVISION() >= 1; }
    bool FEAT_ETMv4p2() const { return FEAT_ETMv4() && TRCDEVARCH_REVISION() >= 2; }
    bool FEAT_ETMv4p3() const { return FEAT_ETMv4() && TRCDEVARCH_REVISION() >= 3; }
    bool FEAT_ETMv4p4() const { return FEAT_ETMv4() && TRCDEVARCH_REVISION() >= 4; }
    bool FEAT_ETMv4p5() const { return FEAT_ETMv4() && TRCDEVARCH_REVISION() >= 5; }
    bool FEAT_ETMv4p6() const { return FEAT_ETMv4() && TRCDEVARCH_REVISION() >= 6; }
    bool FEAT_ETS() const { return ID_AA64MMFR1_EL1_ETS() >= 1; }
    bool FEAT_EVT() const { return ID_AA64MMFR2_EL1_EVT() >= 1; }
    bool FEAT_ExS() const { return ID_AA64MMFR0_EL1_ExS() >= 1; }
    bool FEAT_F32MM() const { return ID_AA64ZFR0_EL1_F32MM() >= 1; }
    bool FEAT_F64MM() const { return ID_AA64ZFR0_EL1_F64MM() >= 1; }
    bool FEAT_FCMA() const { return ID_AA64ISAR1_EL1_FCMA() >= 1; }
    bool FEAT_FGT() const { return ID_AA64MMFR0_EL1_FGT() >= 1; }
    bool FEAT_FGT2() const { return ID_AA64MMFR0_EL1_FGT() >= 2; }
    bool FEAT_FHM() const { return ID_AA64ISAR0_EL1_FHM() >= 1; }
    bool FEAT_FlagM() const { return ID_AA64ISAR0_EL1_TS() >= 1; }
    bool FEAT_FlagM2() const { return ID_AA64ISAR0_EL1_TS() >= 2; }
    bool FEAT_FP() const { return ID_AA64PFR0_EL1_FP() < 15; }
    bool FEAT_FP16() const { return ID_AA64PFR0_EL1_FP() >= 1 && ID_AA64PFR0_EL1_FP() < 15; }
    bool FEAT_FPAC() const { return ID_AA64ISAR1_EL1_API() >= 4 || ID_AA64ISAR1_EL1_APA() >= 4 || ID_AA64ISAR2_EL1_APA3() >= 4; }
    bool FEAT_FPACCOMBINE() const { return ID_AA64ISAR1_EL1_API() >= 5 || ID_AA64ISAR1_EL1_APA() >= 5 || ID_AA64ISAR2_EL1_APA3() >= 5; }
    bool FEAT_FRINTTS() const { return ID_AA64ISAR1_EL1_FRINTTS() >= 1; }
    bool FEAT_GCS() const { return ID_AA64PFR1_EL1_GCS() >= 1; }
    bool FEAT_GICv3() const { return ID_AA64PFR0_EL1_GIC() >= 1; }
    bool FEAT_GICv4() const { return ID_AA64PFR0_EL1_GIC() >= 1; }
    bool FEAT_GICv4p1() const { return ID_AA64PFR0_EL1_GIC() >= 3; }
    bool FEAT_GTG() const { return ID_AA64MMFR0_EL1_TGran4_2() > 1 || ID_AA64MMFR0_EL1_TGran16_2() > 1 || ID_AA64MMFR0_EL1_TGran64_2() > 1; }
    bool FEAT_HAFDBS() const { return ID_AA64MMFR1_EL1_HAFDBS() >= 1; }
    bool FEAT_HAFT() const { return ID_AA64MMFR1_EL1_HAFDBS() >= 3; }
    bool FEAT_HBC() const { return ID_AA64ISAR2_EL1_BC() >= 1; }
    bool FEAT_HCX() const { return ID_AA64MMFR1_EL1_HCX() >= 1; }
    bool FEAT_HPDS() const { return ID_AA64MMFR1_EL1_HPDS() >= 1; }
    bool FEAT_HPDS2() const { return ID_AA64MMFR1_EL1_HPDS() >= 2; }
    bool FEAT_HPMN0() const { return ID_AA64DFR0_EL1_HPMN0() >= 1; }
    bool FEAT_I8MM() const { return ID_AA64ZFR0_EL1_I8MM() >= 1; }
    bool FEAT_IDST() const { return ID_AA64MMFR2_EL1_IDS() >= 1; }
    bool FEAT_IESB() const { return ID_AA64MMFR2_EL1_IESB() >= 1; }
    bool FEAT_ITE() const { return ID_AA64DFR1_EL1_ITE() >= 1; }
    bool FEAT_JSCVT() const { return ID_AA64ISAR1_EL1_JSCVT() >= 1; }
    bool FEAT_LOR() const { return ID_AA64MMFR1_EL1_LO() >= 1; }
    bool FEAT_LPA() const { return ID_AA64MMFR0_EL1_PARange() >= 6; }
    bool FEAT_LPA2() const { return ID_AA64MMFR0_EL1_TGran4_2() >= 3 || ID_AA64MMFR0_EL1_TGran16_2() >= 3; }
    bool FEAT_LRCPC() const { return ID_AA64ISAR1_EL1_LRCPC() >= 1; }
    bool FEAT_LRCPC2() const { return ID_AA64ISAR1_EL1_LRCPC() >= 2; }
    bool FEAT_LRCPC3() const { return ID_AA64ISAR1_EL1_LRCPC() >= 3; }
    bool FEAT_LS64() const { return ID_AA64ISAR1_EL1_LS64() >= 1; }
    bool FEAT_LS64_V() const { return ID_AA64ISAR1_EL1_LS64() >= 2; }
    bool FEAT_LS64_ACCDATA() const { return ID_AA64ISAR1_EL1_LS64() >= 3; }
    bool FEAT_LSE() const { return ID_AA64ISAR0_EL1_Atomic() >= 2; }
    bool FEAT_LSE128() const { return ID_AA64ISAR0_EL1_Atomic() >= 3; }
    bool FEAT_LSE2() const { return ID_AA64MMFR2_EL1_AT() >= 1; }
    bool FEAT_LVA() const { return ID_AA64MMFR2_EL1_VARange() >= 1; }
    bool FEAT_LVA3() const { return ID_AA64MMFR2_EL1_VARange() >= 2; }
    bool FEAT_LSMAOC() const { return ID_AA64MMFR2_EL1_LSM() >= 1; }
    bool FEAT_MEC() const { return ID_AA64MMFR3_EL1_MEC() >= 1; }
    bool FEAT_MOPS() const { return ID_AA64ISAR2_EL1_MOPS() >= 1; }
    bool FEAT_MPAM() const { return ID_AA64PFR0_EL1_MPAM() >= 1 || ID_AA64PFR1_EL1_MPAM_frac() >= 1; }
    bool FEAT_MPAMv0p1() const { return ID_AA64PFR1_EL1_MPAM_frac() >= 1; }
    bool FEAT_MPAMv1p0() const { return ID_AA64PFR0_EL1_MPAM() >= 1; }
    bool FEAT_MPAMv1p1() const { return (ID_AA64PFR0_EL1_MPAM() == 1 && ID_AA64PFR1_EL1_MPAM_frac() >= 1) || ID_AA64PFR0_EL1_MPAM() >= 2; }
    bool FEAT_MTE() const { return ID_AA64PFR1_EL1_MTE() >= 1; }
    bool FEAT_MTE2() const { return ID_AA64PFR1_EL1_MTE() >= 2; }
    bool FEAT_MTE3() const { return ID_AA64PFR1_EL1_MTE() >= 3; }
    bool FEAT_MTE4() const { return FEAT_MTE() && (ID_AA64PFR1_EL1_MTEX() >= 1 || ID_AA64PFR2_EL1_MTEFAR() >= 1 || ID_AA64PFR2_EL1_MTESTOREONLY() >= 1); }
    bool FEAT_MTE_CANONICAL_TAGS() const { return FEAT_MTE() && ID_AA64PFR1_EL1_MTEX() >= 1; }
    bool FEAT_MTE_NO_ADDRESS_TAGS() const { return FEAT_MTE() && ID_AA64PFR1_EL1_MTEX() >= 1; }
    bool FEAT_MTE_PERM() const { return ID_AA64PFR1_EL1_MTE() >= 2 && ID_AA64PFR2_EL1_MTEPERM() >= 1; }
    bool FEAT_MTE_STORE_ONLY() const { return ID_AA64PFR1_EL1_MTE() >= 2 && ID_AA64PFR1_EL1_MTEX() >= 1 && ID_AA64PFR2_EL1_MTESTOREONLY() >= 1; }
    bool FEAT_MTE_TAGGED_FAR() const { return ID_AA64PFR1_EL1_MTE() >= 2 && ID_AA64PFR1_EL1_MTEX() >= 1 && ID_AA64PFR2_EL1_MTEFAR() >= 1; }
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
    bool FEAT_PFAR() const { return ID_AA64PFR1_EL1_PFAR() >= 1; }
    bool FEAT_PMUv3() const { return ID_AA64DFR0_EL1_PMUVer() >= 1 && ID_AA64DFR0_EL1_PMUVer() < 15; }
    bool FEAT_PMUv3p1() const { return ID_AA64DFR0_EL1_PMUVer() >= 4 && ID_AA64DFR0_EL1_PMUVer() < 15; }
    bool FEAT_PMUv3p4() const { return ID_AA64DFR0_EL1_PMUVer() >= 5 && ID_AA64DFR0_EL1_PMUVer() < 15; }
    bool FEAT_PMUv3p5() const { return ID_AA64DFR0_EL1_PMUVer() >= 6 && ID_AA64DFR0_EL1_PMUVer() < 15; }
    bool FEAT_PMUv3p7() const { return ID_AA64DFR0_EL1_PMUVer() >= 7 && ID_AA64DFR0_EL1_PMUVer() < 15; }
    bool FEAT_PMUv3p8() const { return ID_AA64DFR0_EL1_PMUVer() >= 8 && ID_AA64DFR0_EL1_PMUVer() < 15; }
    bool FEAT_PMUv3p9() const { return ID_AA64DFR0_EL1_PMUVer() >= 9 && ID_AA64DFR0_EL1_PMUVer() < 15; }
    bool FEAT_PMUv3_EDGE() const { return PMMIR_EDGE() >= 1; }
    bool FEAT_PMUv3_ICNTR() const { return ID_AA64DFR1_EL1_PMICNTR() >= 1; }
    bool FEAT_PMUv3_SS() const { return ID_AA64DFR0_EL1_PMSS() >= 1; }
    bool FEAT_PMUv3_TH() const { return PMMIR_THWIDTH() >= 1; }
    bool FEAT_PMULL() const { return ID_AA64ISAR0_EL1_AES() >= 2; }
    bool FEAT_PRFMSLC() const { return ID_AA64ISAR2_EL1_PRFMSLC() >= 1; }
    bool FEAT_RAS() const { return ID_AA64PFR0_EL1_RAS() >= 1; }
    bool FEAT_RASv1p1() const { return ID_AA64PFR0_EL1_RAS() >= 2 || ID_AA64PFR1_EL1_RAS_frac() >= 1; }
    bool FEAT_RASv2() const { return ID_AA64PFR0_EL1_RAS() >= 3; }
    bool FEAT_RDM() const { return ID_AA64ISAR0_EL1_RDM() >= 1; }
    bool FEAT_RME() const { return ID_AA64PFR0_EL1_RME() >= 1; }
    bool FEAT_RNG() const { return ID_AA64ISAR0_EL1_RNDR() >= 1; }
    bool FEAT_RNG_TRAP() const { return ID_AA64PFR1_EL1_RNDR_trap() >= 1; }
    bool FEAT_RPRES() const { return ID_AA64ISAR2_EL1_RPRES() >= 1; }
    bool FEAT_RPRFM() const { return ID_AA64ISAR2_EL1_RPRFM() >= 1; }
    bool FEAT_S1PIE() const { return ID_AA64MMFR3_EL1_S1PIE() >= 1; }
    bool FEAT_S1POE() const { return ID_AA64MMFR3_EL1_S1POE() >= 1; }
    bool FEAT_S2PIE() const { return ID_AA64MMFR3_EL1_S2PIE() >= 1; }
    bool FEAT_S2FWB() const { return ID_AA64MMFR2_EL1_FWB() >= 1; }
    bool FEAT_S2POE() const { return ID_AA64MMFR3_EL1_S2POE() >= 1; }
    bool FEAT_SB() const { return ID_AA64ISAR1_EL1_SB() >= 1; }
    bool FEAT_SCTLR2() const { return ID_AA64MMFR3_EL1_SCTLRX() >= 1; }
    bool FEAT_SEBEP() const { return ID_AA64DFR0_EL1_SEBEP() >= 1; }
    bool FEAT_SEL2() const { return ID_AA64PFR0_EL1_SEL2() >= 1; }
    bool FEAT_SHA1() const { return ID_AA64ISAR0_EL1_SHA1() >= 1; }
    bool FEAT_SHA256() const { return ID_AA64ISAR0_EL1_SHA2() >= 1; }
    bool FEAT_SHA512() const { return ID_AA64ISAR0_EL1_SHA2() >= 2; }
    bool FEAT_SHA3() const { return ID_AA64ISAR0_EL1_SHA3() >= 1; }
    bool FEAT_SM3() const { return ID_AA64ISAR0_EL1_SM3() >= 1; }
    bool FEAT_SM4() const { return ID_AA64ISAR0_EL1_SM4() >= 1; }
    bool FEAT_SME() const { return ID_AA64PFR1_EL1_SME() >= 1; }
    bool FEAT_SME_FA64() const { return ID_AA64PFR1_EL1_SME() >= 1 && ID_AA64SMFR0_EL1_FA64() >= 1; }
    bool FEAT_SME_F16F16() const { return ID_AA64PFR1_EL1_SME() >= 1 && ID_AA64SMFR0_EL1_F16F16() >= 1; }
    bool FEAT_SME_F64F64() const { return ID_AA64PFR1_EL1_SME() >= 1 && ID_AA64SMFR0_EL1_F64F64() >= 1; }
    bool FEAT_SME_I16I64() const { return ID_AA64PFR1_EL1_SME() >= 1 && ID_AA64SMFR0_EL1_I16I64() >= 1; }
    bool FEAT_SME2() const { return ID_AA64PFR1_EL1_SME() >= 1 && ID_AA64SMFR0_EL1_SMEver() >= 1; }
    bool FEAT_SME2p1() const { return ID_AA64PFR1_EL1_SME() >= 1 && ID_AA64SMFR0_EL1_SMEver() >= 2; }
    bool FEAT_SPE() const { return ID_AA64DFR0_EL1_PMSVer() >= 1; }
    bool FEAT_SPEv1p1() const { return ID_AA64DFR0_EL1_PMSVer() >= 2; }
    bool FEAT_SPEv1p2() const { return ID_AA64DFR0_EL1_PMSVer() >= 3; }
    bool FEAT_SPEv1p3() const { return ID_AA64DFR0_EL1_PMSVer() >= 4; }
    bool FEAT_SPEv1p4() const { return ID_AA64DFR0_EL1_PMSVer() >= 5; }
    bool FEAT_SPE_CRR() const { return PMSIDR_CRR() >= 1; }
    bool FEAT_SPE_FDS() const { return PMSIDR_FDS() >= 1; }
    bool FEAT_SPECRES() const { return ID_AA64ISAR1_EL1_SPECRES() >= 1; }
    bool FEAT_SPECRES2() const { return ID_AA64ISAR1_EL1_SPECRES() >= 2; }
    bool FEAT_SPMU() const { return ID_AA64DFR1_EL1_SPMU() >= 1; }
    bool FEAT_SSBS() const { return ID_AA64PFR1_EL1_SSBS() >= 1; }
    bool FEAT_SSBS2() const { return ID_AA64PFR1_EL1_SSBS() >= 2; }
    bool FEAT_SVE() const { return ID_AA64PFR0_EL1_SVE() >= 1; }
    bool FEAT_SVE2() const { return ID_AA64ZFR0_EL1_SVEver() >= 1; }
    bool FEAT_SVE2p1() const { return ID_AA64ZFR0_EL1_SVEver() >= 2; }
    bool FEAT_SVE_AES() const { return ID_AA64ZFR0_EL1_AES() >= 1; }
    bool FEAT_SVE_BitPerm() const { return ID_AA64ZFR0_EL1_BitPerm() >= 1; }
    bool FEAT_SVE_PMULL128() const { return ID_AA64ZFR0_EL1_AES() >= 2; }
    bool FEAT_SVE_SHA3() const { return ID_AA64ZFR0_EL1_SHA3() >= 1; }
    bool FEAT_SVE_SM4() const { return ID_AA64ZFR0_EL1_SM4() >= 1; }
    bool FEAT_SYSINSTR128() const { return ID_AA64ISAR2_EL1_SYSINSTR_128() >= 1; }
    bool FEAT_SYSREG128() const { return ID_AA64ISAR2_EL1_SYSREG_128() >= 1; }
    bool FEAT_TCR2() const { return ID_AA64MMFR3_EL1_TCRX() >= 1; }
    bool FEAT_THE() const { return ID_AA64PFR1_EL1_THE() >= 1; }
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

    // Supports PACGA in addition to PACIx and PACDx.
    bool hasPACGA() const;

    // Get the name of the PAC generation algorithm.
    std::string pacAlgo() const;

    // Get the number of QARMA rounds on this platform. Return 5 for QARMA5, 3 for QARMA3, 0 if none supported.
    int pacQARMA() const;

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
    csr_u64_t _aa64pfr2;
    csr_u64_t _aa64dfr0;
    csr_u64_t _aa64dfr1;
    csr_u64_t _aa64mmfr0;
    csr_u64_t _aa64mmfr1;
    csr_u64_t _aa64mmfr2;
    csr_u64_t _aa64mmfr3;
    csr_u64_t _aa64mmfr4;
    csr_u64_t _aa64smfr0;
    csr_u64_t _aa64zfr0;
    csr_u64_t _isar0;
    csr_u64_t _isar1;
    csr_u64_t _isar2;
    csr_u64_t _isar3;
    csr_u64_t _isar4;
    csr_u64_t _isar5;
    csr_u64_t _isar6;
    csr_u64_t _mmfr0;
    csr_u64_t _mmfr1;
    csr_u64_t _mmfr2;
    csr_u64_t _mmfr3;
    csr_u64_t _mmfr4;
    csr_u64_t _mmfr5;
    csr_u64_t _pfr0;
    csr_u64_t _pfr1;
    csr_u64_t _pfr2;
    csr_u64_t _ctr;
    csr_u64_t _tcr;
    csr_u64_t _tcr2;
    csr_u64_t _trcdevarch;
    csr_u64_t _pmmir;
    csr_u64_t _pmsidr;
};
