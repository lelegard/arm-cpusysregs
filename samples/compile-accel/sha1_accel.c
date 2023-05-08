#include "sha1_accel.h"
#include <assert.h>
#include <stdio.h>

void sha1_accel()
{
#if defined(__ARM_FEATURE_CRYPTO)

    printf("sha1(): accelerated implementation\n");

#else

    // Should never be called if the CPU does not support the compilation target of this module;
    printf("sha1(): ACCELERATED IMPLEMENTATION SHOULD NOT GET CALLED !\n");
    assert(0);
    
#endif
}
