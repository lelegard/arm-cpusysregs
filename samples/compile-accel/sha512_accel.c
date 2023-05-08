#include "sha512_accel.h"
#include <assert.h>
#include <stdio.h>

void sha512_accel()
{
#if defined(__ARM_FEATURE_SHA512)

    printf("sha512(): accelerated implementation\n");

#else

    // Should never be called if the CPU does not support the compilation target of this module;
    printf("sha512(): ACCELERATED IMPLEMENTATION SHOULD NOT GET CALLED !\n");
    assert(0);

#endif
}
