//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// A class describing the features of an Arm64 processor.
//
//----------------------------------------------------------------------------

#include "restrictions.h"
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
        reg.read(CSR_REGID_TCR, _tcr) &&
        reg.read(CSR_REGID_CTR, _ctr) &&
        (!csr_has_ete(_aa64dfr0) || reg.read(CSR_REGID_TRCDEVARCH, _trcdevarch));

#if !defined(CSR_SKIP_PMMIR)
    _loaded = _loaded &&
        (!csr_has_pmuv3p4(_aa64dfr0) || reg.read(CSR_REGID_PMMIR, _pmmir));
#endif

    return _loaded;
}

//----------------------------------------------------------------------------
// Load features using direct access to system registers in userland.
// Works on Linux thanks to mrs emulation. Trap on other systems.
//----------------------------------------------------------------------------

void ArmFeatures::loadDirect()
{
    // Linux kernel emulates access to system registers of the following ranges:
    // Op0=3, Op1=0, CRn=0, CRm=0,2,3,4,5,6,7
    // Excluded registers: TCR_EL1, TRCDEVARCH, PMMIR_EL1
    _aa64smfr0 = _aa64zfr0 = _tcr = _trcdevarch = _pmmir = 0;

    csr_mrs_str(_aa64isar0, "id_aa64isar0_el1");
    csr_mrs_str(_aa64isar1, "id_aa64isar1_el1");
    csr_mrs_str(_aa64isar2, "id_aa64isar2_el1");
    csr_mrs_str(_aa64pfr0,  "id_aa64pfr0_el1");
    csr_mrs_str(_aa64pfr1,  "id_aa64pfr1_el1");
    csr_mrs_str(_aa64dfr0,  "id_aa64dfr0_el1");
    csr_mrs_str(_aa64mmfr0, "id_aa64mmfr0_el1");
    csr_mrs_str(_aa64mmfr1, "id_aa64mmfr1_el1");
    csr_mrs_str(_aa64mmfr2, "id_aa64mmfr2_el1");
    csr_mrs_str(_ctr,       "ctr_el0");
    if (csr_has_sme(_aa64pfr1)) {
        csr_mrs_num(_aa64smfr0, CSR_SREG_ID_AA64SMFR0_EL1);
    }
    if (csr_has_sve(_aa64pfr0)) {
        csr_mrs_num(_aa64zfr0, CSR_SREG_ID_AA64ZFR0_EL1);
    }
    _loaded = true;
}


//----------------------------------------------------------------------------
// Descriptions of all features.
//----------------------------------------------------------------------------

const std::list<ArmFeatures::Feature> ArmFeatures::AllFeatures {
    // Automatically generated file:
    #include "_features.h"
};
