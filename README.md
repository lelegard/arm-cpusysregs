# Access Arm64 CPU system registers

The 64-bit Arm architecture (a.k.a. "arm64", "aarch64") defines a large quantity
of special system registers. Many of them are inaccessible from userland. When a
system register name ends in `_EL1`, it is accessible only at EL1 (kernel mode).
Similarly, system registers in `_EL2` are accessible only in hypervisor mode and
`_EL3` in monitor mode.

This educational project provides a way to return the exact content of a few Arm64
system registers to userland through a dedicated loadable kernel module, on Linux,
macOS, and Windows. Some application programs are provided to display an analysis
of the contents of these registers.

More generally, this project provides some notes, examples, and information on the
the Arm64 architecture for developers.

**Contents:**

* [Accessing the system registers](#accessing-the-system-registers)
* [Build instructions](#build-instructions)
* [Usage instructions](#usage-instructions)
* [Focus on Pointer Authentication Code (PAC)](#focus-on-pointer-authentication-code-pac)
* [List of accessible registers](#list-of-accessible-registers)

## Accessing the system registers

Reading and writing system registers is done using the special instructions
`MRS` and `MSR`, respectively. Each system register has a dedicated exception
level, EL0 to EL3. Trying to access a system register from an outer level
results in an "illegal instruction" exception.

On Linux, there is a special feature in the kernel which allows a limited access
to a few `_EL1` system registers from user mode (EL0). The kernel intercepts the
`SIGILL` exception which results from the invalid access to a system register
using an `MRS` instruction. If the requested system register is one of a few
selected allowed registers, the kernel reads the system register and returns it
to the process, as if the `MRS` instruction executed correctly.

This is [explained in details here](https://www.kernel.org/doc/html/latest/arch/arm64/cpu-feature-registers.html).
As a general requirement, no sensitive security information is returned.
In some cases, some parts of the register content are blacked out.

This is a Linux-only feature and it is limited to a few registers, or a subpart of
them. This means that we are never really sure of what the physical register was.

This project provides Linux, macOS, and Windows kernel modules to read and write
selected system registers from user applications.

**Warning:** This project is for educational purpose only, for people wanting to
increase their knowledge in the Arm64 architecture. Loading a custom kernel
module may always have unexpected side effects, including:

- Security effects: the content of the system registers could be used to gain
  information on the system, including the pointer authentication keys on Linux
  (they are better protected on macOS).
- Stability effects:
  - Accessing Arm system registers is not only a matter of exception level.
    The Arm architecture reference manual describes in details the pseudo-code
    to access each register. There are many specific configuration options,
    usually set by the hypervisor (EL2) or monitor (EL3) which filter or
    protect access to the register. In specific configurations, depending on
    the operating system or the platform, accessing a system register from
    the kernel may either work or crash the system.
  - Modifying the PACIA key using a kernel which is built with pointer
    authentication crashes the system since the return pointer of the kernel
    functions are authenticated with a different key as used by the previous
    PACIA (believe me, I tried...)

See the file [docs/references.md](docs/references.md) for a list of reference
documentations on the Arm64 architecture, its system registers and pointer
authentication features.

## Build instructions

For Linux and macOS:
- `make` : Build the kernel module and the applications.
- `make install` : Install the kernel module in the system tree.
- `make load` : Load the kernel module.
- `make unload` : Unload the kernel module.
- `make show` : Show the loaded kernel module.

For Windows, see the directory [msbuild](msbuild).

See also more details in the README files of the [apps](apps) and [kernel](kernel)
subdirectories.

##  Usage instructions

The C++ application `sysregs` is a generic tool to read and write the system registers.
With option `-v` (verbose), most system registers are structured using bit-fields of various
sizes and interpretation.
~~~
Syntax: sysregs [options]

  -r name       : read the content of the named register
  -w name value : write the specified hexadecimal value in the named register
  -d name value : display the specified value in the named register format

  -a : read all supported Arm64 system registers
  -b : display register value in binary (default: hex)
  -f : force read/write register, even if not supposed to (risk of system crash)
  -h : display this help text
  -l : list the names of all supported Arm64 system registers
  -p : summary of supported PAC features
  -s : summary of CPU features
  -S : same as -s but read registers at EL0 (maybe partial, may fail)
  -v : verbose, display register analysis and fields
~~~

See more details in:

- The [apps](apps) subdirectory for other command line tools.
- The [kernel](kernel) subdirectory for programming guidelines.

## Focus on Pointer Authentication Code (PAC)

One of the motivations for this project was a better understanding of the
Pointer Authentication Code (PAC) feature, as introduced in the Armv8.3-A
architecture. PAC is one of the clever "defensive security" features which
were designed by Arm (the other one is BTI, the Branch Target Indentification
in Armv8.5-A).

Understanding PAC is harder than it may seem. There are many configuration
options which depend on the operating system or the platform. Predicting the
size, position and value of a PAC is not trivial. We need to read several
memory management system registers and correctly interpret the complex Arm
pseudo-code (or emulate it as done in this project). The command `sysregs -p`
summarizes this.

There are several documents in the [docs](docs) subdirectory containing the
summary of observations about the PAC on different platforms. The subdirectory
[collect](collect) contains informations which were collected on these
platforms, Linux, macOS, Windows, using various Arm64-based processor chips
implementing Armv8.3-A or higher versions of the architecture.

Specifically, this project was the main tool to support the writing of the white paper
"[Control Flow Integrity, anti-malware active protection on Arm64 systems](https://sipearl.com/wp-content/uploads/2023/10/SiPearl-WP-CFI-on-Arm64.pdf)"
from [SiPearl](https://sipearl.com/).


## List of accessible registers

The reference list of registers which can be accessed by this project is given by
the list of `CSR_REG_xxx` and `CSR_REG2_xxx` constants in file
[kernel/cpusysregs.h](kernel/cpusysregs.h).

Some _EL0 registers can be protected by the kernel using _EL1 control registers.
Reading these _EL0 registers in user mode raises an illegal instruction exception.
In that case, they can be accessed from kernel mode using the kernel module.

| Register         | Access  | Description
| ---------------- | ------- | -----------
| APDAKey_EL1      | R/W [1] | Pointer Authentication Key A for Data (Hi/Lo pair)
| APDBKey_EL1      | R/W [1] | Pointer Authentication Key B for Data (Hi/Lo pair)
| APGAKey_EL1      | R/W [1] | Pointer Authentication Generic Key (Hi/Lo pair)
| APIAKey_EL1      | R/W [1] | Pointer Authentication Key A for Instructions (Hi/Lo pair)
| APIBKey_EL1      | R/W [1] | Pointer Authentication Key B for Instructions (Hi/Lo pair)
| CNTFRQ_EL0       | R       | Counter-timer Frequency register
| CNTKCTL_EL1      | R/W     | Counter-timer Kernel Control register
| CNTPCT_EL0       | R       | Counter-timer Physical Count register
| CNTPS_CTL_EL1    | R/W     | Counter-timer Physical Secure Timer Control register
| CNTVCT_EL0       | R       | Counter-timer Virtual Count register
| CTR_EL0          | R   [5] | Cache Type Register
| HCR_EL2          | R   [2] | Hypervisor Configuration Register
| ID_AA64AFR0_EL1  | R       | AArch64 Auxiliary Feature Register 0
| ID_AA64AFR1_EL1  | R       | AArch64 Auxiliary Feature Register 1
| ID_AA64DFR0_EL1  | R       | AArch64 Debug Feature Register 0
| ID_AA64DFR1_EL1  | R       | AArch64 Debug Feature Register 1
| ID_AA64DFR2_EL1  | R       | AArch64 Debug Feature Register 2
| ID_AA64FPFR0_EL1 | R       | AArch64 Floating-point Feature Register 0
| ID_AA64ISAR0_EL1 | R       | AArch64 Instruction Set Attribute Register 0
| ID_AA64ISAR1_EL1 | R       | AArch64 Instruction Set Attribute Register 1
| ID_AA64ISAR2_EL1 | R       | AArch64 Instruction Set Attribute Register 2
| ID_AA64ISAR3_EL1 | R       | AArch64 Instruction Set Attribute Register 3
| ID_AA64MMFR0_EL1 | R       | AArch64 Memory Model Feature Register 0
| ID_AA64MMFR1_EL1 | R       | AArch64 Memory Model Feature Register 1
| ID_AA64MMFR2_EL1 | R       | AArch64 Memory Model Feature Register 2
| ID_AA64MMFR3_EL1 | R       | AArch64 Memory Model Feature Register 3
| ID_AA64MMFR4_EL1 | R       | AArch64 Memory Model Feature Register 4
| ID_AA64PFR0_EL1  | R       | AArch64 Processor Feature Register 0
| ID_AA64PFR1_EL1  | R       | AArch64 Processor Feature Register 1
| ID_AA64PFR2_EL1  | R       | AArch64 Processor Feature Register 2
| ID_AA64SMFR0_EL1 | R       | SME Feature ID register 0
| ID_AA64ZFR0_EL1  | R       | SVE Feature ID register 0
| ID_ISAR0_EL1     | R       | AArch32 Instruction Set Attribute Register 0
| ID_ISAR1_EL1     | R       | AArch32 Instruction Set Attribute Register 1
| ID_ISAR2_EL1     | R       | AArch32 Instruction Set Attribute Register 2
| ID_ISAR3_EL1     | R       | AArch32 Instruction Set Attribute Register 3
| ID_ISAR4_EL1     | R       | AArch32 Instruction Set Attribute Register 4
| ID_ISAR5_EL1     | R       | AArch32 Instruction Set Attribute Register 5
| ID_ISAR6_EL1     | R       | AArch32 Instruction Set Attribute Register 6
| ID_MMFR0_EL1     | R       | AArch32 Memory Model Feature Register 0
| ID_MMFR1_EL1     | R       | AArch32 Memory Model Feature Register 1
| ID_MMFR2_EL1     | R       | AArch32 Memory Model Feature Register 2
| ID_MMFR3_EL1     | R       | AArch32 Memory Model Feature Register 3
| ID_MMFR4_EL1     | R       | AArch32 Memory Model Feature Register 4
| ID_MMFR5_EL1     | R       | AArch32 Memory Model Feature Register 5
| ID_PFR0_EL1      | R       | AArch32 Processor Feature Register 0
| ID_PFR1_EL1      | R       | AArch32 Processor Feature Register 1
| ID_PFR2_EL1      | R       | AArch32 Processor Feature Register 2
| MAIR_EL1         | R       | Memory Attribute Indirection Register (EL1)
| MAIR2_EL1        | R       | Extended Memory Attribute Indirection Register (EL1)
| MIDR_EL1         | R       | Main ID Register
| MPIDR_EL1        | R       | Multiprocessor Affinity Register
| PIR_EL1          | R       | Permission Indirection Register 1 (EL1)
| PIRE0_EL1        | R       | Permission Indirection Register 0 (EL1)
| PMCCFILTR_EL0    | R       | Performance Monitors Cycle Count Filter Register
| PMCCNTR_EL0      | R       | Performance Monitors Cycle Count Register
| PMCR_EL0         | R       | Performance Monitors Control Register
| PMMIR_EL1        | R       | Performance Monitors Machine Identification Register
| PMSIDR_EL1       | R   [4] | Sampling Profiling ID Register
| PMUSERENR_EL0    | R       | Performance Monitors User Enable Register
| REVIDR_EL1       | R       | Revision ID Register
| RNDR             | R       | Random Number
| RNDRRS           | R       | Reseeded Random Number
| SCR_EL3          |     [3] | Secure Configuration Register (EL3)
| SCTLR_EL1        | R/W     | System Control Register (EL1)
| SCTLR2_EL1       | R/W     | System Control Register 2 (EL1)
| SCXTNUM_EL0      | R/W     | EL0 Read/Write Software Context Number
| SCXTNUM_EL1      | R/W     | EL1 Read/Write Software Context Number
| TCR_EL1          | R       | Translation Control Register (EL1)
| TCR2_EL1         | R       | Extended Translation Control Register (EL1)
| TPIDR_EL0        | R/W [5] | EL0 Read/Write Software Thread ID Register
| TPIDR_EL1        | R/W [5] | EL1 Software Thread ID Register
| TPIDRRO_EL0      | R/W [5] | EL0 Read-Only Software Thread ID Register
| TRCDEVARCH       | R       | Trace Device Architecture Register
| TTBR0_EL1        | R       | Translation Table Base Register 0 (EL1)
| TTBR1_EL1        | R       | Translation Table Base Register 1 (EL1)

[1] The Pointer Authentication Key registers are usually readable and writeable at EL1 (kernel).
This is the case on Linux. On macOS, however, in the default configuration, the PAC key registers
can be accessed at EL3 only. This is explained in file [docs/arm64e-on-macos.md](docs/arm64e-on-macos.md).
Accessing the PAC key registers at EL1 crashes macOS.

[2] HCR_EL2 is readable at EL1 on macOS. Access not allowed in a Linux VM and crashes the system.

[3] SCR_EL3 cannot by read/write at EL1. It is supported to format its possible values only.

[4] PMSIDR_EL1 cannot be read on Linux at EL1, even when FEAT_SPE is implemented.

[5] These registers cannot be accessed on Windows. Reading or writing them crashes the system.
