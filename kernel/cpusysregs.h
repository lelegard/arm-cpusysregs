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

#elif defined(WINDOWS)

    #if defined(KERNEL)
        #include <ntddk.h>
    #else
        #include <windows.h>
        #include <winioctl.h>
        #if defined(__cplusplus)
            #if defined(min)
                #undef min
            #endif
            #if defined(max)
                #undef max
            #endif
        #endif
    #endif
    typedef UINT64 csr_u64_t;

#endif

#if defined(__cplusplus)
extern "C" {
#endif

// Linux kernel module name, macOS kernel extension name, Windows driver name.
#define CSR_MODULE_NAME "cpusysregs"

// Description of a pair of hi/lo registers for PAC authentication keys.
// Most registers are individually read/written. Some registers, such as
// PAC keys, can be accessed only in pairs.
typedef struct {
    csr_u64_t low;
    csr_u64_t high;
} csr_pair_t;

// Attribute of a macro-like function.
#if defined(_MSC_VER)
    #define CSR_INLINE static inline __forceinline
#else
    #define CSR_INLINE static inline __attribute__((always_inline))
#endif


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

// This macro checks if SPE (Statistical Profiling Extension) is supported, based on the value of the
// ID_AA64DFR0_EL1 system register.
#define csr_has_spe(dfr0) (((dfr0 >> 32) & 0x0F) >= 1)

// This macro checks if TCR2 registers are supported, based on the value of the
// ID_AA64MMFR3_EL1 system register.
#define csr_has_tcr2(mmfr3) ((mmfr3) & 0x000000000000000Fllu)

// This macro checks if SCTLR2 registers are supported, based on the value of the
// ID_AA64MMFR3_EL1 system register.
#define csr_has_sctlr2(mmfr3) ((mmfr3) & 0x00000000000000F0llu)

// This macro checks if AIE (Memory Attribute Index Enhancement) is supported, based on the value of the
// ID_AA64MMFR3_EL1 system register.
#define csr_has_aie(mmfr3) ((mmfr3) & 0x000000000F000000llu)

// This macro checks if S1PIE (Permission model enhancements) is supported, based on the value of the
// ID_AA64MMFR3_EL1 system register.
#define csr_has_s1pie(mmfr3) ((mmfr3) & 0x0000000000000F00llu)


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
// - Update inlined functions csr_get_register() and csr_set_register() below.
//   If the register exists only when a given CPU features is supported, make
//   sure to set the list of required features for the register.
// - Add the register in the ../README.md file.
// - Add the description of the register in the ../apps/regview.cpp file.
//   Also make sure to specify the required list of CPU features.

enum {
    CSR_REGID_INVALID,          // Placeholder for invalid register id
    // ------------------------ // Individual registers
    CSR_REGID_ID_AA64PFR0_EL1,  // AArch64 Processor Feature registers 0
    CSR_REGID_ID_AA64PFR1_EL1,  // AArch64 Processor Feature registers 1
    CSR_REGID_ID_AA64PFR2_EL1,  // AArch64 Processor Feature registers 2
    CSR_REGID_ID_AA64ISAR0_EL1, // AArch64 Instruction Set Attribute Register 0
    CSR_REGID_ID_AA64ISAR1_EL1, // AArch64 Instruction Set Attribute Register 1
    CSR_REGID_ID_AA64ISAR2_EL1, // AArch64 Instruction Set Attribute Register 2
    CSR_REGID_TCR_EL1,          // Translation Control Register
    CSR_REGID_TCR2_EL1,         // Extended Translation Control Register
    CSR_REGID_MIDR_EL1,         // Main ID Register (read-only)
    CSR_REGID_MPIDR_EL1,        // Multiprocessor Affinity Register
    CSR_REGID_REVIDR_EL1,       // Revision ID Register
    CSR_REGID_TPIDRRO_EL0,      // EL0 Read-Only Software Thread ID Register (R/W at EL1)
    CSR_REGID_TPIDR_EL0,        // EL0 Read/Write Software Thread ID Register
    CSR_REGID_TPIDR_EL1,        // EL1 Software Thread ID Register
    CSR_REGID_SCXTNUM_EL0,      // EL0 Read/Write Software Context Number
    CSR_REGID_SCXTNUM_EL1,      // EL1 Read/Write Software Context Number
    CSR_REGID_SCTLR_EL1,        // System Control Register
    CSR_REGID_SCTLR2_EL1,       // System Control Register 2
    CSR_REGID_HCR_EL2,          // Hypervisor Configuration Register (EL2)
    CSR_REGID_RNDR,             // Random Number
    CSR_REGID_RNDRRS,           // Reseeded Random Number
    CSR_REGID_SCR_EL3,          // Secure Configuration Register (EL3)
    CSR_REGID_ID_AA64MMFR0_EL1, // AArch64 Memory Model Feature Register 0
    CSR_REGID_ID_AA64MMFR1_EL1, // AArch64 Memory Model Feature Register 1
    CSR_REGID_ID_AA64MMFR2_EL1, // AArch64 Memory Model Feature Register 2
    CSR_REGID_ID_AA64MMFR3_EL1, // AArch64 Memory Model Feature Register 3
    CSR_REGID_ID_AA64MMFR4_EL1, // AArch64 Memory Model Feature Register 4
    CSR_REGID_ID_AA64ZFR0_EL1,  // SVE Feature ID register 0
    CSR_REGID_ID_AA64SMFR0_EL1, // SME Feature ID register 0
    CSR_REGID_ID_AA64AFR0_EL1,  // AArch64 Auxiliary Feature Register 0
    CSR_REGID_ID_AA64AFR1_EL1,  // AArch64 Auxiliary Feature Register 1
    CSR_REGID_ID_AA64DFR0_EL1,  // AArch64 Debug Feature Register 0
    CSR_REGID_ID_AA64DFR1_EL1,  // AArch64 Debug Feature Register 1
    CSR_REGID_TRCDEVARCH,       // Trace Device Architecture Register
    CSR_REGID_PMMIR_EL1,        // Performance Monitors Machine Identification Register
    CSR_REGID_CTR_EL0,          // Cache Type Register
    CSR_REGID_TTBR0_EL1,        // Translation Table Base Register 0 (EL1)
    CSR_REGID_TTBR1_EL1,        // Translation Table Base Register 1 (EL1)
    CSR_REGID_MAIR_EL1,         // Memory Attribute Indirection Register (EL1)
    CSR_REGID_MAIR2_EL1,        // Memory Attribute Indirection Register (EL1)
    CSR_REGID_PIR_EL1,          // Permission Indirection Register 1 (EL1)
    CSR_REGID_PIRE0_EL1,        // Permission Indirection Register 0 (EL1)
    CSR_REGID_ID_ISAR0_EL1,     // AArch32 Instruction Set Attribute Register 0
    CSR_REGID_ID_ISAR1_EL1,     // AArch32 Instruction Set Attribute Register 1
    CSR_REGID_ID_ISAR2_EL1,     // AArch32 Instruction Set Attribute Register 2
    CSR_REGID_ID_ISAR3_EL1,     // AArch32 Instruction Set Attribute Register 3
    CSR_REGID_ID_ISAR4_EL1,     // AArch32 Instruction Set Attribute Register 4
    CSR_REGID_ID_ISAR5_EL1,     // AArch32 Instruction Set Attribute Register 5
    CSR_REGID_ID_ISAR6_EL1,     // AArch32 Instruction Set Attribute Register 6
    CSR_REGID_ID_MMFR0_EL1,     // AArch32 Memory Model Feature Register 0
    CSR_REGID_ID_MMFR1_EL1,     // AArch32 Memory Model Feature Register 1
    CSR_REGID_ID_MMFR2_EL1,     // AArch32 Memory Model Feature Register 2
    CSR_REGID_ID_MMFR3_EL1,     // AArch32 Memory Model Feature Register 3
    CSR_REGID_ID_MMFR4_EL1,     // AArch32 Memory Model Feature Register 4
    CSR_REGID_ID_MMFR5_EL1,     // AArch32 Memory Model Feature Register 5
    CSR_REGID_ID_PFR0_EL1,      // AArch32 Processor Feature Register 0
    CSR_REGID_ID_PFR1_EL1,      // AArch32 Processor Feature Register 1
    CSR_REGID_ID_PFR2_EL1,      // AArch32 Processor Feature Register 2
    CSR_REGID_PMSIDR_EL1,       // Sampling Profiling ID Register
    CSR_REGID_CNTKCTL_EL1,      // Counter-timer Kernel Control register
    // -----------------------  // End of individual registers
    _CSR_REGID_END,
    // -----------------------  // Registers which come in pair
    CSR_REGID2_APIAKEY_EL1,     // Pointer Authentication Key A for Instruction
    CSR_REGID2_APIBKEY_EL1,     // Pointer Authentication Key B for Instruction
    CSR_REGID2_APDAKEY_EL1,     // Pointer Authentication Key A for Data
    CSR_REGID2_APDBKEY_EL1,     // Pointer Authentication Key B for Data
    CSR_REGID2_APGAKEY_EL1,     // Pointer Authentication Generic Key
    // -----------------------  // End of registers which come in pair
    _CSR_REGID2_END
};

// Check if a register id is a single register.
CSR_INLINE int csr_regid_is_single(int regid)
{
    return regid > CSR_REGID_INVALID && regid < _CSR_REGID_END;
}

// Check if a register id is a pair of registers.
CSR_INLINE int csr_regid_is_pair(int regid)
{
    return regid > _CSR_REGID_END && regid < _CSR_REGID2_END;
}

// Check if a register id is in a valid range.
CSR_INLINE int csr_regid_is_valid(int regid)
{
    return csr_regid_is_single(regid) || csr_regid_is_pair(regid);
}


//----------------------------------------------------------------------------
// Pointer authentication commands.
// The PACxx and AUTxx instructions can be delegated into the kernel module.
// The purpose is to exhibit potential differences between user and kernel.
//----------------------------------------------------------------------------

// Codes of instructions to execute in kernel mode.
// These values must fit in one byte to be included in an ioctl() command code.

enum {
    CSR_INSTR_INVALID,  // Placeholder for invalid instruction code.
    CSR_INSTR_PACIA,
    CSR_INSTR_PACIB,
    CSR_INSTR_PACDA,
    CSR_INSTR_PACDB,
    CSR_INSTR_PACGA,
    CSR_INSTR_AUTIA,
    CSR_INSTR_AUTIB,
    CSR_INSTR_AUTDA,
    CSR_INSTR_AUTDB,
    _CSR_INSTR_END
};

// Parameters for an instruction in kernel mode.
typedef struct {
    csr_u64_t value;     // value to sign or authenticate, read/write
    csr_u64_t modifier;  // modifier, read-only
} csr_instr_t;


//----------------------------------------------------------------------------
// Kernel module commands.
// Linux: Use ioctl() on /dev/cpusysregs.
// macOS: Use getsockopt() and setsockopt() on system control cpusysregs.
// Windows: Use DeviceIoControl() on \\.\cpusysregs.
//----------------------------------------------------------------------------

#if defined(__linux__)

    // Special device for this module.
    #define CSR_DEVICE_PATH "/dev/" CSR_MODULE_NAME

    // ioctl() codes for /dev/cpusysregs.
    // Each code shall be unique since all commands go through ioctl().
    #define _CSR_IOC_REG             0x50
    #define _CSR_IOC_INSTR           0x80
    #define CSR_IOC_GET_REG(regid)   _IOR(_CSR_IOC_REG, (regid), csr_u64_t)
    #define CSR_IOC_GET_REG2(regid)  _IOR(_CSR_IOC_REG, (regid), csr_pair_t)
    #define CSR_IOC_SET_REG(regid)   _IOW(_CSR_IOC_REG, (regid), csr_u64_t)
    #define CSR_IOC_SET_REG2(regid)  _IOW(_CSR_IOC_REG, (regid), csr_pair_t)
    #define CSR_IOC_INSTR(instr)     _IOWR(_CSR_IOC_INSTR, (instr), csr_instr_t)

    // Extract the register id from an ioctl() code.
    // Return CSR_REGID_INVALID if not a set/get register command.
    CSR_INLINE int csr_ioc_to_regid(long cmd)
    {
        const int nr = (int)_IOC_NR(cmd);
        return _IOC_TYPE(cmd) == _CSR_IOC_REG && nr != _CSR_REGID_END && nr < _CSR_REGID2_END ? nr : CSR_REGID_INVALID;
    }

    // Extract the instruction code from an ioctl() code.
    // Return CSR_INSTR_INVALID if not an instruction command.
    CSR_INLINE int csr_ioc_to_instr(long cmd)
    {
        const int nr = (int)_IOC_NR(cmd);
        return _IOC_TYPE(cmd) == _CSR_IOC_INSTR && nr < _CSR_INSTR_END ? nr : CSR_INSTR_INVALID;
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
        const int regid = opt & _CSR_SOCKOPT_MASK;
        return (opt & ~_CSR_SOCKOPT_MASK) == _CSR_SOCKOPT_REG && regid != _CSR_REGID_END && regid < _CSR_REGID2_END ?
            regid : CSR_REGID_INVALID;
    }

    // Extract the instruction code from a socket option.
    // Return CSR_INSTR_INVALID if not an instruction command.
    CSR_INLINE int csr_sockopt_to_instr(int opt)
    {
        const int instr = opt & _CSR_SOCKOPT_MASK;
        return (opt & ~_CSR_SOCKOPT_MASK) == _CSR_SOCKOPT_INSTR && instr < _CSR_INSTR_END ? instr : CSR_INSTR_INVALID;
    }

#elif defined(WINDOWS)

    // Device name, as seen from userland applications.
    #define CSR_DEVICE_NAME      "\\\\.\\" CSR_MODULE_NAME

    // Windows NT and DOS devices names, as seen from the driver.
    #define CSR_NT_DEVICE_NAME   L"\\Device\\" CSR_MODULE_NAME
    #define CSR_DOS_DEVICE_NAME  L"\\DosDevices\\" CSR_MODULE_NAME

    // I/O control codes for \\.\cpusysregs.
    // Each code shall be unique since all commands go through DeviceIoControl().
    // Device types (_CSR_IOC_REG, _CSR_IOC_INSTR) are in the "User Defined" range.
    // The IOCTL function codes (12 bits) from 0x800 to 0xFFF are for customer use.
    #define _CSR_IOC                40000
    #define _CSR_FUNC_MASK          0xF00
    #define _CSR_FUNC_GET_REG       0xA00
    #define _CSR_FUNC_SET_REG       0xB00
    #define _CSR_FUNC_INSTR         0xC00
    #define CSR_IOC_GET_REG(regid)  CTL_CODE(_CSR_IOC, _CSR_FUNC_GET_REG | (regid), METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define CSR_IOC_SET_REG(regid)  CTL_CODE(_CSR_IOC, _CSR_FUNC_SET_REG | (regid), METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define CSR_IOC_INSTR(instr)    CTL_CODE(_CSR_IOC, _CSR_FUNC_INSTR | (instr), METHOD_BUFFERED, FILE_ANY_ACCESS)

    // Not found in current version of ntddk.h (similar to DEVICE_TYPE_FROM_CTL_CODE and METHOD_FROM_CTL_CODE.
    #if !defined(FUNCTION_FROM_CTL_CODE)
        #define FUNCTION_FROM_CTL_CODE(ctrlCode)  ((ULONG)((ctrlCode) >> 2) & 0x0FFF)
    #endif

    // Check if a DeviceIoControl() code is a set register command.
    CSR_INLINE int csr_ioc_is_set_reg(ULONG cmd)
    {
        return DEVICE_TYPE_FROM_CTL_CODE(cmd) == _CSR_IOC && (FUNCTION_FROM_CTL_CODE(cmd) & _CSR_FUNC_MASK) == _CSR_FUNC_SET_REG;
    }

    // Extract the register id from a DeviceIoControl() code.
    // Return CSR_REGID_INVALID if not a get/set register command.
    CSR_INLINE int csr_ioc_to_regid(ULONG cmd)
    {
        const ULONG func = FUNCTION_FROM_CTL_CODE(cmd) & _CSR_FUNC_MASK;
        const int regid = (int)(FUNCTION_FROM_CTL_CODE(cmd) & ~_CSR_FUNC_MASK);
        return DEVICE_TYPE_FROM_CTL_CODE(cmd) == _CSR_IOC &&
               (func == _CSR_FUNC_GET_REG || func == _CSR_FUNC_SET_REG) &&
               regid != _CSR_REGID_END &&
               regid < _CSR_REGID2_END ?
               regid : CSR_REGID_INVALID;
    }

    // Extract the instruction code from a DeviceIoControl() code.
    // Return CSR_INSTR_INVALID if not an instruction command.
    CSR_INLINE int csr_ioc_to_instr(ULONG cmd)
    {
        const ULONG func = FUNCTION_FROM_CTL_CODE(cmd) & _CSR_FUNC_MASK;
        const int instr = (int)(FUNCTION_FROM_CTL_CODE(cmd) & ~_CSR_FUNC_MASK);
        return DEVICE_TYPE_FROM_CTL_CODE(cmd) == _CSR_IOC && func == _CSR_FUNC_INSTR && instr < _CSR_INSTR_END ? instr : CSR_INSTR_INVALID;
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
#if defined(__linux__) ||  defined(__APPLE__)
    // Define a value for direct placement in an MRS/MSR instruction.
    #define CSR_SREG(op0, op1, crn, crm, op2) (((op0) << 19) | ((op1) << 16) | ((crn) << 12) | ((crm) << 8) | ((op2) << 5))
#elif defined(WINDOWS)
    // Define the non-shifted value. The bit 20 in the MSR/MRS instructions is always 1.
    // It must not be part of the value for _Read/Write StatusReg intrinsics of the MS compiler.
    #define CSR_SREG(op0, op1, crn, crm, op2) ((((op0) & 0x1) << 14) | ((op1) << 12) | ((crn) << 7) | ((crm) << 3) | (op2))
#endif

//
// The following macros define the encoding of most Arm system registers.
// These definition were automatically generated using the script extract-sreg-definitions.sh.
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
#define CSR_SREG_ALLINT             CSR_SREG(0b11, 0b000, 0b0100, 0b0011, 0b000)
#define CSR_SREG_AMAIR2_EL1         CSR_SREG(0b11, 0b000, 0b1010, 0b0011, 0b001)
#define CSR_SREG_AMAIR2_EL12        CSR_SREG(0b11, 0b101, 0b1010, 0b0011, 0b001)
#define CSR_SREG_AMAIR2_EL2         CSR_SREG(0b11, 0b100, 0b1010, 0b0011, 0b001)
#define CSR_SREG_AMAIR2_EL3         CSR_SREG(0b11, 0b110, 0b1010, 0b0011, 0b001)
#define CSR_SREG_AMAIR_EL1          CSR_SREG(0b11, 0b000, 0b1010, 0b0011, 0b000)
#define CSR_SREG_AMAIR_EL12         CSR_SREG(0b11, 0b101, 0b1010, 0b0011, 0b000)
#define CSR_SREG_AMAIR_EL2          CSR_SREG(0b11, 0b100, 0b1010, 0b0011, 0b000)
#define CSR_SREG_AMAIR_EL3          CSR_SREG(0b11, 0b110, 0b1010, 0b0011, 0b000)
#define CSR_SREG_AMCFGR_EL0         CSR_SREG(0b11, 0b011, 0b1101, 0b0010, 0b001)
#define CSR_SREG_AMCG1IDR_EL0       CSR_SREG(0b11, 0b011, 0b1101, 0b0010, 0b110)
#define CSR_SREG_AMCGCR_EL0         CSR_SREG(0b11, 0b011, 0b1101, 0b0010, 0b010)
#define CSR_SREG_AMCNTENCLR0_EL0    CSR_SREG(0b11, 0b011, 0b1101, 0b0010, 0b100)
#define CSR_SREG_AMCNTENCLR1_EL0    CSR_SREG(0b11, 0b011, 0b1101, 0b0011, 0b000)
#define CSR_SREG_AMCNTENSET0_EL0    CSR_SREG(0b11, 0b011, 0b1101, 0b0010, 0b101)
#define CSR_SREG_AMCNTENSET1_EL0    CSR_SREG(0b11, 0b011, 0b1101, 0b0011, 0b001)
#define CSR_SREG_AMCR_EL0           CSR_SREG(0b11, 0b011, 0b1101, 0b0010, 0b000)
#define CSR_SREG_AMUSERENR_EL0      CSR_SREG(0b11, 0b011, 0b1101, 0b0010, 0b011)
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
#define CSR_SREG_BRBCR_EL1          CSR_SREG(0b10, 0b001, 0b1001, 0b0000, 0b000)
#define CSR_SREG_BRBCR_EL12         CSR_SREG(0b10, 0b101, 0b1001, 0b0000, 0b000)
#define CSR_SREG_BRBCR_EL2          CSR_SREG(0b10, 0b100, 0b1001, 0b0000, 0b000)
#define CSR_SREG_BRBFCR_EL1         CSR_SREG(0b10, 0b001, 0b1001, 0b0000, 0b001)
#define CSR_SREG_BRBIDR0_EL1        CSR_SREG(0b10, 0b001, 0b1001, 0b0010, 0b000)
#define CSR_SREG_BRBINFINJ_EL1      CSR_SREG(0b10, 0b001, 0b1001, 0b0001, 0b000)
#define CSR_SREG_BRBSRCINJ_EL1      CSR_SREG(0b10, 0b001, 0b1001, 0b0001, 0b001)
#define CSR_SREG_BRBTGTINJ_EL1      CSR_SREG(0b10, 0b001, 0b1001, 0b0001, 0b010)
#define CSR_SREG_BRBTS_EL1          CSR_SREG(0b10, 0b001, 0b1001, 0b0000, 0b010)
#define CSR_SREG_CCSIDR2_EL1        CSR_SREG(0b11, 0b001, 0b0000, 0b0000, 0b010)
#define CSR_SREG_CCSIDR_EL1         CSR_SREG(0b11, 0b001, 0b0000, 0b0000, 0b000)
#define CSR_SREG_CLIDR_EL1          CSR_SREG(0b11, 0b001, 0b0000, 0b0000, 0b001)
#define CSR_SREG_CNTFRQ_EL0         CSR_SREG(0b11, 0b011, 0b1110, 0b0000, 0b000)
#define CSR_SREG_CNTHCTL_EL2        CSR_SREG(0b11, 0b100, 0b1110, 0b0001, 0b000)
#define CSR_SREG_CNTHP_CTL_EL2      CSR_SREG(0b11, 0b100, 0b1110, 0b0010, 0b001)
#define CSR_SREG_CNTHP_CVAL_EL2     CSR_SREG(0b11, 0b100, 0b1110, 0b0010, 0b010)
#define CSR_SREG_CNTHPS_CTL_EL2     CSR_SREG(0b11, 0b100, 0b1110, 0b0101, 0b001)
#define CSR_SREG_CNTHPS_CVAL_EL2    CSR_SREG(0b11, 0b100, 0b1110, 0b0101, 0b010)
#define CSR_SREG_CNTHPS_TVAL_EL2    CSR_SREG(0b11, 0b100, 0b1110, 0b0101, 0b000)
#define CSR_SREG_CNTHP_TVAL_EL2     CSR_SREG(0b11, 0b100, 0b1110, 0b0010, 0b000)
#define CSR_SREG_CNTHV_CTL_EL2      CSR_SREG(0b11, 0b100, 0b1110, 0b0011, 0b001)
#define CSR_SREG_CNTHV_CVAL_EL2     CSR_SREG(0b11, 0b100, 0b1110, 0b0011, 0b010)
#define CSR_SREG_CNTHVS_CTL_EL2     CSR_SREG(0b11, 0b100, 0b1110, 0b0100, 0b001)
#define CSR_SREG_CNTHVS_CVAL_EL2    CSR_SREG(0b11, 0b100, 0b1110, 0b0100, 0b010)
#define CSR_SREG_CNTHVS_TVAL_EL2    CSR_SREG(0b11, 0b100, 0b1110, 0b0100, 0b000)
#define CSR_SREG_CNTHV_TVAL_EL2     CSR_SREG(0b11, 0b100, 0b1110, 0b0011, 0b000)
#define CSR_SREG_CNTKCTL_EL1        CSR_SREG(0b11, 0b000, 0b1110, 0b0001, 0b000)
#define CSR_SREG_CNTKCTL_EL12       CSR_SREG(0b11, 0b101, 0b1110, 0b0001, 0b000)
#define CSR_SREG_CNTPCT_EL0         CSR_SREG(0b11, 0b011, 0b1110, 0b0000, 0b001)
#define CSR_SREG_CNTP_CTL_EL0       CSR_SREG(0b11, 0b011, 0b1110, 0b0010, 0b001)
#define CSR_SREG_CNTP_CTL_EL02      CSR_SREG(0b11, 0b101, 0b1110, 0b0010, 0b001)
#define CSR_SREG_CNTPCTSS_EL0       CSR_SREG(0b11, 0b011, 0b1110, 0b0000, 0b101)
#define CSR_SREG_CNTP_CVAL_EL0      CSR_SREG(0b11, 0b011, 0b1110, 0b0010, 0b010)
#define CSR_SREG_CNTP_CVAL_EL02     CSR_SREG(0b11, 0b101, 0b1110, 0b0010, 0b010)
#define CSR_SREG_CNTPOFF_EL2        CSR_SREG(0b11, 0b100, 0b1110, 0b0000, 0b110)
#define CSR_SREG_CNTPS_CTL_EL1      CSR_SREG(0b11, 0b111, 0b1110, 0b0010, 0b001)
#define CSR_SREG_CNTPS_CVAL_EL1     CSR_SREG(0b11, 0b111, 0b1110, 0b0010, 0b010)
#define CSR_SREG_CNTPS_TVAL_EL1     CSR_SREG(0b11, 0b111, 0b1110, 0b0010, 0b000)
#define CSR_SREG_CNTP_TVAL_EL0      CSR_SREG(0b11, 0b011, 0b1110, 0b0010, 0b000)
#define CSR_SREG_CNTP_TVAL_EL02     CSR_SREG(0b11, 0b101, 0b1110, 0b0010, 0b000)
#define CSR_SREG_CNTVCT_EL0         CSR_SREG(0b11, 0b011, 0b1110, 0b0000, 0b010)
#define CSR_SREG_CNTV_CTL_EL0       CSR_SREG(0b11, 0b011, 0b1110, 0b0011, 0b001)
#define CSR_SREG_CNTV_CTL_EL02      CSR_SREG(0b11, 0b101, 0b1110, 0b0011, 0b001)
#define CSR_SREG_CNTVCTSS_EL0       CSR_SREG(0b11, 0b011, 0b1110, 0b0000, 0b110)
#define CSR_SREG_CNTV_CVAL_EL0      CSR_SREG(0b11, 0b011, 0b1110, 0b0011, 0b010)
#define CSR_SREG_CNTV_CVAL_EL02     CSR_SREG(0b11, 0b101, 0b1110, 0b0011, 0b010)
#define CSR_SREG_CNTVOFF_EL2        CSR_SREG(0b11, 0b100, 0b1110, 0b0000, 0b011)
#define CSR_SREG_CNTV_TVAL_EL0      CSR_SREG(0b11, 0b011, 0b1110, 0b0011, 0b000)
#define CSR_SREG_CNTV_TVAL_EL02     CSR_SREG(0b11, 0b101, 0b1110, 0b0011, 0b000)
#define CSR_SREG_CONTEXTIDR_EL1     CSR_SREG(0b11, 0b000, 0b1101, 0b0000, 0b001)
#define CSR_SREG_CONTEXTIDR_EL12    CSR_SREG(0b11, 0b101, 0b1101, 0b0000, 0b001)
#define CSR_SREG_CONTEXTIDR_EL2     CSR_SREG(0b11, 0b100, 0b1101, 0b0000, 0b001)
#define CSR_SREG_CPACR_EL1          CSR_SREG(0b11, 0b000, 0b0001, 0b0000, 0b010)
#define CSR_SREG_CPACR_EL12         CSR_SREG(0b11, 0b101, 0b0001, 0b0000, 0b010)
#define CSR_SREG_CPTR_EL2           CSR_SREG(0b11, 0b100, 0b0001, 0b0001, 0b010)
#define CSR_SREG_CPTR_EL3           CSR_SREG(0b11, 0b110, 0b0001, 0b0001, 0b010)
#define CSR_SREG_CSSELR_EL1         CSR_SREG(0b11, 0b010, 0b0000, 0b0000, 0b000)
#define CSR_SREG_CTR_EL0            CSR_SREG(0b11, 0b011, 0b0000, 0b0000, 0b001)
#define CSR_SREG_CURRENTEL          CSR_SREG(0b11, 0b000, 0b0100, 0b0010, 0b010)
#define CSR_SREG_DACR32_EL2         CSR_SREG(0b11, 0b100, 0b0011, 0b0000, 0b000)
#define CSR_SREG_DAIF               CSR_SREG(0b11, 0b011, 0b0100, 0b0010, 0b001)
#define CSR_SREG_DBGAUTHSTATUS_EL1  CSR_SREG(0b10, 0b000, 0b0111, 0b1110, 0b110)
#define CSR_SREG_DBGCLAIMCLR_EL1    CSR_SREG(0b10, 0b000, 0b0111, 0b1001, 0b110)
#define CSR_SREG_DBGCLAIMSET_EL1    CSR_SREG(0b10, 0b000, 0b0111, 0b1000, 0b110)
#define CSR_SREG_DBGDTR_EL0         CSR_SREG(0b10, 0b011, 0b0000, 0b0100, 0b000)
#define CSR_SREG_DBGDTRRX_EL0       CSR_SREG(0b10, 0b011, 0b0000, 0b0101, 0b000)
#define CSR_SREG_DBGPRCR_EL1        CSR_SREG(0b10, 0b000, 0b0001, 0b0100, 0b100)
#define CSR_SREG_DBGVCR32_EL2       CSR_SREG(0b10, 0b100, 0b0000, 0b0111, 0b000)
#define CSR_SREG_DCZID_EL0          CSR_SREG(0b11, 0b011, 0b0000, 0b0000, 0b111)
#define CSR_SREG_DISR_EL1           CSR_SREG(0b11, 0b000, 0b1100, 0b0001, 0b001)
#define CSR_SREG_DIT                CSR_SREG(0b11, 0b011, 0b0100, 0b0010, 0b101)
#define CSR_SREG_DLR_EL0            CSR_SREG(0b11, 0b011, 0b0100, 0b0101, 0b001)
#define CSR_SREG_DSPSR_EL0          CSR_SREG(0b11, 0b011, 0b0100, 0b0101, 0b000)
#define CSR_SREG_ELR_EL1            CSR_SREG(0b11, 0b000, 0b0100, 0b0000, 0b001)
#define CSR_SREG_ELR_EL12           CSR_SREG(0b11, 0b101, 0b0100, 0b0000, 0b001)
#define CSR_SREG_ELR_EL2            CSR_SREG(0b11, 0b100, 0b0100, 0b0000, 0b001)
#define CSR_SREG_ELR_EL3            CSR_SREG(0b11, 0b110, 0b0100, 0b0000, 0b001)
#define CSR_SREG_ERRIDR_EL1         CSR_SREG(0b11, 0b000, 0b0101, 0b0011, 0b000)
#define CSR_SREG_ERRSELR_EL1        CSR_SREG(0b11, 0b000, 0b0101, 0b0011, 0b001)
#define CSR_SREG_ERXADDR_EL1        CSR_SREG(0b11, 0b000, 0b0101, 0b0100, 0b011)
#define CSR_SREG_ERXCTLR_EL1        CSR_SREG(0b11, 0b000, 0b0101, 0b0100, 0b001)
#define CSR_SREG_ERXFR_EL1          CSR_SREG(0b11, 0b000, 0b0101, 0b0100, 0b000)
#define CSR_SREG_ERXGSR_EL1         CSR_SREG(0b11, 0b000, 0b0101, 0b0011, 0b010)
#define CSR_SREG_ERXMISC0_EL1       CSR_SREG(0b11, 0b000, 0b0101, 0b0101, 0b000)
#define CSR_SREG_ERXMISC1_EL1       CSR_SREG(0b11, 0b000, 0b0101, 0b0101, 0b001)
#define CSR_SREG_ERXMISC2_EL1       CSR_SREG(0b11, 0b000, 0b0101, 0b0101, 0b010)
#define CSR_SREG_ERXMISC3_EL1       CSR_SREG(0b11, 0b000, 0b0101, 0b0101, 0b011)
#define CSR_SREG_ERXPFGCDN_EL1      CSR_SREG(0b11, 0b000, 0b0101, 0b0100, 0b110)
#define CSR_SREG_ERXPFGCTL_EL1      CSR_SREG(0b11, 0b000, 0b0101, 0b0100, 0b101)
#define CSR_SREG_ERXPFGF_EL1        CSR_SREG(0b11, 0b000, 0b0101, 0b0100, 0b100)
#define CSR_SREG_ERXSTATUS_EL1      CSR_SREG(0b11, 0b000, 0b0101, 0b0100, 0b010)
#define CSR_SREG_ESR_EL1            CSR_SREG(0b11, 0b000, 0b0101, 0b0010, 0b000)
#define CSR_SREG_ESR_EL12           CSR_SREG(0b11, 0b101, 0b0101, 0b0010, 0b000)
#define CSR_SREG_ESR_EL2            CSR_SREG(0b11, 0b100, 0b0101, 0b0010, 0b000)
#define CSR_SREG_ESR_EL3            CSR_SREG(0b11, 0b110, 0b0101, 0b0010, 0b000)
#define CSR_SREG_FAR_EL1            CSR_SREG(0b11, 0b000, 0b0110, 0b0000, 0b000)
#define CSR_SREG_FAR_EL12           CSR_SREG(0b11, 0b101, 0b0110, 0b0000, 0b000)
#define CSR_SREG_FAR_EL2            CSR_SREG(0b11, 0b100, 0b0110, 0b0000, 0b000)
#define CSR_SREG_FAR_EL3            CSR_SREG(0b11, 0b110, 0b0110, 0b0000, 0b000)
#define CSR_SREG_FPCR               CSR_SREG(0b11, 0b011, 0b0100, 0b0100, 0b000)
#define CSR_SREG_FPEXC32_EL2        CSR_SREG(0b11, 0b100, 0b0101, 0b0011, 0b000)
#define CSR_SREG_FPSR               CSR_SREG(0b11, 0b011, 0b0100, 0b0100, 0b001)
#define CSR_SREG_GCR_EL1            CSR_SREG(0b11, 0b000, 0b0001, 0b0000, 0b110)
#define CSR_SREG_GCSCRE0_EL1        CSR_SREG(0b11, 0b000, 0b0010, 0b0101, 0b010)
#define CSR_SREG_GCSCR_EL1          CSR_SREG(0b11, 0b000, 0b0010, 0b0101, 0b000)
#define CSR_SREG_GCSCR_EL12         CSR_SREG(0b11, 0b101, 0b0010, 0b0101, 0b000)
#define CSR_SREG_GCSCR_EL2          CSR_SREG(0b11, 0b100, 0b0010, 0b0101, 0b000)
#define CSR_SREG_GCSCR_EL3          CSR_SREG(0b11, 0b110, 0b0010, 0b0101, 0b000)
#define CSR_SREG_GCSPR_EL0          CSR_SREG(0b11, 0b011, 0b0010, 0b0101, 0b001)
#define CSR_SREG_GCSPR_EL1          CSR_SREG(0b11, 0b000, 0b0010, 0b0101, 0b001)
#define CSR_SREG_GCSPR_EL12         CSR_SREG(0b11, 0b101, 0b0010, 0b0101, 0b001)
#define CSR_SREG_GCSPR_EL2          CSR_SREG(0b11, 0b100, 0b0010, 0b0101, 0b001)
#define CSR_SREG_GCSPR_EL3          CSR_SREG(0b11, 0b110, 0b0010, 0b0101, 0b001)
#define CSR_SREG_GMID_EL1           CSR_SREG(0b11, 0b001, 0b0000, 0b0000, 0b100)
#define CSR_SREG_GPCCR_EL3          CSR_SREG(0b11, 0b110, 0b0010, 0b0001, 0b110)
#define CSR_SREG_GPTBR_EL3          CSR_SREG(0b11, 0b110, 0b0010, 0b0001, 0b100)
#define CSR_SREG_HACR_EL2           CSR_SREG(0b11, 0b100, 0b0001, 0b0001, 0b111)
#define CSR_SREG_HAFGRTR_EL2        CSR_SREG(0b11, 0b100, 0b0011, 0b0001, 0b110)
#define CSR_SREG_HCR_EL2            CSR_SREG(0b11, 0b100, 0b0001, 0b0001, 0b000)
#define CSR_SREG_HCRX_EL2           CSR_SREG(0b11, 0b100, 0b0001, 0b0010, 0b010)
#define CSR_SREG_HDFGRTR2_EL2       CSR_SREG(0b11, 0b100, 0b0011, 0b0001, 0b000)
#define CSR_SREG_HDFGRTR_EL2        CSR_SREG(0b11, 0b100, 0b0011, 0b0001, 0b100)
#define CSR_SREG_HDFGWTR2_EL2       CSR_SREG(0b11, 0b100, 0b0011, 0b0001, 0b001)
#define CSR_SREG_HDFGWTR_EL2        CSR_SREG(0b11, 0b100, 0b0011, 0b0001, 0b101)
#define CSR_SREG_HFGITR2_EL2        CSR_SREG(0b11, 0b100, 0b0011, 0b0001, 0b111)
#define CSR_SREG_HFGITR_EL2         CSR_SREG(0b11, 0b100, 0b0001, 0b0001, 0b110)
#define CSR_SREG_HFGRTR2_EL2        CSR_SREG(0b11, 0b100, 0b0011, 0b0001, 0b010)
#define CSR_SREG_HFGRTR_EL2         CSR_SREG(0b11, 0b100, 0b0001, 0b0001, 0b100)
#define CSR_SREG_HFGWTR2_EL2        CSR_SREG(0b11, 0b100, 0b0011, 0b0001, 0b011)
#define CSR_SREG_HFGWTR_EL2         CSR_SREG(0b11, 0b100, 0b0001, 0b0001, 0b101)
#define CSR_SREG_HPFAR_EL2          CSR_SREG(0b11, 0b100, 0b0110, 0b0000, 0b100)
#define CSR_SREG_HSTR_EL2           CSR_SREG(0b11, 0b100, 0b0001, 0b0001, 0b011)
#define CSR_SREG_ICC_BPR0_EL1       CSR_SREG(0b11, 0b000, 0b1100, 0b1000, 0b011)
#define CSR_SREG_ICC_BPR1_EL1       CSR_SREG(0b11, 0b000, 0b1100, 0b1100, 0b011)
#define CSR_SREG_ICC_CTLR_EL1       CSR_SREG(0b11, 0b000, 0b1100, 0b1100, 0b100)
#define CSR_SREG_ICC_CTLR_EL3       CSR_SREG(0b11, 0b110, 0b1100, 0b1100, 0b100)
#define CSR_SREG_ICC_HPPIR0_EL1     CSR_SREG(0b11, 0b000, 0b1100, 0b1000, 0b010)
#define CSR_SREG_ICC_HPPIR1_EL1     CSR_SREG(0b11, 0b000, 0b1100, 0b1100, 0b010)
#define CSR_SREG_ICC_IAR0_EL1       CSR_SREG(0b11, 0b000, 0b1100, 0b1000, 0b000)
#define CSR_SREG_ICC_IAR1_EL1       CSR_SREG(0b11, 0b000, 0b1100, 0b1100, 0b000)
#define CSR_SREG_ICC_IGRPEN0_EL1    CSR_SREG(0b11, 0b000, 0b1100, 0b1100, 0b110)
#define CSR_SREG_ICC_IGRPEN1_EL1    CSR_SREG(0b11, 0b000, 0b1100, 0b1100, 0b111)
#define CSR_SREG_ICC_IGRPEN1_EL3    CSR_SREG(0b11, 0b110, 0b1100, 0b1100, 0b111)
#define CSR_SREG_ICC_NMIAR1_EL1     CSR_SREG(0b11, 0b000, 0b1100, 0b1001, 0b101)
#define CSR_SREG_ICC_PMR_EL1        CSR_SREG(0b11, 0b000, 0b0100, 0b0110, 0b000)
#define CSR_SREG_ICC_RPR_EL1        CSR_SREG(0b11, 0b000, 0b1100, 0b1011, 0b011)
#define CSR_SREG_ICC_SRE_EL1        CSR_SREG(0b11, 0b000, 0b1100, 0b1100, 0b101)
#define CSR_SREG_ICC_SRE_EL2        CSR_SREG(0b11, 0b100, 0b1100, 0b1001, 0b101)
#define CSR_SREG_ICC_SRE_EL3        CSR_SREG(0b11, 0b110, 0b1100, 0b1100, 0b101)
#define CSR_SREG_ICH_EISR_EL2       CSR_SREG(0b11, 0b100, 0b1100, 0b1011, 0b011)
#define CSR_SREG_ICH_ELRSR_EL2      CSR_SREG(0b11, 0b100, 0b1100, 0b1011, 0b101)
#define CSR_SREG_ICH_HCR_EL2        CSR_SREG(0b11, 0b100, 0b1100, 0b1011, 0b000)
#define CSR_SREG_ICH_MISR_EL2       CSR_SREG(0b11, 0b100, 0b1100, 0b1011, 0b010)
#define CSR_SREG_ICH_VMCR_EL2       CSR_SREG(0b11, 0b100, 0b1100, 0b1011, 0b111)
#define CSR_SREG_ICH_VTR_EL2        CSR_SREG(0b11, 0b100, 0b1100, 0b1011, 0b001)
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
#define CSR_SREG_MAIR2_EL1          CSR_SREG(0b11, 0b000, 0b1010, 0b0010, 0b001)
#define CSR_SREG_MAIR2_EL12         CSR_SREG(0b11, 0b101, 0b1010, 0b0010, 0b001)
#define CSR_SREG_MAIR2_EL2          CSR_SREG(0b11, 0b100, 0b1010, 0b0001, 0b001)
#define CSR_SREG_MAIR2_EL3          CSR_SREG(0b11, 0b110, 0b1010, 0b0001, 0b001)
#define CSR_SREG_MAIR_EL1           CSR_SREG(0b11, 0b000, 0b1010, 0b0010, 0b000)
#define CSR_SREG_MAIR_EL12          CSR_SREG(0b11, 0b101, 0b1010, 0b0010, 0b000)
#define CSR_SREG_MAIR_EL2           CSR_SREG(0b11, 0b100, 0b1010, 0b0010, 0b000)
#define CSR_SREG_MAIR_EL3           CSR_SREG(0b11, 0b110, 0b1010, 0b0010, 0b000)
#define CSR_SREG_MDCCINT_EL1        CSR_SREG(0b10, 0b000, 0b0000, 0b0010, 0b000)
#define CSR_SREG_MDCCSR_EL0         CSR_SREG(0b10, 0b011, 0b0000, 0b0001, 0b000)
#define CSR_SREG_MDCR_EL2           CSR_SREG(0b11, 0b100, 0b0001, 0b0001, 0b001)
#define CSR_SREG_MDCR_EL3           CSR_SREG(0b11, 0b110, 0b0001, 0b0011, 0b001)
#define CSR_SREG_MDRAR_EL1          CSR_SREG(0b10, 0b000, 0b0001, 0b0000, 0b000)
#define CSR_SREG_MDSCR_EL1          CSR_SREG(0b10, 0b000, 0b0000, 0b0010, 0b010)
#define CSR_SREG_MDSELR_EL1         CSR_SREG(0b10, 0b000, 0b0000, 0b0100, 0b010)
#define CSR_SREG_MECID_A0_EL2       CSR_SREG(0b11, 0b100, 0b1010, 0b1000, 0b001)
#define CSR_SREG_MECID_A1_EL2       CSR_SREG(0b11, 0b100, 0b1010, 0b1000, 0b011)
#define CSR_SREG_MECID_P0_EL2       CSR_SREG(0b11, 0b100, 0b1010, 0b1000, 0b000)
#define CSR_SREG_MECID_P1_EL2       CSR_SREG(0b11, 0b100, 0b1010, 0b1000, 0b010)
#define CSR_SREG_MECIDR_EL2         CSR_SREG(0b11, 0b100, 0b1010, 0b1000, 0b111)
#define CSR_SREG_MECID_RL_A_EL3     CSR_SREG(0b11, 0b110, 0b1010, 0b1010, 0b001)
#define CSR_SREG_MFAR_EL3           CSR_SREG(0b11, 0b110, 0b0110, 0b0000, 0b101)
#define CSR_SREG_MIDR_EL1           CSR_SREG(0b11, 0b000, 0b0000, 0b0000, 0b000)
#define CSR_SREG_MPAM0_EL1          CSR_SREG(0b11, 0b000, 0b1010, 0b0101, 0b001)
#define CSR_SREG_MPAM1_EL1          CSR_SREG(0b11, 0b000, 0b1010, 0b0101, 0b000)
#define CSR_SREG_MPAM1_EL12         CSR_SREG(0b11, 0b101, 0b1010, 0b0101, 0b000)
#define CSR_SREG_MPAM2_EL2          CSR_SREG(0b11, 0b100, 0b1010, 0b0101, 0b000)
#define CSR_SREG_MPAM3_EL3          CSR_SREG(0b11, 0b110, 0b1010, 0b0101, 0b000)
#define CSR_SREG_MPAMHCR_EL2        CSR_SREG(0b11, 0b100, 0b1010, 0b0100, 0b000)
#define CSR_SREG_MPAMIDR_EL1        CSR_SREG(0b11, 0b000, 0b1010, 0b0100, 0b100)
#define CSR_SREG_MPAMSM_EL1         CSR_SREG(0b11, 0b000, 0b1010, 0b0101, 0b011)
#define CSR_SREG_MPAMVPM0_EL2       CSR_SREG(0b11, 0b100, 0b1010, 0b0110, 0b000)
#define CSR_SREG_MPAMVPM1_EL2       CSR_SREG(0b11, 0b100, 0b1010, 0b0110, 0b001)
#define CSR_SREG_MPAMVPM2_EL2       CSR_SREG(0b11, 0b100, 0b1010, 0b0110, 0b010)
#define CSR_SREG_MPAMVPM3_EL2       CSR_SREG(0b11, 0b100, 0b1010, 0b0110, 0b011)
#define CSR_SREG_MPAMVPM4_EL2       CSR_SREG(0b11, 0b100, 0b1010, 0b0110, 0b100)
#define CSR_SREG_MPAMVPM5_EL2       CSR_SREG(0b11, 0b100, 0b1010, 0b0110, 0b101)
#define CSR_SREG_MPAMVPM6_EL2       CSR_SREG(0b11, 0b100, 0b1010, 0b0110, 0b110)
#define CSR_SREG_MPAMVPM7_EL2       CSR_SREG(0b11, 0b100, 0b1010, 0b0110, 0b111)
#define CSR_SREG_MPAMVPMV_EL2       CSR_SREG(0b11, 0b100, 0b1010, 0b0100, 0b001)
#define CSR_SREG_MPIDR_EL1          CSR_SREG(0b11, 0b000, 0b0000, 0b0000, 0b101)
#define CSR_SREG_MVFR0_EL1          CSR_SREG(0b11, 0b000, 0b0000, 0b0011, 0b000)
#define CSR_SREG_MVFR1_EL1          CSR_SREG(0b11, 0b000, 0b0000, 0b0011, 0b001)
#define CSR_SREG_MVFR2_EL1          CSR_SREG(0b11, 0b000, 0b0000, 0b0011, 0b010)
#define CSR_SREG_NZCV               CSR_SREG(0b11, 0b011, 0b0100, 0b0010, 0b000)
#define CSR_SREG_OSDLR_EL1          CSR_SREG(0b10, 0b000, 0b0001, 0b0011, 0b100)
#define CSR_SREG_OSDTRRX_EL1        CSR_SREG(0b10, 0b000, 0b0000, 0b0000, 0b010)
#define CSR_SREG_OSDTRTX_EL1        CSR_SREG(0b10, 0b000, 0b0000, 0b0011, 0b010)
#define CSR_SREG_OSECCR_EL1         CSR_SREG(0b10, 0b000, 0b0000, 0b0110, 0b010)
#define CSR_SREG_OSLSR_EL1          CSR_SREG(0b10, 0b000, 0b0001, 0b0001, 0b100)
#define CSR_SREG_PAN                CSR_SREG(0b11, 0b000, 0b0100, 0b0010, 0b011)
#define CSR_SREG_PAR_EL1            CSR_SREG(0b11, 0b000, 0b0111, 0b0100, 0b000)
#define CSR_SREG_PFAR_EL1           CSR_SREG(0b11, 0b000, 0b0110, 0b0000, 0b101)
#define CSR_SREG_PFAR_EL12          CSR_SREG(0b11, 0b101, 0b0110, 0b0000, 0b101)
#define CSR_SREG_PFAR_EL2           CSR_SREG(0b11, 0b100, 0b0110, 0b0000, 0b101)
#define CSR_SREG_PIRE0_EL1          CSR_SREG(0b11, 0b000, 0b1010, 0b0010, 0b010)
#define CSR_SREG_PIRE0_EL12         CSR_SREG(0b11, 0b101, 0b1010, 0b0010, 0b010)
#define CSR_SREG_PIRE0_EL2          CSR_SREG(0b11, 0b100, 0b1010, 0b0010, 0b010)
#define CSR_SREG_PIR_EL1            CSR_SREG(0b11, 0b000, 0b1010, 0b0010, 0b011)
#define CSR_SREG_PIR_EL12           CSR_SREG(0b11, 0b101, 0b1010, 0b0010, 0b011)
#define CSR_SREG_PIR_EL2            CSR_SREG(0b11, 0b100, 0b1010, 0b0010, 0b011)
#define CSR_SREG_PIR_EL3            CSR_SREG(0b11, 0b110, 0b1010, 0b0010, 0b011)
#define CSR_SREG_PM                 CSR_SREG(0b11, 0b000, 0b0100, 0b0011, 0b001)
#define CSR_SREG_PMBIDR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1010, 0b111)
#define CSR_SREG_PMBLIMITR_EL1      CSR_SREG(0b11, 0b000, 0b1001, 0b1010, 0b000)
#define CSR_SREG_PMBPTR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1010, 0b001)
#define CSR_SREG_PMBSR_EL1          CSR_SREG(0b11, 0b000, 0b1001, 0b1010, 0b011)
#define CSR_SREG_PMCCFILTR_EL0      CSR_SREG(0b11, 0b011, 0b1110, 0b1111, 0b111)
#define CSR_SREG_PMCCNTR_EL0        CSR_SREG(0b11, 0b011, 0b1001, 0b1101, 0b000)
#define CSR_SREG_PMCCNTSVR_EL1      CSR_SREG(0b10, 0b000, 0b1110, 0b1011, 0b111)
#define CSR_SREG_PMCEID0_EL0        CSR_SREG(0b11, 0b011, 0b1001, 0b1100, 0b110)
#define CSR_SREG_PMCEID1_EL0        CSR_SREG(0b11, 0b011, 0b1001, 0b1100, 0b111)
#define CSR_SREG_PMCNTENCLR_EL0     CSR_SREG(0b11, 0b011, 0b1001, 0b1100, 0b010)
#define CSR_SREG_PMCNTENSET_EL0     CSR_SREG(0b11, 0b011, 0b1001, 0b1100, 0b001)
#define CSR_SREG_PMCR_EL0           CSR_SREG(0b11, 0b011, 0b1001, 0b1100, 0b000)
#define CSR_SREG_PMECR_EL1          CSR_SREG(0b11, 0b000, 0b1001, 0b1110, 0b101)
#define CSR_SREG_PMIAR_EL1          CSR_SREG(0b11, 0b000, 0b1001, 0b1110, 0b111)
#define CSR_SREG_PMICFILTR_EL0      CSR_SREG(0b11, 0b011, 0b1001, 0b0110, 0b000)
#define CSR_SREG_PMICNTR_EL0        CSR_SREG(0b11, 0b011, 0b1001, 0b0100, 0b000)
#define CSR_SREG_PMICNTSVR_EL1      CSR_SREG(0b10, 0b000, 0b1110, 0b1100, 0b000)
#define CSR_SREG_PMINTENCLR_EL1     CSR_SREG(0b11, 0b000, 0b1001, 0b1110, 0b010)
#define CSR_SREG_PMINTENSET_EL1     CSR_SREG(0b11, 0b000, 0b1001, 0b1110, 0b001)
#define CSR_SREG_PMMIR_EL1          CSR_SREG(0b11, 0b000, 0b1001, 0b1110, 0b110)
#define CSR_SREG_PMOVSCLR_EL0       CSR_SREG(0b11, 0b011, 0b1001, 0b1100, 0b011)
#define CSR_SREG_PMOVSSET_EL0       CSR_SREG(0b11, 0b011, 0b1001, 0b1110, 0b011)
#define CSR_SREG_PMSCR_EL1          CSR_SREG(0b11, 0b000, 0b1001, 0b1001, 0b000)
#define CSR_SREG_PMSCR_EL12         CSR_SREG(0b11, 0b101, 0b1001, 0b1001, 0b000)
#define CSR_SREG_PMSCR_EL2          CSR_SREG(0b11, 0b100, 0b1001, 0b1001, 0b000)
#define CSR_SREG_PMSDSFR_EL1        CSR_SREG(0b11, 0b000, 0b1001, 0b1010, 0b100)
#define CSR_SREG_PMSELR_EL0         CSR_SREG(0b11, 0b011, 0b1001, 0b1100, 0b101)
#define CSR_SREG_PMSEVFR_EL1        CSR_SREG(0b11, 0b000, 0b1001, 0b1001, 0b101)
#define CSR_SREG_PMSFCR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1001, 0b100)
#define CSR_SREG_PMSICR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1001, 0b010)
#define CSR_SREG_PMSIDR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1001, 0b111)
#define CSR_SREG_PMSIRR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1001, 0b011)
#define CSR_SREG_PMSLATFR_EL1       CSR_SREG(0b11, 0b000, 0b1001, 0b1001, 0b110)
#define CSR_SREG_PMSNEVFR_EL1       CSR_SREG(0b11, 0b000, 0b1001, 0b1001, 0b001)
#define CSR_SREG_PMSSCR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1101, 0b011)
#define CSR_SREG_PMUACR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1110, 0b100)
#define CSR_SREG_PMUSERENR_EL0      CSR_SREG(0b11, 0b011, 0b1001, 0b1110, 0b000)
#define CSR_SREG_PMXEVCNTR_EL0      CSR_SREG(0b11, 0b011, 0b1001, 0b1101, 0b010)
#define CSR_SREG_PMXEVTYPER_EL0     CSR_SREG(0b11, 0b011, 0b1001, 0b1101, 0b001)
#define CSR_SREG_POR_EL0            CSR_SREG(0b11, 0b011, 0b1010, 0b0010, 0b100)
#define CSR_SREG_POR_EL1            CSR_SREG(0b11, 0b000, 0b1010, 0b0010, 0b100)
#define CSR_SREG_POR_EL12           CSR_SREG(0b11, 0b101, 0b1010, 0b0010, 0b100)
#define CSR_SREG_POR_EL2            CSR_SREG(0b11, 0b100, 0b1010, 0b0010, 0b100)
#define CSR_SREG_POR_EL3            CSR_SREG(0b11, 0b110, 0b1010, 0b0010, 0b100)
#define CSR_SREG_RCWMASK_EL1        CSR_SREG(0b11, 0b000, 0b1101, 0b0000, 0b110)
#define CSR_SREG_RCWSMASK_EL1       CSR_SREG(0b11, 0b000, 0b1101, 0b0000, 0b011)
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
#define CSR_SREG_S2PIR_EL2          CSR_SREG(0b11, 0b100, 0b1010, 0b0010, 0b101)
#define CSR_SREG_S2POR_EL1          CSR_SREG(0b11, 0b000, 0b1010, 0b0010, 0b101)
#define CSR_SREG_SCR_EL3            CSR_SREG(0b11, 0b110, 0b0001, 0b0001, 0b000)
#define CSR_SREG_SCTLR2_EL1         CSR_SREG(0b11, 0b000, 0b0001, 0b0000, 0b011)
#define CSR_SREG_SCTLR2_EL12        CSR_SREG(0b11, 0b101, 0b0001, 0b0000, 0b011)
#define CSR_SREG_SCTLR2_EL2         CSR_SREG(0b11, 0b100, 0b0001, 0b0000, 0b011)
#define CSR_SREG_SCTLR2_EL3         CSR_SREG(0b11, 0b110, 0b0001, 0b0000, 0b011)
#define CSR_SREG_SCTLR_EL1          CSR_SREG(0b11, 0b000, 0b0001, 0b0000, 0b000)
#define CSR_SREG_SCTLR_EL12         CSR_SREG(0b11, 0b101, 0b0001, 0b0000, 0b000)
#define CSR_SREG_SCTLR_EL2          CSR_SREG(0b11, 0b100, 0b0001, 0b0000, 0b000)
#define CSR_SREG_SCTLR_EL3          CSR_SREG(0b11, 0b110, 0b0001, 0b0000, 0b000)
#define CSR_SREG_SCXTNUM_EL0        CSR_SREG(0b11, 0b011, 0b1101, 0b0000, 0b111)
#define CSR_SREG_SCXTNUM_EL1        CSR_SREG(0b11, 0b000, 0b1101, 0b0000, 0b111)
#define CSR_SREG_SCXTNUM_EL12       CSR_SREG(0b11, 0b101, 0b1101, 0b0000, 0b111)
#define CSR_SREG_SCXTNUM_EL2        CSR_SREG(0b11, 0b100, 0b1101, 0b0000, 0b111)
#define CSR_SREG_SCXTNUM_EL3        CSR_SREG(0b11, 0b110, 0b1101, 0b0000, 0b111)
#define CSR_SREG_SDER32_EL2         CSR_SREG(0b11, 0b100, 0b0001, 0b0011, 0b001)
#define CSR_SREG_SDER32_EL3         CSR_SREG(0b11, 0b110, 0b0001, 0b0001, 0b001)
#define CSR_SREG_SMCR_EL1           CSR_SREG(0b11, 0b000, 0b0001, 0b0010, 0b110)
#define CSR_SREG_SMCR_EL12          CSR_SREG(0b11, 0b101, 0b0001, 0b0010, 0b110)
#define CSR_SREG_SMCR_EL2           CSR_SREG(0b11, 0b100, 0b0001, 0b0010, 0b110)
#define CSR_SREG_SMCR_EL3           CSR_SREG(0b11, 0b110, 0b0001, 0b0010, 0b110)
#define CSR_SREG_SMIDR_EL1          CSR_SREG(0b11, 0b001, 0b0000, 0b0000, 0b110)
#define CSR_SREG_SMPRI_EL1          CSR_SREG(0b11, 0b000, 0b0001, 0b0010, 0b100)
#define CSR_SREG_SMPRIMAP_EL2       CSR_SREG(0b11, 0b100, 0b0001, 0b0010, 0b101)
#define CSR_SREG_SP_EL0             CSR_SREG(0b11, 0b000, 0b0100, 0b0001, 0b000)
#define CSR_SREG_SP_EL1             CSR_SREG(0b11, 0b100, 0b0100, 0b0001, 0b000)
#define CSR_SREG_SP_EL2             CSR_SREG(0b11, 0b110, 0b0100, 0b0001, 0b000)
#define CSR_SREG_SPMACCESSR_EL1     CSR_SREG(0b10, 0b000, 0b1001, 0b1101, 0b011)
#define CSR_SREG_SPMACCESSR_EL12    CSR_SREG(0b10, 0b101, 0b1001, 0b1101, 0b011)
#define CSR_SREG_SPMACCESSR_EL2     CSR_SREG(0b10, 0b100, 0b1001, 0b1101, 0b011)
#define CSR_SREG_SPMACCESSR_EL3     CSR_SREG(0b10, 0b110, 0b1001, 0b1101, 0b011)
#define CSR_SREG_SPMCFGR_EL1        CSR_SREG(0b10, 0b000, 0b1001, 0b1101, 0b111)
#define CSR_SREG_SPMCNTENCLR_EL0    CSR_SREG(0b10, 0b011, 0b1001, 0b1100, 0b010)
#define CSR_SREG_SPMCNTENSET_EL0    CSR_SREG(0b10, 0b011, 0b1001, 0b1100, 0b001)
#define CSR_SREG_SPMCR_EL0          CSR_SREG(0b10, 0b011, 0b1001, 0b1100, 0b000)
#define CSR_SREG_SPMDEVAFF_EL1      CSR_SREG(0b10, 0b000, 0b1001, 0b1101, 0b110)
#define CSR_SREG_SPMDEVARCH_EL1     CSR_SREG(0b10, 0b000, 0b1001, 0b1101, 0b101)
#define CSR_SREG_SPMIIDR_EL1        CSR_SREG(0b10, 0b000, 0b1001, 0b1101, 0b100)
#define CSR_SREG_SPMINTENCLR_EL1    CSR_SREG(0b10, 0b000, 0b1001, 0b1110, 0b010)
#define CSR_SREG_SPMINTENSET_EL1    CSR_SREG(0b10, 0b000, 0b1001, 0b1110, 0b001)
#define CSR_SREG_SPMOVSCLR_EL0      CSR_SREG(0b10, 0b011, 0b1001, 0b1100, 0b011)
#define CSR_SREG_SPMOVSSET_EL0      CSR_SREG(0b10, 0b011, 0b1001, 0b1110, 0b011)
#define CSR_SREG_SPMROOTCR_EL3      CSR_SREG(0b10, 0b110, 0b1001, 0b1110, 0b111)
#define CSR_SREG_SPMSCR_EL1         CSR_SREG(0b10, 0b111, 0b1001, 0b1110, 0b111)
#define CSR_SREG_SPMSELR_EL0        CSR_SREG(0b10, 0b011, 0b1001, 0b1100, 0b101)
#define CSR_SREG_SPSEL              CSR_SREG(0b11, 0b000, 0b0100, 0b0010, 0b000)
#define CSR_SREG_SPSR_ABT           CSR_SREG(0b11, 0b100, 0b0100, 0b0011, 0b001)
#define CSR_SREG_SPSR_EL1           CSR_SREG(0b11, 0b000, 0b0100, 0b0000, 0b000)
#define CSR_SREG_SPSR_EL12          CSR_SREG(0b11, 0b101, 0b0100, 0b0000, 0b000)
#define CSR_SREG_SPSR_EL2           CSR_SREG(0b11, 0b100, 0b0100, 0b0000, 0b000)
#define CSR_SREG_SPSR_EL3           CSR_SREG(0b11, 0b110, 0b0100, 0b0000, 0b000)
#define CSR_SREG_SPSR_FIQ           CSR_SREG(0b11, 0b100, 0b0100, 0b0011, 0b011)
#define CSR_SREG_SPSR_IRQ           CSR_SREG(0b11, 0b100, 0b0100, 0b0011, 0b000)
#define CSR_SREG_SPSR_UND           CSR_SREG(0b11, 0b100, 0b0100, 0b0011, 0b010)
#define CSR_SREG_SSBS               CSR_SREG(0b11, 0b011, 0b0100, 0b0010, 0b110)
#define CSR_SREG_SVCR               CSR_SREG(0b11, 0b011, 0b0100, 0b0010, 0b010)
#define CSR_SREG_TCO                CSR_SREG(0b11, 0b011, 0b0100, 0b0010, 0b111)
#define CSR_SREG_TCR2_EL1           CSR_SREG(0b11, 0b000, 0b0010, 0b0000, 0b011)
#define CSR_SREG_TCR2_EL12          CSR_SREG(0b11, 0b101, 0b0010, 0b0000, 0b011)
#define CSR_SREG_TCR2_EL2           CSR_SREG(0b11, 0b100, 0b0010, 0b0000, 0b011)
#define CSR_SREG_TCR_EL1            CSR_SREG(0b11, 0b000, 0b0010, 0b0000, 0b010)
#define CSR_SREG_TCR_EL12           CSR_SREG(0b11, 0b101, 0b0010, 0b0000, 0b010)
#define CSR_SREG_TCR_EL2            CSR_SREG(0b11, 0b100, 0b0010, 0b0000, 0b010)
#define CSR_SREG_TCR_EL3            CSR_SREG(0b11, 0b110, 0b0010, 0b0000, 0b010)
#define CSR_SREG_TFSRE0_EL1         CSR_SREG(0b11, 0b000, 0b0101, 0b0110, 0b001)
#define CSR_SREG_TFSR_EL1           CSR_SREG(0b11, 0b000, 0b0101, 0b0110, 0b000)
#define CSR_SREG_TFSR_EL12          CSR_SREG(0b11, 0b101, 0b0101, 0b0110, 0b000)
#define CSR_SREG_TFSR_EL2           CSR_SREG(0b11, 0b100, 0b0101, 0b0110, 0b000)
#define CSR_SREG_TFSR_EL3           CSR_SREG(0b11, 0b110, 0b0101, 0b0110, 0b000)
#define CSR_SREG_TPIDR2_EL0         CSR_SREG(0b11, 0b011, 0b1101, 0b0000, 0b101)
#define CSR_SREG_TPIDR_EL0          CSR_SREG(0b11, 0b011, 0b1101, 0b0000, 0b010)
#define CSR_SREG_TPIDR_EL1          CSR_SREG(0b11, 0b000, 0b1101, 0b0000, 0b100)
#define CSR_SREG_TPIDR_EL2          CSR_SREG(0b11, 0b100, 0b1101, 0b0000, 0b010)
#define CSR_SREG_TPIDR_EL3          CSR_SREG(0b11, 0b110, 0b1101, 0b0000, 0b010)
#define CSR_SREG_TPIDRRO_EL0        CSR_SREG(0b11, 0b011, 0b1101, 0b0000, 0b011)
#define CSR_SREG_TRBBASER_EL1       CSR_SREG(0b11, 0b000, 0b1001, 0b1011, 0b010)
#define CSR_SREG_TRBIDR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1011, 0b111)
#define CSR_SREG_TRBLIMITR_EL1      CSR_SREG(0b11, 0b000, 0b1001, 0b1011, 0b000)
#define CSR_SREG_TRBMAR_EL1         CSR_SREG(0b11, 0b000, 0b1001, 0b1011, 0b100)
#define CSR_SREG_TRBMPAM_EL1        CSR_SREG(0b11, 0b000, 0b1001, 0b1011, 0b101)
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
#define CSR_SREG_TRCITECR_EL1       CSR_SREG(0b11, 0b000, 0b0001, 0b0010, 0b011)
#define CSR_SREG_TRCITECR_EL12      CSR_SREG(0b11, 0b101, 0b0001, 0b0010, 0b011)
#define CSR_SREG_TRCITECR_EL2       CSR_SREG(0b11, 0b100, 0b0001, 0b0010, 0b011)
#define CSR_SREG_TRCITEEDCR         CSR_SREG(0b10, 0b001, 0b0000, 0b0010, 0b001)
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
#define CSR_SREG_TRFCR_EL1          CSR_SREG(0b11, 0b000, 0b0001, 0b0010, 0b001)
#define CSR_SREG_TRFCR_EL12         CSR_SREG(0b11, 0b101, 0b0001, 0b0010, 0b001)
#define CSR_SREG_TRFCR_EL2          CSR_SREG(0b11, 0b100, 0b0001, 0b0010, 0b001)
#define CSR_SREG_TTBR0_EL1          CSR_SREG(0b11, 0b000, 0b0010, 0b0000, 0b000)
#define CSR_SREG_TTBR0_EL12         CSR_SREG(0b11, 0b101, 0b0010, 0b0000, 0b000)
#define CSR_SREG_TTBR0_EL2          CSR_SREG(0b11, 0b100, 0b0010, 0b0000, 0b000)
#define CSR_SREG_TTBR0_EL3          CSR_SREG(0b11, 0b110, 0b0010, 0b0000, 0b000)
#define CSR_SREG_TTBR1_EL1          CSR_SREG(0b11, 0b000, 0b0010, 0b0000, 0b001)
#define CSR_SREG_TTBR1_EL12         CSR_SREG(0b11, 0b101, 0b0010, 0b0000, 0b001)
#define CSR_SREG_TTBR1_EL2          CSR_SREG(0b11, 0b100, 0b0010, 0b0000, 0b001)
#define CSR_SREG_UAO                CSR_SREG(0b11, 0b000, 0b0100, 0b0010, 0b100)
#define CSR_SREG_VBAR_EL1           CSR_SREG(0b11, 0b000, 0b1100, 0b0000, 0b000)
#define CSR_SREG_VBAR_EL12          CSR_SREG(0b11, 0b101, 0b1100, 0b0000, 0b000)
#define CSR_SREG_VBAR_EL2           CSR_SREG(0b11, 0b100, 0b1100, 0b0000, 0b000)
#define CSR_SREG_VBAR_EL3           CSR_SREG(0b11, 0b110, 0b1100, 0b0000, 0b000)
#define CSR_SREG_VDISR_EL2          CSR_SREG(0b11, 0b100, 0b1100, 0b0001, 0b001)
#define CSR_SREG_VMECID_A_EL2       CSR_SREG(0b11, 0b100, 0b1010, 0b1001, 0b001)
#define CSR_SREG_VMECID_P_EL2       CSR_SREG(0b11, 0b100, 0b1010, 0b1001, 0b000)
#define CSR_SREG_VMPIDR_EL2         CSR_SREG(0b11, 0b100, 0b0000, 0b0000, 0b101)
#define CSR_SREG_VNCR_EL2           CSR_SREG(0b11, 0b100, 0b0010, 0b0010, 0b000)
#define CSR_SREG_VPIDR_EL2          CSR_SREG(0b11, 0b100, 0b0000, 0b0000, 0b000)
#define CSR_SREG_VSESR_EL2          CSR_SREG(0b11, 0b100, 0b0101, 0b0010, 0b011)
#define CSR_SREG_VSTCR_EL2          CSR_SREG(0b11, 0b100, 0b0010, 0b0110, 0b010)
#define CSR_SREG_VSTTBR_EL2         CSR_SREG(0b11, 0b100, 0b0010, 0b0110, 0b000)
#define CSR_SREG_VTCR_EL2           CSR_SREG(0b11, 0b100, 0b0010, 0b0001, 0b010)
#define CSR_SREG_VTTBR_EL2          CSR_SREG(0b11, 0b100, 0b0010, 0b0001, 0b000)
#define CSR_SREG_ZCR_EL1            CSR_SREG(0b11, 0b000, 0b0001, 0b0010, 0b000)
#define CSR_SREG_ZCR_EL12           CSR_SREG(0b11, 0b101, 0b0001, 0b0010, 0b000)
#define CSR_SREG_ZCR_EL2            CSR_SREG(0b11, 0b100, 0b0001, 0b0010, 0b000)
#define CSR_SREG_ZCR_EL3            CSR_SREG(0b11, 0b110, 0b0001, 0b0010, 0b000)

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
#if defined(__linux__) ||  defined(__APPLE__)
    // gcc/clang syntax
    #define csr_msr(sreg,value) asm(_CSR_DEFINE_GPR ".inst 0xd5000000|(" CSR_STRINGIFY(sreg) ")|(.csr_gpr_%0)" : : "r" (value))
    #define csr_mrs(result,sreg) asm(_CSR_DEFINE_GPR ".inst 0xd5200000|(" CSR_STRINGIFY(sreg) ")|(.csr_gpr_%0)" : "=r" (result))
#elif defined(WINDOWS)
    // msvc syntax
    #define csr_msr(sreg,value) _WriteStatusReg((sreg), (value))
    #define csr_mrs(result,sreg) ((result) = _ReadStatusReg(sreg))
#endif

//
// Macros to generate PACxx and AUTxx instructions.
// This method works at all levels of architecture, including when PAuth is not
// supported by the assembler. Since these instructions are in the HINT range,
// executing them before Armv8.3 is a NOP.
//
#if defined(__linux__) ||  defined(__APPLE__)
    // gcc/clang syntax
    #define csr_pacia(data,mod) asm(_CSR_DEFINE_GPR ".inst 0xdac10000|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "+r" (data) : "r" (mod))
    #define csr_pacib(data,mod) asm(_CSR_DEFINE_GPR ".inst 0xdac10400|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "+r" (data) : "r" (mod))
    #define csr_pacda(data,mod) asm(_CSR_DEFINE_GPR ".inst 0xdac10800|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "+r" (data) : "r" (mod))
    #define csr_pacdb(data,mod) asm(_CSR_DEFINE_GPR ".inst 0xdac10c00|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "+r" (data) : "r" (mod))
    #define csr_autia(data,mod) asm(_CSR_DEFINE_GPR ".inst 0xdac11000|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "+r" (data) : "r" (mod))
    #define csr_autib(data,mod) asm(_CSR_DEFINE_GPR ".inst 0xdac11400|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "+r" (data) : "r" (mod))
    #define csr_autda(data,mod) asm(_CSR_DEFINE_GPR ".inst 0xdac11800|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "+r" (data) : "r" (mod))
    #define csr_autdb(data,mod) asm(_CSR_DEFINE_GPR ".inst 0xdac11c00|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "+r" (data) : "r" (mod))
    #define csr_pacga(result,data,mod) asm(_CSR_DEFINE_GPR ".inst 0x9ac03000|((.csr_gpr_%2)<<16)|((.csr_gpr_%1)<<5)|(.csr_gpr_%0)" : "=r" (result) : "r" (data), "r" (mod))
#elif defined(_MSC_VER)
    // msvc does not support inline asm and has no intrinsics for PAC => need an external .asm module
    __int64 csr_pacia_helper(__int64, __int64);
    __int64 csr_pacib_helper(__int64, __int64);
    __int64 csr_pacda_helper(__int64, __int64);
    __int64 csr_pacdb_helper(__int64, __int64);
    __int64 csr_autia_helper(__int64, __int64);
    __int64 csr_autib_helper(__int64, __int64);
    __int64 csr_autda_helper(__int64, __int64);
    __int64 csr_autdb_helper(__int64, __int64);
    __int64 csr_pacga_helper(__int64, __int64);
    #define csr_pacia(data,mod) ((data) = csr_pacia_helper((data), (mod)))
    #define csr_pacib(data,mod) ((data) = csr_pacib_helper((data), (mod)))
    #define csr_pacda(data,mod) ((data) = csr_pacda_helper((data), (mod)))
    #define csr_pacdb(data,mod) ((data) = csr_pacdb_helper((data), (mod)))
    #define csr_autia(data,mod) ((data) = csr_autia_helper((data), (mod)))
    #define csr_autib(data,mod) ((data) = csr_autib_helper((data), (mod)))
    #define csr_autda(data,mod) ((data) = csr_autda_helper((data), (mod)))
    #define csr_autdb(data,mod) ((data) = csr_autdb_helper((data), (mod)))
    #define csr_pacga(result,data,mod) ((result) = csr_pacga_helper((data), (mod)))
#endif


//----------------------------------------------------------------------------
// This code in used in the kernel only (Linux or macOS).
// All functions are typically called only once in the kernel module.
//----------------------------------------------------------------------------

#if defined(KERNEL)

// Define a few CPU features which are required to access some registers.
#define FEAT_PAC      0x00000001
#define FEAT_PACGA    0x00000002
#define FEAT_BTI      0x00000004
#define FEAT_RME      0x00000008
#define FEAT_CSV2_2   0x00000010
#define FEAT_RNG      0x00000020
#define FEAT_SVE      0x00000040
#define FEAT_SME      0x00000080
#define FEAT_ETE      0x00000100
#define FEAT_PMUv3p4  0x00000200
#define FEAT_TCR2     0x00000400
#define FEAT_SCTLR2   0x00000800
#define FEAT_AIE      0x00001000
#define FEAT_S1PIE    0x00002000
#define FEAT_SPE      0x00004000

// Get the CPU features. Typically called once on module initialization.
static int csr_get_cpu_features(void)
{
    csr_u64_t pfr0, pfr1, dfr0, isar0, isar1, isar2, mmfr3;
    csr_mrs(pfr0, CSR_SREG_ID_AA64PFR0_EL1);
    csr_mrs(pfr1, CSR_SREG_ID_AA64PFR1_EL1);
    csr_mrs(dfr0, CSR_SREG_ID_AA64DFR0_EL1);
    csr_mrs(isar0, CSR_SREG_ID_AA64ISAR0_EL1);
    csr_mrs(isar1, CSR_SREG_ID_AA64ISAR1_EL1);
    csr_mrs(isar2, CSR_SREG_ID_AA64ISAR2_EL1);
    csr_mrs(mmfr3, CSR_SREG_ID_AA64MMFR3_EL1);
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
           (csr_has_tcr2(mmfr3) ? FEAT_TCR2 : 0) |
           (csr_has_sctlr2(mmfr3) ? FEAT_SCTLR2 : 0) |
           (csr_has_aie(mmfr3) ? FEAT_AIE : 0) |
           (csr_has_s1pie(mmfr3) ? FEAT_S1PIE : 0) |
           (csr_has_spe(dfr0) ? FEAT_SPE : 0);
}

// Set the value of a single register or pair of registers.
// Return values: 0=success, 1=unknown register, 2=CPU feature missing
static int csr_set_register(int regid, const csr_pair_t* value, int cpu_features)
{
#define _check(features) if (((features) & cpu_features) != (features)) return 2
#define _setreg(id, sreg, features) \
    case (id):                      \
        _check(features);           \
        csr_msr(sreg, value->low);  \
        return 0
#define _setreg2(id, sreg_high, sreg_low, features) \
    case (id):                                      \
        _check(features);                           \
        csr_msr(sreg_high, value->high);            \
        csr_msr(sreg_low, value->low);              \
        return 0

    switch (regid) {
        _setreg(CSR_REGID_TPIDRRO_EL0,   CSR_SREG_TPIDRRO_EL0, 0);
        _setreg(CSR_REGID_TPIDR_EL0,     CSR_SREG_TPIDR_EL0, 0);
        _setreg(CSR_REGID_TPIDR_EL1,     CSR_SREG_TPIDR_EL1, 0);
        _setreg(CSR_REGID_SCTLR_EL1,     CSR_SREG_SCTLR_EL1, 0);
        _setreg(CSR_REGID_SCTLR2_EL1,    CSR_SREG_SCTLR2_EL1, FEAT_SCTLR2);
        _setreg(CSR_REGID_SCXTNUM_EL0,   CSR_SREG_SCXTNUM_EL0, FEAT_CSV2_2);
        _setreg(CSR_REGID_SCXTNUM_EL1,   CSR_SREG_SCXTNUM_EL1, FEAT_CSV2_2);
        _setreg(CSR_REGID_CNTKCTL_EL1,   CSR_SREG_CNTKCTL_EL1, 0);
        _setreg2(CSR_REGID2_APIAKEY_EL1, CSR_SREG_APIAKEYHI_EL1, CSR_SREG_APIAKEYLO_EL1, FEAT_PAC);
        _setreg2(CSR_REGID2_APIBKEY_EL1, CSR_SREG_APIBKEYHI_EL1, CSR_SREG_APIBKEYLO_EL1, FEAT_PAC);
        _setreg2(CSR_REGID2_APDAKEY_EL1, CSR_SREG_APDAKEYHI_EL1, CSR_SREG_APDAKEYLO_EL1, FEAT_PAC);
        _setreg2(CSR_REGID2_APDBKEY_EL1, CSR_SREG_APDBKEYHI_EL1, CSR_SREG_APDBKEYLO_EL1, FEAT_PAC);
        _setreg2(CSR_REGID2_APGAKEY_EL1, CSR_SREG_APGAKEYHI_EL1, CSR_SREG_APGAKEYLO_EL1, FEAT_PACGA);
        default: return 1;
    }

#undef _check
#undef _setreg
#undef _setreg2
}

// Get the value of a single register or pair of registers.
// Return values: 0=success, 1=unknown register, 2=CPU feature missing
static int csr_get_register(int regid, csr_pair_t* value, int cpu_features)
{
#define _check(features) if (((features) & cpu_features) != (features)) return 2
#define _getreg(id, sreg, features) \
    case (id):                      \
        _check(features);           \
        csr_mrs(value->low, sreg);  \
        return 0
#define _getreg2(id, sreg_high, sreg_low, features) \
    case (id):                                      \
        _check(features);                           \
        csr_mrs(value->high, sreg_high);            \
        csr_mrs(value->low, sreg_low);              \
        return 0

    switch (regid) {
        _getreg(CSR_REGID_ID_AA64PFR0_EL1,  CSR_SREG_ID_AA64PFR0_EL1, 0);
        _getreg(CSR_REGID_ID_AA64PFR1_EL1,  CSR_SREG_ID_AA64PFR1_EL1, 0);
        _getreg(CSR_REGID_ID_AA64PFR2_EL1,  CSR_SREG_ID_AA64PFR2_EL1, 0);
        _getreg(CSR_REGID_ID_AA64ISAR0_EL1, CSR_SREG_ID_AA64ISAR0_EL1, 0);
        _getreg(CSR_REGID_ID_AA64ISAR1_EL1, CSR_SREG_ID_AA64ISAR1_EL1, 0);
        _getreg(CSR_REGID_ID_AA64ISAR2_EL1, CSR_SREG_ID_AA64ISAR2_EL1, 0);
        _getreg(CSR_REGID_TCR_EL1,          CSR_SREG_TCR_EL1, 0);
        _getreg(CSR_REGID_TCR2_EL1,         CSR_SREG_TCR2_EL1, FEAT_TCR2);
        _getreg(CSR_REGID_MIDR_EL1,         CSR_SREG_MIDR_EL1, 0);
        _getreg(CSR_REGID_MPIDR_EL1,        CSR_SREG_MPIDR_EL1, 0);
        _getreg(CSR_REGID_REVIDR_EL1,       CSR_SREG_REVIDR_EL1, 0);
        _getreg(CSR_REGID_TPIDRRO_EL0,      CSR_SREG_TPIDRRO_EL0, 0);
        _getreg(CSR_REGID_TPIDR_EL0,        CSR_SREG_TPIDR_EL0, 0);
        _getreg(CSR_REGID_TPIDR_EL1,        CSR_SREG_TPIDR_EL1, 0);
        _getreg(CSR_REGID_SCXTNUM_EL0,      CSR_SREG_SCXTNUM_EL0, FEAT_CSV2_2);
        _getreg(CSR_REGID_SCXTNUM_EL1,      CSR_SREG_SCXTNUM_EL1, FEAT_CSV2_2);
        _getreg(CSR_REGID_SCTLR_EL1,        CSR_SREG_SCTLR_EL1, 0);
        _getreg(CSR_REGID_SCTLR2_EL1,       CSR_SREG_SCTLR2_EL1, FEAT_SCTLR2);
        _getreg(CSR_REGID_HCR_EL2,          CSR_SREG_HCR_EL2, 0);
        _getreg(CSR_REGID_RNDR,             CSR_SREG_RNDR, FEAT_RNG);
        _getreg(CSR_REGID_RNDRRS,           CSR_SREG_RNDRRS, FEAT_RNG);
        _getreg(CSR_REGID_SCR_EL3,          CSR_SREG_SCR_EL3, 0);
        _getreg(CSR_REGID_ID_AA64MMFR0_EL1, CSR_SREG_ID_AA64MMFR0_EL1, 0);
        _getreg(CSR_REGID_ID_AA64MMFR1_EL1, CSR_SREG_ID_AA64MMFR1_EL1, 0);
        _getreg(CSR_REGID_ID_AA64MMFR2_EL1, CSR_SREG_ID_AA64MMFR2_EL1, 0);
        _getreg(CSR_REGID_ID_AA64MMFR3_EL1, CSR_SREG_ID_AA64MMFR3_EL1, 0);
        _getreg(CSR_REGID_ID_AA64MMFR4_EL1, CSR_SREG_ID_AA64MMFR4_EL1, 0);
        _getreg(CSR_REGID_ID_AA64ZFR0_EL1,  CSR_SREG_ID_AA64ZFR0_EL1, FEAT_SVE);
        _getreg(CSR_REGID_ID_AA64SMFR0_EL1, CSR_SREG_ID_AA64SMFR0_EL1, FEAT_SME);
        _getreg(CSR_REGID_ID_AA64AFR0_EL1,  CSR_SREG_ID_AA64AFR0_EL1, 0);
        _getreg(CSR_REGID_ID_AA64AFR1_EL1,  CSR_SREG_ID_AA64AFR1_EL1, 0);
        _getreg(CSR_REGID_ID_AA64DFR0_EL1,  CSR_SREG_ID_AA64DFR0_EL1, 0);
        _getreg(CSR_REGID_ID_AA64DFR1_EL1,  CSR_SREG_ID_AA64DFR1_EL1, 0);
        _getreg(CSR_REGID_TRCDEVARCH,       CSR_SREG_TRCDEVARCH, FEAT_ETE);
        _getreg(CSR_REGID_PMMIR_EL1,        CSR_SREG_PMMIR_EL1, FEAT_PMUv3p4);
        _getreg(CSR_REGID_CTR_EL0,          CSR_SREG_CTR_EL0, 0);
        _getreg(CSR_REGID_TTBR0_EL1,        CSR_SREG_TTBR0_EL1, 0);
        _getreg(CSR_REGID_TTBR1_EL1,        CSR_SREG_TTBR1_EL1, 0);
        _getreg(CSR_REGID_MAIR_EL1,         CSR_SREG_MAIR_EL1, 0);
        _getreg(CSR_REGID_MAIR2_EL1,        CSR_SREG_MAIR2_EL1, FEAT_AIE);
        _getreg(CSR_REGID_PIR_EL1,          CSR_SREG_PIR_EL1, FEAT_S1PIE);
        _getreg(CSR_REGID_PIRE0_EL1,        CSR_SREG_PIRE0_EL1, FEAT_S1PIE);
        _getreg(CSR_REGID_ID_ISAR0_EL1,     CSR_SREG_ID_ISAR0_EL1, 0);
        _getreg(CSR_REGID_ID_ISAR1_EL1,     CSR_SREG_ID_ISAR1_EL1, 0);
        _getreg(CSR_REGID_ID_ISAR2_EL1,     CSR_SREG_ID_ISAR2_EL1, 0);
        _getreg(CSR_REGID_ID_ISAR3_EL1,     CSR_SREG_ID_ISAR3_EL1, 0);
        _getreg(CSR_REGID_ID_ISAR4_EL1,     CSR_SREG_ID_ISAR4_EL1, 0);
        _getreg(CSR_REGID_ID_ISAR5_EL1,     CSR_SREG_ID_ISAR5_EL1, 0);
        _getreg(CSR_REGID_ID_ISAR6_EL1,     CSR_SREG_ID_ISAR6_EL1, 0);
        _getreg(CSR_REGID_ID_MMFR0_EL1,     CSR_SREG_ID_MMFR0_EL1, 0);
        _getreg(CSR_REGID_ID_MMFR1_EL1,     CSR_SREG_ID_MMFR1_EL1, 0);
        _getreg(CSR_REGID_ID_MMFR2_EL1,     CSR_SREG_ID_MMFR2_EL1, 0);
        _getreg(CSR_REGID_ID_MMFR3_EL1,     CSR_SREG_ID_MMFR3_EL1, 0);
        _getreg(CSR_REGID_ID_MMFR4_EL1,     CSR_SREG_ID_MMFR4_EL1, 0);
        _getreg(CSR_REGID_ID_MMFR5_EL1,     CSR_SREG_ID_MMFR5_EL1, 0);
        _getreg(CSR_REGID_ID_PFR0_EL1,      CSR_SREG_ID_PFR0_EL1, 0);
        _getreg(CSR_REGID_ID_PFR1_EL1,      CSR_SREG_ID_PFR1_EL1, 0);
        _getreg(CSR_REGID_ID_PFR2_EL1,      CSR_SREG_ID_PFR2_EL1, 0);
        _getreg(CSR_REGID_PMSIDR_EL1,       CSR_SREG_PMSIDR_EL1, FEAT_SPE);
        _getreg(CSR_REGID_CNTKCTL_EL1,      CSR_SREG_CNTKCTL_EL1, 0);
        _getreg2(CSR_REGID2_APIAKEY_EL1,    CSR_SREG_APIAKEYHI_EL1, CSR_SREG_APIAKEYLO_EL1, FEAT_PAC);
        _getreg2(CSR_REGID2_APIBKEY_EL1,    CSR_SREG_APIBKEYHI_EL1, CSR_SREG_APIBKEYLO_EL1, FEAT_PAC);
        _getreg2(CSR_REGID2_APDAKEY_EL1,    CSR_SREG_APDAKEYHI_EL1, CSR_SREG_APDAKEYLO_EL1, FEAT_PAC);
        _getreg2(CSR_REGID2_APDBKEY_EL1,    CSR_SREG_APDBKEYHI_EL1, CSR_SREG_APDBKEYLO_EL1, FEAT_PAC);
        _getreg2(CSR_REGID2_APGAKEY_EL1,    CSR_SREG_APGAKEYHI_EL1, CSR_SREG_APGAKEYLO_EL1, FEAT_PACGA);
        default: return 1;
    }

#undef _check
#undef _getreg
#undef _getreg2
}

// Execute a PACxx or AUTxx instruction.
// Return values: 0=success, 1=unknown instruction.
static int csr_exec_instr(int instr, csr_instr_t* args)
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

#if defined(__cplusplus)
}
#endif

#endif // CPUSYSREGS_H
