#include "sha1_accel.h"
#include <assert.h>
#include <stdio.h>

#if defined(__ARM_FEATURE_CRYPTO)

    const int sha1_accel_compiled = 1;
    void sha1_accel()
    {
        printf("sha1():   accelerated implementation\n");
        // Dummy SHA-1 instruction, just to demonstrate it is accepted by the compiler.
        asm("sha1h s8, s8" : : : "s8");
    }

#else

    const int sha1_accel_compiled = 0;
    void sha1_accel()
    {
        // Should never be called if the CPU does not support the compilation target of this module;
        printf("sha1():   ACCELERATED IMPLEMENTATION SHOULD NOT GET CALLED !\n");
        assert(0);
    }

#endif
