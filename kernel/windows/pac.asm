;----------------------------------------------------------------------------
;
; Arm64 CPU system registers tools
; Copyright (c) 2023, Thierry Lelegard
; BSD-2-Clause license, see the LICENSE file.
;
; Visual Studio does not support inline asm and has no intrinsics for PAC.
; This .asm module contains helper functions for PAT and AUT sequences.
;
;----------------------------------------------------------------------------

#include "ksarm64.h"

    TEXTAREA

    NESTED_ENTRY csr_pacia_helper
    pacia x0, x1
    ret
    NESTED_END

    NESTED_ENTRY csr_pacib_helper
    pacib x0, x1
    ret
    NESTED_END

    NESTED_ENTRY csr_pacda_helper
    pacda x0, x1
    ret
    NESTED_END

    NESTED_ENTRY csr_pacdb_helper
    pacdb x0, x1
    ret
    NESTED_END

    NESTED_ENTRY csr_autia_helper
    autia x0, x1
    ret
    NESTED_END

    NESTED_ENTRY csr_autib_helper
    autib x0, x1
    ret
    NESTED_END

    NESTED_ENTRY csr_autda_helper
    autda x0, x1
    ret
    NESTED_END

    NESTED_ENTRY csr_autdb_helper
    autdb x0, x1
    ret
    NESTED_END

    NESTED_ENTRY csr_pacga_helper
    pacga x0, x0, x1
    ret
    NESTED_END

    END
