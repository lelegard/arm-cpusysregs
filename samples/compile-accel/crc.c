#include "crc.h"
#include "crc_accel.h"
#include "armfeature.h"
#include <stdio.h>

static volatile int accel_checked = 0;
static volatile int accel_supported = 0;

void crc()
{
    // Check done once only. No need for multi-thread synchronization.
    if (!accel_checked) {
        accel_supported = armfeature(AT_HWCAP, HWCAP_CRC32, "hw.optional.armv8_crc32");
        accel_checked = 1;
    }

    // Each time, select accelerated implementation when supported.
    if (accel_supported) {
        crc_accel();
    }
    else {
        printf("crc(): portable implementation\n");
    }
}
