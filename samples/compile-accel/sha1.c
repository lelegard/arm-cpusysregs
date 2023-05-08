#include "sha1.h"
#include "sha1_accel.h"
#include "armfeature.h"
#include <stdio.h>

static volatile int accel_checked = 0;
static volatile int accel_supported = 0;

void sha1()
{
    // Check done once only. No need for multi-thread synchronization.
    if (!accel_checked) {
        accel_supported = armfeature(AT_HWCAP, HWCAP_SHA1, "hw.optional.arm.FEAT_SHA1");
        accel_checked = 1;
    }

    // Each time, select accelerated implementation when supported.
    if (accel_supported) {
        sha1_accel();
    }
    else {
        printf("sha1(): portable implementation\n");
    }
}
