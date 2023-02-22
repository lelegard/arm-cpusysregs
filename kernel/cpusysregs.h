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
    csr_u64_t low;
    csr_u64_t high;
} csr_pair_t;

// Attribute of a macro-like function.
#define CSR_INLINE static inline __attribute__((always_inline))


//----------------------------------------------------------------------------
// Check CPU features based on system registers values.
//----------------------------------------------------------------------------

// This macro checks if PACI and PACD are supported, based on the values of the
// ID_AA64ISAR1_EL1 (API or APA) and ID_AA64ISAR2_EL1 (APA3) system registers.
#define csr_has_pac(isar1,isar2) (((isar1) & 0x00000FF0) || ((isar2) & 0x0000F000))

// This macro checks if PACGA is supported, based on the values of the
// ID_AA64ISAR1_EL1 (GPI or GPA) and ID_AA64ISAR2_EL1 (GPA3) system registers.
#define csr_has_pacga(isar1,isar2) (((isar1) & 0xFF000000) || ((isar2) & 0x00000F00))

// This macro checks if BTI (Branch Target Identification) is supported,
// based on the values of the ID_AA64PFR1_EL1 system register.
#define csr_has_bti(pfr1) ((pfr1) & 0x0F)

// This macro checks if SVE (Scalable Vector Extension) is supported,
// based on the values of the ID_AA64PFR0_EL1 system register.
#define csr_has_sve(pfr0) ((pfr0) & 0x0000000F00000000llu)

// This macro checks if SME (Scalable Matrix Extension) is supported,
// based on the values of the ID_AA64PFR1_EL1 system register.
#define csr_has_sme(pfr1) ((pfr1) & 0x000000000F000000llu)

// This macro checks if RME (Realm Management Extension) is supported,
// based on the values of the ID_AA64PFR0_EL1 system register.
#define csr_has_rme(pfr0) ((pfr0) & 0x00F0000000000000llu)

// This macro gets the RME version (Realm Management Extension),
// based on the values of the ID_AA64PFR0_EL1 system register.
#define csr_rme_version(pfr0) (((pfr0) >> 52) & 0x0F)

// This macro checks if CSV2_2 (Cache Speculation Variant 2_2) is supported,
// based on the values of the ID_AA64PFR0_EL1 system register.
#define csr_has_csv2_2(pfr0) ((((pfr0) >> 56) & 0x0F) >= 2)

// This macro checks if random number generation is supported, based on the value of the
// ID_AA64ISAR0_EL1 system register.
#define csr_has_rng(isar0) ((isar0) & 0xF000000000000000llu)

// This macro checks if ETE (Embedded Trace Extension) is supported, based on the value of the
// ID_AA64DFR0_EL1 system register.
#define csr_has_ete(dfr0) ((dfr0) & 0x00000000000000F0llu)

// This macro checks if PMUv3p4 (Performance Monitor Extension v3.4) is supported, based on the value of the
// ID_AA64DFR0_EL1 system register.
#define csr_has_pmuv3p4(dfr0) (((dfr0 >> 8) & 0x0F) >= 5 && ((dfr0 >> 8) & 0x0F) < 15)

// This macro checks if TCR2 registers are supported, based on the value of the
// ID_AA64MMFR3_EL1 system register.
#define csr_has_tcr2(mmfr3) ((mmfr3) & 0x000000000000000Fllu)


//----------------------------------------------------------------------------
// List of system registers which are handled by the kernel module.
//----------------------------------------------------------------------------

// These identifiers are strictly internal to this project. We cannot use the
// Arm ids (CSR_SREG_) because we need ids which fit in one byte (constraint
// of ioctl() codes on Linux).
//
// Most registers are individually accessible on 64 bits, using csr_u64_t.
// Some registers are accessible as pairs (CSR_REGID2_), using csr_pair_t.
//
// Maintenance notes: When adding new registers, also:
// - If the register does not exist in "older" versions of the Arm Architecture,
//   its name may not be recognized by the assembler (Linux only). In that case,
//   add the corresponding CSR_SREG_name constant below and access the register
//   by number instead of name.
// - Update inlined functions csr_get_register() and csr_set_register() below.
//   If the register exists only when a given CPU features is supported, make
//   sure to set the list of required features for the register.
// - Add the register in the ../README.md file.
// - Add the description of the register in the ../apps/regview.cpp file.
//   Also make sure to specify the required list of CPU features.

#define _CSR_REGID_BASE   0x0000
#define _CSR_REGID2_BASE  0x0100
#define _CSR_REGID_MASK   0x00FF

// Individual registers.
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
#define CSR_REGID_TRCDEVARCH   (_CSR_REGID_BASE | 0x1C)   // Trace Device Architecture Register
#define CSR_REGID_PMMIR        (_CSR_REGID_BASE | 0x1D)   // Performance Monitors Machine Identification Register
#define CSR_REGID_CTR          (_CSR_REGID_BASE | 0x1E)   // Cache Type Register
#define CSR_REGID_TTBR0_EL1    (_CSR_REGID_BASE | 0x1F)   // Translation Table Base Register 0 (EL1)
#define CSR_REGID_TTBR1_EL1    (_CSR_REGID_BASE | 0x20)   // Translation Table Base Register 1 (EL1)
#define CSR_REGID_TCR2         (_CSR_REGID_BASE | 0x21)   // Extended Translation Control Register
#define CSR_REGID_AA64MMFR3    (_CSR_REGID_BASE | 0x22)   // AArch64 Memory Model Feature Register 3

// Registers which come in pair.
#define CSR_REGID2_APIAKEY     (_CSR_REGID2_BASE | 0x00)  // Pointer Authentication Key A for Instruction
#define CSR_REGID2_APIBKEY     (_CSR_REGID2_BASE | 0x01)  // Pointer Authentication Key B for Instruction
#define CSR_REGID2_APDAKEY     (_CSR_REGID2_BASE | 0x02)  // Pointer Authentication Key A for Data
#define CSR_REGID2_APDBKEY     (_CSR_REGID2_BASE | 0x03)  // Pointer Authentication Key B for Data
#define CSR_REGID2_APGAKEY     (_CSR_REGID2_BASE | 0x04)  // Pointer Authentication Generic Key

// Placeholder for invalid register id.
#define CSR_REGID_INVALID (~0)

// Check if a register id is in a valid range.
CSR_INLINE int csr_regid_is_valid(int regid)
{
    const int base = regid & ~_CSR_REGID_MASK;
    return base == _CSR_REGID_BASE || base == _CSR_REGID2_BASE;
}

// Check if a register id is a single register.
CSR_INLINE int csr_regid_is_single(int regid)
{
    return (regid & ~_CSR_REGID_MASK) == _CSR_REGID_BASE;
}

// Check if a register id is a pair of registers.
CSR_INLINE int csr_regid_is_pair(int regid)
{
    return (regid & ~_CSR_REGID_MASK) == _CSR_REGID2_BASE;
}


//----------------------------------------------------------------------------
// Pointer authentication commands.
// The PACxx and AUTxx instructions can be delegated into the kernel module.
// The purpose is to exhibit potential differences between user and kernel.
//----------------------------------------------------------------------------

// Codes of instructions to execute in kernel mode.
// These values must fit in one byte to be included in an ioctl() command code.
#define CSR_INSTR_PACIA  0x00
#define CSR_INSTR_PACIB  0x01
#define CSR_INSTR_PACDA  0x02
#define CSR_INSTR_PACDB  0x03
#define CSR_INSTR_PACGA  0x04
#define CSR_INSTR_AUTIA  0x05
#define CSR_INSTR_AUTIB  0x06
#define CSR_INSTR_AUTDA  0x07
#define CSR_INSTR_AUTDB  0x08

// Placeholder for invalid instruction code.
#define CSR_INSTR_INVALID (~0)

// Parameters for an instruction in kernel mode.
typedef struct {
    csr_u64_t value;     // value to sign or authenticate, read/write
    csr_u64_t modifier;  // modifier, read-only
} csr_instr_t;


//----------------------------------------------------------------------------
// Kernel module commands.
// Linux: Use ioctl() on /dev/cpusysregs.
// macOS: Use getsockopt() and setsockopt() on system control cpusysregs.
//----------------------------------------------------------------------------

#if defined(__linux__)

    // Special device for this module.
    #define CSR_DEVICE_PATH "/dev/" CSR_MODULE_NAME

    // ioctl() codes for /dev/cpusysregs.
    // Each code shall be unique since all commands go through ioctl().
    #define _CSR_IOC_REG              0x10
    #define _CSR_IOC_REG2             0x20
    #define _CSR_IOC_INSTR            0x30
    #define CSR_IOC_GET_REG(regid)    _IOR(_CSR_IOC_REG,  (regid)  - _CSR_REGID_BASE,  csr_u64_t)
    #define CSR_IOC_GET_REG2(regid2)  _IOR(_CSR_IOC_REG2, (regid2) - _CSR_REGID2_BASE, csr_pair_t)
    #define CSR_IOC_SET_REG(regid)    _IOW(_CSR_IOC_REG,  (regid)  - _CSR_REGID_BASE,  csr_u64_t)
    #define CSR_IOC_SET_REG2(regid2)  _IOW(_CSR_IOC_REG2, (regid2) - _CSR_REGID2_BASE, csr_pair_t)
    #define CSR_IOC_INSTR(instr)      _IOWR(_CSR_IOC_INSTR, (instr), csr_instr_t)

    // Extract the register id from an ioctl() code.
    // Return CSR_REGID_INVALID if not a set/get register command.
    CSR_INLINE int csr_ioc_to_regid(long cmd)
    {
        const long type = _IOC_TYPE(cmd);
        if (type == _CSR_IOC_REG) {
            return _CSR_REGID_BASE + _IOC_NR(cmd);
        }
        else if (type == _CSR_IOC_REG2) {
            return _CSR_REGID2_BASE + _IOC_NR(cmd);
        }
        else {
            return CSR_REGID_INVALID;
        }
    }

    // Extract the instruction code from an ioctl() code.
    // Return CSR_INSTR_INVALID if not an instruction command.
    CSR_INLINE int csr_ioc_to_instr(long cmd)
    {
        return _IOC_TYPE(cmd) == _CSR_IOC_INSTR ? _IOC_NR(cmd) : CSR_INSTR_INVALID;
    }

