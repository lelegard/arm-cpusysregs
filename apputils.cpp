//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Some common utilities for userland applications.
//
//----------------------------------------------------------------------------

#include "apputils.h"
#include <cstdarg>


//----------------------------------------------------------------------------
// Format booleans and integers.
//----------------------------------------------------------------------------

std::string YesNo(bool value)
{
    return value ? "yes" : "no";
}

std::string ToString(csr_u64_t value)
{
    return Format("%08llX-%08llX", value >> 32, value & 0xFFFFFFFF);
}

std::string ToString(csr_u64_t hi, csr_u64_t lo)
{
    return Format("%08llX-%08llX-%08llX-%08llX", hi >> 32, hi & 0xFFFFFFFF, lo >> 32, lo & 0xFFFFFFFF);
}

std::string ToString(const csr_pac_key_t& key)
{
    return ToString(key.high, key.low);
}

std::string ToBinary(csr_u64_t value)
{
    std::string str;
    str.reserve(82);
    for (int shift = 63; shift >= 0; --shift) {
        if (shift == 31) {
            str += " - ";
        }
        else if (shift < 63 && shift % 4 == 3) {
            str += ' ';
        }
        str += (int(value >> shift) & 1) ? '1' : '0';
    }
    return str;
}


//----------------------------------------------------------------------------
// Format a C++ string in a printf-way.
//----------------------------------------------------------------------------

std::string Format(const char* fmt, ...)
{
    va_list ap;

    // Get required output size.
    va_start(ap, fmt);
    int len = ::vsnprintf(nullptr, 0, fmt, ap);
    va_end(ap);

    if (len < 0) {
        return std::string(); // error
    }

    // Actual formatting.
    std::string buf(len + 1, '\0');
    va_start(ap, fmt);
    len = ::vsnprintf(buf.data(), buf.size(), fmt, ap);
    va_end(ap);

    buf.resize(std::max(0, len));
    return buf;
}


//----------------------------------------------------------------------------
// Pad a string to a given width.
//----------------------------------------------------------------------------

std::string Pad(const std::string& str, size_t width, char pad, bool right)
{
    std::string res(str);
    if (str.length() < width) {
        res.insert(right ? res.end() : res.begin(), width - str.length(), pad);
    }
    return res;
}
