#if !defined(SHA3_ACCEL_H)
#define SHA3_ACCEL_H 1

// Boolean: indicate if this module could be compiled with accelerated instructions.
extern const int sha3_accel_compiled;

// Accelerated SHA-1 function.
void sha3_accel();

#endif // SHA3_ACCEL_H
