#include "armfeature.h"

#if defined(__APPLE__) && (defined(__aarch64__) || defined(__arm64__))

#include <sys/param.h>
#include <sys/sysctl.h>

int armfeature_macos(const char* arg)
{
    int val = 0;
    size_t len = sizeof(val);
    return sysctlbyname(arg, &val, &len, NULL, 0) == 0 && val != 0;
}

#endif
