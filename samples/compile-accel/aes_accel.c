#include "aes_accel.h"
#include <assert.h>
#include <stdio.h>

#if defined(__ARM_FEATURE_CRYPTO)

    const int aes_accel_compiled = 1;
    void aes_accel()
    {
        printf("aes():    accelerated implementation\n");
        // Dummy AES instruction, just to demonstrate it is accepted by the compiler.
        asm("aese v8.16B, v8.16B" : : : "v8");
    }

#else

    const int aes_accel_compiled = 0;
    void aes_accel()
    {
        // Should never be called if the CPU does not support the compilation target of this module;
        printf("aes():    ACCELERATED IMPLEMENTATION SHOULD NOT GET CALLED !\n");
        assert(0);
    }

#endif
