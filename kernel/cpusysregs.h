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

// Define an unsigned 64-bit int which is valid in userland and kernel, Linux and macOS.
#if defined(__linux__)

    #include <linux/types.h>
    #include <linux/ioctl.h>
    typedef __u64 csr_u64_t;

#elif defined(__APPLE__)

    #include <mach/mach_types.h>
    typedef u_int64_t csr_u64_t;

#endif

// Linux kernel module or macOS kernel extension name.
#define CSR_MODULE_NAME "cpusysregs"

// Description of a pair of hi/lo registers for PAC authentication keys.
// Most registers are individually read/written. Some registers, such as
// PAC keys, can be accessed only in pairs.
typedef struct {
    csr_u64_t high;
    csr_u64_t low;
} csr_pair_t;

// Attribute of a macro-like function.
#define CSR_INLINE static inline __attribute__((always_inline))


//----------------------------------------------------------------------------
// Check CPU features based on system registers values.
//----------------------------------------------------------------------------

// This macro checks if PACI and PACD are supported, based on the values of the
// ID_AA64ISAR1_EL1 (API or APA) and ID_AA64ISAR2_EL1 (APA3) system registers.
#define CSR_HAS_PAC(isar1,isar2) (((isar1) & 0x00000FF0) || ((isar2) & 0x0000F000))

// This macro checks if PACGA is supported, based on the values of the
// ID_AA64ISAR1_EL1 (GPI or GPA) and ID_AA64ISAR2_EL1 (GPA3) system registers.
#define CSR_HAS_PACGA(isar1,isar2) (((isar1) & 0xFF000000) || ((isar2) & 0x00000F00))

// This macro checks if BTI (Branch Target Identification) is supported,
// based on the values of the ID_AA64PFR1_EL1 system register.
#define CSR_HAS_BTI(pfr1) ((pfr1) & 0x0F)

// This macro checks if RME (Realm Management Extension) is supported,
// based on the values of the ID_AA64PFR0_EL1 system register.
#define CSR_HAS_RME(pfr0) ((pfr0) & 0x00F0000000000000llu)

// This macro gets the RME version (Realm Management Extension),
// based on the values of the ID_AA64PFR0_EL1 system register.
#define CSR_RME_VERSION(pfr0) (((pfr0) >> 52) & 0x0F)

// This macro checks if CSV2_2 (Cache Speculation Variant 2_2) is supported,
// based on the values of the ID_AA64PFR0_EL1 system register.
#define CSR_HAS_CSV2_2(pfr0) ((((pfr0) >> 56) & 0x0F) >= 2)

// This macro checks if random number generation is supported, based on the value of the
// ID_AA64ISAR0_EL1 system register.
#define CSR_HAS_RNG(isar0) ((isar0) & 0xF000000000000000llu)


//----------------------------------------------------------------------------
// List of system registers which are handled by the kernel module.
// These identifiers are strictly internal to this project. We cannot use the
// Arm ids (CSR_SREG_) because we need ids which fit on one byte.
// Most registers are individually accessible on 64 bits, using csr_u64_t.
// Some registers are accessible as pairs (CSR_REGID2_), using csr_pair_t.
//----------------------------------------------------------------------------

#define _CSR_REGID_BASE   0x0000
#define _CSR_REGID2_BASE  0x0100
#define _CSR_REGID_MASK   0x00FF

