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
#include <algorithm>


//----------------------------------------------------------------------------
// Format booleans and integers.
//----------------------------------------------------------------------------

std::string YesNo(bool value)
{
    return value ? "yes" : "no";
}

std::string ToHexa(csr_u64_t value)
{
    return Format("%08llX-%08llX", value >> 32, value & 0xFFFFFFFF);
}

std::string ToHexa(csr_u64_t hi, csr_u64_t lo)
{
    return Format("%08llX-%08llX-%08llX-%08llX", hi >> 32, hi & 0xFFFFFFFF, lo >> 32, lo & 0xFFFFFFFF);
}

std::string ToHexa(const csr_pair_t& pair)
{
    return ToHexa(pair.high, pair.low);
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
// Decode hexadecimal strings, return false on invalid input.
//----------------------------------------------------------------------------

bool DecodeHexa(csr_u64_t& value, const std::string& hex, const std::string& sep)
{
    csr_pair_t pair;
    const bool res = DecodeHexa(pair, hex, sep);
    value = pair.low;
    return res;
}

bool DecodeHexa(csr_pair_t& value, const std::string& hex, const std::string& sep)
{
    value.high = value.low = 0;
    bool found = false;
    for (char c : hex) {
        int nibble = 0;
        if (c >= '0' && c <= '9') {
            nibble = c - '0';
            found = true;
        }
        else if (c >= 'a' && c <= 'f') {
            nibble = c - 'a' + 10;
            found = true;
        }
        else if (c >= 'A' && c <= 'F') {
            nibble = c - 'A' + 10;
            found = true;
        }
        else if (sep.find(c) != std::string::npos) {
            continue; // ignore acceptable separator
        }
        else {
            return false; // invalid character
        }
        value.high = (value.high << 4) | (value.low >> 60);
        value.low = (value.low << 4) | nibble;
    }
    return found;
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
    len = ::vsnprintf(&buf[0], buf.size(), fmt, ap);
    va_end(ap);

    buf.resize(std::max(0, len));
    return buf;
}


//----------------------------------------------------------------------------
// Case conversions.
//----------------------------------------------------------------------------

std::string ToLower(const std::string& s)
{
    std::string res(s);
    std::transform(res.begin(), res.end(), res.begin(), [](unsigned char c){ return std::tolower(c); });
    return res;
}

std::string ToUpper(const std::string& s)
{
    std::string res(s);
    std::transform(res.begin(), res.end(), res.begin(), [](unsigned char c){ return std::toupper(c); });
    return res;
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

#if defined(__linux__) || defined(__APPLE__)

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

#endif

std::string Error(int code)
{
#if defined(__linux__) || defined(__APPLE__)

    char message[1024];
    Zero(message, sizeof(message));

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

#elif defined(WINDOWS)

    std::string message;
    message.resize(1024);
    size_t length = ::FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, code, 0, &message[0], ::DWORD(message.size()), nullptr);
    message.resize(std::min(length, message.size()));

    if (!message.empty()) {
        return message;
    }
    else {
        // Message is not found.
        return Format("System error %d (0x%X)", code, code);
    }

#endif
}
