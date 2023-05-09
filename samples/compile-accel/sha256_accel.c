#include "sha256_accel.h"
#include <assert.h>
#include <stdio.h>

#if defined(__ARM_FEATURE_SHA2)

    const int sha256_accel_compiled = 1;
    void sha256_accel()
    {
        printf("sha256(): accelerated implementation\n");
        // Dummy SHA-256 instruction, just to demonstrate it is accepted by the compiler.
        asm("sha256su0 v8.4S, v8.4S" : : : "v8");
    }

#else

    const int sha256_accel_compiled = 0;
    void sha256_accel()
    {
        // Should never be called if the CPU does not support the compilation target of this module;
        printf("sha256(): ACCELERATED IMPLEMENTATION SHOULD NOT GET CALLED !\n");
        assert(0);
    }
    
#endif
