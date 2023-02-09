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
static int cpu_features = 0;

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
    // Get CPU features we may need later.
    cpu_features = csr_get_cpu_features();
    stop_pending = 0;

    // Register the control interface of this kernel extension.
    // Control id and unit are left as zero and will be dynamically allocated.
    struct kern_ctl_reg reg;
    bzero(&reg, sizeof(reg));
    strncpy(reg.ctl_name, CSR_SOCKET_NAME, sizeof(reg.ctl_name));
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
            stop_pending = 0;
        }
    }
    return 0;
}


//----------------------------------------------------------------------------
// Called on getsockopt() from userland.
//----------------------------------------------------------------------------

static errno_t csr_getopt(kern_ctl_ref kctlref, u_int32_t unit, void* unitinfo, int opt, void* data, size_t* len)
{
    const int regid = csr_sockopt_to_regid(opt);
    const size_t size = csr_regid_is_pair(regid) ? sizeof(csr_pair_t) : sizeof(csr_u64_t);

    if (!csr_regid_is_valid(regid)) {
        return EINVAL;
    }
    else if (len == NULL) {
        return EFAULT;
    }
    else if (*len < size) {
        return EINVAL;
    }
    else if (offsetof(csr_pair_t, low) != 0) { // sanity check for csr_get_register()
        return EPROTO;
    }

    // If data is NULL, simply return the expected size.
    *len = size;
    if (data != NULL && csr_get_register(regid, (csr_pair_t*)data, cpu_features)) {
        return ENOTSUP;
    }
    else {
        return 0;
    }
}


//----------------------------------------------------------------------------
// Called on setsockopt() from userland.
//----------------------------------------------------------------------------

static errno_t csr_setopt(kern_ctl_ref kctlref, u_int32_t unit, void* unitinfo, int opt, void* data, size_t len)
{
    const int regid = csr_sockopt_to_regid(opt);
    const size_t size = csr_regid_is_pair(regid) ? sizeof(csr_pair_t) : sizeof(csr_u64_t);

    if (!csr_regid_is_valid(regid)) {
        return EINVAL;
    }
    else if (data == NULL) {
        return EFAULT;
    }
    else if (len < size) {
        return EINVAL;
    }
    else if (offsetof(csr_pair_t, low) != 0) { // sanity check for csr_set_register()
        return EPROTO;
    }
    else if (csr_set_register(regid, (const csr_pair_t*)data, cpu_features)) {
        return ENOTSUP;
    }
    else {
        return 0;
    }
}
