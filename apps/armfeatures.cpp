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
    _aa64pfr2(0),
    _aa64dfr0(0),
    _aa64dfr1(0),
    _aa64mmfr0(0),
    _aa64mmfr1(0),
    _aa64mmfr2(0),
    _aa64mmfr3(0),
    _aa64smfr0(0),
    _aa64zfr0(0),
    _isar0(0),
    _isar1(0),
    _isar2(0),
    _isar3(0),
    _isar4(0),
    _isar5(0),
    _isar6(0),
    _mmfr0(0),
    _mmfr1(0),
    _mmfr2(0),
    _mmfr3(0),
    _mmfr4(0),
    _mmfr5(0),
    _pfr0(0),
    _pfr1(0),
    _pfr2(0),
    _ctr(0),
    _tcr(0),
    _tcr2(0),
    _trcdevarch(0),
    _pmmir(0),
    _pmsidr(0)
{
}

ArmFeatures::ArmFeatures(RegAccess& reg) :
    ArmFeatures()
{
    load(reg);
}

void ArmFeatures::clear()
{
    _loaded = false;
    _aa64isar0 = _aa64isar1 = _aa64isar2 = _aa64pfr0 = _aa64pfr1 = _aa64pfr2 = _aa64dfr0 = _aa64dfr1 = 0;
    _aa64mmfr0 = _aa64mmfr1 = _aa64mmfr2 = _aa64mmfr3 = _aa64smfr0 = _aa64zfr0 = 0;
    _isar0 = _isar1 = _isar2 = _isar3 = _isar4 = _isar5 = _isar6 = 0;
    _mmfr0 = _mmfr1 = _mmfr2 = _mmfr3 = _mmfr4 = _mmfr5 = 0;
    _ctr = _tcr = _tcr2 = _trcdevarch = _pmmir = _pmsidr = 0;
}


//----------------------------------------------------------------------------
// Synthetic features of the processor.
//----------------------------------------------------------------------------

// Supports PACGA in addition to PACIx and PACDx.
bool ArmFeatures::hasPACGA() const
{
    return ID_AA64ISAR1_EL1_GPI() >= 1 || ID_AA64ISAR1_EL1_GPA() >= 1 || ID_AA64ISAR2_EL1_GPA3() >= 1;
}

// Get the name of the PAC generation algorithm.
std::string ArmFeatures::pacAlgo() const
{
    if (FEAT_PACQARMA5()) {
        return "QARMA5";
    }
    else if (FEAT_PACQARMA3()) {
        return "QARMA3";
    }
    else if (FEAT_PACIMP()) {
        return "implementation-defined";
    }
    else {
        return "none";
    }
}

// Get the number of QARMA rounds on this platform. Return 5 for QARMA5, 3 for QARMA3, 0 if none supported.
int ArmFeatures::pacQARMA() const
{
    if (FEAT_PACQARMA5()) {
        return 5;
    }
    else if (FEAT_PACQARMA3()) {
        return 3;
    }
    else {
        return 0;
    }
}


//----------------------------------------------------------------------------
// Load features from the system registers.
//----------------------------------------------------------------------------

