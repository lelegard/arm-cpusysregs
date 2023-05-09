#if !defined(AES_ACCEL_H)
#define AES_ACCEL_H 1

// Boolean: indicate if this module could be compiled with accelerated instructions.
extern const int aes_accel_compiled;

// Accelerated AES function.
void aes_accel();

#endif // AES_ACCEL_H
