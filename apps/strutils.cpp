//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Some string utilities.
//
//----------------------------------------------------------------------------

#include "strutils.h"
#include <cstring>
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

std::string ToString(const csr_pair_t& pair)
{
    return ToString(pair.high, pair.low);
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


//----------------------------------------------------------------------------
// Transform an errno value into an error message string.
//----------------------------------------------------------------------------

// Depending on GNU vs. POSIX, strerror_r returns an int or a char*.
// There are two short functions to handle the strerror_r result.
// The C++ compiler will automatically invoke the right one.
namespace {
    // POSIX version, strerror_r returns an int, leave result unmodified.
    inline void handle_strerror_r(bool& found, char*& result, int strerror_t_ret)
    {
        found = strerror_t_ret == 0; // success
    }
    // GNU version, strerror_r returns char*, not necessarily in buffer.
    inline void handle_strerror_r(bool& found, char*& result, char* strerror_t_ret)
    {
        result = strerror_t_ret; // actual message
        found = result != nullptr;
    }
}

std::string Error(int code)
{
    char message[1024];
    bzero(message, sizeof(message));

    char* result = message;
    bool found = false;
    handle_strerror_r(found, result, strerror_r(code, message, sizeof(message)));

    if (found) {
        // Make sure message is nul-terminated.
        message[sizeof(message) - 1] = 0;
        // Remove trailing newlines (if any)
        for (size_t i = ::strlen(result); i > 0 && (result[i - 1] == '\n' || result[i - 1] == '\r'); result[--i] = 0) {}
        return std::string(result);
    }
    else {
        // Message is not found.
        return Format("System error %d (0x%X)", code, code);
    }
}
