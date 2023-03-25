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

#if defined(__linux__)
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/ioctl.h>
#elif defined(__APPLE__)
    #include <unistd.h>
    #include <sys/socket.h>
    #include <sys/sys_domain.h>
    #include <sys/kern_control.h>
    #include <sys/ioctl.h>
#endif


//----------------------------------------------------------------------------
// Constructor and destructor.
//----------------------------------------------------------------------------

RegAccess::RegAccess(bool print_errors, bool exit_on_open_error) :
    _fd(CSR_INVALID_SYSHANDLE),
    _print_errors(print_errors),
    _error(CSR_SUCCESS),
    _error_ref()
{
#if defined(__linux__)

    // Open the pseudo-device for the kernel module.
    if ((_fd = ::open(CSR_DEVICE_PATH, O_RDONLY)) < 0) {
        setError(errno, "Error opening " CSR_DEVICE_PATH ", kernel module probably not loaded", false, exit_on_open_error);
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
    Zero(&info, sizeof(info));
    ::strncpy(info.ctl_name, CSR_SOCKET_NAME, sizeof(info.ctl_name));
    if (::ioctl(_fd, CTLIOCGINFO, &info) < 0) {
        setError(errno, "Error accessing system socket " CSR_SOCKET_NAME ", kernel extension probably not loaded", true, exit_on_open_error);
        return;
    }

    // Connect to the kernel extension using its id.
    struct sockaddr_ctl addr;
    Zero(&addr, sizeof(addr));
    addr.sc_len = sizeof(addr);
    addr.sc_family = AF_SYSTEM;
    addr.ss_sysaddr = AF_SYS_CONTROL;
    addr.sc_id = info.ctl_id;
    if (::connect(_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        setError(errno, "connect()", true, exit_on_open_error);
        return;
    }

#elif defined(WINDOWS)

    // Open the pseudo-device for the kernel driver.
    _fd = ::CreateFileA(CSR_DEVICE_NAME, GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (_fd == INVALID_HANDLE_VALUE) {
        setError(::GetLastError(), "Error opening " CSR_DEVICE_NAME ", kernel driver probably not loaded", false, exit_on_open_error);
        return;
    }

#endif
}


//----------------------------------------------------------------------------
// Close the kernel module, check if open.
//----------------------------------------------------------------------------

bool RegAccess::isOpen() const
{
    return _fd != CSR_INVALID_SYSHANDLE;
}

void RegAccess::close()
{
    if (_fd != CSR_INVALID_SYSHANDLE) {
#if defined(__linux__) || defined(__APPLE__)
        if (::close(_fd) < 0) {
            setError(errno, "close");
        }
#elif defined(WINDOWS)
        if (!::CloseHandle(_fd)) {
            setError(::GetLastError(), "CloseHandle");
        }
#endif
    }
    _fd = CSR_INVALID_SYSHANDLE;
}


//----------------------------------------------------------------------------
// Error reporting.
//----------------------------------------------------------------------------

void RegAccess::printLastError(const std::string& label, std::ostream& file) const
{
    if (_error != CSR_SUCCESS) {
        if (!label.empty()) {
            file << label << ": ";
        }
        if (!_error_ref.empty()) {
            file << _error_ref << ": ";
        }
        file << Error(_error) << std::endl;
    }
}

bool RegAccess::setError(SysError code, const std::string& ref, bool close_fd, bool exit_on_error)
{
    _error = code;
    _error_ref = ref;
    if (close_fd) {
        close();
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

bool RegAccess::read(int regid, csr_u64_t& reg)
{
    if (!csr_regid_is_single(regid)) {
        return setError(EINVAL, "invalid register id");
    }
#if defined(__linux__)
    if (::ioctl(_fd, CSR_IOC_GET_REG(regid), &reg) < 0) {
        return setError(errno, "ioctl(GET_REG)");
    }
#elif defined(__APPLE__)
    ::socklen_t len = sizeof(reg);
    if (::getsockopt(_fd, SYSPROTO_CONTROL, CSR_SOCKOPT_REG(regid), &reg, &len) < 0)  {
        return setError(errno, "getsockopt(GET_REG)");
    }
#elif defined(WINDOWS)
    ::ULONG retsize = 0;
    if (!::DeviceIoControl(_fd, CSR_IOC_GET_REG(regid), nullptr, 0, &reg, sizeof(reg), &retsize, nullptr)) {
        return setError(::GetLastError(), "DeviceIoControl(GET_REG)");
    }
    if (retsize < sizeof(reg)) {
        return setError(ERROR_INVALID_DATA, Format("DeviceIoControl(GET_REG) returned size too short: ", retsize));
    }
#endif
    return true;
}

bool RegAccess::read(int regid, csr_pair_t& reg)
{
    if (csr_regid_is_single(regid)) {
        reg.high = 0;
        return read(regid, reg.low);
    }
    if (!csr_regid_is_pair(regid)) {
        return setError(EINVAL, "invalid register pair id");
    }
#if defined(__linux__)
    if (::ioctl(_fd, CSR_IOC_GET_REG2(regid), &reg) < 0) {
        return setError(errno, "ioctl(GET_REG2)");
    }
#elif defined(__APPLE__)
    ::socklen_t len = sizeof(reg);
    if (::getsockopt(_fd, SYSPROTO_CONTROL, CSR_SOCKOPT_REG(regid), &reg, &len) < 0)  {
        return setError(errno, "getsockopt(GET_REG2)");
    }
#elif defined(WINDOWS)
    ::ULONG retsize = 0;
    if (!::DeviceIoControl(_fd, CSR_IOC_GET_REG(regid), nullptr, 0, &reg, sizeof(reg), &retsize, nullptr)) {
        return setError(::GetLastError(), "DeviceIoControl(GET_REG)");
    }
    if (retsize < sizeof(reg)) {
        return setError(ERROR_INVALID_DATA, Format("DeviceIoControl(GET_REG) returned size too short: ", retsize));
    }
#endif
    return true;
}


//----------------------------------------------------------------------------
// Write CPU registers.
//----------------------------------------------------------------------------

bool RegAccess::write(int regid, csr_u64_t reg)
{
    if (!csr_regid_is_single(regid)) {
        return setError(EINVAL, "invalid register id");
    }
#if defined(__linux__)
    if (::ioctl(_fd, CSR_IOC_SET_REG(regid), &reg) < 0) {
        return setError(errno, "ioctl(SET_REG)");
    }
#elif defined(__APPLE__)
    if (::setsockopt(_fd, SYSPROTO_CONTROL, CSR_SOCKOPT_REG(regid), &reg, sizeof(reg)) < 0)  {
        return setError(errno, "setsockopt(SET_REG)");
    }
#elif defined(WINDOWS)
    if (!::DeviceIoControl(_fd, CSR_IOC_SET_REG(regid), const_cast<csr_u64_t*>(&reg), sizeof(reg), nullptr, 0, nullptr, nullptr)) {
        return setError(::GetLastError(), "DeviceIoControl(SET_REG)");
    }
#endif
    return true;
}

bool RegAccess::write(int regid, const csr_pair_t& reg)
{
    if (csr_regid_is_single(regid)) {
        return write(regid, reg.low);
    }
    if (!csr_regid_is_pair(regid)) {
        return setError(EINVAL, "invalid register pair id");
    }
#if defined(__linux__)
    if (::ioctl(_fd, CSR_IOC_SET_REG2(regid), &reg) < 0) {
        return setError(errno, "ioctl(SET_REG2)");
    }
#elif defined(__APPLE__)
    if (::setsockopt(_fd, SYSPROTO_CONTROL, CSR_SOCKOPT_REG(regid), &reg, sizeof(reg)) < 0)  {
        return setError(errno, "setsockopt(SET_REG2)");
    }
#elif defined(WINDOWS)
    if (!::DeviceIoControl(_fd, CSR_IOC_SET_REG(regid), const_cast<csr_pair_t*>(&reg), sizeof(reg), nullptr, 0, nullptr, nullptr)) {
        return setError(::GetLastError(), "DeviceIoControl(SET_REG)");
    }
#endif
    return true;
}


//----------------------------------------------------------------------------
// Execute a PACxx or AUTxx in kernel mode.
//----------------------------------------------------------------------------

bool RegAccess::executeInstr(int instr, csr_instr_t& args)
{
#if defined(__linux__)
    if (::ioctl(_fd, CSR_IOC_INSTR(instr), &args) < 0) {
        return setError(errno, "ioctl(INSTR)");
    }
#elif defined(__APPLE__)
    ::socklen_t len = sizeof(args);
    if (::getsockopt(_fd, SYSPROTO_CONTROL, CSR_SOCKOPT_INSTR(instr), &args, &len) < 0)  {
        return setError(errno, "getsockopt(INSTR)");
    }
#elif defined(WINDOWS)
    ::ULONG retsize = 0;
    if (!::DeviceIoControl(_fd, CSR_IOC_INSTR(instr), &args, sizeof(args), &args, sizeof(args), &retsize, nullptr)) {
        return setError(::GetLastError(), "DeviceIoControl(INSTR)");
    }
    if (retsize < sizeof(args)) {
        return setError(ERROR_INVALID_DATA, Format("DeviceIoControl(INSTR) returned size too short: ", retsize));
    }
#endif
    return true;
}
