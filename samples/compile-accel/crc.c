#include "crc.h"
#include "crc_accel.h"
#include "armfeature.h"
#include <stdio.h>

static volatile int crc_accel_checked = 0;
static volatile int crc_accel_supported = 0;

void crc()
{
    // Check done once only. No need for multi-thread synchronization.
    if (!crc_accel_checked) {
        crc_accel_supported = crc_accel_compiled && armfeature(AT_HWCAP, HWCAP_CRC32, "hw.optional.armv8_crc32");
        crc_accel_checked = 1;
    }

    // Each time, select accelerated implementation when supported.
    if (crc_accel_supported) {
        crc_accel();
    }
    else {
        printf("crc():    portable implementation\n");
    }
}
