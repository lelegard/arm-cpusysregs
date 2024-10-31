#include "sha3_accel.h"
#include <assert.h>
#include <stdio.h>

#if defined(__ARM_FEATURE_SHA3)

    const int sha3_accel_compiled = 1;
    void sha3_accel()
    {
        printf("sha3():   accelerated implementation\n");
        // Dummy SHA-3 instruction, just to demonstrate it is accepted by the compiler.
        asm("eor3 v8.16B, v8.16B, v8.16B, v8.16B" : : : "v8");
    }

#else

    const int sha3_accel_compiled = 0;
    void sha3_accel()
    {
        // Should never be called if the CPU does not support the compilation target of this module;
        printf("sha3():   ACCELERATED IMPLEMENTATION SHOULD NOT GET CALLED !\n");
        assert(0);
    }

#endif
