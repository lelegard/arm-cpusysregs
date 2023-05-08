#include "aes.h"
#include "aes_accel.h"
#include "armfeature.h"
#include <stdio.h>

static volatile int accel_checked = 0;
static volatile int accel_supported = 0;

void aes()
{
    // Check done once only. No need for multi-thread synchronization.
    if (!accel_checked) {
        accel_supported = armfeature(AT_HWCAP, HWCAP_AES, "hw.optional.arm.FEAT_AES");
        accel_checked = 1;
    }

    // Each time, select accelerated implementation when supported.
    if (accel_supported) {
        aes_accel();
    }
    else {
        printf("aes(): portable implementation\n");
    }
}
