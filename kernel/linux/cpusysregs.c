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
// Get ioctl() parameter from userland for CSR_IOCTL_SET_KEYxx commands.
//----------------------------------------------------------------------------

static long csr_ioctl_get_key(csr_pac_key_t* key, unsigned long param, int ga)
{
    csr_u64_t isar1, isar2;
    CSR_MRS_STR(isar1, "id_aa64isar1_el1");
    CSR_MRS_STR(isar2, "id_aa64isar2_el1");
    if ((!ga && !CSR_HAS_PAC(isar1, isar2)) || (ga && !CSR_HAS_PACGA(isar1, isar2))) {
        return -ENOKEY;
    }
    else if (copy_from_user(key, (void*)param, sizeof(csr_pac_key_t))) {
        return -EFAULT;
    }
    else {
        return 0;
    }
}


//----------------------------------------------------------------------------
// Called on ioctl() from userland.
//----------------------------------------------------------------------------

static long csr_ioctl(struct file* filp, unsigned int cmd, unsigned long param)
{
    long status = 0;
    csr_registers_t regs;
    csr_pac_key_t key;

    switch (cmd) {
        case CSR_IOCTL_GET_REGS: {
            // Get all CPU system registers.
            csr_read_registers(&regs);
            if (copy_to_user((void*)param, &regs, sizeof(regs))) {
                status = -EFAULT;
            }
            break;
        }
        case CSR_IOCTL_SET_KEYIA: {
            // Set PAC key A register for instruction pointers.
            status = csr_ioctl_get_key(&key, param, 0);
            if (!status) {
                CSR_MSR_NUM(CSR_APIAKEYHI_EL1, key.high);
                CSR_MSR_NUM(CSR_APIAKEYLO_EL1, key.low);
            }
            break;
        }
        case CSR_IOCTL_SET_KEYIB: {
            // Set PAC key B register for instruction pointers.
            status = csr_ioctl_get_key(&key, param, 0);
            if (!status) {
                CSR_MSR_NUM(CSR_APIBKEYHI_EL1, key.high);
                CSR_MSR_NUM(CSR_APIBKEYLO_EL1, key.low);
            }
            break;
        }
        case CSR_IOCTL_SET_KEYDA: {
            // Set PAC key A register for data pointers.
            status = csr_ioctl_get_key(&key, param, 0);
            if (!status) {
                CSR_MSR_NUM(CSR_APDAKEYHI_EL1, key.high);
                CSR_MSR_NUM(CSR_APDAKEYLO_EL1, key.low);
            }
            break;
        }
        case CSR_IOCTL_SET_KEYDB: {
            // Set PAC key B register for data pointers.
            status = csr_ioctl_get_key(&key, param, 0);
            if (!status) {
                CSR_MSR_NUM(CSR_APDBKEYHI_EL1, key.high);
                CSR_MSR_NUM(CSR_APDBKEYLO_EL1, key.low);
            }
            break;
        }
        case CSR_IOCTL_SET_KEYGA: {
            // Set PAC generic key register.
            status = csr_ioctl_get_key(&key, param, 1);
            if (!status) {
                CSR_MSR_NUM(CSR_APGAKEYHI_EL1, key.high);
                CSR_MSR_NUM(CSR_APGAKEYLO_EL1, key.low);
            }
            break;
        }
        default: {
            status = -EINVAL;
            break;
        }
    }
    return status;
}
