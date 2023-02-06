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
#include <string>
#include <list>

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

    int TCR_EL1_TCMA1() const { return (int)(_tcr >> 58) & 0x01; }
    int TCR_EL1_TCMA0() const { return (int)(_tcr >> 57) & 0x01; }
    int TCR_EL1_TBID1() const { return (int)(_tcr >> 52) & 0x01; }
    int TCR_EL1_TBID0() const { return (int)(_tcr >> 51) & 0x01; }
    int TCR_EL1_TBI1() const { return (int)(_tcr >> 38) & 0x01; }
    int TCR_EL1_TBI0() const { return (int)(_tcr >> 37) & 0x01; }
    int TCR_EL1_AS() const { return (int)(_tcr >> 36) & 0x01; }
    int TCR_EL1_T1SZ() const { return (int)(_tcr >> 16) & 0x3F; }
    int TCR_EL1_T0SZ() const { return (int)(_tcr) & 0x3F; }

    // Processor features, using same names as Arm Architecture Reference Manual.

    bool FEAT_AES() const { return ID_AA64ISAR0_EL1_AES() >= 1; }
    bool FEAT_BTI() const { return ID_AA64PFR1_EL1_BT() >= 1; }
    bool FEAT_AMUv1() const { return ID_AA64PFR0_EL1_AMU() >= 1; }
    bool FEAT_AMUv1p1() const { return ID_AA64PFR0_EL1_AMU() >= 2; }
    bool FEAT_BF16() const { return ID_AA64ISAR1_EL1_BF16() >= 1; }
    bool FEAT_CONSTPACFIELD() const { return ID_AA64ISAR2_EL1_PAC_frac() >= 1; }
    bool FEAT_CSV2() const { return ID_AA64PFR0_EL1_CSV2() >= 1; }
    bool FEAT_CSV2_1p1() const { return ID_AA64PFR1_EL1_CSV2_frac() >= 1; }
    bool FEAT_CSV2_1p2() const { return ID_AA64PFR1_EL1_CSV2_frac() >= 2; }
    bool FEAT_CSV2_2() const { return ID_AA64PFR0_EL1_CSV2() >= 2; }
    bool FEAT_CSV2_3() const { return ID_AA64PFR0_EL1_CSV2() >= 3; }
    bool FEAT_CSV3() const { return ID_AA64PFR0_EL1_CSV3() >= 1; }
    bool FEAT_DIT() const { return ID_AA64PFR0_EL1_DIT() >= 1; }
    bool FEAT_DotProd() const { return ID_AA64ISAR0_EL1_DP() >= 1; }
    bool FEAT_EBF16() const { return ID_AA64ISAR1_EL1_BF16() >= 2; }
    bool FEAT_EPAC() const { return ID_AA64ISAR1_EL1_API() >= 2 || ID_AA64ISAR1_EL1_APA() >= 2 || ID_AA64ISAR2_EL1_APA3() >= 2; }
    bool FEAT_FHM() const { return ID_AA64ISAR0_EL1_FHM() >= 1; }
    bool FEAT_FlagM() const { return ID_AA64ISAR0_EL1_TS() >= 1; }
    bool FEAT_FlagM2() const { return ID_AA64ISAR0_EL1_TS() >= 2; }
    bool FEAT_FP() const { return ID_AA64PFR0_EL1_FP() < 15; }
    bool FEAT_FP16() const { return ID_AA64PFR0_EL1_FP() >= 2 && ID_AA64PFR0_EL1_FP() < 15; }
    bool FEAT_FPAC() const { return ID_AA64ISAR1_EL1_API() >= 4 || ID_AA64ISAR1_EL1_APA() >= 4 || ID_AA64ISAR2_EL1_APA3() >= 4; }
    bool FEAT_FPACCOMBINE() const { return ID_AA64ISAR1_EL1_API() >= 5 || ID_AA64ISAR1_EL1_APA() >= 5 || ID_AA64ISAR2_EL1_APA3() >= 5; }
    bool FEAT_FRINTTS() const { return ID_AA64ISAR1_EL1_FRINTTS() >= 1; }
    bool FEAT_HBC() const { return ID_AA64ISAR2_EL1_BC() >= 1; }
    bool FEAT_LSE() const { return ID_AA64ISAR0_EL1_Atomic() >= 2; }
    bool FEAT_MOPS() const { return ID_AA64ISAR2_EL1_MOPS() >= 1; }
    bool FEAT_MTE() const { return ID_AA64PFR1_EL1_MTE() >= 1; }
    bool FEAT_MTE2() const { return ID_AA64PFR1_EL1_MTE() >= 2; }
    bool FEAT_MTE3() const { return ID_AA64PFR1_EL1_MTE() >= 3; }
    bool FEAT_NMI() const { return ID_AA64PFR1_EL1_NMI() >= 1; }
    bool FEAT_PACIMP() const { return ID_AA64ISAR1_EL1_GPI() >= 1 || ID_AA64ISAR1_EL1_API() >= 1; }
    bool FEAT_PACQARMA3() const { return ID_AA64ISAR2_EL1_GPA3() >= 1 || ID_AA64ISAR2_EL1_APA3() >= 1; }
    bool FEAT_PACQARMA5() const { return ID_AA64ISAR1_EL1_GPA() >= 1 || ID_AA64ISAR1_EL1_APA() >= 1; }
    bool FEAT_PAuth() const { return ID_AA64ISAR1_EL1_API() >= 1 || ID_AA64ISAR1_EL1_APA() >= 1 || ID_AA64ISAR2_EL1_APA3() >= 1; }
    bool FEAT_PAuth2() const { return ID_AA64ISAR1_EL1_API() >= 3 || ID_AA64ISAR1_EL1_APA() >= 3 || ID_AA64ISAR2_EL1_APA3() >= 3; }
    bool FEAT_PMULL() const { return ID_AA64ISAR0_EL1_AES() >= 2; }
    bool FEAT_RAS() const { return ID_AA64PFR0_EL1_RAS() >= 1; }
    bool FEAT_RASv1p1() const { return ID_AA64PFR1_EL1_RAS_frac() >= 1; }
    bool FEAT_RDM() const { return ID_AA64ISAR0_EL1_RDM() >= 1; }
    bool FEAT_RME() const { return ID_AA64PFR0_EL1_RME() >= 1; }
    bool FEAT_RNG() const { return ID_AA64ISAR0_EL1_RNDR() >= 1; }
    bool FEAT_SEL2() const { return ID_AA64PFR0_EL1_SEL2() >= 1; }
    bool FEAT_SHA1() const { return ID_AA64ISAR0_EL1_SHA1() >= 1; }
    bool FEAT_SHA256() const { return ID_AA64ISAR0_EL1_SHA2() >= 1; }
    bool FEAT_SHA512() const { return ID_AA64ISAR0_EL1_SHA2() >= 2; }
    bool FEAT_SHA3() const { return ID_AA64ISAR0_EL1_SHA3() >= 1; }
    bool FEAT_SM3() const { return ID_AA64ISAR0_EL1_SM3() >= 1; }
    bool FEAT_SM4() const { return ID_AA64ISAR0_EL1_SM4() >= 1; }
    bool FEAT_SME() const { return ID_AA64PFR1_EL1_SME() >= 1; }
    bool FEAT_SPECRES() const { return ID_AA64ISAR1_EL1_SPECRES() >= 1; }
    bool FEAT_SSBS() const { return ID_AA64PFR1_EL1_SSBS() >= 1; }
    bool FEAT_SSBS2() const { return ID_AA64PFR1_EL1_SSBS() >= 2; }
    bool FEAT_SVE() const { return ID_AA64PFR0_EL1_SVE() >= 1; }
    bool FEAT_TLBIOS() const { return ID_AA64ISAR0_EL1_TLB() >= 1; }
    bool FEAT_TLBIRANGE() const { return ID_AA64ISAR0_EL1_TLB() >= 2; }

    // Synthetic features of the processor.

    // Supports PACGA in addition to PACIx and PACDx.
    bool hasPACGA() const { return ID_AA64ISAR1_EL1_GPI() >= 1 || ID_AA64ISAR1_EL1_GPA() >= 1 || ID_AA64ISAR2_EL1_GPA3() >= 1; }

    // Check if address tagging is enabled. Variant when two VA ranges are used.
    bool addressTaggingEnabled() const { return FEAT_MTE() && TCR_EL1_TBI0(); }
    bool AddressTaggingEnabled0() const { return FEAT_MTE() && TCR_EL1_TBI0(); } // lower VA range
    bool AddressTaggingEnabled1() const { return FEAT_MTE() && TCR_EL1_TBI1(); } // upper VA range

    // Description of a feature.
    class Feature
    {
    public:
        std::string name;                  // Feature name
        bool (ArmFeatures::*get)() const;  // Method to get that feature
    };

    // Descriptions of all features.
    static const std::list<Feature> AllFeatures;

private:
    bool      _loaded;
    csr_u64_t _aa64isar0;
    csr_u64_t _aa64isar1;
    csr_u64_t _aa64isar2;
    csr_u64_t _aa64pfr0;
    csr_u64_t _aa64pfr1;
    csr_u64_t _tcr;
};