#elif defined(__APPLE__)

    // System socket name for this module.
    #define CSR_SOCKET_NAME CSR_MODULE_NAME

    // Socket options for system control cpusysregs.
    // There is one socket option name per register.
    #define _CSR_SOCKOPT_MASK         0x0000FFFF
    #define _CSR_SOCKOPT_REG          0x00AC0000
    #define _CSR_SOCKOPT_INSTR        0x00AD0000
    #define CSR_SOCKOPT_REG(regid)    (_CSR_SOCKOPT_REG | (regid))
    #define CSR_SOCKOPT_INSTR(instr)  (_CSR_SOCKOPT_INSTR | (instr))

    // Extract the register id from a socket option.
    // Return CSR_REGID_INVALID if not a set/get register command.
    CSR_INLINE int csr_sockopt_to_regid(int opt)
    {
        return (opt & ~_CSR_SOCKOPT_MASK) == _CSR_SOCKOPT_REG ? (opt & _CSR_SOCKOPT_MASK) : CSR_REGID_INVALID;
    }

    // Extract the instruction code from a socket option.
    // Return CSR_INSTR_INVALID if not an instruction command.
    CSR_INLINE int csr_sockopt_to_instr(int opt)
    {
        return (opt & ~_CSR_SOCKOPT_MASK) == _CSR_SOCKOPT_INSTR ? (opt & _CSR_SOCKOPT_MASK) : CSR_INSTR_INVALID;
    }

#endif


//----------------------------------------------------------------------------
// Definitions of Arm64 system registers and instructions to access them.
// Useful in the kernel only with accessing EL1 registers.
//----------------------------------------------------------------------------
//
// The system registers are described in section D17.2 of the Arm Architecture Reference Manual.
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
// See the description of each system register in section D17.2 to get its identifiers.
//
#define CSR_SREG(op0, op1, crn, crm, op2) (((op0) << 19) | ((op1) << 16) | ((crn) << 12) | ((crm) << 8) | ((op2) << 5))

