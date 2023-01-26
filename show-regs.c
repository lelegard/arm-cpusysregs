//----------------------------------------------------------------------------
// Userland application to display the Arm64 CPU system registers.
//----------------------------------------------------------------------------

#include "cpusysregs.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define ARRAYSIZE(a) ((sizeof(a) / sizeof(*(a))) / (size_t)(!(sizeof(a) % sizeof(*(a)))))


//----------------------------------------------------------------------------
// Description of Arm64 system registers using the "ID feature" scheme.
// See the Arm Architecture Reference Manual, section D17.1.3.
//----------------------------------------------------------------------------

// List of ID registers:
// — The AArch32 Auxiliary Feature register ID_AFR0_EL1.
// — The AArch32 Processor Feature registers ID_PFR0_EL1 and ID_PFR1_EL1.
// — The AArch32 Debug Feature register ID_DFR0_EL1.
// — The AArch32 Memory Model Feature registers ID_MMFR0_EL1, ID_MMFR1_EL1,
//   ID_MMFR2_EL1, ID_MMFR3_EL1, and ID_MMFR4_EL1.
// — The AArch32 Instruction Set Attribute registers ID_ISAR0_EL1, ID_ISAR1_EL1,
//   ID_ISAR2_EL1, ID_ISAR3_EL1, ID_ISAR4_EL1, and ID_ISAR5_EL1.
// — The AArch32 Media and VFP Feature registers MVFR0_EL1, MVFR1_EL1, and MVFR2_EL1.
// - The AArch64 Auxiliary Feature registers ID_AA64AFR0_EL1 and ID_AA64AFR1_EL1.
// - The AArch64 Processor Feature registers ID_AA64PFR0_EL1 and ID_AA64PFR1_EL1.
// - The AArch64 Debug Feature registers ID_AA64DFR0_EL1 and ID_AA64DFR1_EL1.
// - The AArch64 Memory Model Feature registers ID_AA64MMFR0_EL1, ID_AA64MMFR1_EL1,
//   and ID_AA64MMFR2_EL1.
// - The AArch64 Instruction Set Attribute registers ID_AA64ISAR0_EL1 and ID_AA64ISAR1_EL1.

// Description of one value in a bitfield in a register.
typedef struct {
    csr_u64_t   value;
    const char* name;
} name_t;

// Description of one bit-field in a register.
typedef struct {
    const char* name;       // bitfield name
    int         msb;        // most significant bit index
    int         lsb;        // least significant bit index
    name_t      values[20]; // known values, end with a NULL name
} bitfield_t;

// Description of one register with bitfields.
typedef struct {
    const char* name;       // register name
    const char* section;    // section in Arm arch ref manual
    size_t      offset;     // offset in bytes in structure csr_registers_t
    bitfield_t  fields[20]; // known bitfields
} id_register_t;

