#if !defined(SHA256_ACCEL_H)
#define SHA256_ACCEL_H 1

// Boolean: indicate if this module could be compiled with accelerated instructions.
extern const int sha256_accel_compiled;

// Accelerated SHA-256 function.
void sha256_accel();

#endif // SHA256_ACCEL_H
