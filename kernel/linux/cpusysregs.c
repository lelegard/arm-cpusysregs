//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
//
// Dual license BSD-2-Clause / GPLv2. See the LICENSE file.
// All files in this project use a BSD-2-Clause license, except this one for
// compatibility with the Linux kernel license requirements.
//
// Linux kernel module for /dev/cpusysregs.
// Reads the Arm64 CPU system registers and return them to userland.
// For test and educational purpose only, can have unexpected security effects.
//
//----------------------------------------------------------------------------

#include "cpusysregs.h"
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>

// Description of the kernel module.

MODULE_AUTHOR("Thierry Lelegard");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Access the Arm64 CPU system registers");
MODULE_VERSION("1.0");

// Description of the /dev/cpusysregs device.
// The major number is dynamically allocated when the module is loaded.

static int csr_major_number = 0;
static struct class* csr_class = NULL;
static struct device* csr_device = NULL;

// Functions in this module.

static int __init csr_init(void);
static void __exit csr_exit(void);
static char* csr_devnode(struct device* dev, umode_t* mode);
static long csr_ioctl(struct file* filp, unsigned int cmd, unsigned long argp);

// Registration of the module.

module_init(csr_init);
module_exit(csr_exit);

// File operations instance for our device.

static struct file_operations csr_fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = csr_ioctl,
};


//----------------------------------------------------------------------------
// Initialize the kernel module (upon "insmod").
//----------------------------------------------------------------------------

static int __init csr_init(void)
{
    // Register the device. Use same name for module and device.
    // Allocate a major number (first param is zero).
    csr_major_number = register_chrdev(0, CSR_MODULE_NAME, &csr_fops);
    if (csr_major_number < 0) {
        pr_alert("%s: failed to register a major number\n", CSR_MODULE_NAME);
        return csr_major_number;
    }
    pr_info("%s: device major number is %d\n", CSR_MODULE_NAME, csr_major_number);

    // Create the device class. Use same name for class and module and device.
    csr_class = class_create(THIS_MODULE, CSR_MODULE_NAME);
    if (IS_ERR(csr_class)) {
        unregister_chrdev(csr_major_number, CSR_MODULE_NAME);
        pr_alert("%s: failed to register device class\n", CSR_MODULE_NAME);
        return PTR_ERR(csr_class);
    }
    csr_class->devnode = csr_devnode;

    // Create the device.
    csr_device = device_create(csr_class, NULL, MKDEV(csr_major_number, 0), NULL, CSR_MODULE_NAME);
    if (IS_ERR(csr_device)) {
        class_destroy(csr_class);
        unregister_chrdev(csr_major_number, CSR_MODULE_NAME);
        pr_alert("%s: failed to create the device\n", CSR_MODULE_NAME);
        return PTR_ERR(csr_device);
    }

    return 0;
}


//----------------------------------------------------------------------------
// Cleanup the kernel module (upon "rmmod").
//----------------------------------------------------------------------------

static void __exit csr_exit(void)
{
    // Close resources in reverse order from csr_init().
    device_destroy(csr_class, MKDEV(csr_major_number, 0));
    class_destroy(csr_class);
    unregister_chrdev(csr_major_number, CSR_MODULE_NAME);
    pr_info("%s: module removed\n", CSR_MODULE_NAME);
}


//----------------------------------------------------------------------------
// Called during the creation of our device to set its permissions.
//----------------------------------------------------------------------------

static char* csr_devnode(struct device* dev, umode_t* mode)
{
    // Warning, mode is null when called on device deletion.
    if (mode != NULL && dev->devt == MKDEV(csr_major_number, 0)) {
        // Always set permissions -rw-rw-rw- on /dev/cpusysregs.
        *mode = 0666;
    }
    return NULL;
}


//----------------------------------------------------------------------------
// Check presence of PAC and/or PACGA.
// Return zero if required features are present, an error code otherwise.
//----------------------------------------------------------------------------

static long csr_check_pac(int need_pac, int need_pacga)
{
    if (need_pac || need_pacga) {
        csr_u64_t isar1, isar2;
        CSR_MRS_STR(isar1, "id_aa64isar1_el1");
        CSR_MRS_STR(isar2, "id_aa64isar2_el1");
        if ((need_pac && !CSR_HAS_PAC(isar1, isar2)) || (need_pacga && !CSR_HAS_PACGA(isar1, isar2))) {
            return -EINVAL;
        }
    }
    return 0;
}


//----------------------------------------------------------------------------
// Return the value of a register to userland or fetch it from userland.
// Return the ioctl() status.
//----------------------------------------------------------------------------

static inline long csr_return_reg(csr_u64_t reg, unsigned long param)
{
    return copy_to_user((void*)param, &reg, sizeof(csr_u64_t)) ? -EFAULT : 0;
}

static inline long csr_return_pair(const csr_pair_t* reg, unsigned long param)
{
    return copy_to_user((void*)param, reg, sizeof(csr_pair_t)) ? -EFAULT : 0;
}

static inline long csr_fetch_reg(csr_u64_t* reg, unsigned long param)
{
    return copy_from_user(reg, (void*)param, sizeof(csr_u64_t)) ? -EFAULT : 0;
}

static long csr_fetch_pair(csr_pair_t* reg, unsigned long param, int need_pac, int need_pacga)
{
    long status = csr_check_pac(need_pac, need_pacga);
    if (!status && copy_from_user(reg, (void*)param, sizeof(csr_pair_t))) {
        status = -EFAULT;
    }
    return status;
}


