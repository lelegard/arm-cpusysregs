#include "crc_accel.h"
#include <assert.h>
#include <stdio.h>

void crc_accel()
{
#if defined(__ARM_FEATURE_CRC32)

    printf("crc(): accelerated implementation\n");

#else

    // Should never be called if the CPU does not support the compilation target of this module;
    printf("crc(): ACCELERATED IMPLEMENTATION SHOULD NOT GET CALLED !\n");
    assert(0);
    
#endif
}
