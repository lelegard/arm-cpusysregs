#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Pointer to an instruction:
typedef const uint32_t* instr_ptr_t;

int f(int x)
{
    printf("in f(%d)\n", x);
    return 0;
}

int main(int argc, char* argv[])
{
    // Verify that we were compiled with BTI, i.e, the first instruction in f() is a BTI.
    const instr_ptr_t f_instr = (instr_ptr_t)f;
    if ((*f_instr & 0xFFFFFF3F) != 0xD503241F) {
        printf("Not compiled with BTI, use -mbranch-protection=bti\n");
        return EXIT_FAILURE;
    }

    // Verify that the next instruction is the beginning of a standard function prolog: stp x29, x30, [sp, #-size]!
    if ((f_instr[1] & 0x7FC07FFF) != 0x29807BFD) {
        printf("warning: f() second instruction is %08x\n", f_instr[1]);
        printf("warning: expected \"stp x29, x30, [sp, #-size]!\", may give unpredictable results\n");
    }

    printf("start of main(), calling f(1)\n");
    f(1);
    printf("next call should fail if BTI is supported on this CPU\n");

    // call f(47), branching to next instruction after bti in f()
    // use assembly code to enforce an indirect call through BLR
    asm("mov w0, #47\n\t"
        "blr %x0\n\t"
        : : "r" (f_instr + 1) : "x0");

    printf("end of main()\n");
    return EXIT_SUCCESS;
}
