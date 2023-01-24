#if !defined(CPUSYSREGS_H)
#define CPUSYSREGS_H 1

#include <linux/types.h>
#include <linux/ioctl.h>

#define CSR_DEVICE_NAME "cpusysregs"
#define CSR_DEVICE_PATH "/dev/" CSR_DEVICE_NAME

// stdint.h and uint64_t are not available in the kernel, must use a kernel type.
typedef __u64 csr_u64_t;

// All Arm64 system registers which are read by the cpusysregs kernel and returned to userland.
typedef struct _csr_registers {
    csr_u64_t id_aa64pfr0_el1;   // AArch64 Processor Feature registers 0
    csr_u64_t id_aa64pfr1_el1;   // AArch64 Processor Feature registers 1
    csr_u64_t id_aa64isar0_el1;  // AArch64 Instruction Set Attribute Register 0
    csr_u64_t id_aa64isar1_el1;  // AArch64 Instruction Set Attribute Register 1
    csr_u64_t id_aa64isar2_el1;  // AArch64 Instruction Set Attribute Register 2
} csr_registers_t;

// IOCTL codes for 
#define CSR_IOC_MAGIC '\xF0'
#define CSR_IOCTL_GET_REGS _IOR(CSR_IOC_MAGIC, 0, csr_registers_t)  // read all system registers
#define CSR_IOCTL_SET_KEYA _IOW(CSR_IOC_MAGIC, 1, csr_u64_t)
#define CSR_IOCTL_SET_KEYB _IOW(CSR_IOC_MAGIC, 2, csr_u64_t)

#endif // CPUSYSREGS_H