//
// The following macros define the encoding of most Arm system registers.
// These definition were automatically generated from a PDF copy of the Arm
// Architecture Reference Manual using the script extract-sreg-definitions.sh.
//
#define CSR_SREG_ACCDATA_EL1        CSR_SREG(0b11, 0b000, 0b1101, 0b0000, 0b101)
#define CSR_SREG_ACTLR_EL1          CSR_SREG(0b11, 0b000, 0b0001, 0b0000, 0b001)
#define CSR_SREG_ACTLR_EL2          CSR_SREG(0b11, 0b100, 0b0001, 0b0000, 0b001)
#define CSR_SREG_ACTLR_EL3          CSR_SREG(0b11, 0b110, 0b0001, 0b0000, 0b001)
#define CSR_SREG_AFSR0_EL1          CSR_SREG(0b11, 0b000, 0b0101, 0b0001, 0b000)
#define CSR_SREG_AFSR0_EL12         CSR_SREG(0b11, 0b101, 0b0101, 0b0001, 0b000)
#define CSR_SREG_AFSR0_EL2          CSR_SREG(0b11, 0b100, 0b0101, 0b0001, 0b000)
#define CSR_SREG_AFSR0_EL3          CSR_SREG(0b11, 0b110, 0b0101, 0b0001, 0b000)
#define CSR_SREG_AFSR1_EL1          CSR_SREG(0b11, 0b000, 0b0101, 0b0001, 0b001)
#define CSR_SREG_AFSR1_EL12         CSR_SREG(0b11, 0b101, 0b0101, 0b0001, 0b001)
#define CSR_SREG_AFSR1_EL2          CSR_SREG(0b11, 0b100, 0b0101, 0b0001, 0b001)
#define CSR_SREG_AFSR1_EL3          CSR_SREG(0b11, 0b110, 0b0101, 0b0001, 0b001)
#define CSR_SREG_AIDR_EL1           CSR_SREG(0b11, 0b001, 0b0000, 0b0000, 0b111)
#define CSR_SREG_AMAIR_EL1          CSR_SREG(0b11, 0b000, 0b1010, 0b0011, 0b000)
#define CSR_SREG_AMAIR_EL12         CSR_SREG(0b11, 0b101, 0b1010, 0b0011, 0b000)
#define CSR_SREG_AMAIR_EL2          CSR_SREG(0b11, 0b100, 0b1010, 0b0011, 0b000)
#define CSR_SREG_AMAIR_EL3          CSR_SREG(0b11, 0b110, 0b1010, 0b0011, 0b000)
#define CSR_SREG_APDAKEYHI_EL1      CSR_SREG(0b11, 0b000, 0b0010, 0b0010, 0b001)
#define CSR_SREG_APDAKEYLO_EL1      CSR_SREG(0b11, 0b000, 0b0010, 0b0010, 0b000)
#define CSR_SREG_APDBKEYHI_EL1      CSR_SREG(0b11, 0b000, 0b0010, 0b0010, 0b011)
#define CSR_SREG_APDBKEYLO_EL1      CSR_SREG(0b11, 0b000, 0b0010, 0b0010, 0b010)
#define CSR_SREG_APGAKEYHI_EL1      CSR_SREG(0b11, 0b000, 0b0010, 0b0011, 0b001)
#define CSR_SREG_APGAKEYLO_EL1      CSR_SREG(0b11, 0b000, 0b0010, 0b0011, 0b000)
#define CSR_SREG_APIAKEYHI_EL1      CSR_SREG(0b11, 0b000, 0b0010, 0b0001, 0b001)
#define CSR_SREG_APIAKEYLO_EL1      CSR_SREG(0b11, 0b000, 0b0010, 0b0001, 0b000)
#define CSR_SREG_APIBKEYHI_EL1      CSR_SREG(0b11, 0b000, 0b0010, 0b0001, 0b011)
#define CSR_SREG_APIBKEYLO_EL1      CSR_SREG(0b11, 0b000, 0b0010, 0b0001, 0b010)
#define CSR_SREG_CCSIDR2_EL1        CSR_SREG(0b11, 0b001, 0b0000, 0b0000, 0b010)
#define CSR_SREG_CCSIDR_EL1         CSR_SREG(0b11, 0b001, 0b0000, 0b0000, 0b000)
#define CSR_SREG_CLIDR_EL1          CSR_SREG(0b11, 0b001, 0b0000, 0b0000, 0b001)
#define CSR_SREG_CONTEXTIDR_EL1     CSR_SREG(0b11, 0b000, 0b1101, 0b0000, 0b001)
#define CSR_SREG_CONTEXTIDR_EL12    CSR_SREG(0b11, 0b101, 0b1101, 0b0000, 0b001)
#define CSR_SREG_CONTEXTIDR_EL2     CSR_SREG(0b11, 0b100, 0b1101, 0b0000, 0b001)
#define CSR_SREG_CPACR_EL1          CSR_SREG(0b11, 0b000, 0b0001, 0b0000, 0b010)
#define CSR_SREG_CPACR_EL12         CSR_SREG(0b11, 0b101, 0b0001, 0b0000, 0b010)
#define CSR_SREG_CPTR_EL2           CSR_SREG(0b11, 0b100, 0b0001, 0b0001, 0b010)
#define CSR_SREG_CPACR_EL1          CSR_SREG(0b11, 0b000, 0b0001, 0b0000, 0b010)
#define CSR_SREG_CPTR_EL3           CSR_SREG(0b11, 0b110, 0b0001, 0b0001, 0b010)
#define CSR_SREG_CSSELR_EL1         CSR_SREG(0b11, 0b010, 0b0000, 0b0000, 0b000)
#define CSR_SREG_CTR_EL0            CSR_SREG(0b11, 0b011, 0b0000, 0b0000, 0b001)
#define CSR_SREG_DACR32_EL2         CSR_SREG(0b11, 0b100, 0b0011, 0b0000, 0b000)
#define CSR_SREG_DCZID_EL0          CSR_SREG(0b11, 0b011, 0b0000, 0b0000, 0b111)
#define CSR_SREG_ESR_EL1            CSR_SREG(0b11, 0b000, 0b0101, 0b0010, 0b000)
#define CSR_SREG_ESR_EL12           CSR_SREG(0b11, 0b101, 0b0101, 0b0010, 0b000)
#define CSR_SREG_ESR_EL2            CSR_SREG(0b11, 0b100, 0b0101, 0b0010, 0b000)
#define CSR_SREG_ESR_EL2            CSR_SREG(0b11, 0b100, 0b0101, 0b0010, 0b000)
#define CSR_SREG_ESR_EL3            CSR_SREG(0b11, 0b110, 0b0101, 0b0010, 0b000)
#define CSR_SREG_FAR_EL1            CSR_SREG(0b11, 0b000, 0b0110, 0b0000, 0b000)
#define CSR_SREG_FAR_EL12           CSR_SREG(0b11, 0b101, 0b0110, 0b0000, 0b000)
#define CSR_SREG_FAR_EL2            CSR_SREG(0b11, 0b100, 0b0110, 0b0000, 0b000)
#define CSR_SREG_FAR_EL2            CSR_SREG(0b11, 0b100, 0b0110, 0b0000, 0b000)
#define CSR_SREG_FAR_EL1            CSR_SREG(0b11, 0b000, 0b0110, 0b0000, 0b000)
#define CSR_SREG_FAR_EL3            CSR_SREG(0b11, 0b110, 0b0110, 0b0000, 0b000)
#define CSR_SREG_FPEXC32_EL2        CSR_SREG(0b11, 0b100, 0b0101, 0b0011, 0b000)
#define CSR_SREG_GCR_EL1            CSR_SREG(0b11, 0b000, 0b0001, 0b0000, 0b110)
#define CSR_SREG_GMID_EL1           CSR_SREG(0b11, 0b001, 0b0000, 0b0000, 0b100)
#define CSR_SREG_HACR_EL2           CSR_SREG(0b11, 0b100, 0b0001, 0b0001, 0b111)
#define CSR_SREG_HAFGRTR_EL2        CSR_SREG(0b11, 0b100, 0b0011, 0b0001, 0b110)
#define CSR_SREG_HCR_EL2            CSR_SREG(0b11, 0b100, 0b0001, 0b0001, 0b000)
#define CSR_SREG_HCRX_EL2           CSR_SREG(0b11, 0b100, 0b0001, 0b0010, 0b010)
#define CSR_SREG_HDFGRTR_EL2        CSR_SREG(0b11, 0b100, 0b0011, 0b0001, 0b100)
#define CSR_SREG_HDFGWTR_EL2        CSR_SREG(0b11, 0b100, 0b0011, 0b0001, 0b101)
#define CSR_SREG_HFGITR_EL2         CSR_SREG(0b11, 0b100, 0b0001, 0b0001, 0b110)
#define CSR_SREG_HFGRTR_EL2         CSR_SREG(0b11, 0b100, 0b0001, 0b0001, 0b100)
#define CSR_SREG_HFGWTR_EL2         CSR_SREG(0b11, 0b100, 0b0001, 0b0001, 0b101)
#define CSR_SREG_HPFAR_EL2          CSR_SREG(0b11, 0b100, 0b0110, 0b0000, 0b100)
#define CSR_SREG_HSTR_EL2           CSR_SREG(0b11, 0b100, 0b0001, 0b0001, 0b011)
#define CSR_SREG_ID_AA64AFR0_EL1    CSR_SREG(0b11, 0b000, 0b0000, 0b0101, 0b100)
#define CSR_SREG_ID_AA64AFR1_EL1    CSR_SREG(0b11, 0b000, 0b0000, 0b0101, 0b101)
#define CSR_SREG_ID_AA64DFR0_EL1    CSR_SREG(0b11, 0b000, 0b0000, 0b0101, 0b000)
#define CSR_SREG_ID_AA64DFR1_EL1    CSR_SREG(0b11, 0b000, 0b0000, 0b0101, 0b001)
#define CSR_SREG_ID_AA64ISAR0_EL1   CSR_SREG(0b11, 0b000, 0b0000, 0b0110, 0b000)
#define CSR_SREG_ID_AA64ISAR1_EL1   CSR_SREG(0b11, 0b000, 0b0000, 0b0110, 0b001)
#define CSR_SREG_ID_AA64ISAR2_EL1   CSR_SREG(0b11, 0b000, 0b0000, 0b0110, 0b010)
#define CSR_SREG_ID_AA64MMFR0_EL1   CSR_SREG(0b11, 0b000, 0b0000, 0b0111, 0b000)
#define CSR_SREG_ID_AA64MMFR1_EL1   CSR_SREG(0b11, 0b000, 0b0000, 0b0111, 0b001)
#define CSR_SREG_ID_AA64MMFR2_EL1   CSR_SREG(0b11, 0b000, 0b0000, 0b0111, 0b010)
#define CSR_SREG_ID_AA64MMFR3_EL1   CSR_SREG(0b11, 0b000, 0b0000, 0b0111, 0b011)
#define CSR_SREG_ID_AA64MMFR4_EL1   CSR_SREG(0b11, 0b000, 0b0000, 0b0111, 0b100)
#define CSR_SREG_ID_AA64PFR0_EL1    CSR_SREG(0b11, 0b000, 0b0000, 0b0100, 0b000)
#define CSR_SREG_ID_AA64PFR1_EL1    CSR_SREG(0b11, 0b000, 0b0000, 0b0100, 0b001)
#define CSR_SREG_ID_AA64PFR2_EL1    CSR_SREG(0b11, 0b000, 0b0000, 0b0100, 0b010)
#define CSR_SREG_ID_AA64SMFR0_EL1   CSR_SREG(0b11, 0b000, 0b0000, 0b0100, 0b101)
#define CSR_SREG_ID_AA64ZFR0_EL1    CSR_SREG(0b11, 0b000, 0b0000, 0b0100, 0b100)
#define CSR_SREG_ID_AFR0_EL1        CSR_SREG(0b11, 0b000, 0b0000, 0b0001, 0b011)
#define CSR_SREG_ID_DFR0_EL1        CSR_SREG(0b11, 0b000, 0b0000, 0b0001, 0b010)
#define CSR_SREG_ID_DFR1_EL1        CSR_SREG(0b11, 0b000, 0b0000, 0b0011, 0b101)
#define CSR_SREG_ID_ISAR0_EL1       CSR_SREG(0b11, 0b000, 0b0000, 0b0010, 0b000)
#define CSR_SREG_ID_ISAR1_EL1       CSR_SREG(0b11, 0b000, 0b0000, 0b0010, 0b001)
#define CSR_SREG_ID_ISAR2_EL1       CSR_SREG(0b11, 0b000, 0b0000, 0b0010, 0b010)
#define CSR_SREG_ID_ISAR3_EL1       CSR_SREG(0b11, 0b000, 0b0000, 0b0010, 0b011)
#define CSR_SREG_ID_ISAR4_EL1       CSR_SREG(0b11, 0b000, 0b0000, 0b0010, 0b100)
#define CSR_SREG_ID_ISAR5_EL1       CSR_SREG(0b11, 0b000, 0b0000, 0b0010, 0b101)
#define CSR_SREG_ID_ISAR6_EL1       CSR_SREG(0b11, 0b000, 0b0000, 0b0010, 0b111)
#define CSR_SREG_ID_MMFR0_EL1       CSR_SREG(0b11, 0b000, 0b0000, 0b0001, 0b100)
#define CSR_SREG_ID_MMFR1_EL1       CSR_SREG(0b11, 0b000, 0b0000, 0b0001, 0b101)
#define CSR_SREG_ID_MMFR2_EL1       CSR_SREG(0b11, 0b000, 0b0000, 0b0001, 0b110)
#define CSR_SREG_ID_MMFR3_EL1       CSR_SREG(0b11, 0b000, 0b0000, 0b0001, 0b111)
#define CSR_SREG_ID_MMFR4_EL1       CSR_SREG(0b11, 0b000, 0b0000, 0b0010, 0b110)
#define CSR_SREG_ID_MMFR5_EL1       CSR_SREG(0b11, 0b000, 0b0000, 0b0011, 0b110)
#define CSR_SREG_ID_PFR0_EL1        CSR_SREG(0b11, 0b000, 0b0000, 0b0001, 0b000)
#define CSR_SREG_ID_PFR1_EL1        CSR_SREG(0b11, 0b000, 0b0000, 0b0001, 0b001)
#define CSR_SREG_ID_PFR2_EL1        CSR_SREG(0b11, 0b000, 0b0000, 0b0011, 0b100)
#define CSR_SREG_IFSR32_EL2         CSR_SREG(0b11, 0b100, 0b0101, 0b0000, 0b001)
#define CSR_SREG_ISR_EL1            CSR_SREG(0b11, 0b000, 0b1100, 0b0001, 0b000)
#define CSR_SREG_LORC_EL1           CSR_SREG(0b11, 0b000, 0b1010, 0b0100, 0b011)
#define CSR_SREG_LOREA_EL1          CSR_SREG(0b11, 0b000, 0b1010, 0b0100, 0b001)
#define CSR_SREG_LORID_EL1          CSR_SREG(0b11, 0b000, 0b1010, 0b0100, 0b111)
#define CSR_SREG_LORN_EL1           CSR_SREG(0b11, 0b000, 0b1010, 0b0100, 0b010)
#define CSR_SREG_LORSA_EL1          CSR_SREG(0b11, 0b000, 0b1010, 0b0100, 0b000)
#define CSR_SREG_MAIR_EL1           CSR_SREG(0b11, 0b000, 0b1010, 0b0010, 0b000)
#define CSR_SREG_MAIR_EL12          CSR_SREG(0b11, 0b101, 0b1010, 0b0010, 0b000)
#define CSR_SREG_MAIR_EL2           CSR_SREG(0b11, 0b100, 0b1010, 0b0010, 0b000)
#define CSR_SREG_MAIR_EL1           CSR_SREG(0b11, 0b000, 0b1010, 0b0010, 0b000)
#define CSR_SREG_MAIR_EL3           CSR_SREG(0b11, 0b110, 0b1010, 0b0010, 0b000)
#define CSR_SREG_MIDR_EL1           CSR_SREG(0b11, 0b000, 0b0000, 0b0000, 0b000)
#define CSR_SREG_MPIDR_EL1          CSR_SREG(0b11, 0b000, 0b0000, 0b0000, 0b101)
#define CSR_SREG_MVFR0_EL1          CSR_SREG(0b11, 0b000, 0b0000, 0b0011, 0b000)
#define CSR_SREG_MVFR1_EL1          CSR_SREG(0b11, 0b000, 0b0000, 0b0011, 0b001)
#define CSR_SREG_MVFR2_EL1          CSR_SREG(0b11, 0b000, 0b0000, 0b0011, 0b010)
#define CSR_SREG_PAR_EL1            CSR_SREG(0b11, 0b000, 0b0111, 0b0100, 0b000)
#define CSR_SREG_REVIDR_EL1         CSR_SREG(0b11, 0b000, 0b0000, 0b0000, 0b110)
#define CSR_SREG_RGSR_EL1           CSR_SREG(0b11, 0b000, 0b0001, 0b0000, 0b101)
#define CSR_SREG_RMR_EL1            CSR_SREG(0b11, 0b000, 0b1100, 0b0000, 0b010)
#define CSR_SREG_RMR_EL2            CSR_SREG(0b11, 0b100, 0b1100, 0b0000, 0b010)
#define CSR_SREG_RMR_EL3            CSR_SREG(0b11, 0b110, 0b1100, 0b0000, 0b010)
#define CSR_SREG_RNDR               CSR_SREG(0b11, 0b011, 0b0010, 0b0100, 0b000)
#define CSR_SREG_RNDRRS             CSR_SREG(0b11, 0b011, 0b0010, 0b0100, 0b001)
#define CSR_SREG_RVBAR_EL1          CSR_SREG(0b11, 0b000, 0b1100, 0b0000, 0b001)
#define CSR_SREG_RVBAR_EL2          CSR_SREG(0b11, 0b100, 0b1100, 0b0000, 0b001)
#define CSR_SREG_RVBAR_EL3          CSR_SREG(0b11, 0b110, 0b1100, 0b0000, 0b001)
#define CSR_SREG_SCR_EL3            CSR_SREG(0b11, 0b110, 0b0001, 0b0001, 0b000)
#define CSR_SREG_SCTLR_EL1          CSR_SREG(0b11, 0b000, 0b0001, 0b0000, 0b000)
#define CSR_SREG_SCTLR_EL12         CSR_SREG(0b11, 0b101, 0b0001, 0b0000, 0b000)
#define CSR_SREG_SCTLR_EL2          CSR_SREG(0b11, 0b100, 0b0001, 0b0000, 0b000)
#define CSR_SREG_SCTLR_EL3          CSR_SREG(0b11, 0b110, 0b0001, 0b0000, 0b000)
#define CSR_SREG_SCXTNUM_EL0        CSR_SREG(0b11, 0b011, 0b1101, 0b0000, 0b111)
#define CSR_SREG_SCXTNUM_EL1        CSR_SREG(0b11, 0b000, 0b1101, 0b0000, 0b111)
#define CSR_SREG_SCXTNUM_EL12       CSR_SREG(0b11, 0b101, 0b1101, 0b0000, 0b111)
#define CSR_SREG_SCXTNUM_EL2        CSR_SREG(0b11, 0b100, 0b1101, 0b0000, 0b111)
#define CSR_SREG_SCXTNUM_EL1        CSR_SREG(0b11, 0b000, 0b1101, 0b0000, 0b111)
#define CSR_SREG_SCXTNUM_EL3        CSR_SREG(0b11, 0b110, 0b1101, 0b0000, 0b111)
#define CSR_SREG_SMCR_EL1           CSR_SREG(0b11, 0b000, 0b0001, 0b0010, 0b110)
#define CSR_SREG_SMCR_EL12          CSR_SREG(0b11, 0b101, 0b0001, 0b0010, 0b110)
#define CSR_SREG_SMCR_EL2           CSR_SREG(0b11, 0b100, 0b0001, 0b0010, 0b110)
#define CSR_SREG_SMCR_EL1           CSR_SREG(0b11, 0b000, 0b0001, 0b0010, 0b110)
#define CSR_SREG_SMCR_EL3           CSR_SREG(0b11, 0b110, 0b0001, 0b0010, 0b110)
#define CSR_SREG_SMIDR_EL1          CSR_SREG(0b11, 0b001, 0b0000, 0b0000, 0b110)
#define CSR_SREG_SMPRIMAP_EL2       CSR_SREG(0b11, 0b100, 0b0001, 0b0010, 0b101)
#define CSR_SREG_SMPRI_EL1          CSR_SREG(0b11, 0b000, 0b0001, 0b0010, 0b100)
#define CSR_SREG_TCO                CSR_SREG(0b11, 0b011, 0b0100, 0b0010, 0b111)
#define CSR_SREG_TCR_EL1            CSR_SREG(0b11, 0b000, 0b0010, 0b0000, 0b010)
#define CSR_SREG_TCR_EL12           CSR_SREG(0b11, 0b101, 0b0010, 0b0000, 0b010)
#define CSR_SREG_TCR_EL2            CSR_SREG(0b11, 0b100, 0b0010, 0b0000, 0b010)
#define CSR_SREG_TCR_EL1            CSR_SREG(0b11, 0b000, 0b0010, 0b0000, 0b010)
#define CSR_SREG_TCR_EL3            CSR_SREG(0b11, 0b110, 0b0010, 0b0000, 0b010)
#define CSR_SREG_TCR2_EL1           CSR_SREG(0b11, 0b000, 0b0010, 0b0000, 0b011)
#define CSR_SREG_TCR2_EL12          CSR_SREG(0b11, 0b101, 0b0010, 0b0000, 0b011)
#define CSR_SREG_TCR2_EL2           CSR_SREG(0b11, 0b100, 0b0010, 0b0000, 0b011)
#define CSR_SREG_TFSRE0_EL1         CSR_SREG(0b11, 0b000, 0b0101, 0b0110, 0b001)
#define CSR_SREG_TFSR_EL1           CSR_SREG(0b11, 0b000, 0b0101, 0b0110, 0b000)
#define CSR_SREG_TFSR_EL12          CSR_SREG(0b11, 0b101, 0b0101, 0b0110, 0b000)
#define CSR_SREG_TFSR_EL2           CSR_SREG(0b11, 0b100, 0b0101, 0b0110, 0b000)
#define CSR_SREG_TFSR_EL2           CSR_SREG(0b11, 0b100, 0b0101, 0b0110, 0b000)
#define CSR_SREG_TFSR_EL1           CSR_SREG(0b11, 0b000, 0b0101, 0b0110, 0b000)
#define CSR_SREG_TFSR_EL3           CSR_SREG(0b11, 0b110, 0b0101, 0b0110, 0b000)
#define CSR_SREG_TPIDR2_EL0         CSR_SREG(0b11, 0b011, 0b1101, 0b0000, 0b101)
#define CSR_SREG_TPIDR_EL0          CSR_SREG(0b11, 0b011, 0b1101, 0b0000, 0b010)
#define CSR_SREG_TPIDR_EL1          CSR_SREG(0b11, 0b000, 0b1101, 0b0000, 0b100)
#define CSR_SREG_TPIDR_EL2          CSR_SREG(0b11, 0b100, 0b1101, 0b0000, 0b010)
#define CSR_SREG_TPIDR_EL3          CSR_SREG(0b11, 0b110, 0b1101, 0b0000, 0b010)
#define CSR_SREG_TPIDRRO_EL0        CSR_SREG(0b11, 0b011, 0b1101, 0b0000, 0b011)
#define CSR_SREG_TTBR0_EL1          CSR_SREG(0b11, 0b000, 0b0010, 0b0000, 0b000)
#define CSR_SREG_TTBR0_EL12         CSR_SREG(0b11, 0b101, 0b0010, 0b0000, 0b000)
#define CSR_SREG_TTBR0_EL2          CSR_SREG(0b11, 0b100, 0b0010, 0b0000, 0b000)
#define CSR_SREG_TTBR0_EL1          CSR_SREG(0b11, 0b000, 0b0010, 0b0000, 0b000)
#define CSR_SREG_TTBR0_EL3          CSR_SREG(0b11, 0b110, 0b0010, 0b0000, 0b000)
#define CSR_SREG_TTBR1_EL1          CSR_SREG(0b11, 0b000, 0b0010, 0b0000, 0b001)
#define CSR_SREG_TTBR1_EL12         CSR_SREG(0b11, 0b101, 0b0010, 0b0000, 0b001)
#define CSR_SREG_TTBR1_EL2          CSR_SREG(0b11, 0b100, 0b0010, 0b0000, 0b001)
#define CSR_SREG_TTBR1_EL1          CSR_SREG(0b11, 0b000, 0b0010, 0b0000, 0b001)
#define CSR_SREG_VBAR_EL1           CSR_SREG(0b11, 0b000, 0b1100, 0b0000, 0b000)
#define CSR_SREG_VBAR_EL12          CSR_SREG(0b11, 0b101, 0b1100, 0b0000, 0b000)
#define CSR_SREG_VBAR_EL2           CSR_SREG(0b11, 0b100, 0b1100, 0b0000, 0b000)
#define CSR_SREG_VBAR_EL1           CSR_SREG(0b11, 0b000, 0b1100, 0b0000, 0b000)
#define CSR_SREG_VBAR_EL3           CSR_SREG(0b11, 0b110, 0b1100, 0b0000, 0b000)
#define CSR_SREG_VMPIDR_EL2         CSR_SREG(0b11, 0b100, 0b0000, 0b0000, 0b101)
#define CSR_SREG_VNCR_EL2           CSR_SREG(0b11, 0b100, 0b0010, 0b0010, 0b000)
#define CSR_SREG_VPIDR_EL2          CSR_SREG(0b11, 0b100, 0b0000, 0b0000, 0b000)
#define CSR_SREG_VSTCR_EL2          CSR_SREG(0b11, 0b100, 0b0010, 0b0110, 0b010)
#define CSR_SREG_VSTTBR_EL2         CSR_SREG(0b11, 0b100, 0b0010, 0b0110, 0b000)
#define CSR_SREG_VTCR_EL2           CSR_SREG(0b11, 0b100, 0b0010, 0b0001, 0b010)
#define CSR_SREG_VTTBR_EL2          CSR_SREG(0b11, 0b100, 0b0010, 0b0001, 0b000)
#define CSR_SREG_ZCR_EL1            CSR_SREG(0b11, 0b000, 0b0001, 0b0010, 0b000)
#define CSR_SREG_ZCR_EL12           CSR_SREG(0b11, 0b101, 0b0001, 0b0010, 0b000)
#define CSR_SREG_ZCR_EL2            CSR_SREG(0b11, 0b100, 0b0001, 0b0010, 0b000)
#define CSR_SREG_ZCR_EL1            CSR_SREG(0b11, 0b000, 0b0001, 0b0010, 0b000)
#define CSR_SREG_ZCR_EL3            CSR_SREG(0b11, 0b110, 0b0001, 0b0010, 0b000)
#define CSR_SREG_DBGAUTHSTATUS_EL1  CSR_SREG(0b10, 0b000, 0b0111, 0b1110, 0b110)
#define CSR_SREG_DBGCLAIMCLR_EL1    CSR_SREG(0b10, 0b000, 0b0111, 0b1001, 0b110)
#define CSR_SREG_DBGCLAIMSET_EL1    CSR_SREG(0b10, 0b000, 0b0111, 0b1000, 0b110)
#define CSR_SREG_DBGDTR_EL0         CSR_SREG(0b10, 0b011, 0b0000, 0b0100, 0b000)
#define CSR_SREG_DBGDTRRX_EL0       CSR_SREG(0b10, 0b011, 0b0000, 0b0101, 0b000)
#define CSR_SREG_DBGPRCR_EL1        CSR_SREG(0b10, 0b000, 0b0001, 0b0100, 0b100)
#define CSR_SREG_DBGVCR32_EL2       CSR_SREG(0b10, 0b100, 0b0000, 0b0111, 0b000)
#define CSR_SREG_DLR_EL0            CSR_SREG(0b11, 0b011, 0b0100, 0b0101, 0b001)
#define CSR_SREG_DSPSR_EL0          CSR_SREG(0b11, 0b011, 0b0100, 0b0101, 0b000)
#define CSR_SREG_MDCCINT_EL1        CSR_SREG(0b10, 0b000, 0b0000, 0b0010, 0b000)
#define CSR_SREG_MDCCSR_EL0         CSR_SREG(0b10, 0b011, 0b0000, 0b0001, 0b000)
#define CSR_SREG_MDCR_EL2           CSR_SREG(0b11, 0b100, 0b0001, 0b0001, 0b001)
#define CSR_SREG_MDCR_EL3           CSR_SREG(0b11, 0b110, 0b0001, 0b0011, 0b001)
#define CSR_SREG_MDRAR_EL1          CSR_SREG(0b10, 0b000, 0b0001, 0b0000, 0b000)
#define CSR_SREG_MDSCR_EL1          CSR_SREG(0b10, 0b000, 0b0000, 0b0010, 0b010)
#define CSR_SREG_OSDLR_EL1          CSR_SREG(0b10, 0b000, 0b0001, 0b0011, 0b100)
#define CSR_SREG_OSDTRRX_EL1        CSR_SREG(0b10, 0b000, 0b0000, 0b0000, 0b010)
#define CSR_SREG_OSDTRTX_EL1        CSR_SREG(0b10, 0b000, 0b0000, 0b0011, 0b010)
#define CSR_SREG_OSECCR_EL1         CSR_SREG(0b10, 0b000, 0b0000, 0b0110, 0b010)
#define CSR_SREG_OSLSR_EL1          CSR_SREG(0b10, 0b000, 0b0001, 0b0001, 0b100)
#define CSR_SREG_SDER32_EL2         CSR_SREG(0b11, 0b100, 0b0001, 0b0011, 0b001)
#define CSR_SREG_SDER32_EL3         CSR_SREG(0b11, 0b110, 0b0001, 0b0001, 0b001)
#define CSR_SREG_TRFCR_EL1          CSR_SREG(0b11, 0b000, 0b0001, 0b0010, 0b001)
#define CSR_SREG_TRFCR_EL12         CSR_SREG(0b11, 0b101, 0b0001, 0b0010, 0b001)
#define CSR_SREG_TRFCR_EL2          CSR_SREG(0b11, 0b100, 0b0001, 0b0010, 0b001)
#define CSR_SREG_TRFCR_EL1          CSR_SREG(0b11, 0b000, 0b0001, 0b0010, 0b001)
#define CSR_SREG_TRBBASER_EL1       CSR_SREG(0b11, 0b000, 0b1001, 0b1011, 0b010)
#define CSR_SREG_TRBIDR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1011, 0b111)
#define CSR_SREG_TRBLIMITR_EL1      CSR_SREG(0b11, 0b000, 0b1001, 0b1011, 0b000)
#define CSR_SREG_TRBMAR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1011, 0b100)
#define CSR_SREG_TRBPTR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1011, 0b001)
#define CSR_SREG_TRBSR_EL1          CSR_SREG(0b11, 0b000, 0b1001, 0b1011, 0b011)
#define CSR_SREG_TRBTRG_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1011, 0b110)
#define CSR_SREG_TRCAUTHSTATUS      CSR_SREG(0b10, 0b001, 0b0111, 0b1110, 0b110)
#define CSR_SREG_TRCAUXCTLR         CSR_SREG(0b10, 0b001, 0b0000, 0b0110, 0b000)
#define CSR_SREG_TRCBBCTLR          CSR_SREG(0b10, 0b001, 0b0000, 0b1111, 0b000)
#define CSR_SREG_TRCCCCTLR          CSR_SREG(0b10, 0b001, 0b0000, 0b1110, 0b000)
#define CSR_SREG_TRCCIDCCTLR0       CSR_SREG(0b10, 0b001, 0b0011, 0b0000, 0b010)
#define CSR_SREG_TRCCIDCCTLR1       CSR_SREG(0b10, 0b001, 0b0011, 0b0001, 0b010)
#define CSR_SREG_TRCCLAIMCLR        CSR_SREG(0b10, 0b001, 0b0111, 0b1001, 0b110)
#define CSR_SREG_TRCCLAIMSET        CSR_SREG(0b10, 0b001, 0b0111, 0b1000, 0b110)
#define CSR_SREG_TRCCONFIGR         CSR_SREG(0b10, 0b001, 0b0000, 0b0100, 0b000)
#define CSR_SREG_TRCDEVARCH         CSR_SREG(0b10, 0b001, 0b0111, 0b1111, 0b110)
#define CSR_SREG_TRCDEVID           CSR_SREG(0b10, 0b001, 0b0111, 0b0010, 0b111)
#define CSR_SREG_TRCEVENTCTL0R      CSR_SREG(0b10, 0b001, 0b0000, 0b1000, 0b000)
#define CSR_SREG_TRCEVENTCTL1R      CSR_SREG(0b10, 0b001, 0b0000, 0b1001, 0b000)
#define CSR_SREG_TRCIDR0            CSR_SREG(0b10, 0b001, 0b0000, 0b1000, 0b111)
#define CSR_SREG_TRCIDR1            CSR_SREG(0b10, 0b001, 0b0000, 0b1001, 0b111)
#define CSR_SREG_TRCIDR10           CSR_SREG(0b10, 0b001, 0b0000, 0b0010, 0b110)
#define CSR_SREG_TRCIDR11           CSR_SREG(0b10, 0b001, 0b0000, 0b0011, 0b110)
#define CSR_SREG_TRCIDR12           CSR_SREG(0b10, 0b001, 0b0000, 0b0100, 0b110)
#define CSR_SREG_TRCIDR13           CSR_SREG(0b10, 0b001, 0b0000, 0b0101, 0b110)
#define CSR_SREG_TRCIDR2            CSR_SREG(0b10, 0b001, 0b0000, 0b1010, 0b111)
#define CSR_SREG_TRCIDR3            CSR_SREG(0b10, 0b001, 0b0000, 0b1011, 0b111)
#define CSR_SREG_TRCIDR4            CSR_SREG(0b10, 0b001, 0b0000, 0b1100, 0b111)
#define CSR_SREG_TRCIDR5            CSR_SREG(0b10, 0b001, 0b0000, 0b1101, 0b111)
#define CSR_SREG_TRCIDR6            CSR_SREG(0b10, 0b001, 0b0000, 0b1110, 0b111)
#define CSR_SREG_TRCIDR7            CSR_SREG(0b10, 0b001, 0b0000, 0b1111, 0b111)
#define CSR_SREG_TRCIDR8            CSR_SREG(0b10, 0b001, 0b0000, 0b0000, 0b110)
#define CSR_SREG_TRCIDR9            CSR_SREG(0b10, 0b001, 0b0000, 0b0001, 0b110)
#define CSR_SREG_TRCIMSPEC0         CSR_SREG(0b10, 0b001, 0b0000, 0b0000, 0b111)
#define CSR_SREG_TRCOSLSR           CSR_SREG(0b10, 0b001, 0b0001, 0b0001, 0b100)
#define CSR_SREG_TRCPRGCTLR         CSR_SREG(0b10, 0b001, 0b0000, 0b0001, 0b000)
#define CSR_SREG_TRCQCTLR           CSR_SREG(0b10, 0b001, 0b0000, 0b0001, 0b001)
#define CSR_SREG_TRCRSR             CSR_SREG(0b10, 0b001, 0b0000, 0b1010, 0b000)
#define CSR_SREG_TRCSEQRSTEVR       CSR_SREG(0b10, 0b001, 0b0000, 0b0110, 0b100)
#define CSR_SREG_TRCSEQSTR          CSR_SREG(0b10, 0b001, 0b0000, 0b0111, 0b100)
#define CSR_SREG_TRCSTALLCTLR       CSR_SREG(0b10, 0b001, 0b0000, 0b1011, 0b000)
#define CSR_SREG_TRCSTATR           CSR_SREG(0b10, 0b001, 0b0000, 0b0011, 0b000)
#define CSR_SREG_TRCSYNCPR          CSR_SREG(0b10, 0b001, 0b0000, 0b1101, 0b000)
#define CSR_SREG_TRCTRACEIDR        CSR_SREG(0b10, 0b001, 0b0000, 0b0000, 0b001)
#define CSR_SREG_TRCTSCTLR          CSR_SREG(0b10, 0b001, 0b0000, 0b1100, 0b000)
#define CSR_SREG_TRCVICTLR          CSR_SREG(0b10, 0b001, 0b0000, 0b0000, 0b010)
#define CSR_SREG_TRCVIIECTLR        CSR_SREG(0b10, 0b001, 0b0000, 0b0001, 0b010)
#define CSR_SREG_TRCVIPCSSCTLR      CSR_SREG(0b10, 0b001, 0b0000, 0b0011, 0b010)
#define CSR_SREG_TRCVISSCTLR        CSR_SREG(0b10, 0b001, 0b0000, 0b0010, 0b010)
#define CSR_SREG_TRCVMIDCCTLR0      CSR_SREG(0b10, 0b001, 0b0011, 0b0010, 0b010)
#define CSR_SREG_TRCVMIDCCTLR1      CSR_SREG(0b10, 0b001, 0b0011, 0b0011, 0b010)
#define CSR_SREG_PMCCFILTR_EL0      CSR_SREG(0b11, 0b011, 0b1110, 0b1111, 0b111)
#define CSR_SREG_PMCCNTR_EL0        CSR_SREG(0b11, 0b011, 0b1001, 0b1101, 0b000)
#define CSR_SREG_PMCEID0_EL0        CSR_SREG(0b11, 0b011, 0b1001, 0b1100, 0b110)
#define CSR_SREG_PMCEID1_EL0        CSR_SREG(0b11, 0b011, 0b1001, 0b1100, 0b111)
#define CSR_SREG_PMCNTENCLR_EL0     CSR_SREG(0b11, 0b011, 0b1001, 0b1100, 0b010)
#define CSR_SREG_PMCNTENSET_EL0     CSR_SREG(0b11, 0b011, 0b1001, 0b1100, 0b001)
#define CSR_SREG_PMCR_EL0           CSR_SREG(0b11, 0b011, 0b1001, 0b1100, 0b000)
#define CSR_SREG_PMINTENCLR_EL1     CSR_SREG(0b11, 0b000, 0b1001, 0b1110, 0b010)
#define CSR_SREG_PMINTENSET_EL1     CSR_SREG(0b11, 0b000, 0b1001, 0b1110, 0b001)
#define CSR_SREG_PMMIR_EL1          CSR_SREG(0b11, 0b000, 0b1001, 0b1110, 0b110)
#define CSR_SREG_PMOVSCLR_EL0       CSR_SREG(0b11, 0b011, 0b1001, 0b1100, 0b011)
#define CSR_SREG_PMOVSSET_EL0       CSR_SREG(0b11, 0b011, 0b1001, 0b1110, 0b011)
#define CSR_SREG_PMSELR_EL0         CSR_SREG(0b11, 0b011, 0b1001, 0b1100, 0b101)
#define CSR_SREG_PMUSERENR_EL0      CSR_SREG(0b11, 0b011, 0b1001, 0b1110, 0b000)
#define CSR_SREG_PMXEVCNTR_EL0      CSR_SREG(0b11, 0b011, 0b1001, 0b1101, 0b010)
#define CSR_SREG_PMXEVTYPER_EL0     CSR_SREG(0b11, 0b011, 0b1001, 0b1101, 0b001)
#define CSR_SREG_AMCFGR_EL0         CSR_SREG(0b11, 0b011, 0b1101, 0b0010, 0b001)
#define CSR_SREG_AMCG1IDR_EL0       CSR_SREG(0b11, 0b011, 0b1101, 0b0010, 0b110)
#define CSR_SREG_AMCGCR_EL0         CSR_SREG(0b11, 0b011, 0b1101, 0b0010, 0b010)
#define CSR_SREG_AMCNTENCLR0_EL0    CSR_SREG(0b11, 0b011, 0b1101, 0b0010, 0b100)
#define CSR_SREG_AMCNTENCLR1_EL0    CSR_SREG(0b11, 0b011, 0b1101, 0b0011, 0b000)
#define CSR_SREG_AMCNTENSET0_EL0    CSR_SREG(0b11, 0b011, 0b1101, 0b0010, 0b101)
#define CSR_SREG_AMCNTENSET1_EL0    CSR_SREG(0b11, 0b011, 0b1101, 0b0011, 0b001)
#define CSR_SREG_AMCR_EL0           CSR_SREG(0b11, 0b011, 0b1101, 0b0010, 0b000)
#define CSR_SREG_AMUSERENR_EL0      CSR_SREG(0b11, 0b011, 0b1101, 0b0010, 0b011)
#define CSR_SREG_PMBIDR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1010, 0b111)
#define CSR_SREG_PMBLIMITR_EL1      CSR_SREG(0b11, 0b000, 0b1001, 0b1010, 0b000)
#define CSR_SREG_PMBPTR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1010, 0b001)
#define CSR_SREG_PMBSR_EL1          CSR_SREG(0b11, 0b000, 0b1001, 0b1010, 0b011)
#define CSR_SREG_PMSCR_EL1          CSR_SREG(0b11, 0b000, 0b1001, 0b1001, 0b000)
#define CSR_SREG_PMSCR_EL12         CSR_SREG(0b11, 0b101, 0b1001, 0b1001, 0b000)
#define CSR_SREG_PMSCR_EL2          CSR_SREG(0b11, 0b100, 0b1001, 0b1001, 0b000)
#define CSR_SREG_PMSCR_EL1          CSR_SREG(0b11, 0b000, 0b1001, 0b1001, 0b000)
#define CSR_SREG_PMSEVFR_EL1        CSR_SREG(0b11, 0b000, 0b1001, 0b1001, 0b101)
#define CSR_SREG_PMSFCR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1001, 0b100)
#define CSR_SREG_PMSICR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1001, 0b010)
#define CSR_SREG_PMSIDR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1001, 0b111)
#define CSR_SREG_PMSIRR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1001, 0b011)
#define CSR_SREG_PMSLATFR_EL1       CSR_SREG(0b11, 0b000, 0b1001, 0b1001, 0b110)
#define CSR_SREG_PMSNEVFR_EL1       CSR_SREG(0b11, 0b000, 0b1001, 0b1001, 0b001)
#define CSR_SREG_BRBCR_EL1          CSR_SREG(0b10, 0b001, 0b1001, 0b0000, 0b000)
#define CSR_SREG_BRBCR_EL12         CSR_SREG(0b10, 0b101, 0b1001, 0b0000, 0b000)
#define CSR_SREG_BRBCR_EL1          CSR_SREG(0b10, 0b001, 0b1001, 0b0000, 0b000)
#define CSR_SREG_BRBCR_EL2          CSR_SREG(0b10, 0b100, 0b1001, 0b0000, 0b000)
#define CSR_SREG_BRBFCR_EL1         CSR_SREG(0b10, 0b001, 0b1001, 0b0000, 0b001)
#define CSR_SREG_BRBIDR0_EL1        CSR_SREG(0b10, 0b001, 0b1001, 0b0010, 0b000)
#define CSR_SREG_BRBINFINJ_EL1      CSR_SREG(0b10, 0b001, 0b1001, 0b0001, 0b000)
#define CSR_SREG_BRBSRCINJ_EL1      CSR_SREG(0b10, 0b001, 0b1001, 0b0001, 0b001)
#define CSR_SREG_BRBTGTINJ_EL1      CSR_SREG(0b10, 0b001, 0b1001, 0b0001, 0b010)
#define CSR_SREG_BRBTS_EL1          CSR_SREG(0b10, 0b001, 0b1001, 0b0000, 0b010)
#define CSR_SREG_DISR_EL1           CSR_SREG(0b11, 0b000, 0b1100, 0b0001, 0b001)
#define CSR_SREG_ERRIDR_EL1         CSR_SREG(0b11, 0b000, 0b0101, 0b0011, 0b000)
#define CSR_SREG_ERRSELR_EL1        CSR_SREG(0b11, 0b000, 0b0101, 0b0011, 0b001)
#define CSR_SREG_ERXADDR_EL1        CSR_SREG(0b11, 0b000, 0b0101, 0b0100, 0b011)
#define CSR_SREG_ERXCTLR_EL1        CSR_SREG(0b11, 0b000, 0b0101, 0b0100, 0b001)
#define CSR_SREG_ERXFR_EL1          CSR_SREG(0b11, 0b000, 0b0101, 0b0100, 0b000)
#define CSR_SREG_ERXMISC0_EL1       CSR_SREG(0b11, 0b000, 0b0101, 0b0101, 0b000)
#define CSR_SREG_ERXMISC1_EL1       CSR_SREG(0b11, 0b000, 0b0101, 0b0101, 0b001)
#define CSR_SREG_ERXMISC2_EL1       CSR_SREG(0b11, 0b000, 0b0101, 0b0101, 0b010)
#define CSR_SREG_ERXMISC3_EL1       CSR_SREG(0b11, 0b000, 0b0101, 0b0101, 0b011)
#define CSR_SREG_ERXPFGCDN_EL1      CSR_SREG(0b11, 0b000, 0b0101, 0b0100, 0b110)
#define CSR_SREG_ERXPFGCTL_EL1      CSR_SREG(0b11, 0b000, 0b0101, 0b0100, 0b101)
#define CSR_SREG_ERXPFGF_EL1        CSR_SREG(0b11, 0b000, 0b0101, 0b0100, 0b100)
#define CSR_SREG_ERXSTATUS_EL1      CSR_SREG(0b11, 0b000, 0b0101, 0b0100, 0b010)
#define CSR_SREG_VDISR_EL2          CSR_SREG(0b11, 0b100, 0b1100, 0b0001, 0b001)
#define CSR_SREG_DISR_EL1           CSR_SREG(0b11, 0b000, 0b1100, 0b0001, 0b001)
#define CSR_SREG_VSESR_EL2          CSR_SREG(0b11, 0b100, 0b0101, 0b0010, 0b011)
#define CSR_SREG_GPCCR_EL3          CSR_SREG(0b11, 0b110, 0b0010, 0b0001, 0b110)
#define CSR_SREG_GPTBR_EL3          CSR_SREG(0b11, 0b110, 0b0010, 0b0001, 0b100)
#define CSR_SREG_MFAR_EL3           CSR_SREG(0b11, 0b110, 0b0110, 0b0000, 0b101)
#define CSR_SREG_CNTFRQ_EL0         CSR_SREG(0b11, 0b011, 0b1110, 0b0000, 0b000)
#define CSR_SREG_CNTHCTL_EL2        CSR_SREG(0b11, 0b100, 0b1110, 0b0001, 0b000)
#define CSR_SREG_CNTHP_CTL_EL2      CSR_SREG(0b11, 0b100, 0b1110, 0b0010, 0b001)
#define CSR_SREG_CNTP_CTL_EL0       CSR_SREG(0b11, 0b011, 0b1110, 0b0010, 0b001)
#define CSR_SREG_CNTHP_CVAL_EL2     CSR_SREG(0b11, 0b100, 0b1110, 0b0010, 0b010)
#define CSR_SREG_CNTHP_TVAL_EL2     CSR_SREG(0b11, 0b100, 0b1110, 0b0010, 0b000)
#define CSR_SREG_CNTP_TVAL_EL0      CSR_SREG(0b11, 0b011, 0b1110, 0b0010, 0b000)
#define CSR_SREG_CNTHPS_CTL_EL2     CSR_SREG(0b11, 0b100, 0b1110, 0b0101, 0b001)
#define CSR_SREG_CNTP_CTL_EL0       CSR_SREG(0b11, 0b011, 0b1110, 0b0010, 0b001)
#define CSR_SREG_CNTHPS_CVAL_EL2    CSR_SREG(0b11, 0b100, 0b1110, 0b0101, 0b010)
#define CSR_SREG_CNTHPS_TVAL_EL2    CSR_SREG(0b11, 0b100, 0b1110, 0b0101, 0b000)
#define CSR_SREG_CNTP_TVAL_EL0      CSR_SREG(0b11, 0b011, 0b1110, 0b0010, 0b000)
#define CSR_SREG_CNTHV_CTL_EL2      CSR_SREG(0b11, 0b100, 0b1110, 0b0011, 0b001)
#define CSR_SREG_CNTV_CTL_EL0       CSR_SREG(0b11, 0b011, 0b1110, 0b0011, 0b001)
#define CSR_SREG_CNTHV_CVAL_EL2     CSR_SREG(0b11, 0b100, 0b1110, 0b0011, 0b010)
#define CSR_SREG_CNTHV_TVAL_EL2     CSR_SREG(0b11, 0b100, 0b1110, 0b0011, 0b000)
#define CSR_SREG_CNTV_TVAL_EL0      CSR_SREG(0b11, 0b011, 0b1110, 0b0011, 0b000)
#define CSR_SREG_CNTHVS_CTL_EL2     CSR_SREG(0b11, 0b100, 0b1110, 0b0100, 0b001)
#define CSR_SREG_CNTV_CTL_EL0       CSR_SREG(0b11, 0b011, 0b1110, 0b0011, 0b001)
#define CSR_SREG_CNTHVS_CVAL_EL2    CSR_SREG(0b11, 0b100, 0b1110, 0b0100, 0b010)
#define CSR_SREG_CNTHVS_TVAL_EL2    CSR_SREG(0b11, 0b100, 0b1110, 0b0100, 0b000)
#define CSR_SREG_CNTV_TVAL_EL0      CSR_SREG(0b11, 0b011, 0b1110, 0b0011, 0b000)
#define CSR_SREG_CNTKCTL_EL1        CSR_SREG(0b11, 0b000, 0b1110, 0b0001, 0b000)
#define CSR_SREG_CNTP_CTL_EL0       CSR_SREG(0b11, 0b011, 0b1110, 0b0010, 0b001)
#define CSR_SREG_CNTP_CTL_EL02      CSR_SREG(0b11, 0b101, 0b1110, 0b0010, 0b001)
#define CSR_SREG_CNTP_CVAL_EL0      CSR_SREG(0b11, 0b011, 0b1110, 0b0010, 0b010)
#define CSR_SREG_CNTP_CVAL_EL02     CSR_SREG(0b11, 0b101, 0b1110, 0b0010, 0b010)
#define CSR_SREG_CNTP_TVAL_EL0      CSR_SREG(0b11, 0b011, 0b1110, 0b0010, 0b000)
#define CSR_SREG_CNTP_TVAL_EL02     CSR_SREG(0b11, 0b101, 0b1110, 0b0010, 0b000)
#define CSR_SREG_CNTPCTSS_EL0       CSR_SREG(0b11, 0b011, 0b1110, 0b0000, 0b101)
#define CSR_SREG_CNTPCT_EL0         CSR_SREG(0b11, 0b011, 0b1110, 0b0000, 0b001)
#define CSR_SREG_CNTPS_CTL_EL1      CSR_SREG(0b11, 0b111, 0b1110, 0b0010, 0b001)
#define CSR_SREG_CNTPOFF_EL2        CSR_SREG(0b11, 0b100, 0b1110, 0b0000, 0b110)
#define CSR_SREG_CNTPS_CVAL_EL1     CSR_SREG(0b11, 0b111, 0b1110, 0b0010, 0b010)
#define CSR_SREG_CNTPS_TVAL_EL1     CSR_SREG(0b11, 0b111, 0b1110, 0b0010, 0b000)
#define CSR_SREG_CNTV_CTL_EL0       CSR_SREG(0b11, 0b011, 0b1110, 0b0011, 0b001)
#define CSR_SREG_CNTV_CTL_EL02      CSR_SREG(0b11, 0b101, 0b1110, 0b0011, 0b001)
#define CSR_SREG_CNTV_CVAL_EL0      CSR_SREG(0b11, 0b011, 0b1110, 0b0011, 0b010)
#define CSR_SREG_CNTV_CVAL_EL02     CSR_SREG(0b11, 0b101, 0b1110, 0b0011, 0b010)
#define CSR_SREG_CNTV_TVAL_EL0      CSR_SREG(0b11, 0b011, 0b1110, 0b0011, 0b000)
#define CSR_SREG_CNTV_TVAL_EL02     CSR_SREG(0b11, 0b101, 0b1110, 0b0011, 0b000)
#define CSR_SREG_CNTVCTSS_EL0       CSR_SREG(0b11, 0b011, 0b1110, 0b0000, 0b110)
#define CSR_SREG_CNTVCT_EL0         CSR_SREG(0b11, 0b011, 0b1110, 0b0000, 0b010)
#define CSR_SREG_CNTVOFF_EL2        CSR_SREG(0b11, 0b100, 0b1110, 0b0000, 0b011)

