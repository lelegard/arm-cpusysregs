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


//----------------------------------------------------------------------------
// Description of Arm64 system registers using the "ID feature" scheme.
// See the Arm Architecture Reference Manual, section D17.1.3.
//----------------------------------------------------------------------------

// List of ID registers:
// — The AArch32 Auxiliary Feature register ID_AFR0_EL1.
// — The AArch32 Processor Feature registers ID_PFR0_EL1 and ID_PFR1_EL1.
// — The AArch32 Debug Feature register ID_DFR0_EL1.
// — The AArch32 Memory Model Feature registers ID_MMFR0_EL1, ID_MMFR1_EL1, ID_MMFR2_EL1, ID_MMFR3_EL1, and ID_MMFR4_EL1.
// — The AArch32 Instruction Set Attribute registers ID_ISAR0_EL1, ID_ISAR1_EL1, ID_ISAR2_EL1, ID_ISAR3_EL1, ID_ISAR4_EL1, and ID_ISAR5_EL1.
// — The AArch32 Media and VFP Feature registers MVFR0_EL1, MVFR1_EL1, and MVFR2_EL1.
// - The AArch64 Auxiliary Feature registers ID_AA64AFR0_EL1 and ID_AA64AFR1_EL1.
// - The AArch64 Processor Feature registers ID_AA64PFR0_EL1 and ID_AA64PFR1_EL1.
// - The AArch64 Debug Feature registers ID_AA64DFR0_EL1 and ID_AA64DFR1_EL1.
// - The AArch64 Memory Model Feature registers ID_AA64MMFR0_EL1, ID_AA64MMFR1_EL1, and ID_AA64MMFR2_EL1.
// - The AArch64 Instruction Set Attribute registers ID_AA64ISAR0_EL1 and ID_AA64ISAR1_EL1.

// Description of one ID register.
typedef struct {
    const char* name;    // register name
    size_t      offset;  // offset in bytes in structure csr_registers_t
} id_reg_description_t;

// Descriptions of all ID system registers which are returned by the kernel module.
static const id_reg_description_t all_id_registers[] = {
    {"ID_AA64PFR0_EL1", offsetof(csr_registers_t, id_aa64pfr0_el1)},
    {"ID_AA64PFR1_EL1", offsetof(csr_registers_t, id_aa64pfr1_el1)},
    {"ID_AA64ISAR0_EL1", offsetof(csr_registers_t, id_aa64isar0_el1)},
    {"ID_AA64ISAR1_EL1", offsetof(csr_registers_t, id_aa64isar1_el1)},
    {"ID_AA64ISAR2_EL1", offsetof(csr_registers_t, id_aa64isar2_el1)},
    {NULL} // end of list
};


//----------------------------------------------------------------------------
// Display all ID registers.
//----------------------------------------------------------------------------

static void print_all_id_registers(const csr_registers_t* regs)                                   
{
    // Loop on all supported registers.
    for (const id_reg_description_t* desc = all_id_registers; desc->name != NULL; desc++) {

        // Extract the register value from the structure.
        const csr_u64_t value = *(const csr_u64_t*)((const char*)regs + desc->offset);

        // Print the register content as a suite of 4-bit binary values.
        printf("\n%s:", desc->name);
        for (int shift = 60; shift >= 0; shift -= 4) {
            const int n = (int)(value >> shift);
            printf("%s%d%d%d%d", shift == 28 ? " - " : " ", (n >> 3) & 1, (n >> 2) & 1, (n >> 1) & 1, n & 1);
        }
        printf("\n");
    }
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
    print_all_id_registers(&regs);

    // Cleanup resources.
    close(fd);
    return EXIT_SUCCESS;
}
