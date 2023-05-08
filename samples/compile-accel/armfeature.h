#if !defined(ARMFEATURE_H)
#define ARMFEATURE_H 1

// Check if an Arm64 feature is supported on the current CPU.
// This is a macro which takes Linux and macOS arguments.
// Return non-zero if the feature is supported.

#if defined(__linux__) && (defined(__aarch64__) || defined(__arm64__))

    #include <sys/auxv.h>

    // On Linux, use an integer arg for getauxval(3) and the bitmask to test.
    #define armfeature(linux_arg, linux_mask, macos_sysctl) (getauxval(linux_arg) & (linux_mask))

#elif defined(__APPLE__) && (defined(__aarch64__) || defined(__arm64__))

    // On macOS, use a string arg for sysctlbyname(3).
    int armfeature_macos(const char*);
    #define armfeature(linux_arg, linux_mask, macos_sysctl) armfeature_macos(macos_sysctl)

#else

    // Other system or architecture: the feature is not supported.
    #define armfeature(linux_arg, linux_mask, macos_sysctl) (0)

#endif

#endif // ARMFEATURE_H
