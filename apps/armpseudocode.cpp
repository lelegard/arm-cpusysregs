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
#include "qarma64.h"
#include "strutils.h"
#include <cstring>
#include <cassert>

// Constructor.
ArmPseudoCode::ArmPseudoCode(RegAccess& regs) :
    _regs(regs),
    _feat(regs)
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

// AArch64.S1DecodeTG0()
// =====================
// Decode stage 1 granule size configuration bits TG0
ArmPseudoCode::TGx ArmPseudoCode::AArch64_S1DecodeTG0(int tg0)
{
    switch (tg0) {
        case 0b00: return TGx_4KB;
        case 0b01: return TGx_64KB;
        case 0b10: return TGx_16KB;
        default:   return TGx_4KB;
    }
}

// AArch64.S1DecodeTG1()
// =====================
// Decode stage 1 granule size configuration bits TG1
ArmPseudoCode::TGx ArmPseudoCode::AArch64_S1DecodeTG1(int tg1)
{
    switch (tg1) {
        case 0b10: return TGx_4KB;
        case 0b11: return TGx_64KB;
        case 0b01: return TGx_16KB;
        default:   return TGx_4KB;
    }
}

// AArch64.GetVARange()
// ====================
// Determines if the VA that is to be translated lies in LOWER or UPPER address range.
ArmPseudoCode::VARange ArmPseudoCode::AArch64_GetVARange(csr_u64_t va)
{
    return ((va >> 55) & 1) ? VARange_UPPER : VARange_LOWER;
}

// AArch64.GetS1TTWParams()
// ========================
// Returns stage 1 translation table walk parameters from respective controlling System registers.
void ArmPseudoCode::AArch64_GetS1TTWParams(S1TTWParams& walkparams, csr_u64_t  va)
{
    AArch64_S1TTWParamsEL10(walkparams, AArch64_GetVARange(va));
}

