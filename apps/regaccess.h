//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// A class to access Arm64 system registers.
//
//----------------------------------------------------------------------------

#pragma once
#include "cpusysregs.h"
#include <iostream>

//
// A class to access Arm64 system registers.
//
// Most methods return true on success and false on error.
// Use error reporting methods to print errors.
//
class RegAccess
{
public:
    // Constructor and destructor.
    // If print_errors is true, error messages are automatically displayed on stderr.
    // Terminate application when exit_on_open_error is true and the kernel module not accessible.
    RegAccess(bool print_errors = false, bool exit_on_open_error = false);
    ~RegAccess() { close(); }

    // Check if the kernel module was successfully open.
    bool isOpen() const;

    // Forbid copy (keep only one instance per file descriptor).
    RegAccess(RegAccess&&) = delete;
    RegAccess(const RegAccess&) = delete;
    RegAccess& operator=(RegAccess&&) = delete;
    RegAccess& operator=(const RegAccess&) = delete;

    // Error reporting.
    int lastError() const { return _error; }
    void clearError() { _error = 0; }
    void printLastError(const std::string& label = std::string(), std::ostream& file = std::cerr) const;

    // Read/write one CPU register.
    bool read(int regid, csr_u64_t& reg);
    bool write(int regid, csr_u64_t reg);

    // Read a pair of CPU registers.
    // If the specified register is not a pair, use reg.low only.
    bool read(int regid, csr_pair_t& reg);
    bool write(int regid, const csr_pair_t& reg);

    // Execute a PACxx or AUTxx in kernel mode.
    bool executeInstr(int instr, csr_instr_t& args);

private:

    // File descriptor, device handle, per system.
    #if defined(__linux__) || defined(__APPLE__)
        typedef int SysHandle;
        typedef int SysError;
        #define CSR_INVALID_SYSHANDLE (-1)
        #define CSR_SUCCESS 0
    #elif defined(WINDOWS)
        typedef ::HANDLE SysHandle;
        typedef ::DWORD SysError;
        #define CSR_INVALID_SYSHANDLE INVALID_HANDLE_VALUE
        #define CSR_SUCCESS ERROR_SUCCESS
    #endif

    SysHandle   _fd;            // file descriptor to access the kernel module
    bool        _print_errors;  // automatic error reporting
    SysError    _error;         // last error code
    std::string _error_ref;     // reference of last error

    // Close the kernel module.
    void close();

    // Set error code and return false. Report when necessary.
    bool setError(SysError code, const std::string& ref, bool close_fd = false, bool exit_on_error = false);
};
