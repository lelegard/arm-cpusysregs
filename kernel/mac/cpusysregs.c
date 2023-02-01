//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Kernel extension (kext) for macOS.
// Reads the Arm64 CPU system registers and return them to userland.
// For test and educational purpose only, can have unexpected security effects.
//
//----------------------------------------------------------------------------

#include "cpusysregs.h"
#include <libkern/libkern.h>
#include <sys/kern_control.h>
#include <sys/errno.h>
#include <os/log.h>

// Reference to the control interface.

static void* _ctlref = NULL;
static int stop_pending = 0;

// Functions in this module.

static kern_return_t csr_start(kmod_info_t*, void*);
static kern_return_t csr_stop(kmod_info_t*, void*);
static errno_t csr_connect(kern_ctl_ref, struct sockaddr_ctl*, void**);
static errno_t csr_disconnect(kern_ctl_ref, u_int32_t, void*);
static errno_t csr_getopt(kern_ctl_ref, u_int32_t, void*, int, void*, size_t*);
static errno_t csr_setopt(kern_ctl_ref, u_int32_t, void*, int, void*, size_t);

// Registration of the module.

extern kern_return_t _start(kmod_info_t *ki, void *data);
extern kern_return_t _stop(kmod_info_t *ki, void *data);
 
__attribute__((visibility("default"))) KMOD_EXPLICIT_DECL(cpusysregs, "1.0.0d1", _start, _stop)
__private_extern__ kmod_start_func_t* _realmain = csr_start;
__private_extern__ kmod_stop_func_t* _antimain = csr_stop;
__private_extern__ int _kext_apple_cc = __APPLE_CC__;


//----------------------------------------------------------------------------
// Called when the kernel extension is loaded.
//----------------------------------------------------------------------------

static kern_return_t csr_start(kmod_info_t* kinfo, void* data)
{
    stop_pending = 0;

    // Register the control interface of this kernel extension.
    // Control id and unit are left as zero and will be dynamically allocated.
    struct kern_ctl_reg reg;
    bzero(&reg, sizeof(reg));
    strncpy(reg.ctl_name, CSR_MODULE_NAME, sizeof(reg.ctl_name));
    reg.ctl_connect = csr_connect;
    reg.ctl_disconnect = csr_disconnect;
    reg.ctl_getopt = csr_getopt;
    reg.ctl_setopt = csr_setopt;
 
    const int err = ctl_register(&reg, &_ctlref);
    if (err != 0) {
        os_log_error(OS_LOG_DEFAULT, "ctl_register failed, error %d\n", err);
        return KERN_FAILURE;
    }

    os_log_info(OS_LOG_DEFAULT, "%s loaded\n", CSR_MODULE_NAME);
    return KERN_SUCCESS;
}


//----------------------------------------------------------------------------
// Called when the kernel extension is unloaded.
//----------------------------------------------------------------------------

static kern_return_t csr_stop(kmod_info_t* kinfo, void* data)
{
    if (_ctlref != NULL) {
        // Deregister the control interface.
        const int err = ctl_deregister(_ctlref);
        if (err != 0) {
            // Could possibly fail with EBUSY if some client is still connected.
            // In that case, we should mark the module as "stop pending" and
            // retry to deregister in the disconnect callback, where deregister
            // will succeed when the last client disconnects.
            stop_pending = 1;
            os_log_error(OS_LOG_DEFAULT, "ctl_deregister failed, error %d\n", err);
            return KERN_FAILURE;
        }
        os_log_info(OS_LOG_DEFAULT, "%s unloaded\n", CSR_MODULE_NAME);
        _ctlref = NULL;
    }
    return KERN_SUCCESS;
}


//----------------------------------------------------------------------------
// Receive notification of a client connecting to the kernel control.
//----------------------------------------------------------------------------

static errno_t csr_connect(kern_ctl_ref kctlref, struct sockaddr_ctl* sac, void** unitinfo)
{
    // This function is mandatory, even empty, otherwise ctl_register() fails.
    return 0;
}


//----------------------------------------------------------------------------
// Receive notification that a client has disconnected from the kernel control.
//----------------------------------------------------------------------------

static errno_t csr_disconnect(kern_ctl_ref kctlref, u_int32_t unit, void* unitinfo)
{
    if (stop_pending && _ctlref != NULL) {
        // See comment in csr_stop().
        const int err = ctl_deregister(_ctlref);
        if (err != 0) {
            os_log_error(OS_LOG_DEFAULT, "ctl_deregister failed, error %d\n", err);
        }
        else {
            os_log_info(OS_LOG_DEFAULT, "%s unloaded\n", CSR_MODULE_NAME);
            _ctlref = NULL;
            stop_pending = 1;
        }
    }
    return 0;
}


