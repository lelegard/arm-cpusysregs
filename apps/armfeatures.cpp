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
#include "restrictions.h"


//----------------------------------------------------------------------------
// Clear contents.
//----------------------------------------------------------------------------

void ArmFeatures::clear()
{
    _loaded = false;
    _aa64isar0 = _aa64isar1 = _aa64isar2 = _aa64isar3 = _aa64pfr0 = _aa64pfr1 = _aa64pfr2 = 0;
    _aa64dfr0 = _aa64dfr1 = _aa64dfr2 = _aa64fpfr0 = 0;
    _aa64mmfr0 = _aa64mmfr1 = _aa64mmfr2 = _aa64mmfr3 = _aa64mmfr4 = _aa64smfr0 = _aa64zfr0 = 0;
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
    _loaded =
        reg.read(CSR_REGID_ID_AA64ISAR0_EL1, _aa64isar0) &&
        reg.read(CSR_REGID_ID_AA64ISAR1_EL1, _aa64isar1) &&
        reg.read(CSR_REGID_ID_AA64ISAR2_EL1, _aa64isar2) &&
        reg.read(CSR_REGID_ID_AA64ISAR3_EL1, _aa64isar3) &&
        reg.read(CSR_REGID_ID_AA64PFR0_EL1, _aa64pfr0) &&
        reg.read(CSR_REGID_ID_AA64PFR1_EL1, _aa64pfr1) &&
        reg.read(CSR_REGID_ID_AA64PFR2_EL1, _aa64pfr2) &&
        reg.read(CSR_REGID_ID_AA64DFR0_EL1, _aa64dfr0) &&
        reg.read(CSR_REGID_ID_AA64DFR1_EL1, _aa64dfr1) &&
        reg.read(CSR_REGID_ID_AA64DFR2_EL1, _aa64dfr2) &&
        reg.read(CSR_REGID_ID_AA64FPFR0_EL1, _aa64fpfr0) &&
        reg.read(CSR_REGID_ID_AA64MMFR0_EL1, _aa64mmfr0) &&
        reg.read(CSR_REGID_ID_AA64MMFR1_EL1, _aa64mmfr1) &&
        reg.read(CSR_REGID_ID_AA64MMFR2_EL1, _aa64mmfr2) &&
        reg.read(CSR_REGID_ID_AA64MMFR3_EL1, _aa64mmfr3) &&
        reg.read(CSR_REGID_ID_AA64MMFR4_EL1, _aa64mmfr4) &&
        reg.read(CSR_REGID_ID_ISAR0_EL1, _isar0) &&
        reg.read(CSR_REGID_ID_ISAR1_EL1, _isar1) &&
        reg.read(CSR_REGID_ID_ISAR2_EL1, _isar2) &&
        reg.read(CSR_REGID_ID_ISAR3_EL1, _isar3) &&
        reg.read(CSR_REGID_ID_ISAR4_EL1, _isar4) &&
        reg.read(CSR_REGID_ID_ISAR5_EL1, _isar5) &&
        reg.read(CSR_REGID_ID_ISAR6_EL1, _isar6) &&
        reg.read(CSR_REGID_ID_MMFR0_EL1, _mmfr0) &&
        reg.read(CSR_REGID_ID_MMFR1_EL1, _mmfr1) &&
        reg.read(CSR_REGID_ID_MMFR2_EL1, _mmfr2) &&
        reg.read(CSR_REGID_ID_MMFR3_EL1, _mmfr3) &&
        reg.read(CSR_REGID_ID_MMFR4_EL1, _mmfr4) &&
        reg.read(CSR_REGID_ID_MMFR5_EL1, _mmfr5) &&
        reg.read(CSR_REGID_ID_PFR0_EL1, _pfr0) &&
        reg.read(CSR_REGID_ID_PFR1_EL1, _pfr1) &&
        reg.read(CSR_REGID_ID_PFR2_EL1, _pfr2) &&
        (!csr_has_sme(_aa64pfr1) || reg.read(CSR_REGID_ID_AA64SMFR0_EL1, _aa64smfr0)) &&
        (!csr_has_sve(_aa64pfr0) || reg.read(CSR_REGID_ID_AA64ZFR0_EL1, _aa64zfr0)) &&
        reg.read(CSR_REGID_TCR_EL1, _tcr) &&
        (!csr_has_tcr2(_aa64mmfr3) || reg.read(CSR_REGID_TCR2_EL1, _tcr2)) &&
        (!csr_has_ete(_aa64dfr0) || reg.read(CSR_REGID_TRCDEVARCH, _trcdevarch)) &&
        (!csr_has_pmuv3p4(_aa64dfr0) || reg.read(CSR_REGID_PMMIR_EL1, _pmmir));

#if !defined(CSR_AVOID_CTR_EL0)
    _loaded = _loaded &&
        reg.read(CSR_REGID_CTR_EL0, _ctr);
#endif

#if !defined(CSR_AVOID_PMSIDR_EL1)
    _loaded = _loaded &&
        (!csr_has_spe(_aa64dfr0) || reg.read(CSR_REGID_PMSIDR_EL1, _pmsidr));
#endif

    return _loaded;
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

    csr_mrs(_aa64isar0, CSR_SREG_ID_AA64ISAR0_EL1);
    csr_mrs(_aa64isar1, CSR_SREG_ID_AA64ISAR1_EL1);
    csr_mrs(_aa64isar2, CSR_SREG_ID_AA64ISAR2_EL1);
    csr_mrs(_aa64isar3, CSR_SREG_ID_AA64ISAR3_EL1);
    csr_mrs(_aa64pfr0,  CSR_SREG_ID_AA64PFR0_EL1);
    csr_mrs(_aa64pfr1,  CSR_SREG_ID_AA64PFR1_EL1);
    csr_mrs(_aa64pfr2,  CSR_SREG_ID_AA64PFR2_EL1);
    csr_mrs(_aa64dfr0,  CSR_SREG_ID_AA64DFR0_EL1);
    csr_mrs(_aa64dfr1,  CSR_SREG_ID_AA64DFR1_EL1);
    csr_mrs(_aa64dfr2,  CSR_SREG_ID_AA64DFR2_EL1);
    csr_mrs(_aa64fpfr0, CSR_SREG_ID_AA64FPFR0_EL1);
    csr_mrs(_aa64mmfr0, CSR_SREG_ID_AA64MMFR0_EL1);
    csr_mrs(_aa64mmfr1, CSR_SREG_ID_AA64MMFR1_EL1);
    csr_mrs(_aa64mmfr2, CSR_SREG_ID_AA64MMFR2_EL1);
    csr_mrs(_aa64mmfr3, CSR_SREG_ID_AA64MMFR3_EL1);
    csr_mrs(_ctr,       CSR_SREG_CTR_EL0);
    if (csr_has_sme(_aa64pfr1)) {
        csr_mrs(_aa64smfr0, CSR_SREG_ID_AA64SMFR0_EL1);
    }
    if (csr_has_sve(_aa64pfr0)) {
        csr_mrs(_aa64zfr0, CSR_SREG_ID_AA64ZFR0_EL1);
    }
    _loaded = true;
}