#define CSR_REGID_AA64PFR0     (_CSR_REGID_BASE | 0x00)   // AArch64 Processor Feature registers 0 (read-only)
#define CSR_REGID_AA64PFR1     (_CSR_REGID_BASE | 0x01)   // AArch64 Processor Feature registers 1 (read-only)
#define CSR_REGID_AA64ISAR0    (_CSR_REGID_BASE | 0x02)   // AArch64 Instruction Set Attribute Register 0 (read-only)
#define CSR_REGID_AA64ISAR1    (_CSR_REGID_BASE | 0x03)   // AArch64 Instruction Set Attribute Register 1 (read-only)
#define CSR_REGID_AA64ISAR2    (_CSR_REGID_BASE | 0x04)   // AArch64 Instruction Set Attribute Register 2 (read-only)
#define CSR_REGID_TCR          (_CSR_REGID_BASE | 0x05)   // Translation Control Register (read-only)
#define CSR_REGID_MIDR         (_CSR_REGID_BASE | 0x06)   // Main ID Register (read-only)
#define CSR_REGID_MPIDR        (_CSR_REGID_BASE | 0x07)   // Multiprocessor Affinity Register (read-only)
#define CSR_REGID_REVIDR       (_CSR_REGID_BASE | 0x08)   // Revision ID Register (read-only)
#define CSR_REGID_TPIDRRO_EL0  (_CSR_REGID_BASE | 0x09)   // EL0 Read-Only Software Thread ID Register (R/W at EL1)
#define CSR_REGID_TPIDR_EL0    (_CSR_REGID_BASE | 0x0A)   // EL0 Read/Write Software Thread ID Register
#define CSR_REGID_TPIDR_EL1    (_CSR_REGID_BASE | 0x0B)   // EL1 Software Thread ID Register
#define CSR_REGID_SCXTNUM_EL0  (_CSR_REGID_BASE | 0x0C)   // EL0 Read/Write Software Context Number
#define CSR_REGID_SCXTNUM_EL1  (_CSR_REGID_BASE | 0x0D)   // EL1 Read/Write Software Context Number
#define CSR_REGID_SCTLR        (_CSR_REGID_BASE | 0x0E)   // System Control Register
#define CSR_REGID_HCR          (_CSR_REGID_BASE | 0x0F)   // System Control Register (EL2)
#define CSR_REGID_RNDR         (_CSR_REGID_BASE | 0x10)   // Random Number
#define CSR_REGID_RNDRRS       (_CSR_REGID_BASE | 0x11)   // Reseeded Random Number
#define CSR_REGID_SCR          (_CSR_REGID_BASE | 0x12)   // Secure Configuration Register (EL3)
#define CSR_REGID_AA64MMFR0    (_CSR_REGID_BASE | 0x13)   // AArch64 Memory Model Feature Register 0
#define CSR_REGID_AA64MMFR1    (_CSR_REGID_BASE | 0x14)   // AArch64 Memory Model Feature Register 1
#define CSR_REGID_AA64MMFR2    (_CSR_REGID_BASE | 0x15)   // AArch64 Memory Model Feature Register 2
#define CSR_REGID_AA64ZFR0     (_CSR_REGID_BASE | 0x16)   // SVE Feature ID register 0
#define CSR_REGID_AA64SMFR0    (_CSR_REGID_BASE | 0x17)   // SME Feature ID register 0
#define CSR_REGID_AA64AFR0     (_CSR_REGID_BASE | 0x18)   // AArch64 Auxiliary Feature Register 0
#define CSR_REGID_AA64AFR1     (_CSR_REGID_BASE | 0x19)   // AArch64 Auxiliary Feature Register 1
#define CSR_REGID_AA64DFR0     (_CSR_REGID_BASE | 0x1A)   // AArch64 Debug Feature Register 0
#define CSR_REGID_AA64DFR1     (_CSR_REGID_BASE | 0x1B)   // AArch64 Debug Feature Register 1

#define CSR_REGID2_APIAKEY     (_CSR_REGID2_BASE | 0x00)  // Pointer Authentication Key A for Instruction
#define CSR_REGID2_APIBKEY     (_CSR_REGID2_BASE | 0x01)  // Pointer Authentication Key B for Instruction
#define CSR_REGID2_APDAKEY     (_CSR_REGID2_BASE | 0x02)  // Pointer Authentication Key A for Data
#define CSR_REGID2_APDBKEY     (_CSR_REGID2_BASE | 0x03)  // Pointer Authentication Key B for Data
#define CSR_REGID2_APGAKEY     (_CSR_REGID2_BASE | 0x04)  // Pointer Authentication Generic Key

// Check if a register id is in a valid range.
CSR_INLINE int csr_regid_is_valid(long regid)
{
    const long base = regid & ~_CSR_REGID_MASK;
    return base == _CSR_REGID_BASE || base == _CSR_REGID2_BASE;
}

// Check if a register id is a single register.
CSR_INLINE int csr_regid_is_single(long regid)
{
    return (regid & ~_CSR_REGID_MASK) == _CSR_REGID_BASE;
}

// Check if a register id is a pair of registers.
CSR_INLINE int csr_regid_is_pair(long regid)
{
    return (regid & ~_CSR_REGID_MASK) == _CSR_REGID2_BASE;
}


//----------------------------------------------------------------------------
// Kernel module commands.
// Linux: Use ioctl() on /dev/cpusysregs.
// macOS: Use getsockopt() and setsockopt() on system control cpusysregs.
//----------------------------------------------------------------------------

