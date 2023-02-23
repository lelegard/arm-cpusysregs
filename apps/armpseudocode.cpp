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
ArmPseudoCode::ArmPseudoCode(ArmFeatures& feat) :
    _feat(feat)
{
}

// TGxGranuleBits()
// ================
// Retrieve the address size, in bits, of a granule
int ArmPseudoCode::TGxGranuleBits(TGx tgx)
{
    switch (tgx) {
        case TGx_4KB:  return 12;
        case TGx_16KB: return 14;
        case TGx_64KB: return 16;
        default:       return 0;
    }
}

// ==== shared/functions/memory/EffectiveTBI
// Returns the effective TBI (top-byte ignore) in the AArch64 stage 1 translation regime for EL0/EL1.
bool ArmPseudoCode::EffectiveTBI(uint64_t address, bool is_instr)
{
    // Translation regine is always EL1, when coming from EL0 or EL1, without inner access.
    const bool bit55 = (address & (1ull << 55));
    const bool tbi = bit55 ? _feat.TCR_EL1_TBI1() : _feat.TCR_EL1_TBI0();
    const bool pacext = _feat.FEAT_PAuth();
    const bool tbid = pacext && bit55 ? _feat.TCR_EL1_TBID1() : _feat.TCR_EL1_TBID0();
    return tbi && (!pacext || !tbid || !is_instr);
}

// ==== shared/functions/memory/EffectiveMTX
// Returns the effective MTX (memory tagging extension) in the AArch64 stage 1 translation regime for EL0/EL1.
bool ArmPseudoCode::EffectiveMTX(uint64_t address, bool is_instr)
{
    // Translation regine is always EL1, when coming from EL0 or EL1, without inner access.
    if (!_feat.FEAT_MTE4() || is_instr) {
        return false;
    }
    else {
        return (address & (1ull << 55)) ? _feat.TCR_EL1_MTX1() : _feat.TCR_EL1_MTX0();
    }
}

// ==== aarch64/functions/pac/addpac/AddPAC
// Some intermediate functions, used to implement AddPAC(), also useful outside.
// See AddPAC() pseudo code in Arm manual for details.
int ArmPseudoCode::pacTopBit(uint64_t address, bool is_instr)
{
    return EffectiveTBI(address, is_instr) ? 55 : 63;
}
int ArmPseudoCode::pacSelBit(uint64_t address, bool is_instr)
{
    // if HaveEnhancedPAC2() && ConstPACField() then selbit = ptr<55>;
    if (_feat.FEAT_PAuth2() && _feat.FEAT_CONSTPACFIELD()) {
        return 55;
    }
    // PtrHasUpperAndLowerAddRanges() should be true at EL0 (?)
    // S1TranslationRegime() should be EL1.
    // Consequently, applicable pseudocode is:
    //   if data then
    //       if TCR_EL1.TBI1 == '1' || TCR_EL1.TBI0 == '1' then
    //           selbit = ptr<55>;
    //       else
    //           selbit = ptr<63>;
    //   else
    //       if ((TCR_EL1.TBI1 == '1' && TCR_EL1.TBID1 == '0') ||
    //           (TCR_EL1.TBI0 == '1' && TCR_EL1.TBID0 == '0')) then
    //           selbit = ptr<55>;
    //       else
    //           selbit = ptr<63>;
    if (!is_instr) {
        return (_feat.TCR_EL1_TBI1() == 1 || _feat.TCR_EL1_TBI0() == 1) ? 55 : 63;
    }
    else {
        return ((_feat.TCR_EL1_TBI1() == 1 && _feat.TCR_EL1_TBID1() == 0) ||
                (_feat.TCR_EL1_TBI0() == 1 && _feat.TCR_EL1_TBID0() == 0)) ?
                55 : 63;
    }
}
int ArmPseudoCode::pacBottomBit(uint64_t address, bool is_instr)
{
    // Reference: ISA_A64_xml_A_profile-2022-12.pdf
    // CalculateBottomPACBit() page 4871
    // AArch64.PACEffectiveTxSZ() page 4871
    // AArch64.S1TTWParamsEL10() page 5076
    // walkparams: need 

    return -1; //@@@@@
}