// Descriptions of registers which are returned by the kernel module. End with a NULL name.
static const id_register_t all_id_registers[] = {
    {
        "ID_AA64PFR0_EL1", "D17.2.67", offsetof(csr_registers_t, id_aa64pfr0_el1),
        {
            {"CSV3",    63, 60, {{0, "undefined"}, {1, "safe"}, {0, NULL}}},
            {"CSV2",    59, 56, {{0, "none"}, {1, "CSV2"}, {2, "CSV2_2"}, {3, "CSV2_3"}, {0, NULL}}},
            {"RME",     55, 52, {{0, "none"}, {1, "RMEv1"}, {0, NULL}}},
            {"DIT",     51, 48, {{0, "none"}, {1, "DIT"}, {0, NULL}}},
            {"AMU",     47, 44, {{0, "none"}, {1, "AMUv1p1"}, {0, NULL}}},
            {"MPAM",    43, 40, {{0, "v0"}, {1, "v1"}, {0, NULL}}},
            {"SEL2",    39, 36, {{0, "none"}, {1, "Secure EL2"}, {0, NULL}}},
            {"SVE",     35, 32, {{0, "none"}, {1, "SVE"}, {0, NULL}}},
            {"RAS",     31, 28, {{0, "none"}, {1, "RAS"}, {2, "RASv1p1"}, {0, NULL}}},
            {"GIC",     27, 24, {{0, "none"}, {1, "3.0+4.0"}, {3, "4.1"}, {0, NULL}}},
            {"AdvSIMD", 23, 20, {{0, "basic"}, {1, "basic+FP16"}, {15, "none"}, {0, NULL}}},
            {"FP",      19, 16, {{0, "FP"}, {1, "FP+FP16"}, {15, "none"}, {0, NULL}}},
            {"EL3",     15, 12, {{0, "none"}, {1, "AArch64-only"}, {2, "AArch64+32"}, {0, NULL}}},
            {"EL2",     11,  8, {{0, "none"}, {1, "AArch64-only"}, {2, "AArch64+32"}, {0, NULL}}},
            {"EL2",      7,  4, {{1, "AArch64-only"}, {2, "AArch64+32"}, {0, NULL}}},
            {"EL0",      3,  0, {{1, "AArch64-only"}, {2, "AArch64+32"}, {0, NULL}}},
            {NULL}
        }
    },
    {
        "ID_AA64PFR1_EL1", "D17.2.68", offsetof(csr_registers_t, id_aa64pfr1_el1),
        {
            {"NMI",       39, 36, {{0, "none"}, {1, "NMI"}, {0, NULL}}},
            {"CSV2_frac", 35, 32, {{0, "none"}, {1, "CSV2_1p1"}, {2, "CSV2_1p2"}, {0, NULL}}},
            {"RNDR_trap", 31, 28, {{0, "none"}, {1, "RNG_TRAP"}, {0, NULL}}},
            {"SME",       27, 24, {{0, "none"}, {1, "SME"}, {0, NULL}}},
            {"MPAM_frac", 19, 16, {{0, "v.0"}, {1, "v.1"}, {0, NULL}}},
            {"RAS_frac",  15, 12, {{0, "none"}, {1, "VARv1p1"}, {0, NULL}}},
            {"MTE",       11,  8, {{0, "none"}, {1, "MTE"}, {2, "MTE2"}, {3, "MTE3"}, {0, NULL}}},
            {"SSBS",       7,  4, {{0, "none"}, {1, "SSBS"}, {2, "SSBS2"}, {0, NULL}}},
            {"BT",         3,  0, {{0, "none"}, {1, "BTI"}, {0, NULL}}},
            {NULL}
        }
    },
    {
        "ID_AA64ISAR0_EL1", "D17.2.61", offsetof(csr_registers_t, id_aa64isar0_el1),
        {
            {"RNDR",   63, 60, {{0, "none"}, {1, "RNG"}, {0, NULL}}},
            {"TLB",    59, 56, {{0, "none"}, {1, "TLBIOS"}, {2, "TLBIOS+TLBIRANGE"}, {0, NULL}}},
            {"TS",     55, 52, {{0, "none"}, {1, "FlagM"}, {2, "FlagM2"}, {0, NULL}}},
            {"FHM",    51, 48, {{0, "none"}, {1, "FHM"}, {0, NULL}}},
            {"DP",     47, 44, {{0, "none"}, {1, "DotProd"}, {0, NULL}}},
            {"SM4",    43, 40, {{0, "none"}, {1, "SM4"}, {0, NULL}}},
            {"SM3",    39, 36, {{0, "none"}, {1, "SM3"}, {0, NULL}}},
            {"SHA3",   35, 32, {{0, "none"}, {1, "SHA3"}, {0, NULL}}},
            {"RDM",    31, 28, {{0, "none"}, {1, "RDM"}, {0, NULL}}},
            {"TME",    27, 24, {{0, "none"}, {1, "TME"}, {0, NULL}}},
            {"Atomic", 23, 20, {{0, "none"}, {2, "LSE"}, {0, NULL}}},
            {"CRC32",  19, 16, {{0, "none"}, {1, "CRC32"}, {0, NULL}}},
            {"SHA2",   15, 12, {{0, "none"}, {1, "SHA256"}, {2, "SHA256+SHA512"}, {0, NULL}}},
            {"SHA1",   11,  8, {{0, "none"}, {1, "SHA1"}, {0, NULL}}},
            {"AES",     7,  4, {{0, "none"}, {1, "AES"}, {2, "AES+PMULL"}, {0, NULL}}},
            {NULL}
        }
    },
    {
        "ID_AA64ISAR1_EL1", "D17.2.62", offsetof(csr_registers_t, id_aa64isar1_el1),
        {
            {"LS64",    63, 60, {{0, "none"}, {1, "LS64"}, {2, "LS64+LS64_V"}, {3, "LS64+LS64_V+LS64_ACCDATA"}, {0, NULL}}},
            {"XS",      59, 56, {{0, "none"}, {1, "XS"}, {0, NULL}}},
            {"I8MM",    55, 52, {{0, "none"}, {1, "I8MM"}, {0, NULL}}},
            {"DGH",     51, 48, {{0, "none"}, {1, "BF16"}, {2, "EBF16"}, {0, NULL}}},
            {"BF16",    47, 44, {{0, "none"}, {1, "AMUv1p1"}, {0, NULL}}},
            {"SPECRES", 43, 40, {{0, "none"}, {1, "SHA256v1"}, {0, NULL}}},
            {"SB",      39, 36, {{0, "none"}, {1, "SB"}, {0, NULL}}},
            {"FRINTTS", 35, 32, {{0, "none"}, {1, "FRINTTS"}, {0, NULL}}},
            {"GPI",     31, 28, {{0, "none"}, {1, "PACIMP"}, {0, NULL}}},
            {"GPA",     27, 24, {{0, "none"}, {1, "PACQARMA5"}, {0, NULL}}},
            {"LRCPC",   23, 20, {{0, "none"}, {1, "LRCPC"}, {2, "LRCPC2"}, {0, NULL}}},
            {"FCMA",    19, 16, {{0, "none"}, {1, "FCMA"}, {0, NULL}}},
            {"JSCVT",   15, 12, {{0, "none"}, {1, "JSCVT"}, {0, NULL}}},
            {"API",     11,  8, {{0, "none"}, {1, "IMP PAuth"}, {2, "IMP PAuth+EPAC"}, {3, "IMP PAuth+EPAC+PAuth2"},
                                 {4, "IMP PAuth+EPAC+PAuth2+FPAC"}, {5, "IMP PAuth+EPAC+PAuth2+FPAC+FPACCOMBINE"}, {0, NULL}}},
            {"APA",      7,  4, {{0, "none"}, {1, "QARMA5 PAuth"}, {2, "QARMA5 PAuth+EPAC"}, {3, "QARMA5 PAuth+EPAC+PAuth2"},
                                 {4, "QARMA5 PAuth+EPAC+PAuth2+FPAC"}, {5, "QARMA5 PAuth+EPAC+PAuth2+FPAC+FPACCOMBINE"}, {0, NULL}}},
            {"DPB",      3,  0, {{0, "none"}, {1, "DPB"}, {2, "DPB2"}, {0, NULL}}},
            {NULL}
        }
    },
    {
        "ID_AA64ISAR2_EL1", "D17.2.63", offsetof(csr_registers_t, id_aa64isar2_el1),
        {
            {"PAC_frac", 27, 24, {{0, "none"}, {1, "ConstPACField"}, {0, NULL}}},
            {"BC",       23, 20, {{0, "none"}, {1, "HBC"}, {0, NULL}}},
            {"MOPS",     19, 16, {{0, "none"}, {1, "MOPS"}, {0, NULL}}},
            {"APA3",     15, 12, {{0, "none"}, {1, "QARMA3 PAuth"}, {2, "QARMA3 PAuth+EPAC"}, {3, "QARMA3 PAuth+EPAC+PAuth2"},
                                 {4, "QARMA3 PAuth+EPAC+PAuth2+FPAC"}, {5, "QARMA3 PAuth+EPAC+PAuth2+FPAC+FPACCOMBINE"}, {0, NULL}}},
            {"GPA3",     11,  8, {{0, "none"}, {1, "PACQARMA3"}, {0, NULL}}},
            {"RPRES",     7,  4, {{0, "none"}, {1, "RPRES"}, {0, NULL}}},
            {"WFxT",      3,  0, {{0, "none"}, {1, "WFxT"}, {0, NULL}}},
            {NULL}
        }
    },
};