//----------------------------------------------------------------------------
// Called on ioctl() from userland.
//----------------------------------------------------------------------------

static long csr_ioctl(struct file* filp, unsigned int cmd, unsigned long param)
{
    long status = 0;
    csr_pair_t reg;

    switch (cmd) {

#define _GET_SINGLE(index, name)                      \
        case CSR_CMD_GET_REG(index): {                \
            CSR_MRS_STR(reg.low, name);               \
            status = csr_return_reg(reg.low, param);  \
            break;                                    \
        }
#define _GET_PAIR(index, num_high, num_low, need_pac, need_pacga)  \
        case CSR_CMD_GET_REG2(index): {                            \
            status = csr_check_pac((need_pac), (need_pacga));      \
            if (!status) {                                         \
                CSR_MRS_NUM(reg.high, num_high);                   \
                CSR_MRS_NUM(reg.low, num_low);                     \
                status = csr_return_pair(&reg, param);             \
            }                                                      \
            break;                                                 \
        }
#define _SET_SINGLE(index, name)                      \
        case CSR_CMD_SET_REG(index): {                \
            status = csr_fetch_reg(&reg.low, param);  \
            if (!status) {                            \
                CSR_MSR_STR(name, reg.low);           \
            }                                         \
            break;                                    \
        }
#define _SET_PAIR(index, num_high, num_low, need_pac, need_pacga)            \
        case CSR_CMD_SET_REG2(index): {                                      \
            status = csr_fetch_pair(&reg, param, (need_pac), (need_pacga));  \
            if (!status) {                                                   \
                CSR_MSR_NUM(num_high, reg.high);                             \
                CSR_MSR_NUM(num_low, reg.low);                               \
            }                                                                \
            break;                                                           \
        }

        _GET_SINGLE(CSR_REG_AA64PFR0,    "id_aa64pfr0_el1")
        _GET_SINGLE(CSR_REG_AA64PFR1,    "id_aa64pfr1_el1")
        _GET_SINGLE(CSR_REG_AA64ISAR0,   "id_aa64isar0_el1")
        _GET_SINGLE(CSR_REG_AA64ISAR1,   "id_aa64isar1_el1")
        _GET_SINGLE(CSR_REG_AA64ISAR2,   "id_aa64isar2_el1")
        _GET_SINGLE(CSR_REG_TCR,         "tcr_el1")
        _GET_SINGLE(CSR_REG_MIDR,        "midr_el1")
        _GET_SINGLE(CSR_REG_MPIDR,       "mpidr_el1")
        _GET_SINGLE(CSR_REG_REVIDR,      "revidr_el1")
        _GET_SINGLE(CSR_REG_TPIDRRO_EL0, "tpidrro_el0")
        _GET_SINGLE(CSR_REG_TPIDR_EL0,   "tpidr_el0")
        _GET_SINGLE(CSR_REG_TPIDR_EL1,   "tpidr_el1")
        _GET_SINGLE(CSR_REG_SCXTNUM_EL0, "scxtnum_el0")
        _GET_SINGLE(CSR_REG_SCXTNUM_EL1, "scxtnum_el1")
        _GET_SINGLE(CSR_REG_SCTLR,       "sctlr_el1")

        _SET_SINGLE(CSR_REG_TPIDRRO_EL0, "tpidrro_el0")
        _SET_SINGLE(CSR_REG_TPIDR_EL0,   "tpidr_el0")
        _SET_SINGLE(CSR_REG_TPIDR_EL1,   "tpidr_el1")
        _SET_SINGLE(CSR_REG_SCXTNUM_EL0, "scxtnum_el0")
        _SET_SINGLE(CSR_REG_SCXTNUM_EL1, "scxtnum_el1")
        _SET_SINGLE(CSR_REG_SCTLR,       "sctlr_el1")

        _GET_PAIR(CSR_REG2_APIAKEY, CSR_APIAKEYHI_EL1, CSR_APIAKEYLO_EL1, 1, 0)
        _GET_PAIR(CSR_REG2_APIBKEY, CSR_APIBKEYHI_EL1, CSR_APIBKEYLO_EL1, 1, 0)
        _GET_PAIR(CSR_REG2_APDAKEY, CSR_APDAKEYHI_EL1, CSR_APDAKEYLO_EL1, 1, 0)
        _GET_PAIR(CSR_REG2_APDBKEY, CSR_APDBKEYHI_EL1, CSR_APDBKEYLO_EL1, 1, 0)
        _GET_PAIR(CSR_REG2_APGAKEY, CSR_APGAKEYHI_EL1, CSR_APGAKEYLO_EL1, 0, 1)
  
        _SET_PAIR(CSR_REG2_APIAKEY, CSR_APIAKEYHI_EL1, CSR_APIAKEYLO_EL1, 1, 0)
        _SET_PAIR(CSR_REG2_APIBKEY, CSR_APIBKEYHI_EL1, CSR_APIBKEYLO_EL1, 1, 0)
        _SET_PAIR(CSR_REG2_APDAKEY, CSR_APDAKEYHI_EL1, CSR_APDAKEYLO_EL1, 1, 0)
        _SET_PAIR(CSR_REG2_APDBKEY, CSR_APDBKEYHI_EL1, CSR_APDBKEYLO_EL1, 1, 0)
        _SET_PAIR(CSR_REG2_APGAKEY, CSR_APGAKEYHI_EL1, CSR_APGAKEYLO_EL1, 0, 1)

#undef _SET_PAIR
#undef _GET_PAIR
#undef _GET_SINGLE

        default: {
            status = -EINVAL;
            break;
        }
    }
    return status;
}
