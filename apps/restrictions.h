//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Definitions of per-platforms restrictions and other peculiarities.
//
//----------------------------------------------------------------------------

#pragma once

// The register PMSIDR_EL1 cannot be read on Linux at EL1, even though FEAT_SPE is implemented.
// Reading PMSIDR_EL1 generates "kernel BUG at arch/arm64/kernel/traps.c:498!" in dmesg.
#if defined(__linux__)
    #define CSR_AVOID_PMSIDR_EL1 1
#endif

// The PAC key registers cannot be read on macOS at EL1. Reading or writing them crashes the system.
// See note in ../docs/arm64e-on-macos.md
#if defined(__APPLE__)
    #define CSR_AVOID_PAC_KEY_REGISTERS 1
#endif
