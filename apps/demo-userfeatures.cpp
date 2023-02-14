//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Demo program: display Arm features from userland only.
//
//----------------------------------------------------------------------------

#include "strutils.h"
#include "userfeatures.h"
#include <iostream>
#include <string>
#include <list>


// Descriptions of all features.
class Feature
{
public:
    std::string name;             // Feature name
    bool (UserFeatures::*get)();  // Method to get that feature
};
const std::list<Feature> AllUserFeatures {
    // Automatically generated file:
    #include "_userfeatures.h"
};


// Program entry point
int main(int argc, char* argv[])
{
    size_t name_width = 0;
    for (const auto& feat : AllUserFeatures) {
        name_width = std::max(name_width, feat.name.length());
    }

    UserFeatures features;
    for (const auto& feat : AllUserFeatures) {
        std::cout << Pad(feat.name + " ", name_width + 1) << " " << YesNo((features.*feat.get)()) << std::endl;
    }

    return EXIT_SUCCESS;
}
