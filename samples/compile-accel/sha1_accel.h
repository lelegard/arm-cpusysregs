#if !defined(SHA1_ACCEL_H)
#define SHA1_ACCEL_H 1

// Boolean: indicate if this module could be compiled with accelerated instructions.
extern const int sha1_accel_compiled;

// Accelerated SHA-1 function.
void sha1_accel();

#endif // SHA1_ACCEL_H
