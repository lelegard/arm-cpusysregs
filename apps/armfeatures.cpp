//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// A class describing the features of an Arm64 processor.
//
//----------------------------------------------------------------------------

#include "armfeatures.h"


//----------------------------------------------------------------------------
// Constructors:
//----------------------------------------------------------------------------

ArmFeatures::ArmFeatures() :
    _loaded(false),
    _aa64isar0(0),
    _aa64isar1(0),
    _aa64isar2(0),
    _aa64pfr0(0),
    _aa64pfr1(0),
    _tcr(0)
{
}

ArmFeatures::ArmFeatures(RegAccess& regaccess) :
    ArmFeatures()
{
    load(regaccess);
}


//----------------------------------------------------------------------------
// Load features from the system registers.
//----------------------------------------------------------------------------

bool ArmFeatures::load(RegAccess& regaccess)
{
    _loaded =
        regaccess.read(CSR_REGID_AA64ISAR0, _aa64isar0) &&
        regaccess.read(CSR_REGID_AA64ISAR1, _aa64isar1) &&
        regaccess.read(CSR_REGID_AA64ISAR2, _aa64isar2) &&
        regaccess.read(CSR_REGID_AA64PFR0, _aa64pfr0) &&
        regaccess.read(CSR_REGID_AA64PFR1, _aa64pfr1) &&
        regaccess.read(CSR_REGID_TCR, _tcr);

    return _loaded;
}


//----------------------------------------------------------------------------
// Descriptions of all features.
//----------------------------------------------------------------------------

const std::list<ArmFeatures::Feature> ArmFeatures::AllFeatures {
    {"FEAT_AES", &ArmFeatures::FEAT_AES},
    {"FEAT_BTI", &ArmFeatures::FEAT_BTI},
    {"FEAT_AMUv1", &ArmFeatures::FEAT_AMUv1},
    {"FEAT_AMUv1p1", &ArmFeatures::FEAT_AMUv1p1},
    {"FEAT_BF16", &ArmFeatures::FEAT_BF16},
    {"FEAT_CONSTPACFIELD", &ArmFeatures::FEAT_CONSTPACFIELD},
    {"FEAT_CSV2", &ArmFeatures::FEAT_CSV2},
    {"FEAT_CSV2_1p1", &ArmFeatures::FEAT_CSV2_1p1},
    {"FEAT_CSV2_1p2", &ArmFeatures::FEAT_CSV2_1p2},
    {"FEAT_CSV2_2", &ArmFeatures::FEAT_CSV2_2},
    {"FEAT_CSV2_3", &ArmFeatures::FEAT_CSV2_3},
    {"FEAT_CSV3", &ArmFeatures::FEAT_CSV3},
    {"FEAT_DIT", &ArmFeatures::FEAT_DIT},
    {"FEAT_DotProd", &ArmFeatures::FEAT_DotProd},
    {"FEAT_EBF16", &ArmFeatures::FEAT_EBF16},
    {"FEAT_EPAC", &ArmFeatures::FEAT_EPAC},
    {"FEAT_FHM", &ArmFeatures::FEAT_FHM},
    {"FEAT_FlagM", &ArmFeatures::FEAT_FlagM},
    {"FEAT_FlagM2", &ArmFeatures::FEAT_FlagM2},
    {"FEAT_FP", &ArmFeatures::FEAT_FP},
    {"FEAT_FP16", &ArmFeatures::FEAT_FP16},
    {"FEAT_FPAC", &ArmFeatures::FEAT_FPAC},
    {"FEAT_FPACCOMBINE", &ArmFeatures::FEAT_FPACCOMBINE},
    {"FEAT_FRINTTS", &ArmFeatures::FEAT_FRINTTS},
    {"FEAT_HBC", &ArmFeatures::FEAT_HBC},
    {"FEAT_LSE", &ArmFeatures::FEAT_LSE},
    {"FEAT_MOPS", &ArmFeatures::FEAT_MOPS},
    {"FEAT_MTE", &ArmFeatures::FEAT_MTE},
    {"FEAT_MTE2", &ArmFeatures::FEAT_MTE2},
    {"FEAT_MTE3", &ArmFeatures::FEAT_MTE3},
    {"FEAT_NMI", &ArmFeatures::FEAT_NMI},
    {"FEAT_PACIMP", &ArmFeatures::FEAT_PACIMP},
    {"FEAT_PACQARMA3", &ArmFeatures::FEAT_PACQARMA3},
    {"FEAT_PACQARMA5", &ArmFeatures::FEAT_PACQARMA5},
    {"FEAT_PAuth", &ArmFeatures::FEAT_PAuth},
    {"FEAT_PAuth2", &ArmFeatures::FEAT_PAuth2},
    {"FEAT_PMULL", &ArmFeatures::FEAT_PMULL},
    {"FEAT_RAS", &ArmFeatures::FEAT_RAS},
    {"FEAT_RASv1p1", &ArmFeatures::FEAT_RASv1p1},
    {"FEAT_RDM", &ArmFeatures::FEAT_RDM},
    {"FEAT_RME", &ArmFeatures::FEAT_RME},
    {"FEAT_RNG", &ArmFeatures::FEAT_RNG},
    {"FEAT_SEL2", &ArmFeatures::FEAT_SEL2},
    {"FEAT_SHA1", &ArmFeatures::FEAT_SHA1},
    {"FEAT_SHA256", &ArmFeatures::FEAT_SHA256},
    {"FEAT_SHA512", &ArmFeatures::FEAT_SHA512},
    {"FEAT_SHA3", &ArmFeatures::FEAT_SHA3},
    {"FEAT_SM3", &ArmFeatures::FEAT_SM3},
    {"FEAT_SM4", &ArmFeatures::FEAT_SM4},
    {"FEAT_SME", &ArmFeatures::FEAT_SME},
    {"FEAT_SPECRES", &ArmFeatures::FEAT_SPECRES},
    {"FEAT_SSBS", &ArmFeatures::FEAT_SSBS},
    {"FEAT_SSBS2", &ArmFeatures::FEAT_SSBS2},
    {"FEAT_SVE", &ArmFeatures::FEAT_SVE},
    {"FEAT_TLBIOS", &ArmFeatures::FEAT_TLBIOS},
    {"FEAT_TLBIRANGE", &ArmFeatures::FEAT_TLBIRANGE},
};