//
// Standard stringification macro (not so standard since we must define it again and again).
//
#define _CSR_STRINGIFY_1(x) #x
#define CSR_STRINGIFY(x) _CSR_STRINGIFY_1(x)

//
// The following macro is a trick to forge instructions with general-purpose registers (GPR),
// In an asm directive, argument references such as "%0" or "%1" are replaced by the compiler
// back-end with some GPR names such as "w12" or "x24". To build the instruction code, we need
// to transform "w12" as 12 or "x24" as 24. To do that, we define all possible identifiers for
// all GPR in the form .csr_gpr_wNN or .csr_gpr_xNN. In an asm directive, we use .csr_gpr_%0,
// which will be replaced by .csr_gpr_x24 (if GPR x24 has been allocated), which will be
// replaced by 24. We also define xzr and wzr (zero register) and sp as x31 since this is
// their default encoding in Arm instructions.
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
// Macros to read/write system registers using their identifier.
// This method works at all levels of architecture, including when the target
// register does not exist. It is the responsibility of the code logic to execute
// this instruction only after checking that the corresponding system register
// exists. Also see the comments in _CSR_DEFINE_GPR macro.
//
// Examples:
//    csr_u64_t r;
//    csr_msr_num(CSR_APIAKEYHI_EL1, r);
//    csr_mrs_num(r, CSR_APIAKEYHI_EL1);
//
#define csr_msr_num(sreg,value) \
    asm(_CSR_DEFINE_GPR ".inst 0xd5000000|(" CSR_STRINGIFY(sreg) ")|(.csr_gpr_%0)" : : "r" (value))