//----------------------------------------------------------------------------
// Display all registers.
//----------------------------------------------------------------------------

static void print_all_registers(const csr_registers_t* regs)                                   
{
    // Loop on all supported registers.
    for (const id_register_t* desc = all_id_registers; desc < all_id_registers + ARRAYSIZE(all_id_registers); desc++) {

        // Extract the register value from the structure.
        const csr_u64_t regval = *(const csr_u64_t*)((const char*)regs + desc->offset);

        // Print the register content as a suite of 4-bit binary values.
        printf("\n%s:", desc->name);
        for (int shift = 60; shift >= 0; shift -= 4) {
            const int n = (int)(regval >> shift);
            printf("%s%d%d%d%d", shift == 28 ? " - " : " ", (n >> 3) & 1, (n >> 2) & 1, (n >> 1) & 1, n & 1);
        }
        printf("\n\n  Arch. Ref. Manual section %s\n", desc->section);

        // Print the various bit fields.
        for (const bitfield_t* bf = desc->fields; bf < desc->fields + ARRAYSIZE(desc->fields) && bf->name != NULL; bf++) {
            // Value of the bitfield.
            const csr_u64_t bfval = (regval << (63 - bf->msb)) >> (63 - bf->msb + bf->lsb);
            // Look for a name for this value.
            const char* name = NULL;
            for (const name_t* nm = bf->values; nm < bf->values + ARRAYSIZE(bf->values) && nm->name != NULL && name == NULL; nm++) {
                if (nm->value == bfval) {
                    name = nm->name;
                }
            }
            // Print the bitfield description.
            const int hexwidth = (bf->msb - bf->lsb) / 4 + 1;
            printf("  %s: 0x%*llX (%s)\n", bf->name, hexwidth, bfval, name != NULL ? name : "reserved");
        }
    }
    printf("\n");
}


//----------------------------------------------------------------------------
// Program entry point
//----------------------------------------------------------------------------

int main(int argc, char* argv)
{
    // Open the pseudo-device for the kernel module.
    int fd = open(CSR_DEVICE_PATH, O_RDONLY);
    if (fd < 0) {
        perror(CSR_DEVICE_PATH);
        return EXIT_FAILURE;
    }

    // Read and display all system registers.
    csr_registers_t regs;
    memset(&regs, 0, sizeof(regs));
    if (ioctl(fd, CSR_IOCTL_GET_REGS, &regs) < 0) {
        perror("get regs");
        return EXIT_FAILURE;
    }
    print_all_registers(&regs);

    // Cleanup resources.
    close(fd);
    return EXIT_SUCCESS;
}
