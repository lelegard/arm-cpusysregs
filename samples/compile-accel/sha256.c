#include "sha256.h"
#include "sha256_accel.h"
#include "armfeature.h"
#include <stdio.h>

static volatile int sha256_accel_checked = 0;
static volatile int sha256_accel_supported = 0;

void sha256()
{
    // Check done once only. No need for multi-thread synchronization.
    if (!sha256_accel_checked) {
        sha256_accel_supported = sha256_accel_compiled && armfeature(AT_HWCAP, HWCAP_SHA2, "hw.optional.arm.FEAT_SHA256");
        sha256_accel_checked = 1;
    }

    // Each time, select accelerated implementation when supported.
    if (sha256_accel_supported) {
        sha256_accel();
    }
    else {
        printf("sha256(): portable implementation\n");
    }
}