bool ArmFeatures::load(RegAccess& reg)
{
    clear();
    return _loaded =
        reg.read(CSR_REGID_AA64ISAR0, _aa64isar0) &&
        reg.read(CSR_REGID_AA64ISAR1, _aa64isar1) &&
        reg.read(CSR_REGID_AA64ISAR2, _aa64isar2) &&
        reg.read(CSR_REGID_AA64PFR0, _aa64pfr0) &&
        reg.read(CSR_REGID_AA64PFR1, _aa64pfr1) &&
        reg.read(CSR_REGID_AA64PFR2, _aa64pfr2) &&
        reg.read(CSR_REGID_AA64DFR0, _aa64dfr0) &&
        reg.read(CSR_REGID_AA64DFR1, _aa64dfr1) &&
        reg.read(CSR_REGID_AA64MMFR0, _aa64mmfr0) &&
        reg.read(CSR_REGID_AA64MMFR1, _aa64mmfr1) &&
        reg.read(CSR_REGID_AA64MMFR2, _aa64mmfr2) &&
        reg.read(CSR_REGID_AA64MMFR3, _aa64mmfr3) &&
        reg.read(CSR_REGID_ISAR0, _isar0) &&
        reg.read(CSR_REGID_ISAR1, _isar1) &&
        reg.read(CSR_REGID_ISAR2, _isar2) &&
        reg.read(CSR_REGID_ISAR3, _isar3) &&
        reg.read(CSR_REGID_ISAR4, _isar4) &&
        reg.read(CSR_REGID_ISAR5, _isar5) &&
        reg.read(CSR_REGID_ISAR6, _isar6) &&
        reg.read(CSR_REGID_MMFR0, _mmfr0) &&
        reg.read(CSR_REGID_MMFR1, _mmfr1) &&
        reg.read(CSR_REGID_MMFR2, _mmfr2) &&
        reg.read(CSR_REGID_MMFR3, _mmfr3) &&
        reg.read(CSR_REGID_MMFR4, _mmfr4) &&
        reg.read(CSR_REGID_MMFR5, _mmfr5) &&
        reg.read(CSR_REGID_PFR0, _pfr0) &&
        reg.read(CSR_REGID_PFR1, _pfr1) &&
        reg.read(CSR_REGID_PFR2, _pfr2) &&
        (!csr_has_sme(_aa64pfr1) || reg.read(CSR_REGID_AA64SMFR0, _aa64smfr0)) &&
        (!csr_has_sve(_aa64pfr0) || reg.read(CSR_REGID_AA64ZFR0, _aa64zfr0)) &&
        reg.read(CSR_REGID_TCR, _tcr) &&
        (!csr_has_tcr2(_aa64mmfr3) || reg.read(CSR_REGID_TCR2, _tcr2)) &&
        reg.read(CSR_REGID_CTR, _ctr) &&
        (!csr_has_ete(_aa64dfr0) || reg.read(CSR_REGID_TRCDEVARCH, _trcdevarch)) &&
        (!csr_has_pmuv3p4(_aa64dfr0) || reg.read(CSR_REGID_PMMIR, _pmmir)) &&
        (!csr_has_spe(_aa64dfr0) || reg.read(CSR_REGID_PMSIDR, _pmsidr));
}

//----------------------------------------------------------------------------
// Load features using direct access to system registers in userland.
// Works on Linux thanks to mrs emulation. Trap on other systems.
//----------------------------------------------------------------------------

void ArmFeatures::loadDirect()
{
    clear();

    // Linux kernel emulates access to system registers of the following ranges:
    // Op0=3, Op1=0, CRn=0, CRm=0,2,3,4,5,6,7

    csr_mrs_str(_aa64isar0, "id_aa64isar0_el1");
    csr_mrs_str(_aa64isar1, "id_aa64isar1_el1");
    csr_mrs_str(_aa64isar2, "id_aa64isar2_el1");
    csr_mrs_str(_aa64pfr0,  "id_aa64pfr0_el1");
    csr_mrs_str(_aa64pfr1,  "id_aa64pfr1_el1");
    csr_mrs_num(_aa64pfr2,  CSR_SREG_ID_AA64PFR2_EL1);
    csr_mrs_str(_aa64dfr0,  "id_aa64dfr0_el1");
    csr_mrs_str(_aa64dfr1,  "id_aa64dfr1_el1");
    csr_mrs_str(_aa64mmfr0, "id_aa64mmfr0_el1");
    csr_mrs_str(_aa64mmfr1, "id_aa64mmfr1_el1");
    csr_mrs_str(_aa64mmfr2, "id_aa64mmfr2_el1");
    csr_mrs_num(_aa64mmfr3, CSR_SREG_ID_AA64MMFR3_EL1);
    csr_mrs_str(_ctr,       "ctr_el0");
    if (csr_has_sme(_aa64pfr1)) {
        csr_mrs_num(_aa64smfr0, CSR_SREG_ID_AA64SMFR0_EL1);
    }
    if (csr_has_sve(_aa64pfr0)) {
        csr_mrs_num(_aa64zfr0, CSR_SREG_ID_AA64ZFR0_EL1);
    }
    _loaded = true;
}