#if defined(__linux__)

    // Special device for this module.
    #define CSR_DEVICE_PATH "/dev/" CSR_MODULE_NAME

    // IOCTL codes for /dev/cpusysregs.
    // Each code shall be unique since all commands go through ioctl().
    #define _CSR_IOC_MAGIC            0x10
    #define _CSR_IOC_MAGIC2           0x20
    #define CSR_CMD_GET_REG(regid)    _IOR(_CSR_IOC_MAGIC,  (regid)  - _CSR_REGID_BASE,  csr_u64_t)
    #define CSR_CMD_GET_REG2(regid2)  _IOR(_CSR_IOC_MAGIC2, (regid2) - _CSR_REGID2_BASE, csr_pair_t)
    #define CSR_CMD_SET_REG(regid)    _IOW(_CSR_IOC_MAGIC,  (regid)  - _CSR_REGID_BASE,  csr_u64_t)
    #define CSR_CMD_SET_REG2(regid2)  _IOW(_CSR_IOC_MAGIC2, (regid2) - _CSR_REGID2_BASE, csr_pair_t)

    // Extract the register id from a command.
    CSR_INLINE int csr_cmd_to_regid(long cmd)
    {
        return (_IOC_TYPE(cmd) == _CSR_IOC_MAGIC2 ? _CSR_REGID2_BASE : _CSR_REGID_BASE) + _IOC_NR(cmd);
    }

#elif defined(__APPLE__)

    // System socket name for this module.
    #define CSR_SOCKET_NAME CSR_MODULE_NAME

    // Socket options for system control cpusysregs.
    // Get and set commands have identical values since they are used by distinct syscalls.
    #define _CSR_SOCKOPT_BASE         0x00AC0000
    #define CSR_CMD_GET_REG(regid)    (_CSR_SOCKOPT_BASE | (regid))
    #define CSR_CMD_GET_REG2(regid2)  (_CSR_SOCKOPT_BASE | (regid2))
    #define CSR_CMD_SET_REG(regid)    (_CSR_SOCKOPT_BASE | (regid))
    #define CSR_CMD_SET_REG2(regid2)  (_CSR_SOCKOPT_BASE | (regid2))

    // Extract the register id from a command.
    CSR_INLINE int csr_cmd_to_regid(long cmd)
    {
        return (int)(cmd & ~_CSR_SOCKOPT_BASE);
    }

#endif


//----------------------------------------------------------------------------
// Definitions of Arm64 system registers and instructions to access them.
// Useful in the kernel only with accessing EL1 registers.
//----------------------------------------------------------------------------
//
// The system registers are described in section D17 of the Arm Architecture Reference Manual.
//
// - To read a system register into a general-purpose register (GPR), use instruction MRS.
//   Example: asm("mrs %0, id_aa64pfr0_el1" : "=r" (result));
// - To write a system register from a general-purpose register (GPR), use instruction MSR.
//   Example: asm("msr id_aa64pfr0_el1, %0" : : "r" (value));
//
// The assembler recognizes the name of system registers which are defined for a given level
// of architecture. For instance, the register apiakeyhi_el1 is defined starting with Armv8.3.
// Using it in an asm directive works only if the compilation option -march=armv8.3-a or higher
// is used. Without an appropriate -march option, the compilation fails.
//
// However this does not work with the following standard use case: compile for a minimum
// architecture level, test at runtime the supported features, access the system register
// only if the corresponding feature is supported. Even though the corresponding MRS or MSR
// instructions are only executed at the required level of architecture, these instructions
// must be compiled for a lower level of architecture, for which the register names are not
// defined.
//
// To solve that case, we provide macros to forge MRS and MSR instructions using the
// numerical identification of the system register, without providing its name to the
// assembler. A system register is defined by 5 short identifiers: op0, op1, CRn, CRm, op2.
// In the MSR and MRS instructions, these identifiers are located at the following bits:
//   [20-19] op0, [18-16] op1, [15-12] CRn, [11-8] CRm, [7-5] op2
//
// The following macro build the encoding of a system register for a MSR or MRS instruction.
// See the description of each system register in section D17 to get its identifiers.
//
#define CSR_SREG(op0, op1, crn, crm, op2) (((op0) << 19) | ((op1) << 16) | ((crn) << 12) | ((crm) << 8) | ((op2) << 5))

