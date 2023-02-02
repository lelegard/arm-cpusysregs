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
std::string ToHexa(csr_u64_t);
std::string ToHexa(csr_u64_t hi, csr_u64_t lo);
std::string ToHexa(const csr_pair_t&);
std::string ToBinary(csr_u64_t);

// Decode hexadecimal strings, return false on invalid input.
bool DecodeHexa(csr_u64_t&, const std::string&, const std::string& sep = "-_., \t\r\n");
bool DecodeHexa(csr_pair_t&, const std::string&, const std::string& sep = "-_., \t\r\n");

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
