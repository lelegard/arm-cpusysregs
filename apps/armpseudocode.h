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

#pragma once
#include "regaccess.h"
#include "armfeatures.h"

//
// A class implementing some pseudo-code functions from the Arm Architecture Reference Manual.
//
// In most cases, EL0 or EL1 is assumed. Inner EL requires access to EL2 or EL3 registers,
// which is not possible.
//
class ArmPseudoCode
{
public:
    // Constructor.
    ArmPseudoCode(RegAccess&);

    // Forbid copy (keep only one instance per RegAccess reference).
    ArmPseudoCode(ArmPseudoCode&&) = delete;
    ArmPseudoCode(const ArmPseudoCode&) = delete;
    ArmPseudoCode& operator=(ArmPseudoCode&&) = delete;
    ArmPseudoCode& operator=(const ArmPseudoCode&) = delete;

    // Build a mask with bits top..bottom set, others are zero.
    static csr_u64_t Bits(int top, int bottom)
    {
        return (~0ull >> (63 - top)) & ~(~0ull >> (64 - bottom));
    }

    // TGx
    // ===
    // Translation granules sizes
    enum TGx {TGx_4KB, TGx_16KB, TGx_64KB};

    // TGxGranuleBits()
    // ================
    // Retrieve the address size, in bits, of a granule
    int TGxGranuleBits(TGx tgx);

    // AArch64.S1DecodeTG0()
    // =====================
    // Decode stage 1 granule size configuration bits TG0
    TGx AArch64_S1DecodeTG0(int tg0_in);

    // AArch64.S1DecodeTG1()
    // =====================
    // Decode stage 1 granule size configuration bits TG1
    TGx AArch64_S1DecodeTG1(int tg1_in);

    // VARange
    // =======
    // Virtual address ranges
    enum VARange {VARange_LOWER, VARange_UPPER};

    // AArch64.GetVARange()
    // ====================
    // Determines if the VA that is to be translated lies in LOWER or UPPER address range.
    VARange AArch64_GetVARange(csr_u64_t va);

    // S1TTWParams
    // ===========
    // Register fields corresponding to stage 1 translation
    // For A32-VMSA, if noted, they correspond to A32-LPAE (Long descriptor format)
    struct S1TTWParams {
        // A64-VMSA exclusive parameters
        bool      ha;
        bool      hd;
        bool      tbi;
        bool      tbid;
        bool      nfd;
        bool      e0pd;
        bool      d128;
        bool      aie;
        csr_u64_t mair2;
        bool      ds;
        int       ps;    // 3 bits
        int       txsz;  // 6 bits
        bool      epan;
        bool      dct;
        bool      nv1;
        bool      cmow;
        bool      pnch;
        bool      disch;
        bool      haft;
        bool      mtx;
        int       skl;   // 2 bits
        bool      pie;
        csr_u64_t pir;
        csr_u64_t pire0;
        bool      emec;
        bool      amec;
        // A32-VMSA exclusive parameters
        int       t0sz;  // 3 bits
        int       t1sz;  // 3 bits
        bool      uwxn;
        // Parameters common to both A64-VMSA & A32-VMSA (A64/A32)
        TGx       tgx;
        int       irgn;  // 2 bits
        int       orgn;  // 2 bits
        int       sh;    // 2 bits
        bool      hpd;
        bool      ee;
        bool      wxn;
        bool      ntlsmd;
        bool      dc;
        bool      sif;
        csr_u64_t mair;
    };

    // AArch64.GetS1TTWParams()
    // ========================
    // Returns stage 1 translation table walk parameters from respective controlling System registers.
    void AArch64_GetS1TTWParams(S1TTWParams& walkparams, csr_u64_t va);

    // AArch64.S1TTWParamsEL10()
    // =========================
    // Gather stage 1 translation table walk parameters for EL1&0 regime (with EL2 enabled or disabled)
    void AArch64_S1TTWParamsEL10(S1TTWParams& walkparams, VARange varange);