//
// The following macros define the encoding of some system registers the names of which
// are not recognized with the default level of architecture.
//
#define CSR_APIAKEYLO_EL1 CSR_SREG(3, 0,  2, 1, 0)
#define CSR_APIAKEYHI_EL1 CSR_SREG(3, 0,  2, 1, 1)
#define CSR_APIBKEYLO_EL1 CSR_SREG(3, 0,  2, 1, 2)
#define CSR_APIBKEYHI_EL1 CSR_SREG(3, 0,  2, 1, 3)
#define CSR_APDAKEYLO_EL1 CSR_SREG(3, 0,  2, 2, 0)
#define CSR_APDAKEYHI_EL1 CSR_SREG(3, 0,  2, 2, 1)
#define CSR_APDBKEYLO_EL1 CSR_SREG(3, 0,  2, 2, 2)
#define CSR_APDBKEYHI_EL1 CSR_SREG(3, 0,  2, 2, 3)
#define CSR_APGAKEYLO_EL1 CSR_SREG(3, 0,  2, 3, 0)
#define CSR_APGAKEYHI_EL1 CSR_SREG(3, 0,  2, 3, 1)
#define CSR_RNDR          CSR_SREG(3, 3,  2, 4, 0)
#define CSR_RNDRRS        CSR_SREG(3, 3,  2, 4, 1)
#define CSR_SCXTNUM_EL0   CSR_SREG(3, 3, 13, 0, 7)
#define CSR_SCXTNUM_EL1   CSR_SREG(3, 0, 13, 0, 7)

//
// Standard stringification macro (not so standard since we must define it again and again).
//
#define _CSR_STRINGIFY_1(x) #x
#define CSR_STRINGIFY(x) _CSR_STRINGIFY_1(x)

//
// The following macro is a trick to forge instructions with general-purpose registers (GPR),
// In an asm directive, argument references such as "%0" or "%1" are replaced by the compiler
// backed with some GPR names such as "w12" or "x24". To build the instruction code, we need
// to transform "w12" as 12 or "x24" as 24. To do that, we define all possible identifiers for
// all GPR in the form .csr_gpr_wNN or .csr_gpr_xNN. In an asm directive, we use .csr_gpr_%0,
// which will be replaced by .csr_gpr_x24 (if GPR x24 has been allocated), which will be
// replaced by 24. We also define xzr and wzr as x31 (zero register).
//
#define _CSR_DEFINE_GPR             \
    ".irp num,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30\n" \
    ".equ .csr_gpr_x\\num, \\num\n" \
    ".equ .csr_gpr_w\\num, \\num\n" \
    ".endr\n"                       \
    ".equ .csr_gpr_sp, 31\n"        \
    ".equ .csr_gpr_xzr, 31\n"       \
    ".equ .csr_gpr_wzr, 31\n"

//
// Macros to read/write system registers by name.
// The corresponding register names must be known at all levels of architecture.
// Examples:
//    csr_u64_t r;
//    csr_mrs_str(r, "id_aa64pfr0_el1");
//    csr_msr_str("id_aa64pfr0_el1", r);
//
#define csr_msr_str(sreg,value)   asm("msr " sreg ", %0" : : "r" (value))
#define csr_mrs_str(result,sreg)  asm("mrs %0, " sreg : "=r" (result))

//
// Macros to read/write system registers by identifiers.
// This method works at all levels of architecture.
// Examples:
//    csr_u64_t r;
//    csr_msr_num(CSR_APIAKEYHI_EL1, r);
//    csr_mrs_num(r, CSR_APIAKEYHI_EL1);
//
#define csr_msr_num(sreg,value) \
    asm(_CSR_DEFINE_GPR ".inst 0xd5000000|(" CSR_STRINGIFY(sreg) ")|(.csr_gpr_%0)" : : "r" (value))

#define csr_mrs_num(result,sreg) \
    asm(_CSR_DEFINE_GPR ".inst 0xd5200000|(" CSR_STRINGIFY(sreg) ")|(.csr_gpr_%0)" : "=r" (result))


//----------------------------------------------------------------------------
// This code in used in the kernel only (Linux or macOS).
// All functions are typically called only once in the kernel module.
// For this reason, they are all inlined.
//----------------------------------------------------------------------------

#if defined(KERNEL)

