#include "sha512_accel.h"
#include <assert.h>
#include <stdio.h>

#if defined(__ARM_FEATURE_SHA512)

    const int sha512_accel_compiled = 1;
    void sha512_accel()
    {
        printf("sha512(): accelerated implementation\n");
        // Dummy SHA-512 instruction, just to demonstrate it is accepted by the compiler.
        asm("sha512su0 v8.2D, v8.2D" : : : "v8");
    }

#else

    const int sha512_accel_compiled = 0;
    void sha512_accel()
    {
        // Should never be called if the CPU does not support the compilation target of this module;
        printf("sha512(): ACCELERATED IMPLEMENTATION SHOULD NOT GET CALLED !\n");
        assert(0);
    }
    
#endif
