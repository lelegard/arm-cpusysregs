#include "aes_accel.h"
#include <assert.h>
#include <stdio.h>

void aes_accel()
{
#if defined(__ARM_FEATURE_CRYPTO)

    printf("aes(): accelerated implementation\n");

#else

    // Should never be called if the CPU does not support the compilation target of this module;
    printf("aes(): ACCELERATED IMPLEMENTATION SHOULD NOT GET CALLED !\n");
    assert(0);
    
#endif
}
