#include "sha256_accel.h"
#include <assert.h>
#include <stdio.h>

void sha256_accel()
{
#if defined(__ARM_FEATURE_SHA2)

    printf("sha256(): accelerated implementation\n");

#else

    // Should never be called if the CPU does not support the compilation target of this module;
    printf("sha256(): ACCELERATED IMPLEMENTATION SHOULD NOT GET CALLED !\n");
    assert(0);
    
#endif
}
