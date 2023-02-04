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
// Check the presence of some CPU features.
// Return zero if required features are present, an error code otherwise.
//----------------------------------------------------------------------------

static inline __attribute__((always_inline)) errno_t csr_check_feature(int features)
{
    return features == (features & cpu_features) ? 0 : ENOTSUP;
}


//----------------------------------------------------------------------------
// Check getsockopt() parameters, update the requested size.
//----------------------------------------------------------------------------

static errno_t csr_check_getopt(void* data, size_t* len, size_t retsize, int features)
{
    if (len == NULL) {
        return EFAULT;
    }
    else if (*len < retsize) {
        return EINVAL;
    }
    else {
        *len = retsize;
        return csr_check_feature(features);
    }
}


//----------------------------------------------------------------------------
// Check setsockopt() parameters.
//----------------------------------------------------------------------------

static errno_t csr_check_setopt(void* data, size_t len, size_t retsize, int features)
{
    if (data == NULL) {
        return EFAULT;
    }
    else if (len < retsize) {
        return EINVAL;
    }
    else {
        return csr_check_feature(features);
    }
}


//----------------------------------------------------------------------------
// Called on getsockopt() from userland.
//----------------------------------------------------------------------------

static errno_t csr_getopt(kern_ctl_ref kctlref, u_int32_t unit, void* unitinfo, int opt, void* data, size_t* len)
{
    errno_t status = 0;
    csr_pair_t* pair = NULL;

    switch (opt) {

#define _GET_SINGLE(index, name, features)               \
        case CSR_CMD_GET_REG(index): {                   \
            status = csr_check_getopt(data, len, sizeof(csr_u64_t), (features)); \
            if (!status && data) {                       \
                CSR_MRS_STR(*(csr_u64_t*)(data), name);  \
            }                                            \
            break;                                       \
        }
#define _GET_PAIR(index, name_high, name_low, features)  \
        case CSR_CMD_GET_REG2(index): {                  \
            status = csr_check_getopt(data, len, sizeof(csr_pair_t), (features)); \
            if (!status && data) {                       \
                pair = (csr_pair_t*)(data);              \
                CSR_MRS_STR(pair->high, name_high);      \
                CSR_MRS_STR(pair->low,  name_low);       \
            }                                            \
            break;                                       \
        }

        _GET_SINGLE(CSR_REG_AA64PFR0,    "id_aa64pfr0_el1", 0)
        _GET_SINGLE(CSR_REG_AA64PFR1,    "id_aa64pfr1_el1", 0)
        _GET_SINGLE(CSR_REG_AA64ISAR0,   "id_aa64isar0_el1", 0)
        _GET_SINGLE(CSR_REG_AA64ISAR1,   "id_aa64isar1_el1", 0)
        _GET_SINGLE(CSR_REG_AA64ISAR2,   "id_aa64isar2_el1", 0)
        _GET_SINGLE(CSR_REG_TCR,         "tcr_el1", 0)
        _GET_SINGLE(CSR_REG_MIDR,        "midr_el1", 0)
        _GET_SINGLE(CSR_REG_MPIDR,       "mpidr_el1", 0)
        _GET_SINGLE(CSR_REG_REVIDR,      "revidr_el1", 0)
        _GET_SINGLE(CSR_REG_TPIDRRO_EL0, "tpidrro_el0", 0)
        _GET_SINGLE(CSR_REG_TPIDR_EL0,   "tpidr_el0", 0)
        _GET_SINGLE(CSR_REG_TPIDR_EL1,   "tpidr_el1", 0)
        _GET_SINGLE(CSR_REG_SCTLR,       "sctlr_el1", 0)

        _GET_SINGLE(CSR_REG_SCXTNUM_EL0, "scxtnum_el0", FEAT_CSV2_2)
        _GET_SINGLE(CSR_REG_SCXTNUM_EL1, "scxtnum_el1", FEAT_CSV2_2)

        _GET_PAIR(CSR_REG2_APIAKEY, "apiakeyhi_el1", "apiakeylo_el1", FEAT_PAC)
        _GET_PAIR(CSR_REG2_APIBKEY, "apibkeyhi_el1", "apibkeylo_el1", FEAT_PAC)
        _GET_PAIR(CSR_REG2_APDAKEY, "apdakeyhi_el1", "apdakeylo_el1", FEAT_PAC)
        _GET_PAIR(CSR_REG2_APDBKEY, "apdbkeyhi_el1", "apdbkeylo_el1", FEAT_PAC)
        _GET_PAIR(CSR_REG2_APGAKEY, "apgakeyhi_el1", "apgakeylo_el1", FEAT_PACGA)

#undef _GET_PAIR
#undef _GET_SINGLE

        default: {
            status = EINVAL;
            break;
        }
    }
    return status;
}


//----------------------------------------------------------------------------
// Called on setsockopt() from userland.
//----------------------------------------------------------------------------

static errno_t csr_setopt(kern_ctl_ref kctlref, u_int32_t unit, void* unitinfo, int opt, void* data, size_t len)
{
    errno_t status = 0;
    csr_pair_t* pair = NULL;

    switch (opt) {

#define _SET_SINGLE(index, name, features)               \
        case CSR_CMD_SET_REG2(index): {                  \
            status = csr_check_setopt(data, len, sizeof(csr_u64_t), (features)); \
            if (!status) {                               \
                CSR_MSR_STR(name, *(csr_u64_t*)(data));  \
            }                                            \
            break;                                       \
        }
#define _SET_PAIR(index, name_high, name_low, features)  \
        case CSR_CMD_SET_REG2(index): {                  \
            status = csr_check_setopt(data, len, sizeof(csr_pair_t), (features)); \
            if (!status) {                               \
                pair = (csr_pair_t*)(data);              \
                CSR_MSR_STR(name_high, pair->high);      \
                CSR_MSR_STR(name_low, pair->low);        \
            }                                            \
            break;                                       \
        }

        _SET_SINGLE(CSR_REG_TPIDRRO_EL0, "tpidrro_el0", 0)
        _SET_SINGLE(CSR_REG_TPIDR_EL0,   "tpidr_el0", 0)
        _SET_SINGLE(CSR_REG_TPIDR_EL1,   "tpidr_el1", 0)
        _SET_SINGLE(CSR_REG_SCTLR,       "sctlr_el1", 0)

        _SET_SINGLE(CSR_REG_SCXTNUM_EL0, "scxtnum_el0", FEAT_CSV2_2)
        _SET_SINGLE(CSR_REG_SCXTNUM_EL1, "scxtnum_el1", FEAT_CSV2_2)

        _SET_PAIR(CSR_REG2_APIAKEY, "apiakeyhi_el1", "apiakeylo_el1", FEAT_PAC)
        _SET_PAIR(CSR_REG2_APIBKEY, "apibkeyhi_el1", "apibkeylo_el1", FEAT_PAC)
        _SET_PAIR(CSR_REG2_APDAKEY, "apdakeyhi_el1", "apdakeylo_el1", FEAT_PAC)
        _SET_PAIR(CSR_REG2_APDBKEY, "apdbkeyhi_el1", "apdbkeylo_el1", FEAT_PAC)
        _SET_PAIR(CSR_REG2_APGAKEY, "apgakeyhi_el1", "apgakeylo_el1", FEAT_PACGA)

#undef _SET_SINGLE
#undef _SET_PAIR

        default: {
            // Trying to set read-only registers ends up here.
            status = EINVAL;
            break;
        }
    }
    return status;
}