// Define a few CPU features which are required to access some registers.
#define FEAT_PAC    0x0001
#define FEAT_PACGA  0x0002
#define FEAT_BTI    0x0004
#define FEAT_RME    0x0008
#define FEAT_CSV2_2 0x0010
#define FEAT_RNG    0x0020

// Get the CPU features. Typically called once on module initialization.
CSR_INLINE int csr_get_cpu_features(void)
{
    csr_u64_t pfr0, pfr1, isar0, isar1, isar2;
    csr_mrs_str(pfr0,  "id_aa64pfr0_el1");
    csr_mrs_str(pfr1,  "id_aa64pfr1_el1");
    csr_mrs_str(isar0, "id_aa64isar0_el1");
    csr_mrs_str(isar1, "id_aa64isar1_el1");
    csr_mrs_str(isar2, "id_aa64isar2_el1");
    return (CSR_HAS_PAC(isar1, isar2) ? FEAT_PAC : 0) |
           (CSR_HAS_PACGA(isar1, isar2) ? FEAT_PACGA : 0) |
           (CSR_HAS_BTI(pfr1) ? FEAT_BTI : 0) |
           (CSR_HAS_RME(pfr0) ? FEAT_RME : 0) |
           (CSR_HAS_CSV2_2(pfr0) ? FEAT_CSV2_2 : 0) |
           (CSR_HAS_RNG(isar0) ? FEAT_RNG : 0);
}

// Set the value of a single register or pair of registers.
// Return values: 0=success, 1=unknown register, 2=CPU feature missing
CSR_INLINE int csr_set_register(int regid, const csr_pair_t* value, int cpu_features)
{
#define _CHECK(features) if (((features) & cpu_features) != (features)) return 2
#define _SETREG_NUM(id, sreg, features) \
    case (id):                          \
        _CHECK(features);               \
        csr_msr_num(sreg, value->low);  \
        return 0
#define _SETREG_STR(id, sreg, features) \
    case (id):                          \
        _CHECK(features);               \
        csr_msr_str(sreg, value->low);  \
        return 0
#define _SETREG2_NUM(id, sreg_high, sreg_low, features) \
    case (id):                                          \
        _CHECK(features);                               \
        csr_msr_num(sreg_high, value->high);            \
        csr_msr_num(sreg_low, value->low);              \
        return 0
#define _SETREG2_STR(id, sreg_high, sreg_low, features) \
    case (id):                                          \
        _CHECK(features);                               \
        csr_msr_str(sreg_high, value->high);            \
        csr_msr_str(sreg_low, value->low);              \
        return 0

    switch (regid) {
        _SETREG_STR(CSR_REGID_TPIDRRO_EL0, "tpidrro_el0", 0);
        _SETREG_STR(CSR_REGID_TPIDR_EL0,   "tpidr_el0", 0);
        _SETREG_STR(CSR_REGID_TPIDR_EL1,   "tpidr_el1", 0);
        _SETREG_STR(CSR_REGID_SCTLR,       "sctlr_el1", 0);
        _SETREG_NUM(CSR_REGID_SCXTNUM_EL0, CSR_SCXTNUM_EL0, FEAT_CSV2_2);
        _SETREG_NUM(CSR_REGID_SCXTNUM_EL1, CSR_SCXTNUM_EL1, FEAT_CSV2_2);
        _SETREG2_NUM(CSR_REGID2_APIAKEY,   CSR_APIAKEYHI_EL1, CSR_APIAKEYLO_EL1, FEAT_PAC);
        _SETREG2_NUM(CSR_REGID2_APIBKEY,   CSR_APIBKEYHI_EL1, CSR_APIBKEYLO_EL1, FEAT_PAC);
        _SETREG2_NUM(CSR_REGID2_APDAKEY,   CSR_APDAKEYHI_EL1, CSR_APDAKEYLO_EL1, FEAT_PAC);
        _SETREG2_NUM(CSR_REGID2_APDBKEY,   CSR_APDBKEYHI_EL1, CSR_APDBKEYLO_EL1, FEAT_PAC);
        _SETREG2_NUM(CSR_REGID2_APGAKEY,   CSR_APGAKEYHI_EL1, CSR_APGAKEYLO_EL1, FEAT_PACGA);
        default: return 1;
    }

#undef _CHECK
#undef _SETREG_NUM
#undef _SETREG_STR
#undef _SETREG2_NUM
#undef _SETREG2_STR
}

#endif // KERNEL

#endif // CPUSYSREGS_H
