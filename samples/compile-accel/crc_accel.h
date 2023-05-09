#if !defined(CRC_ACCEL_H)
#define CRC_ACCEL_H 1

// Boolean: indicate if this module could be compiled with accelerated instructions.
extern const int crc_accel_compiled;

// Accelerated CRC function.
void crc_accel();

#endif // CRC_ACCEL_H
