#include "crc_accel.h"
#include <assert.h>
#include <stdio.h>

#if defined(__ARM_FEATURE_CRC32)

    const int crc_accel_compiled = 1;
    void crc_accel()
    {
        printf("crc():    accelerated implementation\n");
        // Dummy CRC instruction, just to demonstrate it is accepted by the compiler.
        asm("crc32x w8, w8, x8" : : : "x8");
    }

#else

    const int crc_accel_compiled = 0;
    void crc_accel()
    {
        // Should never be called if the CPU does not support the compilation target of this module;
        printf("crc():    ACCELERATED IMPLEMENTATION SHOULD NOT GET CALLED !\n");
        assert(0);
    }

#endif
