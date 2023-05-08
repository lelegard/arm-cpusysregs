#include "sha512.h"
#include "sha512_accel.h"
#include "armfeature.h"
#include <stdio.h>

static volatile int accel_checked = 0;
static volatile int accel_supported = 0;

void sha512()
{
    // Check done once only. No need for multi-thread synchronization.
    if (!accel_checked) {
        accel_supported = armfeature(AT_HWCAP, HWCAP_SHA512, "hw.optional.arm.FEAT_SHA512");
        accel_checked = 1;
    }

    // Each time, select accelerated implementation when supported.
    if (accel_supported) {
        sha512_accel();
    }
    else {
        printf("sha512(): portable implementation\n");
    }
}
