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
#include "armfeatures.h"
#include <cinttypes>

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
    ArmPseudoCode(ArmFeatures&);

    // Forbid copy (keep only one instance per RegAccess reference).
    ArmPseudoCode(ArmPseudoCode&&) = delete;
    ArmPseudoCode(const ArmPseudoCode&) = delete;
    ArmPseudoCode& operator=(ArmPseudoCode&&) = delete;
    ArmPseudoCode& operator=(const ArmPseudoCode&) = delete;

    // TGx
    // ===
    // Translation granules sizes
    enum TGx {TGx_4KB, TGx_16KB, TGx_64KB};

    // TGxGranuleBits()
    // ================
    // Retrieve the address size, in bits, of a granule
    int TGxGranuleBits(TGx tgx);

    // S1TTWParams
    // ===========
    // Register fields corresponding to stage 1 translation
    // For A32-VMSA, if noted, they correspond to A32-LPAE (Long descriptor format)
    struct S1TTWParams {
        // A64-VMSA exclusive parameters
        bool     ha;
        bool     hd;
        bool     tbi;
        bool     tbid;
        bool     nfd;
        bool     e0pd;
        bool     d128;
        bool     aie;
        uint64_t mair2;
        bool     ds;
        int      ps;    // 3 bits
        int      txsz;  // 6 bits
        bool     epan;
        bool     dct;
        bool     nv1;
        bool     cmow;
        bool     pnch;
        bool     disch;
        bool     haft;
        bool     mtx;
        int      skl;   // 2 bits
        bool     pie;
        uint64_t pir;
        uint64_t pire0;
        bool     emec;
        bool     amec;
        // A32-VMSA exclusive parameters
        int      t0sz;  // 3 bits
        int      t1sz;  // 3 bits
        bool     uwxn;
        // Parameters common to both A64-VMSA & A32-VMSA (A64/A32)
        TGx      tgx;
        int      irgn;  // 2 bits
        int      orgn;  // 2 bits
        int      sh;    // 2 bits
        bool     hpd;
        bool     ee;
        bool     wxn;
        bool     ntlsmd;
        bool     dc;
        bool     sif;
        uint64_t mair;
    };

    // ==== shared/functions/memory/EffectiveTBI
    // Returns the effective TBI (top-byte ignore) in the AArch64 stage 1 translation regime for EL0/EL1.
    bool EffectiveTBI(uint64_t address, bool is_instr);

    // ==== shared/functions/memory/EffectiveMTX
    // Returns the effective MTX (memory tagging extension) in the AArch64 stage 1 translation regime for EL0/EL1.
    bool EffectiveMTX(uint64_t address, bool is_instr);

    // ==== aarch64/functions/pac/addpac/AddPAC
    // Some intermediate functions, used to implement AddPAC(), also useful outside.
    // See AddPAC() pseudo code in Arm manual for details.
    int pacTopBit(uint64_t address, bool is_instr);
    int pacSelBit(uint64_t address, bool is_instr);
    int pacBottomBit(uint64_t address, bool is_instr);

private:
    ArmFeatures& _feat;
};
