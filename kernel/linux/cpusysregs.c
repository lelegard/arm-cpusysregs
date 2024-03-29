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
#include <linux/version.h>

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
static int cpu_features = 0;

// Functions in this module.

static int __init csr_init(void);
static void __exit csr_exit(void);
static char* csr_devnode(const struct device* dev, umode_t* mode);
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
    // Get CPU features we may need later.
    cpu_features = csr_get_cpu_features();

    // Register the device. Use same name for module and device.
    // Allocate a major number (first param is zero).
    csr_major_number = register_chrdev(0, CSR_MODULE_NAME, &csr_fops);
    if (csr_major_number < 0) {
        pr_alert("%s: failed to register a major number\n", CSR_MODULE_NAME);
        return csr_major_number;
    }
    pr_info("%s: device major number is %d\n", CSR_MODULE_NAME, csr_major_number);

    // Create the device class. Use same name for class and module and device.
#if LINUX_VERSION_CODE < KERNEL_VERSION(6, 4, 0)
    csr_class = class_create(THIS_MODULE, CSR_MODULE_NAME);
#else
    csr_class = class_create(CSR_MODULE_NAME);
#endif
    if (IS_ERR(csr_class)) {
        unregister_chrdev(csr_major_number, CSR_MODULE_NAME);
        pr_alert("%s: failed to register device class\n", CSR_MODULE_NAME);
        return PTR_ERR(csr_class);
    }

    // Dirty warning ignore, due to RHEL 9.3 backport of post 6.2 features.
    // See comments in function csr_devnode().
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
    csr_class->devnode = csr_devnode;
    #pragma GCC diagnostic pop

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

// Parameter type issue: Starting with Linux 6.2, the devnode callback in the
// device class structure uses "const struct device*" instead of "struct device*".
// We initially used "#if LINUX_VERSION_CODE < KERNEL_VERSION(6, 2, 0)" to condition
// the parameter type. However, we noticed that some distros back-ported some kernel
// features which broke the test on kernel version. For instance RHEL 9.2 used kernel
// 5.14.0-284.25.1 with "struct device*". But RHEL 9.3, with the almost identical kernel
// 5.14.0-362.24.1, uses "const struct device*", clearly indicating some sort backport
// from 6.2. Because it is now impossible to test the kernel version to determine the
// parameter type, we simply use "const" and mute the warning :-(

static char* csr_devnode(const struct device* dev, umode_t* mode)
{
    // Warning, mode is null when called on device deletion.
    if (mode != NULL && dev->devt == MKDEV(csr_major_number, 0)) {
        // Always set permissions -rw-rw-rw- on /dev/cpusysregs.
        *mode = 0666;
    }
    return NULL;
}


//----------------------------------------------------------------------------
// Called on ioctl() from userland.
//----------------------------------------------------------------------------

static long csr_ioctl(struct file* filp, unsigned int cmd, unsigned long param)
{
    // Check if this an instruction to execute.
    const int instr = csr_ioc_to_instr(cmd);
    if (instr != CSR_INSTR_INVALID) {
        // Execute that specific instruction.
        csr_instr_t args;
        if (copy_from_user(&args, (void*)param, sizeof(args))) {
            return -EFAULT;
        }
        else if (csr_exec_instr(instr, &args)) {
            return -EINVAL;
        }
        else if (copy_to_user((void*)param, &args, sizeof(args))) {
            return -EFAULT;
        }
        else {
            return 0;
        }
    }
    else {
        // This must be a register to read/write. Get REGID from ioctl() command.
        csr_pair_t reg;
        const int regid = csr_ioc_to_regid(cmd);
        const size_t size = csr_regid_is_pair(regid) ? sizeof(reg) : sizeof(reg.low);
        if (!csr_regid_is_valid(regid)) {
            return -EINVAL;
        }

        // Sanity check on data size and layout.
        if (size != _IOC_SIZE(cmd) || (char*)(&reg) != (char*)(&reg.low)) {
            return -EPROTO;
        }

        // Get or set operation.
        switch (_IOC_DIR(cmd)) {
            case _IOC_READ:
                // Get register value.
                if (csr_get_register(regid, &reg, cpu_features)) {
                    return -EINVAL;
                }
                else if (copy_to_user((void*)param, &reg, size)) {
                    return -EFAULT;
                }
                else {
                    return 0;
                }
            case _IOC_WRITE:
                // Set register value.
                if (copy_from_user(&reg, (void*)param, size)) {
                    return -EFAULT;
                }
                else if (csr_set_register(regid, &reg, cpu_features)) {
                    return -EINVAL;
                }
                else {
                    return 0;
                }
            default:
                return -EINVAL;
        }
    }
}
