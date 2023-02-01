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
// If fail_on_error is true in the constructor, any error is fatal: a message
// is printed on the standard error and the application terminates.
//
// Most methods return true on success and false on error. Use error reporting
// methods to print errors.
//
class RegAccess
{
public:
    // Constructor and destructor.
    RegAccess(bool fail_on_error = false);
    ~RegAccess();

    // Forbid copy (keep only one instance per file descriptor.
    RegAccess(RegAccess&&) = delete;
    RegAccess(const RegAccess&) = delete;
    RegAccess& operator=(RegAccess&&) = delete;
    RegAccess& operator=(const RegAccess&) = delete;

    // Open and close access to the kernel module.
    bool open();
    bool close();
    bool isOpen() const { return _fd >= 0; }

    // Read CPU registers.
    bool read(csr_registers_t& regs);

    // Set the various Pointer Authentication keys.
    // Warning: setting a key which is already used by the kernel or the application to
    // authenticate its own code will mostly likely crash the system or the application.
    bool setKeyIA(const csr_pac_key_t& key);
    bool setKeyIB(const csr_pac_key_t& key);
    bool setKeyDA(const csr_pac_key_t& key);
    bool setKeyDB(const csr_pac_key_t& key);
    bool setKeyGA(const csr_pac_key_t& key);

    // Error reporting.
    int lastError() const { return _error; }
    void clearError() { _error = 0; }
    void printLastError(const std::string& label = std::string(), std::ostream& file = std::cerr) const;

private:
    int  _fd;      // file descriptor to access the kernel module
    bool _fail;    // fail on error
    int  _error;   // last error code
    std::string _error_ref;  // reference of last error

    // Set error code and return false. Fail when necessary.
    bool setError(int code, const char* ref, bool close_fd);
};