    // EffectiveTBI()
    // ==============
    // Returns the effective TBI (top-byte ignore) in the AArch64 stage 1 translation regime for EL0/EL1.
    bool EffectiveTBI(csr_u64_t address, bool is_instr);

    // EffectiveMTX()
    // ==============
    // Returns the effective MTX (memory tagging extension) in the AArch64 stage 1 translation regime for EL0/EL1.
    bool EffectiveMTX(csr_u64_t address, bool is_instr);

    // AArch64.MaxTxSZ()
    // =================
    // Retrieve the maximum value of TxSZ indicating minimum input address size for both stages of translation
    int AArch64_MaxTxSZ(TGx tgx);

    // AArch64.S1MinTxSZ()
    // ===================
    // Retrieve the minimum value of TxSZ indicating maximum input address size for stage 1
    int AArch64_S1MinTxSZ(bool d128, bool ds, TGx tgx);

    // AArch64.PACEffectiveTxSZ()
    // ==========================
    // Compute the effective value for TxSZ used to determine the placement of the PAC field
    int AArch64_PACEffectiveTxSZ(const S1TTWParams& walkparams);

    // ComputePAC()
    // ============
    csr_u64_t ComputePAC(csr_u64_t data, csr_u64_t modifier, csr_u64_t key0, csr_u64_t key1, bool isgeneric);

    // UsePACIMP()
    // ===========
    // Checks whether IMPLEMENTATION DEFINED cryptographic algorithm to be used for PAC calculation.
    bool UsePACIMP(bool isgeneric);

    // UsePACQARMA3()
    // ==============
    // Checks whether QARMA3 cryptographic algorithm to be used for PAC calculation.
    bool UsePACQARMA3(bool isgeneric);

    // UsePACQARMA5()
    // ==============
    // Checks whether QARMA5 cryptographic algorithm to be used for PAC calculation.
    bool UsePACQARMA5(bool isgeneric);

    // ComputePACIMPDEF()
    // ==================
    // Compute IMPLEMENTATION DEFINED cryptographic algorithm to be used for PAC calculation.
    csr_u64_t ComputePACIMPDEF(csr_u64_t data, csr_u64_t modifier, csr_u64_t key0, csr_u64_t key1);

    // ComputePACQARMA()
    // =================
    // Compute QARMA3 or QARMA5 cryptographic algorithm for PAC calculation
    csr_u64_t ComputePACQARMA(csr_u64_t data, csr_u64_t modifier, csr_u64_t key0, csr_u64_t key1, bool isqarma3);

    // AddPAC()
    // ========
    // Calculates the pointer authentication code for a 64-bit quantity and then
    // inserts that into pointer authentication code field of that 64-bit quantity.
    csr_u64_t AddPAC(csr_u64_t ptr, csr_u64_t modifier, const csr_pair_t& K, bool data);

    // AddPACGA()
    // ==========
    // Returns a 64-bit value where the lower 32 bits are 0, and the upper 32 bits contain
    // a 32-bit pointer authentication code which is derived using a cryptographic
    // algorithm as a combination of x, y and the APGAKey_EL1.
    csr_u64_t AddPACGA(csr_u64_t x, csr_u64_t y);
    csr_u64_t AddPACGA(csr_u64_t x, csr_u64_t y, const csr_pair_t& key);

    // Some intermediate functions, used to implement AddPAC(), also useful outside.
    // See AddPAC() pseudo code in Arm manual for details.
    int pacTopBit(csr_u64_t address, bool is_instr);
    int pacSelBit(csr_u64_t address, bool is_instr);
    int pacBottomBit(csr_u64_t address, bool is_instr);

    // Size in bits and mask for PAC.
    int pacSize(csr_u64_t address, bool is_instr);
    csr_u64_t pacMask(csr_u64_t address, bool is_instr);

private:
    RegAccess&  _regs;
    ArmFeatures _feat;
};
