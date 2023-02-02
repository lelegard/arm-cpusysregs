//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Some string utilities.
//
//----------------------------------------------------------------------------

#pragma once

#include "cpusysregs.h"
#include <string>

// Format booleans and integers.
std::string YesNo(bool);
std::string ToString(csr_u64_t);
std::string ToString(csr_u64_t hi, csr_u64_t lo);
std::string ToString(const csr_pair_t&);
std::string ToBinary(csr_u64_t);

// Format a C++ string in a printf-way.
std::string Format(const char* fmt, ...);

// Case conversions.
std::string ToLower(const std::string&);
std::string ToUpper(const std::string&);

// Pad a string to a given width.
std::string Pad(const std::string& str, size_t width, char pad = '.', bool right = true);

// Join a container of strings.
template <class CONTAINER>
std::string Join(const CONTAINER& container, const std::string& separator = ", ", bool noempty = false);

// Transform an errno value into an error message string.
std::string Error(int);

// Template expansions...
template <class CONTAINER>
std::string Join(const CONTAINER& container, const std::string& separator, bool noempty)
{
    std::string res;
    for (auto iter = container.begin(); iter != container.end(); ++iter) {
        if (!noempty || !iter->empty()) {
            if (!res.empty()) {
                res.append(separator);
            }
            res.append(*iter);
        }
    }
    return res;
}
