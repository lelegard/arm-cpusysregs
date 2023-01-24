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
#define CSR_MODULE_NAME "cpusysregs"
#define CSR_CLASS_NAME  "cpusysregs"
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

// Initialize the kernel module (upon "insmod").
static int __init csr_init(void)
{
    // Register the device. Allocating a major number (first param iz zero).
    csr_major_number = register_chrdev(0, CSR_DEVICE_NAME, &csr_fops);
    if (csr_major_number < 0) {
        pr_alert("%s: failed to register a major number\n", CSR_MODULE_NAME);
        return csr_major_number;
    }
    pr_info("%s: device major number is %d\n", CSR_MODULE_NAME, csr_major_number);

    // Create the device class.
    csr_class = class_create(THIS_MODULE, CSR_CLASS_NAME);
    if (IS_ERR(csr_class)) {
        unregister_chrdev(csr_major_number, CSR_DEVICE_NAME);
        pr_alert("%s: failed to register device class\n", CSR_MODULE_NAME);
        return PTR_ERR(csr_class);
    }
    csr_class->devnode = csr_devnode;

    // Create the device.
    csr_device = device_create(csr_class, NULL, MKDEV(csr_major_number, 0), NULL, CSR_DEVICE_NAME);
    if (IS_ERR(csr_device)) {
        class_destroy(csr_class);
        unregister_chrdev(csr_major_number, CSR_DEVICE_NAME);
        pr_alert("%s: failed to create the device\n", CSR_DEVICE_NAME);
        return PTR_ERR(csr_device);
    }

    return 0;
}

// Cleanup the kernel module (upon "rmmod").
static void __exit csr_exit(void)
{
    // Close resources in reverse order from csr_init().
    device_destroy(csr_class, MKDEV(csr_major_number, 0));
    class_destroy(csr_class);
    unregister_chrdev(csr_major_number, CSR_DEVICE_NAME);
    pr_info("%s: module removed\n", CSR_MODULE_NAME);
}

// Called during the creation of our device to set its permissions.
static char* csr_devnode(struct device* dev, umode_t* mode)
{
    // Warning, mode is null when called on device deletion.
    if (mode != NULL && dev->devt == MKDEV(csr_major_number, 0)) {
        // Always set permissions -rw-rw-rw- on /dev/cpusysregs.
        *mode = 0666;
    }
    return NULL;
}

// Called on ioctl() from userland.
static long csr_ioctl(struct file* filp, unsigned int cmd, unsigned long param)
{
    switch (cmd) {
        case CSR_IOCTL_GET_REGS: {
            // Get all CPU system registers.
            csr_registers_t regs;
#define MRS(name) asm("mrs %[result], " #name : [result] "=r" (regs.name))
            MRS(id_aa64pfr0_el1);
            MRS(id_aa64pfr1_el1);
            MRS(id_aa64isar0_el1);
            MRS(id_aa64isar1_el1);
            MRS(id_aa64isar2_el1);
#undef MRS
            if (copy_to_user((void*)param, &regs, sizeof(regs))) {
                return -EFAULT;
            }
            break;
        }
        case CSR_IOCTL_SET_KEYA: {
            // Set PAC key A register.
            csr_u64_t key = 0;
            if (copy_from_user(&key, (const void*)param, sizeof(key))) {
                return -EFAULT;
            }
            pr_info("key A: %08X-%08X\n", (__u32)((key >> 32) & 0xFFFFFFFF), (__u32)(key & 0xFFFFFFFF));
            break;
        }
        case CSR_IOCTL_SET_KEYB: {
            // Set PAC key B register.
            csr_u64_t key = 0;
            if (copy_from_user(&key, (const void*)param, sizeof(key))) {
                return -EFAULT;
            }
            pr_info("key B: %08X-%08X\n", (__u32)((key >> 32) & 0xFFFFFFFF), (__u32)(key & 0xFFFFFFFF));
            break;
        }
        default: {
            return -EINVAL;
        }
    }
    return 0;
}
