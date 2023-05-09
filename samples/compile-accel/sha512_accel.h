#if !defined(SHA512_ACCEL_H)
#define SHA512_ACCEL_H 1

// Boolean: indicate if this module could be compiled with accelerated instructions.
extern const int sha512_accel_compiled;

// Accelerated SHA-512 function.
void sha512_accel();

#endif // SHA512_ACCEL_H
