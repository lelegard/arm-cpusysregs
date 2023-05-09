#include "sha3.h"
#include "sha3_accel.h"
#include "armfeature.h"
#include <stdio.h>

static volatile int sha3_accel_checked = 0;
static volatile int sha3_accel_supported = 0;

void sha3()
{
    // Check done once only. No need for multi-thread synchronization.
    if (!sha3_accel_checked) {
        sha3_accel_supported = sha3_accel_compiled && armfeature(AT_HWCAP, HWCAP_SHA3, "hw.optional.arm.FEAT_SHA3");
        sha3_accel_checked = 1;
    }

    // Each time, select accelerated implementation when supported.
    if (sha3_accel_supported) {
        sha3_accel();
    }
    else {
        printf("sha3():   portable implementation\n");
    }
}
