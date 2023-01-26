# Access Arm64 CPU system registers

The Arm64 architecture defines a large quantity of special system registers. Many of them are inaccessible from userland. When a system register name ends in `_EL1`, it is accessible only at EL1 (kernel mode). Similarly, system registers in `_EL2` are accessible only in hypervisor mode and `_EL3` in monitor mode.

Reading and writing system registers is done using the special instructions `MRS` and `MSR`, respectively. Trying to access a system register from an outer level results in an "illegal instruction" exception.

On Linux, there is a special feature in the kernel which allows a limited access to a few `_EL1` system registers from user mode. The kernel intecepts the `SIGILL` exception which results from the invalid access to a system register using an `MRS` instruction. If the requested system register is one of a few selected allowed registers, the kernel reads the system register and returns it to the process, as if the `MRS` instruction executed correctly. This is [explained in details here](https://www.kernel.org/doc/html/latest/arm64/cpu-feature-registers.html). As a general requirement, no sensitive security information is returned. In some cases, some parts of the register content are blacked out.

This is a Linux-only feature and it is limited to a few registers, or a subpart of them. This means that we are never really sure of what the physical register was.

This educational project provides a way to return the exact content of a few Arm64 registers to userland through a dedicated loadable kernel module. An application program is provided to display an analysis of the contents of these registers.

Warning: This project is for educational purpose only, for people wanting to increase their knowledge in the Arm64 architecture. Loading a custom kernel module may always have unexpected side effects, including security effects (the content of the system registers could be used to gain information on the system).

## Linux kernel module

The file `cpusysregs.c` contains the source code of the kernel module. The module name is `cpusysregs`. It creates a special device named `/dev/cpusysregs` which can be accessed from any userland process. It is not possible to read or write on this device. We can only send a few `ioctl()`. This is the way the system registers of the CPU are returned.

The kernel module interface is described in the file `cpusysregs.h`. It defines the structure `csr_registers_t` which is used to return the content of the selected system registers.

Usage instructions:
- `make module` : Build the kernel module. This is also part of the default `make`.
- `make load` : Load the kernel module. A `sudo` command is used.
- `make unload` : Unload the kernel module. A `sudo` command is used.

## Demo application

The C++ application `show-regs` reads the system registers from the kernel module and displays their content. Most system registers are structured using bit-field of various size and interpretation. They are all individually displayed.

## References

- [Arm Architecture Reference Manual for A-profile architecture](https://developer.arm.com/documentation/ddi0487/latest), nearly 12,000 pages...