// AArch64.S1TTWParamsEL10()
// =========================
// Gather stage 1 translation table walk parameters for EL1&0 regime (with EL2 enabled or disabled)
void ArmPseudoCode::AArch64_S1TTWParamsEL10(S1TTWParams& walkparams, VARange varange)
{
    bzero(&walkparams, sizeof(walkparams));

    // Currently ignore 128-bit registers.
    if (varange == VARange_LOWER) {
        walkparams.tgx   = AArch64_S1DecodeTG0(_feat.TCR_EL1_TG0());
        walkparams.txsz  = _feat.TCR_EL1_T0SZ();
        walkparams.irgn  = _feat.TCR_EL1_IRGN0();
        walkparams.orgn  = _feat.TCR_EL1_ORGN0();
        walkparams.sh    = _feat.TCR_EL1_SH0();
        walkparams.tbi   = _feat.TCR_EL1_TBI0();
        walkparams.nfd   = _feat.FEAT_SVE() || _feat.FEAT_TME() ? _feat.TCR_EL1_NFD0() : 0;
        walkparams.tbid  = _feat.FEAT_PAuth() ? _feat.TCR_EL1_TBID0() : 0;
        walkparams.e0pd  = _feat.FEAT_E0PD() ? _feat.TCR_EL1_E0PD0() : 0;
        walkparams.hpd   = _feat.FEAT_HPDS() ? _feat.TCR_EL1_HPD0() : 0;
        walkparams.mtx   = _feat.FEAT_MTE4() ? _feat.TCR_EL1_MTX0() : 0;
    }
    else {
        walkparams.tgx   = AArch64_S1DecodeTG1(_feat.TCR_EL1_TG1());
        walkparams.txsz  = _feat.TCR_EL1_T1SZ();
        walkparams.irgn  = _feat.TCR_EL1_IRGN1();
        walkparams.orgn  = _feat.TCR_EL1_ORGN1();
        walkparams.sh    = _feat.TCR_EL1_SH1();
        walkparams.tbi   = _feat.TCR_EL1_TBI1();
        walkparams.nfd   = _feat.FEAT_SVE() || _feat.FEAT_TME() ? _feat.TCR_EL1_NFD1() : 0;
        walkparams.tbid  = _feat.FEAT_PAuth() ? _feat.TCR_EL1_TBID1() : 0;
        walkparams.e0pd  = _feat.FEAT_E0PD() ? _feat.TCR_EL1_E0PD1() : 0;
        walkparams.hpd   = _feat.FEAT_HPDS() ? _feat.TCR_EL1_HPD1() : 0;
        walkparams.mtx   = _feat.FEAT_MTE4() ? _feat.TCR_EL1_MTX1() : 0;
    }
    
    _regs.read(CSR_REGID_MAIR_EL1, walkparams.mair);
    if (_feat.FEAT_AIE()) {
        _regs.read(CSR_REGID_MAIR2_EL1, walkparams.mair2);
    }

    csr_u64_t sctlr = 0;
    _regs.read(CSR_REGID_SCTLR_EL1, sctlr);

    walkparams.aie  = _feat.FEAT_AIE() && _feat.FEAT_TCR2() ? _feat.TCR2_EL1_AIE() : 0;
    walkparams.wxn  = (sctlr >> 19) & 0x01; // STLR_EL1.WXN
    walkparams.ps   = _feat.TCR_EL1_IPS();
    walkparams.ee   = (sctlr >> 25) & 0x01; // SCTLR_EL1.EE
    walkparams.ntlsmd = _feat.FEAT_LSMAOC() ? ((sctlr >> 28) & 0x01) : 1; // SCTLR_EL1.nTLSMD
    walkparams.cmow = _feat.FEAT_CMOW() ? ((sctlr >> 32) & 0x01) : 0; // SCTLR_EL1.CMOW
    walkparams.ha   = _feat.FEAT_HAFDBS() ? _feat.TCR_EL1_HA() : 0;
    walkparams.hd   = _feat.FEAT_HAFDBS() ? _feat.TCR_EL1_HD() : 0;
    if ((walkparams.tgx == TGx_4KB || walkparams.tgx == TGx_16KB) && _feat.FEAT_LPA2()) {
        walkparams.ds = _feat.TCR_EL1_DS();
    }
    else {
        walkparams.ds = 0;
    }
    walkparams.pie = _feat.FEAT_S1PIE() && _feat.FEAT_TCR2() ? _feat.TCR2_EL1_PIE() : 0;
    if (_feat.FEAT_S1PIE()) {
        _regs.read(CSR_REGID_PIR_EL1, walkparams.pir);
        if (!walkparams.nv1) {
            _regs.read(CSR_REGID_PIRE0_EL1, walkparams.pire0);
        }
    }
    if (_feat.FEAT_PAN3()) {
        walkparams.epan = !walkparams.pie ? ((sctlr >> 57) & 0x01) : 1; // SCTLR_EL1.EPAN
    }
    else {
        walkparams.epan = 0;
    }
    if (_feat.FEAT_THE() && _feat.FEAT_TCR2()) {
        walkparams.pnch = _feat.TCR2_EL1_PnCH();
    }
    else {
        walkparams.pnch = 0;
    }
    if (_feat.FEAT_HAFT() && walkparams.ha && _feat.FEAT_TCR2()) {
        walkparams.haft = _feat.TCR2_EL1_HAFT();
    }
    else {
        walkparams.haft = 0;
    }
    // No access to SCTLR2_EL2.EMEC()
}

// EffectiveTBI()
// ==============
// Returns the effective TBI (top-byte ignore) in the AArch64 stage 1 translation regime for EL0/EL1.
bool ArmPseudoCode::EffectiveTBI(csr_u64_t address, bool is_instr)
{
    // Translation regine is always EL1, when coming from EL0 or EL1, without inner access.
    const bool bit55 = (address & (1ull << 55));
    const bool tbi = bit55 ? _feat.TCR_EL1_TBI1() : _feat.TCR_EL1_TBI0();
    const bool pacext = _feat.FEAT_PAuth();
    const bool tbid = pacext && bit55 ? _feat.TCR_EL1_TBID1() : _feat.TCR_EL1_TBID0();
    return tbi && (!pacext || !tbid || !is_instr);
}

