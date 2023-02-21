//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// A class implementing some pseudo-code functions from the
// Arm Architecture Reference Manual.
//
//----------------------------------------------------------------------------

#include "armpseudocode.h"


// Constructor.
ArmPseudoCode::ArmPseudoCode(RegAccess& regs) :
    _regs(regs),
    _features(regs)
{
}

// ==== shared/functions/memory/EffectiveTBI
// Returns the effective TBI (top-byte ignore) in the AArch64 stage 1 translation regime for EL0/EL1.
bool ArmPseudoCode::EffectiveTBI(uint64_t address, bool is_instr)
{
    // Translation regine is always EL1, when coming from EL0 or EL1, without inner access.
    const bool bit55 = (address & (1ull << 55));
    const bool tbi = bit55 ? _features.TCR_EL1_TBI1() : _features.TCR_EL1_TBI0();
    const bool pacext = _features.FEAT_PAuth();
    const bool tbid = pacext && bit55 ? _features.TCR_EL1_TBID1() : _features.TCR_EL1_TBID0();
    return tbi && (!pacext || !tbid || !is_instr);
}

// ==== shared/functions/memory/EffectiveMTX
// Returns the effective MTX (memory tagging extension) in the AArch64 stage 1 translation regime for EL0/EL1.
bool ArmPseudoCode::EffectiveMTX(uint64_t address, bool is_instr)
{
    // Translation regine is always EL1, when coming from EL0 or EL1, without inner access.
    if (!_features.FEAT_MTE4() || is_instr) {
        return false;
    }
    else {
        return (address & (1ull << 55)) ? _features.TCR_EL1_MTX1() : _features.TCR_EL1_MTX0();
    }
}
