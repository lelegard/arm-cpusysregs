//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Define some platform-specific restrictions in userland.
// Typically, the security is more stringent on macOS and reading some
// registers at EL1 may crash the system. We keep the possibility to read
// them in the kernel module, as a test. But we do not read them from the
// command line tools, unless the option -f (force) is used.
//
//----------------------------------------------------------------------------

#pragma once

// Possible restrictions:
// #define CSR_SKIP_PAC_KEYS 1
// #define CSR_SKIP_PMMIR    1

#if defined(__APPLE__)
    #define CSR_SKIP_PAC_KEYS 1
#endif