// EffectiveMTX()
// ==============
// Returns the effective MTX (memory tagging extension) in the AArch64 stage 1 translation regime for EL0/EL1.
bool ArmPseudoCode::EffectiveMTX(csr_u64_t address, bool is_instr)
{
    // Translation regine is always EL1, when coming from EL0 or EL1, without inner access.
    if (!_feat.FEAT_MTE4() || is_instr) {
        return false;
    }
    else {
        return (address & (1ull << 55)) ? _feat.TCR_EL1_MTX1() : _feat.TCR_EL1_MTX0();
    }
}

// AArch64.MaxTxSZ()
// =================
// Retrieve the maximum value of TxSZ indicating minimum input address size for both stages of translation
int ArmPseudoCode::AArch64_MaxTxSZ(TGx tgx)
{
    if (_feat.FEAT_TTST()) {
        switch (tgx) {
            case TGx_4KB:  return 48;
            case TGx_16KB: return 48;
            case TGx_64KB: return 47;
        }
    }
    return 39;
}

// AArch64.S1MinTxSZ()
// ===================
// Retrieve the minimum value of TxSZ indicating maximum input address size for stage 1
int ArmPseudoCode::AArch64_S1MinTxSZ(bool d128, bool ds, TGx tgx)
{
    if (_feat.FEAT_LVA3() && d128) {
        // Assume HasUnprivileged(regime)
        return 9;
    }
    if ((_feat.FEAT_LVA() && tgx == TGx_64KB) || ds) {
        return 12;
    }
    return 16;
}

// AArch64.PACEffectiveTxSZ()
// ==========================
// Compute the effective value for TxSZ used to determine the placement of the PAC field
int ArmPseudoCode::AArch64_PACEffectiveTxSZ(const S1TTWParams& walkparams)
{
    const int s1maxtxsz = AArch64_MaxTxSZ(walkparams.tgx);
    const int s1mintxsz = AArch64_S1MinTxSZ(walkparams.d128, walkparams.ds, walkparams.tgx);
    
    // Assume no AArch64.S1TxSZFaults(walkparams)
    if (walkparams.txsz < s1mintxsz) {
        return s1mintxsz & 0x3F;
    }
    if (walkparams.txsz > s1maxtxsz) {
        return s1maxtxsz & 0x3F;
    }
    return walkparams.txsz;
}

// ComputePAC()
// ============
csr_u64_t ArmPseudoCode::ComputePAC(csr_u64_t data, csr_u64_t modifier, csr_u64_t key0, csr_u64_t key1, bool isgeneric)
{
    if (UsePACIMP(isgeneric)) {
        return ComputePACIMPDEF(data, modifier, key0, key1);
    }
    if (UsePACQARMA3(isgeneric)) {
        return ComputePACQARMA(data, modifier, key0, key1, true);
    }
    if (UsePACQARMA5(isgeneric)) {
        return ComputePACQARMA(data, modifier, key0, key1, false);
    }
    return 0; // unimplemented
}

// UsePACIMP()
// ===========
// Checks whether IMPLEMENTATION DEFINED cryptographic algorithm to be used for PAC calculation.
bool ArmPseudoCode::UsePACIMP(bool isgeneric)
{
    return isgeneric ? _feat.ID_AA64ISAR1_EL1_GPI() >= 1 : _feat.ID_AA64ISAR1_EL1_API() >= 1;
}

// UsePACQARMA3()
// ==============
// Checks whether QARMA3 cryptographic algorithm to be used for PAC calculation.
bool ArmPseudoCode::UsePACQARMA3(bool isgeneric)
{
    return isgeneric ? _feat.ID_AA64ISAR2_EL1_GPA3() >= 1 : _feat.ID_AA64ISAR2_EL1_APA3() >= 1;
}