//----------------------------------------------------------------------------
// Check setsockopt() parameters, update the requested size.
//----------------------------------------------------------------------------

static errno_t csr_check_getopt(void* data, size_t* len, size_t retsize)
{
    if (len == NULL) {
        return EFAULT;
    }
    else if (*len < retsize) {
        return EINVAL;
    }
    else {
        *len = retsize;
        return 0;
    }
}


//----------------------------------------------------------------------------
// Called on getsockopt() from userland.
//----------------------------------------------------------------------------

static errno_t csr_getopt(kern_ctl_ref kctlref, u_int32_t unit, void* unitinfo, int opt, void* data, size_t* len)
{
    errno_t status = 0;
    switch (opt) {
        case CSR_SO_GET_REGS: {
            // Get all CPU system registers.
            status = csr_check_getopt(data, len, sizeof(csr_registers_t));
            if (!status && data) {
                csr_read_registers((csr_registers_t*)(data));
            }
            break;
        }
        default: {
            status = EINVAL;
            break;
        }
    }
    return status;
}


//----------------------------------------------------------------------------
// Get setsockopt() parameter from userland for CSR_SO_SET_KEYxx commands.
//----------------------------------------------------------------------------

static errno_t csr_get_key(csr_pac_key_t* key, void* data, size_t len, int ga)
{
    csr_u64_t isar1, isar2;
    CSR_MRS_STR(isar1, "id_aa64isar1_el1");
    CSR_MRS_STR(isar2, "id_aa64isar2_el1");
    if (data == NULL) {
        return EFAULT;
    }
    else if (len < sizeof(csr_pac_key_t)) {
        return EINVAL;
    }
    else if ((!ga && !CSR_HAS_PAC(isar1, isar2)) || (ga && !CSR_HAS_PACGA(isar1, isar2))) {
        return ENOTSUP;
    }
    else {
        *key = *(csr_pac_key_t*)(data);
        return 0;
    }
}


//----------------------------------------------------------------------------
// Called on setsockopt() from userland.
//----------------------------------------------------------------------------

static errno_t csr_setopt(kern_ctl_ref kctlref, u_int32_t unit, void* unitinfo, int opt, void* data, size_t len)
{
    errno_t status = 0;
    csr_pac_key_t key;

    switch (opt) {
        case CSR_SO_SET_KEYIA: {
            // Set PAC key A register for instruction pointers.
            status = csr_get_key(&key, data, len, 0);
            if (!status) {
                CSR_MSR_NUM(CSR_APIAKEYHI_EL1, key.high);
                CSR_MSR_NUM(CSR_APIAKEYLO_EL1, key.low);
            }
            break;
        }
        case CSR_SO_SET_KEYIB: {
            // Set PAC key B register for instruction pointers.
            status = csr_get_key(&key, data, len, 0);
            if (!status) {
                CSR_MSR_NUM(CSR_APIBKEYHI_EL1, key.high);
                CSR_MSR_NUM(CSR_APIBKEYLO_EL1, key.low);
            }
            break;
        }
        case CSR_SO_SET_KEYDA: {
            // Set PAC key A register for data pointers.
            status = csr_get_key(&key, data, len, 0);
            if (!status) {
                CSR_MSR_NUM(CSR_APDAKEYHI_EL1, key.high);
                CSR_MSR_NUM(CSR_APDAKEYLO_EL1, key.low);
            }
            break;
        }
        case CSR_SO_SET_KEYDB: {
            // Set PAC key B register for data pointers.
            status = csr_get_key(&key, data, len, 0);
            if (!status) {
                CSR_MSR_NUM(CSR_APDBKEYHI_EL1, key.high);
                CSR_MSR_NUM(CSR_APDBKEYLO_EL1, key.low);
            }
            break;
        }
        case CSR_SO_SET_KEYGA: {
            // Set PAC generic key register.
            status = csr_get_key(&key, data, len, 0);
            if (!status) {
                CSR_MSR_NUM(CSR_APGAKEYHI_EL1, key.high);
                CSR_MSR_NUM(CSR_APGAKEYLO_EL1, key.low);
            }
            break;
        }
        default: {
            status = EINVAL;
            break;
        }
    }
    return status;
}
