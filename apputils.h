//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Some common utilities for userland applications.
//
//----------------------------------------------------------------------------

#pragma once

#include "cpusysregs.h"
#include <string>

// Format booleans and integers.
std::string YesNo(bool);
std::string ToString(csr_u64_t);
std::string ToString(csr_u64_t hi, csr_u64_t lo);
std::string ToString(const csr_pac_key_t&);
std::string ToBinary(csr_u64_t);

// Format a C++ string in a printf-way.
std::string Format(const char* fmt, ...);

// Pad a string to a given width.
std::string Pad(const std::string& str, size_t width, char pad = '.', bool right = true);
