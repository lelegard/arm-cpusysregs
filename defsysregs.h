//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Definitions of Arm64 system registers and instructions to access them.
// Must be included in kernel module only.
//
//----------------------------------------------------------------------------

#if !defined(DEFSYSREGS_H)
#define DEFSYSREGS_H 1

//
// The system registers are described in section D17 of the Arm Architecture Reference Manual.
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
#define CSR_APIAKEYLO_EL1 CSR_SREG(3, 0, 2, 1, 0)
#define CSR_APIAKEYHI_EL1 CSR_SREG(3, 0, 2, 1, 1)
#define CSR_APIBKEYLO_EL1 CSR_SREG(3, 0, 2, 1, 2)
#define CSR_APIBKEYHI_EL1 CSR_SREG(3, 0, 2, 1, 3)
#define CSR_APDAKEYLO_EL1 CSR_SREG(3, 0, 2, 2, 0)
#define CSR_APDAKEYHI_EL1 CSR_SREG(3, 0, 2, 2, 1)
#define CSR_APDBKEYLO_EL1 CSR_SREG(3, 0, 2, 2, 2)
#define CSR_APDBKEYHI_EL1 CSR_SREG(3, 0, 2, 2, 3)
#define CSR_APGAKEYLO_EL1 CSR_SREG(3, 0, 2, 3, 0)
#define CSR_APGAKEYHI_EL1 CSR_SREG(3, 0, 2, 3, 1)

//
// Standard stringification macro (not so standard since we must define it again).
//
#define CSR_STRINGIFY_1(x) #x
#define CSR_STRINGIFY(x) CSR_STRINGIFY_1(x)

//
// The following macro is a trick to forge instructions with general-purpose registers (GPR),
// In an asm directive, argument references such as "%0" or "%1" are replaced by the compiler
// backed with some GPR names such as "w12" or "x24". To build the instruction code, we need
// to transform "w12" as 12 or "x24" as 24. To do that, we define all possible identifiers for
// all GPR in the form .csr_gpr_wNN or .csr_gpr_xNN. In an asm directive, we use .csr_gpr_%0,
// which will be replaced by .csr_gpr_x24 (if GPR x24 has been allocated), which will be
// replaced by 24. We also define xzr and wzr as x31 (zero register).
//
#define CSR_DEFINE_GPR              \
    ".irp num,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30\n" \
    ".equ .csr_gpr_x\\num, \\num\n" \
    ".equ .csr_gpr_w\\num, \\num\n" \
    ".endr\n"                       \
    ".equ .csr_gpr_xzr, 31\n"       \
    ".equ .csr_gpr_wzr, 31\n"

//
// Macros the read/write system registers by name.
// The corresponding register names must be known at all levels of architecture.
// Examples:
//    csr_u64_t r;
//    CSR_MRS_STR(r, "id_aa64pfr0_el1");
//    CSR_MSR_STR("id_aa64pfr0_el1", r);
//
#define CSR_MSR_STR(sreg,value)   asm("msr " sreg ", %0" : : "r" (value))
#define CSR_MRS_STR(result,sreg)  asm("mrs %0, " sreg : "=r" (result))

//
// Macros the read/write system registers by identifier.
// This method works at all levels of architecture.
// Examples:
//    csr_u64_t r;
//    CSR_MSR_NUM(CSR_APIAKEYHI_EL1, r);
//    CSR_MRS_NUM(r, CSR_APIAKEYHI_EL1);
//
#define CSR_MSR_NUM(sreg,value) \
    asm(CSR_DEFINE_GPR ".inst 0xd5000000|(" CSR_STRINGIFY((sreg)) ")|(.csr_gpr_%0)" : : "r" (value))

#define CSR_MRS_NUM(result,sreg) \
    asm(CSR_DEFINE_GPR ".inst 0xd5200000|(" CSR_STRINGIFY((sreg)) ")|(.csr_gpr_%0)" : "=r" (result))

#endif // DEFSYSREGS_H