// UsePACQARMA5()
// ==============
// Checks whether QARMA5 cryptographic algorithm to be used for PAC calculation.
bool ArmPseudoCode::UsePACQARMA5(bool isgeneric)
{
    return isgeneric ? _feat.ID_AA64ISAR1_EL1_GPA() >= 1 : _feat.ID_AA64ISAR1_EL1_APA() >= 1;
}

// ComputePACIMPDEF()
// ==================
// Compute IMPLEMENTATION DEFINED cryptographic algorithm to be used for PAC calculation.
csr_u64_t ArmPseudoCode::ComputePACIMPDEF(csr_u64_t data, csr_u64_t modifier, csr_u64_t key0, csr_u64_t key1)
{
    return ~0ull; // unknown by definition...
}

// ComputePACQARMA()
// =================
// Compute QARMA3 or QARMA5 cryptographic algorithm for PAC calculation
csr_u64_t ArmPseudoCode::ComputePACQARMA(csr_u64_t data, csr_u64_t modifier, csr_u64_t key0, csr_u64_t key1, bool isqarma3)
{
    Qarma64 qarma(isqarma3 ? 3 : 5);
    return qarma.encrypt(data, modifier, key0, key1);
}

// AddPAC()
// ========
// Calculates the pointer authentication code for a 64-bit quantity and then
// inserts that into pointer authentication code field of that 64-bit quantity.
csr_u64_t ArmPseudoCode::AddPAC(csr_u64_t ptr, csr_u64_t modifier, const csr_pair_t& K, bool data)
{
    const bool isgeneric = false;
    const bool tbi = EffectiveTBI(ptr, !data);
    const bool mtx = EffectiveMTX(ptr, !data);
    const csr_u64_t selbit = (ptr & (1ull << pacSelBit(ptr, !data))) ? 1 : 0;
    const csr_u64_t extfield = selbit ? ~0ull : 0ull;
    const int top_bit = pacTopBit(ptr, !data);
    const int bottom_PAC_bit = pacBottomBit(ptr, !data);

    if (tbi && bottom_PAC_bit >= 55) {
        return ptr;
    }

    // Compute the pointer authentication code for a ptr with good extension bits.
    csr_u64_t ext_ptr = 0;
    if (tbi) {
        ext_ptr = (ptr & Bits(63, 56)) |
                  (extfield & Bits(55, bottom_PAC_bit)) |
                  (ptr & Bits(bottom_PAC_bit - 1, 0));
    }
    else if (mtx) {
        ext_ptr = (extfield & Bits(63, 60)) |
                  (ptr & Bits(59, 56)) |
                  (extfield & Bits(55, bottom_PAC_bit)) |
                  (ptr & Bits(bottom_PAC_bit - 1, 0));
    }
    else {
        ext_ptr = (extfield & Bits(63, bottom_PAC_bit)) |
                  (ptr & Bits(bottom_PAC_bit - 1, 0));
    }

    csr_u64_t PAC = ComputePAC(ext_ptr, modifier, K.high, K.low, isgeneric);

    // Check if the ptr has good extension bits and corrupt the pointer authentication code if not
    csr_u64_t unusedbits_mask = Bits(54, bottom_PAC_bit);
    if (tbi) {
        unusedbits_mask |= Bits(63, 56);
    }
    else if (mtx) {
        unusedbits_mask |= Bits(63, 60);
    }
    if ((ptr & unusedbits_mask) != 0 && ((ptr & unusedbits_mask) != unusedbits_mask)) {
        if (_feat.FEAT_EPAC()) {
            PAC = 0;
        }
        else if (!_feat.FEAT_PAuth2()) {
            PAC ^= 1ull << (top_bit - 1);
        }
    }

    // Preserve the determination between upper and lower address at bit<55> and insert PAC into
    // bits that are not used for the address or the tag(s).
    csr_u64_t result = 0;
    if (!_feat.FEAT_PAuth2()) {
        if (tbi) {
            result = (ptr & Bits(63, 56)) |
                     (selbit << 55) |
                     (PAC & Bits(54, bottom_PAC_bit)) |
                     (ptr & Bits(bottom_PAC_bit - 1, 0));
        }
        else {
            result = (PAC & Bits(63, 56)) |
                     (selbit << 55) |
                     (PAC & Bits(54, bottom_PAC_bit)) |
                     (ptr & Bits(bottom_PAC_bit - 1, 0));
            // A compliant implementation of FEAT_MTE4 also implements FEAT_PAuth2
            assert(!mtx);
        }
    }
    else {
        if (tbi) {
            result = (ptr & Bits(63, 56)) |
                     (selbit << 55) |
                     ((ptr & Bits(54, bottom_PAC_bit)) ^ (PAC & Bits(54, bottom_PAC_bit))) |
                     (ptr & Bits(bottom_PAC_bit - 1, 0));
        }
        else if (mtx) {
            result = ((ptr & Bits(63, 60)) ^ (PAC & Bits(63, 60))) |
                     (ptr & Bits(59, 56)) |
                     (selbit << 55) |
                     ((ptr & Bits(54, bottom_PAC_bit)) ^ (PAC & Bits(54, bottom_PAC_bit))) |
                     (ptr & Bits(bottom_PAC_bit - 1, 0));
        }
        else {
            result = ((ptr & Bits(63, 56)) ^ (PAC & Bits(63, 56))) |
                     (selbit << 55) |
                     ((ptr & Bits(54, bottom_PAC_bit)) ^ (PAC & Bits(54, bottom_PAC_bit))) |
                     (ptr & Bits(bottom_PAC_bit - 1, 0));
        }
    }
    return result;
}

