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

RegAccess::RegAccess(bool print_errors, bool exit_on_open_error) :
    _fd(-1),
    _print_errors(print_errors),
    _error(0),
    _error_ref()
{
#if defined(__linux__)

    // Open the pseudo-device for the kernel module.
    if ((_fd = ::open(CSR_DEVICE_PATH, O_RDONLY)) < 0) {
        setError(errno, CSR_DEVICE_PATH, false, exit_on_open_error);
        return;
    }

#elif defined(__APPLE__)

    // We use a system socket to communicate with the kernel extension.
    if ((_fd = ::socket(PF_SYSTEM, SOCK_DGRAM, SYSPROTO_CONTROL)) < 0) {
        setError(errno, "socket()", false, exit_on_open_error);
        return;
    }

    // Get the control id of the cpusysregs kernel extension.
    struct ctl_info info;
    bzero(&info, sizeof(info));
    ::strncpy(info.ctl_name, CSR_SOCKET_NAME, sizeof(info.ctl_name));
    if (::ioctl(_fd, CTLIOCGINFO, &info) < 0) {
        setError(errno, "ioctl(CTLIOCGINFO)", true, exit_on_open_error);
        return;
    }

    // Connect to the kernel extension using its id.
    struct sockaddr_ctl addr;
    bzero(&addr, sizeof(addr));
    addr.sc_len = sizeof(addr);
    addr.sc_family = AF_SYSTEM;
    addr.ss_sysaddr = AF_SYS_CONTROL;
    addr.sc_id = info.ctl_id;
    if (::connect(_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        setError(errno, "connect()", true, exit_on_open_error);
        return;
    }

#endif
}

RegAccess::~RegAccess()
{
    if (_fd >= 0 && ::close(_fd) < 0) {
        setError(errno, "close");
    }
    _fd = -1;
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

bool RegAccess::setError(int code, const std::string& ref, bool close_fd, bool exit_on_error)
{
    _error = code;
    _error_ref = ref;
    if (close_fd && _fd >= 0) {
        ::close(_fd);
        _fd = -1;
    }
    if (_print_errors || exit_on_error) {
        printLastError();
    }
    if (exit_on_error) {
        ::exit(EXIT_FAILURE);
    }
    return false;
}


//----------------------------------------------------------------------------
// Read CPU registers.
//----------------------------------------------------------------------------

bool RegAccess::read(int index, csr_u64_t& reg)
{
    if (!CSR_REG_IS_SINGLE(index)) {
        return setError(EINVAL, "invalid register index");
    }
#if defined(__linux__)
    if (::ioctl(_fd, CSR_CMD_GET_REG(index), &reg) < 0) {
        return setError(errno, "ioctl(GET_REG)");
    }
#elif defined(__APPLE__)
    ::socklen_t len = sizeof(reg);
    if (::getsockopt(_fd, SYSPROTO_CONTROL, CSR_CMD_GET_REG(index), &reg, &len) < 0)  {
        return setError(errno, "getsockopt(GET_REG)");
    }
#endif
    return true;
}

bool RegAccess::read(int index, csr_pair_t& reg)
{
    if (CSR_REG_IS_SINGLE(index)) {
        reg.high = 0;
        return read(index, reg.low);
    }
    if (!CSR_REG_IS_PAIR(index)) {
        return setError(EINVAL, "invalid register pair index");
    }
#if defined(__linux__)
    if (::ioctl(_fd, CSR_CMD_GET_REG2(index), &reg) < 0) {
        return setError(errno, "ioctl(GET_REG2)");
    }
#elif defined(__APPLE__)
    ::socklen_t len = sizeof(reg);
    if (::getsockopt(_fd, SYSPROTO_CONTROL, CSR_CMD_GET_REG2(index), &reg, &len) < 0)  {
        return setError(errno, "getsockopt(GET_REG2)");
    }
#endif
    return true;
}


//----------------------------------------------------------------------------
// Write CPU registers.
//----------------------------------------------------------------------------

bool RegAccess::write(int index, csr_u64_t reg)
{
    if (!CSR_REG_IS_SINGLE(index)) {
        return setError(EINVAL, "invalid register index");
    }
#if defined(__linux__)
    if (::ioctl(_fd, CSR_CMD_SET_REG(index), &reg) < 0) {
        return setError(errno, "ioctl(SET_REG)");
    }
#elif defined(__APPLE__)
    if (::setsockopt(_fd, SYSPROTO_CONTROL, CSR_CMD_SET_REG(index), &reg, sizeof(reg)) < 0)  {
        return setError(errno, "getsockopt(SET_REG)");
    }
#endif
    return true;
}

bool RegAccess::write(int index, const csr_pair_t& reg)
{
    if (CSR_REG_IS_SINGLE(index)) {
        return write(index, reg.low);
    }
    if (!CSR_REG_IS_PAIR(index)) {
        return setError(EINVAL, "invalid register pair index");
    }
#if defined(__linux__)
    if (::ioctl(_fd, CSR_CMD_SET_REG2(index), &reg) < 0) {
        return setError(errno, "ioctl(SET_REG2)");
    }
#elif defined(__APPLE__)
    if (::setsockopt(_fd, SYSPROTO_CONTROL, CSR_CMD_SET_REG2(index), &reg, sizeof(reg)) < 0)  {
        return setError(errno, "getsockopt(SET_REG2)");
    }
#endif
    return true;
}
