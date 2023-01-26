//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Kernel module interface.
// Can be included in kernel and userland, C or C++.
//
//----------------------------------------------------------------------------

#if !defined(CPUSYSREGS_H)
#define CPUSYSREGS_H 1

#include <linux/types.h>
#include <linux/ioctl.h>

#if defined(__cplusplus)
extern "C" {
#endif

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
    csr_u64_t tcr_el1;           // Translation Control Register
    csr_u64_t apiakeyhi_el1;     // Pointer Authentication Key A for Instruction (bits[127:64])
    csr_u64_t apiakeylo_el1;     // Pointer Authentication Key A for Instruction (bits[63:0])
    csr_u64_t apibkeyhi_el1;     // Pointer Authentication Key B for Instruction (bits[127:64])
    csr_u64_t apibkeylo_el1;     // Pointer Authentication Key B for Instruction (bits[63:0])
    csr_u64_t apdakeyhi_el1;     // Pointer Authentication Key A for Data (bits[127:64])
    csr_u64_t apdakeylo_el1;     // Pointer Authentication Key A for Data (bits[63:0])
    csr_u64_t apdbkeyhi_el1;     // Pointer Authentication Key B for Data (bits[127:64])
    csr_u64_t apdbkeylo_el1;     // Pointer Authentication Key B for Data (bits[63:0])
    csr_u64_t apgakeyhi_el1;     // Pointer Authentication Generic Key (bits[127:64])
    csr_u64_t apgakeylo_el1;     // Pointer Authentication Generic Key (bits[63:0])
} csr_registers_t;

// This macro checks if PACI and PACD are supported, based on the values of the
// ID_AA64ISAR1_EL1 (API or APA) and ID_AA64ISAR2_EL1 (APA3) system registers.
#define CSR_HAS_PAC(isar1,isar2) (((isar1) & 0x00000FF0) || ((isar2) & 0x0000F000))

// This macro checks if PACGA is supported, based on the values of the
// ID_AA64ISAR1_EL1 (GPI or GPA) and ID_AA64ISAR2_EL1 (GPA3) system registers.
#define CSR_HAS_GPAC(isar1,isar2) (((isar1) & 0xFF000000) || ((isar2) & 0x00000F00))

// This macro checks if BTI (Branch Target Identification) is supported,
// based on the values of the ID_AA64PFR1_EL1 system register.
#define CSR_HAS_BTI(pfr1) ((pfr1) & 0x0F)

// This macro checks if RME (Realm Management Extension) is supported,
// based on the values of the ID_AA64PFR0_EL1 system register.
#define CSR_HAS_RME(pfr0) ((pfr0) & 0x00F0000000000000llu)

// This macro gets the RME version (Realm Management Extension),
// based on the values of the ID_AA64PFR0_EL1 system register.
#define CSR_RME_VERSION(pfr0) (((pfr0) >> 52) & 0x0F)

// Description of a pair of hi/lo registers for PAC authentication key.
typedef struct _csr_pac_key {
    csr_u64_t high;
    csr_u64_t low;
} csr_pac_key_t;

// IOCTL codes for /dev/cpusysregs
#define CSR_IOC_MAGIC '\xF0'
#define CSR_IOCTL_GET_REGS  _IOR(CSR_IOC_MAGIC, 0, csr_registers_t)
#define CSR_IOCTL_SET_KEYIA _IOW(CSR_IOC_MAGIC, 1, csr_pac_key_t)
#define CSR_IOCTL_SET_KEYIB _IOW(CSR_IOC_MAGIC, 2, csr_pac_key_t)
#define CSR_IOCTL_SET_KEYDA _IOW(CSR_IOC_MAGIC, 3, csr_pac_key_t)
#define CSR_IOCTL_SET_KEYDB _IOW(CSR_IOC_MAGIC, 4, csr_pac_key_t)
#define CSR_IOCTL_SET_KEYG  _IOW(CSR_IOC_MAGIC, 5, csr_pac_key_t)

#if defined(__cplusplus)
}
#endif

#endif // CPUSYSREGS_H