// AddPACGA()
// ==========
// Returns a 64-bit value where the lower 32 bits are 0, and the upper 32 bits contain
// a 32-bit pointer authentication code which is derived using a cryptographic
// algorithm as a combination of x, y and the APGAKey_EL1.
csr_u64_t ArmPseudoCode::AddPACGA(csr_u64_t x, csr_u64_t y)
{
    csr_pair_t APGAKey_EL1;
    _regs.read(CSR_REGID2_APGAKEY_EL1, APGAKey_EL1);
    return AddPACGA(x, y, APGAKey_EL1);
}
csr_u64_t ArmPseudoCode::AddPACGA(csr_u64_t x, csr_u64_t y, const csr_pair_t& key)
{
    return ComputePAC(x, y, key.high, key.low, true) & Bits(63, 32);
}

// Some intermediate functions, used to implement AddPAC(), also useful outside.
// See AddPAC() pseudo code in Arm manual for details.
int ArmPseudoCode::pacTopBit(csr_u64_t address, bool is_instr)
{
    return EffectiveTBI(address, is_instr) ? 55 : 63;
}

int ArmPseudoCode::pacSelBit(csr_u64_t address, bool is_instr)
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

int ArmPseudoCode::pacBottomBit(csr_u64_t address, bool is_instr)
{
    S1TTWParams walkparams;
    const int top_bit_pos = pacTopBit(address, is_instr);
    const int top_bit = (address >> top_bit_pos) & 1;
    AArch64_GetS1TTWParams(walkparams, top_bit ? ~0ull : 0);
    return 64 - AArch64_PACEffectiveTxSZ(walkparams);
}

// Size in bits for PAC.
int ArmPseudoCode::pacSize(csr_u64_t address, bool is_instr)
{
    const int top = pacTopBit(address, is_instr);
    const int bottom = pacBottomBit(address, is_instr);
    return std::max(0, top - bottom + (bottom <= 55 && 55 <= top ? 0 : 1));
}

// Mask for PAC.
csr_u64_t ArmPseudoCode::pacMask(csr_u64_t address, bool is_instr)
{
    const int top = pacTopBit(address, is_instr);
    const int bottom = pacBottomBit(address, is_instr);
    return Bits(top, bottom) & ~(1ull << 55);
}
