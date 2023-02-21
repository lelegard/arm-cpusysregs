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

    // ==== shared/functions/memory/EffectiveTBI
    // Returns the effective TBI (top-byte ignore) in the AArch64 stage 1 translation regime for EL0/EL1.
    bool EffectiveTBI(uint64_t address, bool is_instr);

    // ==== shared/functions/memory/EffectiveMTX
    // Returns the effective MTX (memory tagging extension) in the AArch64 stage 1 translation regime for EL0/EL1.
    bool EffectiveMTX(uint64_t address, bool is_instr);

private:
    RegAccess&  _regs;
    ArmFeatures _features;
};
