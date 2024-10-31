//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// macOS demo program: display Arm features as returned by sysctl().
// Using "-v" (verbose), also display the systcl() OID.
//
//----------------------------------------------------------------------------

#include "strutils.h"

#include <iostream>
#include <vector>
#include <cstddef>
#include <cstdlib>
#include <sys/types.h>
#include <sys/sysctl.h>


// List of hw.optional.arm sysctl.
struct Param {
    std::string name;
    std::string sysctl;
};
const std::vector<Param> AllParams {
    // Automatically generated file:
    #include "_sysctl.h"
};


// Program entry point
int main(int argc, char* argv[])
{
    const bool verbose = argc > 1 && std::string(argv[1]) == "-v";

    size_t name_width = 0;
    for (const auto& param : AllParams) {
        name_width = std::max(name_width, param.name.length());
    }

    for (const auto& param : AllParams) {
        int value = 0;
        size_t len = sizeof(value);
        int oid[16];
        size_t oidcount = sizeof(oid) / sizeof(oid[0]);
        if (::sysctlbyname(param.sysctl.c_str(), &value, &len, nullptr, 0) < 0) {
            ::perror(param.sysctl.c_str());
        }
        else if (verbose && ::sysctlnametomib(param.sysctl.c_str(), oid, &oidcount) < 0) {
            ::perror(param.sysctl.c_str());
        }
        else {
            std::cout << Pad(param.name + " ", name_width + 1) << " " << Pad(YesNo(value), 3, ' ', false);
            if (verbose) {
                std::cout << "  OID:";
                for (size_t i = 0; i < oidcount; i++) {
                    std::cout << " " << oid[i];
                }
            }
            std::cout << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
