//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// A class to access Arm64 system registers.
//
//----------------------------------------------------------------------------

#include "regaccess.h"
#include "strutils.h"
#include <cstddef>
#include <cstdlib>
#include <unistd.h>

#if defined(__linux__)
    #include <fcntl.h>
    #include <sys/ioctl.h>
#elif defined(__APPLE__)
    #include <sys/socket.h>
    #include <sys/sys_domain.h>
    #include <sys/kern_control.h>
    #include <sys/ioctl.h>
#endif


//----------------------------------------------------------------------------
// Constructor and destructor.
//----------------------------------------------------------------------------

RegAccess::RegAccess(bool fail_on_error) :
    _fd(-1),
    _fail(fail_on_error),
    _error(0),
    _error_ref()
{
}

RegAccess::~RegAccess()
{
    if (_fd >= 0) {
        close();
    }
}


//----------------------------------------------------------------------------
// Error reporting.
//----------------------------------------------------------------------------

void RegAccess::printLastError(const std::string& label, std::ostream& file) const
{
    if (_error != 0) {
        if (!label.empty()) {
            file << label << ": ";
        }
        if (!_error_ref.empty()) {
            file << _error_ref << ": ";
        }
        file << Error(_error) << std::endl;
    }
}

bool RegAccess::setError(int code, const char* ref, bool close_fd)
{
    _error = code;
    _error_ref = ref;
    if (close_fd && _fd >= 0) {
        ::close(_fd);
        _fd = -1;
    }
    if (_fail) {
        printLastError();
        ::exit(EXIT_FAILURE);
    }
    return false;
}


//----------------------------------------------------------------------------
// Open and close access to the kernel module.
//----------------------------------------------------------------------------

bool RegAccess::open()
{
    if (_fd >= 0) {
        return setError(EINVAL, "already open", false);
    }

#if defined(__linux__)

    // Open the pseudo-device for the kernel module.
    if ((_fd = ::open(CSR_DEVICE_PATH, O_RDONLY)) < 0) {
        return setError(errno, CSR_DEVICE_PATH, false);
    }

#elif defined(__APPLE__)

    // We use a system socket to communicate with the kernel extension.
    if ((_fd = ::socket(PF_SYSTEM, SOCK_DGRAM, SYSPROTO_CONTROL)) < 0) {
        return setError(errno, "socket()", false);
    }

    // Get the control id of the cpusysregs kernel extension.
    struct ctl_info info;
    bzero(&info, sizeof(info));
    ::strncpy(info.ctl_name, CSR_MODULE_NAME, sizeof(info.ctl_name));
    if (::ioctl(_fd, CTLIOCGINFO, &info) < 0) {
        return setError(errno, "ioctl(CTLIOCGINFO)", true);
    }

    // Connect to the kernel extension using its id.
    struct sockaddr_ctl addr;
    bzero(&addr, sizeof(addr));
    addr.sc_len = sizeof(addr);
    addr.sc_family = AF_SYSTEM;
    addr.ss_sysaddr = AF_SYS_CONTROL;
    addr.sc_id = info.ctl_id;
    if (::connect(_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        return setError(errno, "connect()", true);
    }

#endif

    return true;
}

bool RegAccess::close()
{
    // Same stuff on Linux and macOS.
    if (::close(_fd) < 0) {
        return setError(errno, "close", false);
    }
    else {
        _fd = -1;
        return true;
    }
}


//----------------------------------------------------------------------------
// Read CPU registers.
//----------------------------------------------------------------------------

bool RegAccess::read(csr_registers_t& regs)
{
#if defined(__linux__)

    if (::ioctl(_fd, CSR_IOCTL_GET_REGS, &regs) < 0) {
        return setError(errno, "ioctl(GET_REGS)", false);
    }

#elif defined(__APPLE__)

    ::socklen_t len = sizeof(regs);
    if (::getsockopt(_fd, SYSPROTO_CONTROL, CSR_SO_GET_REGS, &regs, &len) < 0)  {
        return setError(errno, "getsockopt(GET_REGS)", false);
    }

#endif

    return true;
}


//----------------------------------------------------------------------------
// Set the various Pointer Authentication keys.
//----------------------------------------------------------------------------

bool RegAccess::setKeyIA(const csr_pac_key_t& key)
{
#if defined(__linux__)
    if (::ioctl(_fd, CSR_IOCTL_SET_KEYIA, &key) < 0) {
#elif defined(__APPLE__)
        if (::setsockopt(_fd, SYSPROTO_CONTROL, CSR_SO_SET_KEYIA, &key, sizeof(key)) < 0)  {
#endif
        return setError(errno, "SET_KEYIA", false);
    }
    return true;
}

bool RegAccess::setKeyIB(const csr_pac_key_t& key)
{
#if defined(__linux__)
    if (::ioctl(_fd, CSR_IOCTL_SET_KEYIB, &key) < 0) {
#elif defined(__APPLE__)
    if (::setsockopt(_fd, SYSPROTO_CONTROL, CSR_SO_SET_KEYIB, &key, sizeof(key)) < 0)  {
#endif
        return setError(errno, "SET_KEYIB", false);
    }
    return true;
}

bool RegAccess::setKeyDA(const csr_pac_key_t& key)
{
#if defined(__linux__)
    if (::ioctl(_fd, CSR_IOCTL_SET_KEYDA, &key) < 0) {
#elif defined(__APPLE__)
    if (::setsockopt(_fd, SYSPROTO_CONTROL, CSR_SO_SET_KEYDA, &key, sizeof(key)) < 0)  {
#endif
        return setError(errno, "SET_KEYDA", false);
    }
    return true;
}

bool RegAccess::setKeyDB(const csr_pac_key_t& key)
{
#if defined(__linux__)
    if (::ioctl(_fd, CSR_IOCTL_SET_KEYDB, &key) < 0) {
#elif defined(__APPLE__)
    if (::setsockopt(_fd, SYSPROTO_CONTROL, CSR_SO_SET_KEYDB, &key, sizeof(key)) < 0)  {
#endif
        return setError(errno, "SET_KEYDB", false);
    }
    return true;
}

bool RegAccess::setKeyGA(const csr_pac_key_t& key)
{
#if defined(__linux__)
    if (::ioctl(_fd, CSR_IOCTL_SET_KEYGA, &key) < 0) {
#elif defined(__APPLE__)
    if (::setsockopt(_fd, SYSPROTO_CONTROL, CSR_SO_SET_KEYGA, &key, sizeof(key)) < 0)  {
#endif
        return setError(errno, "SET_KEYGA", false);
    }
    return true;
}
