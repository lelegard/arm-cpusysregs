# Access Arm64 CPU system registers

The Arm64 architecture defines a large quantity of special system registers.
Many of them are inaccessible from userland. When a system register name ends in `_EL1`,
it is accessible only at EL1 (kernel mode). Similarly, system registers in `_EL2` are
accessible only in hypervisor mode and `_EL3` in monitor mode.

Reading and writing system registers is done using the special instructions `MRS` and `MSR`,
respectively. Trying to access a system register from an outer level results in an "illegal
instruction" exception.

On Linux, there is a special feature in the kernel which allows a limited access to
a few `_EL1` system registers from user mode. The kernel intercepts the `SIGILL` exception
which results from the invalid access to a system register using an `MRS` instruction.
If the requested system register is one of a few selected allowed registers, the kernel
reads the system register and returns it to the process, as if the `MRS` instruction
executed correctly.
This is [explained in details here](https://www.kernel.org/doc/html/latest/arm64/cpu-feature-registers.html).
As a general requirement, no sensitive security information is returned.
In some cases, some parts of the register content are blacked out.

However, this is a Linux-only feature and it is limited to a few registers, or a subpart of them.
This means that we are never really sure of what the physical register was.

This educational project provides a way to return the exact content of a few Arm64 registers
to userland through a dedicated loadable kernel module, on Linux and macOS. Some application
programs are provided to display an analysis of the contents of these registers.

Warning: This project is for educational purpose only, for people wanting to increase their
knowledge in the Arm64 architecture. Loading a custom kernel module may always have unexpected
side effects, including:

- Security effects: the content of the system registers could be used to gain information on
  the system, including the pointer authentication keys.
- Stability effects: modifying the PACIA key using a kernel which is built with pointer authentication
  crashes the system since the return pointer of the kernel functions are authenticated with a
  different key as used by the previous PACIA (believe me, I tried...)

## Build instructions

- `make` : Build the kernel module and the applications.
- `make install` : Install the kernel module in the system tree.
- `make load` : Load the kernel module.
- `make unload` : Unload the kernel module.
- `make show` : Show the loaded kernel module.

See more details in the README files of the various subdirectories.

##  Usage instructions

The C++ application `sysregs` is a generic tool to read and write the system registers.
With option `-v` (verbose), most system registers are structured using bit-fields of various
sizes and interpretation.
~~~
Syntax: sysregs [options]

  -r name : read the content of the named register
  -w name value : write the specified hexadecimal value in the named register
  -d name value : display the specified value in the named register format

  -a : read all supported Arm64 system registers
  -b : display register value in binary (default: hex)
  -f : force read/write register, even if not supposed to (risk of system crash)
  -h : display this help text
  -l : list the names of all supported Arm64 system registers
  -p : summary of supported PAC features
  -s : summary of CPU features
  -v : verbose, display register analysis and fields
~~~

See more details in:

- The `apps` subdirectory for command line tools.

- The `kernel` subdirectory for programming guidelines.

## List of accessible registers

The reference list of registers which can be accessed by this project is given by the list of
`CSR_REG_xxx` and `CSR_REG2_xxx` constants in file `kernel/cpusysregs.h`.

The following table lists them with the corresponding reference sections in the
[Arm Architecture Reference Manual for A-profile architecture](https://developer.arm.com/documentation/ddi0487/latest),
version 0487I.a.

| Register         | Section       | Access  | Description
| ---------------- | ------------- | ------- | -----------
| APDAKey_EL1      | D17.2.15/.16  | R/W (*) | Pointer Authentication Key A for Data (Hi/Lo pair)
| APDBKey_EL1      | D17.2.17/.18  | R/W (*) | Pointer Authentication Key B for Data (Hi/Lo pair)
| APGAKey_EL1      | D17.2.19/.20  | R/W (*) | Pointer Authentication Generic Key
| APIAKey_EL1      | D17.2.21/.22  | R/W (*) | Pointer Authentication Key A for Instructions (Hi/Lo pair)
| APIBKey_EL1      | D17.2.23/.24  | R/W (*) | Pointer Authentication Key B for Instructions (Hi/Lo pair)
| HCR_EL2          | D17.2.48      | R       | Hypervisor Configuration Register
| ID_AA64ISAR0_EL1 | D17.2.61      | R       | AArch64 Instruction Set Attribute Register 0
| ID_AA64ISAR1_EL1 | D17.2.62      | R       | AArch64 Instruction Set Attribute Register 1
| ID_AA64ISAR2_EL1 | D17.2.63      | R       | AArch64 Instruction Set Attribute Register 2
| ID_AA64PFR0_EL1  | D17.2.67      | R       | AArch64 Processor Feature Register 0
| ID_AA64PFR1_EL1  | D17.2.68      | R       | AArch64 Processor Feature Register 1
| MIDR_EL1         | D17.2.100     | R       | Main ID Register
| MPIDR_EL1        | D17.2.101     | R       | Multiprocessor Affinity Register
| REVIDR_EL1       | D17.2.106     | R       | Revision ID Register
| SCTLR_EL1        | D17.2.118     | R/W     | System Control Register (EL1)
| SCXTNUM_EL0      | D17.2.121     | R/W     | EL0 Read/Write Software Context Number
| SCXTNUM_EL1      | D17.2.122     | R/W     | EL1 Read/Write Software Context Number
| TCR_EL1          | D17.2.131     | R       | Translation Control Register (EL1)
| TPIDR_EL0        | D17.2.139     | R/W     | EL0 Read/Write Software Thread ID Register
| TPIDR_EL1        | D17.2.140     | R/W     | EL1 Software Thread ID Register
| TPIDRRO_EL0      | D17.2.143     | R/W     | EL0 Read-Only Software Thread ID Register

(*) The Pointer Authentication Key registers are usually readable and writeable at EL1 (kernel).
This is the case on Linux. On macOS, however, in the default configuration, the PAC key registers
can be accessed at EL3 only. This is explained in
[this article](https://gist.github.com/lelegard/009cbdae78e5993ed9e02160b9130d7f).
Accessing the PAC key registers at EL1 crashes macOS.

## References

- [Arm Architecture Reference Manual for A-profile architecture](https://developer.arm.com/documentation/ddi0487/latest),
  nearly 12,000 pages...
- [Apple architectures arm64 and arm64e on macOS](https://gist.github.com/lelegard/009cbdae78e5993ed9e02160b9130d7f).