#define csr_mrs_num(result,sreg) \
    asm(_CSR_DEFINE_GPR ".inst 0xd5200000|(" CSR_STRINGIFY(sreg) ")|(.csr_gpr_%0)" : "=r" (result))

//
// Macros to generate PACxx and AUTxx instructions.
// This method works at all levels of architecture, including when PAuth is not
// supported by the assembler. Since these instructions are in the HINT range,
// executing them before Armv8.3 is a NOP.
//
#define csr_pacia(data,mod) \
    asm(_CSR_DEFINE_GPR ".inst 0xdac10000|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "+r" (data) : "r" (mod))
#define csr_pacib(data,mod) \
    asm(_CSR_DEFINE_GPR ".inst 0xdac10400|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "+r" (data) : "r" (mod))
#define csr_pacda(data,mod) \
    asm(_CSR_DEFINE_GPR ".inst 0xdac10800|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "+r" (data) : "r" (mod))
#define csr_pacdb(data,mod) \
    asm(_CSR_DEFINE_GPR ".inst 0xdac10c00|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "+r" (data) : "r" (mod))
#define csr_pacga(result,data,mod) \
    asm(_CSR_DEFINE_GPR ".inst 0x9ac03000|((.csr_gpr_%2)<<16)|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "=r" (result) : "r" (data), "r" (mod))
#define csr_autia(data,mod) \
    asm(_CSR_DEFINE_GPR ".inst 0xdac11000|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "+r" (data) : "r" (mod))
#define csr_autib(data,mod) \
    asm(_CSR_DEFINE_GPR ".inst 0xdac11400|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "+r" (data) : "r" (mod))
#define csr_autda(data,mod) \
    asm(_CSR_DEFINE_GPR ".inst 0xdac11800|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "+r" (data) : "r" (mod))
#define csr_autdb(data,mod) \
    asm(_CSR_DEFINE_GPR ".inst 0xdac11c00|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "+r" (data) : "r" (mod))



//----------------------------------------------------------------------------
// This code in used in the kernel only (Linux or macOS).
// All functions are typically called only once in the kernel module.
// For this reason, they are all inlined.
//----------------------------------------------------------------------------

#if defined(KERNEL)

// Define a few CPU features which are required to access some registers.
#define FEAT_PAC      0x0001
#define FEAT_PACGA    0x0002
#define FEAT_BTI      0x0004
#define FEAT_RME      0x0008
#define FEAT_CSV2_2   0x0010
#define FEAT_RNG      0x0020
#define FEAT_SVE      0x0040
#define FEAT_SME      0x0080
#define FEAT_ETE      0x0100
#define FEAT_PMUv3p4  0x0200
#define FEAT_TCR2     0x0400

// Get the CPU features. Typically called once on module initialization.
CSR_INLINE int csr_get_cpu_features(void)
{
    csr_u64_t pfr0, pfr1, dfr0, isar0, isar1, isar2, mmfr3;
    csr_mrs_str(pfr0,  "id_aa64pfr0_el1");
    csr_mrs_str(pfr1,  "id_aa64pfr1_el1");
    csr_mrs_str(dfr0,  "id_aa64dfr0_el1");
    csr_mrs_str(isar0, "id_aa64isar0_el1");
    csr_mrs_str(isar1, "id_aa64isar1_el1");
    csr_mrs_str(isar2, "id_aa64isar2_el1");
    csr_mrs_num(mmfr3, CSR_SREG_ID_AA64MMFR3_EL1);
    return (csr_has_pac(isar1, isar2) ? FEAT_PAC : 0) |
           (csr_has_pacga(isar1, isar2) ? FEAT_PACGA : 0) |
           (csr_has_bti(pfr1) ? FEAT_BTI : 0) |
           (csr_has_rme(pfr0) ? FEAT_RME : 0) |
           (csr_has_csv2_2(pfr0) ? FEAT_CSV2_2 : 0) |
           (csr_has_rng(isar0) ? FEAT_RNG : 0) |
           (csr_has_sve(pfr0) ? FEAT_SVE : 0) |
           (csr_has_sme(pfr1) ? FEAT_SME : 0) |
           (csr_has_ete(dfr0) ? FEAT_ETE : 0) |
           (csr_has_pmuv3p4(dfr0) ? FEAT_PMUv3p4 : 0) |
           (csr_has_tcr2(mmfr3) ? FEAT_TCR2 : 0);
}

// Set the value of a single register or pair of registers.
// Return values: 0=success, 1=unknown register, 2=CPU feature missing
CSR_INLINE int csr_set_register(int regid, const csr_pair_t* value, int cpu_features)
{
#define _check(features) if (((features) & cpu_features) != (features)) return 2
#define _setreg_num(id, sreg, features) \
    case (id):                          \
        _check(features);               \
        csr_msr_num(sreg, value->low);  \
        return 0
#define _setreg_str(id, sreg, features) \
    case (id):                          \
        _check(features);               \
        csr_msr_str(sreg, value->low);  \
        return 0
#define _setreg2_num(id, sreg_high, sreg_low, features) \
    case (id):                                          \
        _check(features);                               \
        csr_msr_num(sreg_high, value->high);            \
        csr_msr_num(sreg_low, value->low);              \
        return 0
#define _setreg2_str(id, sreg_high, sreg_low, features) \
    case (id):                                          \
        _check(features);                               \
        csr_msr_str(sreg_high, value->high);            \
        csr_msr_str(sreg_low, value->low);              \
        return 0

    switch (regid) {
        _setreg_str(CSR_REGID_TPIDRRO_EL0, "tpidrro_el0", 0);
        _setreg_str(CSR_REGID_TPIDR_EL0,   "tpidr_el0", 0);
        _setreg_str(CSR_REGID_TPIDR_EL1,   "tpidr_el1", 0);
        _setreg_str(CSR_REGID_SCTLR,       "sctlr_el1", 0);
        _setreg_num(CSR_REGID_SCXTNUM_EL0, CSR_SREG_SCXTNUM_EL0, FEAT_CSV2_2);
        _setreg_num(CSR_REGID_SCXTNUM_EL1, CSR_SREG_SCXTNUM_EL1, FEAT_CSV2_2);
        _setreg2_num(CSR_REGID2_APIAKEY,   CSR_SREG_APIAKEYHI_EL1, CSR_SREG_APIAKEYLO_EL1, FEAT_PAC);
        _setreg2_num(CSR_REGID2_APIBKEY,   CSR_SREG_APIBKEYHI_EL1, CSR_SREG_APIBKEYLO_EL1, FEAT_PAC);
        _setreg2_num(CSR_REGID2_APDAKEY,   CSR_SREG_APDAKEYHI_EL1, CSR_SREG_APDAKEYLO_EL1, FEAT_PAC);
        _setreg2_num(CSR_REGID2_APDBKEY,   CSR_SREG_APDBKEYHI_EL1, CSR_SREG_APDBKEYLO_EL1, FEAT_PAC);
        _setreg2_num(CSR_REGID2_APGAKEY,   CSR_SREG_APGAKEYHI_EL1, CSR_SREG_APGAKEYLO_EL1, FEAT_PACGA);
        default: return 1;
    }

#undef _check
#undef _setreg_num
#undef _setreg_str
#undef _setreg2_num
#undef _setreg2_str
}

// Get the value of a single register or pair of registers.
// Return values: 0=success, 1=unknown register, 2=CPU feature missing
CSR_INLINE int csr_get_register(int regid, csr_pair_t* value, int cpu_features)
{
#define _check(features) if (((features) & cpu_features) != (features)) return 2
#define _getreg_num(id, sreg, features) \
    case (id):                          \
        _check(features);               \
        csr_mrs_num(value->low, sreg);  \
        return 0
#define _getreg_str(id, sreg, features) \
    case (id):                          \
        _check(features);               \
        csr_mrs_str(value->low, sreg);  \
        return 0
#define _getreg2_num(id, sreg_high, sreg_low, features) \
    case (id):                                          \
        _check(features);                               \
        csr_mrs_num(value->high, sreg_high);            \
        csr_mrs_num(value->low, sreg_low);              \
        return 0
#define _getreg2_str(id, sreg_high, sreg_low, features) \
    case (id):                                          \
        _check(features);                               \
        csr_mrs_str(value->high, sreg_high);            \
        csr_mrs_str(value->low, sreg_low);              \
        return 0

    switch (regid) {
        _getreg_str(CSR_REGID_AA64PFR0,    "id_aa64pfr0_el1", 0);
        _getreg_str(CSR_REGID_AA64PFR1,    "id_aa64pfr1_el1", 0);
        _getreg_str(CSR_REGID_AA64ISAR0,   "id_aa64isar0_el1", 0);
        _getreg_str(CSR_REGID_AA64ISAR1,   "id_aa64isar1_el1", 0);
        _getreg_str(CSR_REGID_AA64ISAR2,   "id_aa64isar2_el1", 0);
        _getreg_str(CSR_REGID_TCR,         "tcr_el1", 0);
        _getreg_num(CSR_REGID_TCR2,        CSR_SREG_TCR2_EL1, FEAT_TCR2);
        _getreg_str(CSR_REGID_MIDR,        "midr_el1", 0);
        _getreg_str(CSR_REGID_MPIDR,       "mpidr_el1", 0);
        _getreg_str(CSR_REGID_REVIDR,      "revidr_el1", 0);
        _getreg_str(CSR_REGID_TPIDRRO_EL0, "tpidrro_el0", 0);
        _getreg_str(CSR_REGID_TPIDR_EL0,   "tpidr_el0", 0);
        _getreg_str(CSR_REGID_TPIDR_EL1,   "tpidr_el1", 0);
        _getreg_num(CSR_REGID_SCXTNUM_EL0, CSR_SREG_SCXTNUM_EL0, FEAT_CSV2_2);
        _getreg_num(CSR_REGID_SCXTNUM_EL1, CSR_SREG_SCXTNUM_EL1, FEAT_CSV2_2);
        _getreg_str(CSR_REGID_SCTLR,       "sctlr_el1", 0);
        _getreg_str(CSR_REGID_HCR,         "hcr_el2", 0);
        _getreg_num(CSR_REGID_RNDR,        CSR_SREG_RNDR, FEAT_RNG);
        _getreg_num(CSR_REGID_RNDRRS,      CSR_SREG_RNDRRS, FEAT_RNG);
        _getreg_str(CSR_REGID_SCR,         "scr_el3", 0);
        _getreg_str(CSR_REGID_AA64MMFR0,   "id_aa64mmfr0_el1", 0);
        _getreg_str(CSR_REGID_AA64MMFR1,   "id_aa64mmfr1_el1", 0);
        _getreg_str(CSR_REGID_AA64MMFR2,   "id_aa64mmfr2_el1", 0);
        _getreg_num(CSR_REGID_AA64MMFR3,   CSR_SREG_ID_AA64MMFR3_EL1, 0);
        _getreg_num(CSR_REGID_AA64ZFR0,    CSR_SREG_ID_AA64ZFR0_EL1, FEAT_SVE);
        _getreg_num(CSR_REGID_AA64SMFR0,   CSR_SREG_ID_AA64SMFR0_EL1, FEAT_SME);
        _getreg_str(CSR_REGID_AA64AFR0,    "id_aa64afr0_el1", 0);
        _getreg_str(CSR_REGID_AA64AFR1,    "id_aa64afr1_el1", 0);
        _getreg_str(CSR_REGID_AA64DFR0,    "id_aa64dfr0_el1", 0);
        _getreg_str(CSR_REGID_AA64DFR1,    "id_aa64dfr1_el1", 0);
        _getreg_num(CSR_REGID_TRCDEVARCH,  CSR_SREG_TRCDEVARCH, FEAT_ETE);
        _getreg_num(CSR_REGID_PMMIR,       CSR_SREG_PMMIR_EL1, FEAT_PMUv3p4);
        _getreg_str(CSR_REGID_CTR,         "ctr_el0", 0);
        _getreg_str(CSR_REGID_TTBR0_EL1,   "ttbr0_el1", 0);
        _getreg_str(CSR_REGID_TTBR1_EL1,   "ttbr1_el1", 0);
        _getreg2_num(CSR_REGID2_APIAKEY,   CSR_SREG_APIAKEYHI_EL1, CSR_SREG_APIAKEYLO_EL1, FEAT_PAC);
        _getreg2_num(CSR_REGID2_APIBKEY,   CSR_SREG_APIBKEYHI_EL1, CSR_SREG_APIBKEYLO_EL1, FEAT_PAC);
        _getreg2_num(CSR_REGID2_APDAKEY,   CSR_SREG_APDAKEYHI_EL1, CSR_SREG_APDAKEYLO_EL1, FEAT_PAC);
        _getreg2_num(CSR_REGID2_APDBKEY,   CSR_SREG_APDBKEYHI_EL1, CSR_SREG_APDBKEYLO_EL1, FEAT_PAC);
        _getreg2_num(CSR_REGID2_APGAKEY,   CSR_SREG_APGAKEYHI_EL1, CSR_SREG_APGAKEYLO_EL1, FEAT_PACGA);
        default: return 1;
    }

#undef _check
#undef _getreg_num
#undef _getreg_str
#undef _getreg2_num
#undef _getreg2_str
}

// Execute a PACxx or AUTxx instruction.
// Return values: 0=success, 1=unknown instruction.
CSR_INLINE int csr_exec_instr(int instr, csr_instr_t* args)
{
    switch (instr) {
        case CSR_INSTR_PACIA:
            csr_pacia(args->value, args->modifier);
            return 0;
        case CSR_INSTR_PACIB:
            csr_pacib(args->value, args->modifier);
            return 0;
        case CSR_INSTR_PACDA:
            csr_pacda(args->value, args->modifier);
            return 0;
        case CSR_INSTR_PACDB:
            csr_pacdb(args->value, args->modifier);
            return 0;
        case CSR_INSTR_PACGA:
            csr_pacga(args->value, args->value, args->modifier);
            return 0;
        case CSR_INSTR_AUTIA:
            csr_autia(args->value, args->modifier);
            return 0;
        case CSR_INSTR_AUTIB:
            csr_autib(args->value, args->modifier);
            return 0;
        case CSR_INSTR_AUTDA:
            csr_autda(args->value, args->modifier);
            return 0;
        case CSR_INSTR_AUTDB:
            csr_autdb(args->value, args->modifier);
            return 0;
        default:
            return 1;
    }
}

#endif // KERNEL

#endif // CPUSYSREGS_H
