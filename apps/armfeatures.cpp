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
    _aa64dfr0(0),
    _aa64mmfr0(0),
    _aa64mmfr1(0),
    _aa64mmfr2(0),
    _aa64smfr0(0),
    _aa64zfr0(0),
    _ctr(0),
    _tcr(0),
    _trcdevarch(0),
    _pmmir(0)
{
}

ArmFeatures::ArmFeatures(RegAccess& reg) :
    ArmFeatures()
{
    load(reg);
}


//----------------------------------------------------------------------------
// Load features from the system registers.
//----------------------------------------------------------------------------

bool ArmFeatures::load(RegAccess& reg)
{
    // These registers may not exist on this CPU.
    _aa64smfr0 = _aa64zfr0 = _trcdevarch = _pmmir = 0;

    _loaded =
        reg.read(CSR_REGID_AA64ISAR0, _aa64isar0) &&
        reg.read(CSR_REGID_AA64ISAR1, _aa64isar1) &&
        reg.read(CSR_REGID_AA64ISAR2, _aa64isar2) &&
        reg.read(CSR_REGID_AA64PFR0, _aa64pfr0) &&
        reg.read(CSR_REGID_AA64PFR1, _aa64pfr1) &&
        reg.read(CSR_REGID_AA64DFR0, _aa64dfr0) &&
        reg.read(CSR_REGID_AA64MMFR0, _aa64mmfr0) &&
        reg.read(CSR_REGID_AA64MMFR1, _aa64mmfr1) &&
        reg.read(CSR_REGID_AA64MMFR2, _aa64mmfr2) &&
        (!csr_has_sme(_aa64pfr1) || reg.read(CSR_REGID_AA64SMFR0, _aa64smfr0)) &&
        (!csr_has_sve(_aa64pfr0) || reg.read(CSR_REGID_AA64ZFR0, _aa64zfr0)) &&
        reg.read(CSR_REGID_CTR, _ctr) &&
        reg.read(CSR_REGID_TCR, _tcr) &&
        (!csr_has_ete(_aa64dfr0) || reg.read(CSR_REGID_TRCDEVARCH, _trcdevarch)) &&
        (!csr_has_pmuv3p4(_aa64dfr0) || reg.read(CSR_REGID_PMMIR, _pmmir));

    return _loaded;
}


//----------------------------------------------------------------------------
// Descriptions of all features.
//----------------------------------------------------------------------------

const std::list<ArmFeatures::Feature> ArmFeatures::AllFeatures {
    // Automatically generated file:
    #include "_features.h"
};
