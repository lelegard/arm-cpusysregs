# Pointer Authentication Code format

This note explains the format of the "signature" which is inserted in pointers using
the PACxx instructions in the Arm64 instruction set. This signature is indifferently
named "pointer authentication code" or PAC.

**Contents:**

* [PAC location](#pac-location)
  * [PAC size](#pac-size)
  * [Four PAC spaces](#four-pac-spaces)
  * [Locating the PAC in practice](#locating-the-pac-in-practice)
  * [The PACGA instruction](#the-pacga-instruction)
* [PAC computation principles](#pac-computation-principles)
  * [PAC algorithms](#pac-algorithms)
  * [PAC keys](#pac-keys)
  * [PAC salt / modifier / discriminator / tweak](#pac-salt--modifier--discriminator--tweak)
    * [Stack diversity](#stack-diversity)
    * [Address diversity and discriminator](#address-diversity-and-discriminator)
* [Examples and demo](#examples-and-demo)
  * [Common to all operating systems](#common-to-all-operating-systems)
  * [Specific to Linux](#specific-to-linux)
  * [Specific to macOS](#specific-to-macos)
  * [Specific to Windows](#specific-to-windows)
  * [Specific to Arm\-designed cores](#specific-to-arm-designed-cores)
  * [Specific to Apple M1 chip](#specific-to-apple-m1-chip)
* [Comparisons of platforms](#comparisons-of-platforms)

## PAC location

The PACxx instructions take a 64-bit address as input and insert a signature
of the address value in the upper bits of this address value. The result is
a "signed pointer" or "authenticated pointer".

In practice, the virtual space of a process never uses 2^64 bytes. This means
that the upper bits of an address are not used and can be used for various purposes.
This is where the PAC is stored.

### PAC size

The number of bits in the PAC is variable, typically from 7 to 16 bits.

The actual number of bits in the PAC depends on several factors:
- The size of the virtual address space for the processes (typically 47 or 48 bits).
- The usage of other security mechanisms which also use the upper bits.
  The optional Memory Tagging Extension (MTE) - which is a more recent Arm extension
  than PAC - uses the upper 8 bits of data addresses to "tag" their usage and check
  illegal mixing of data spaces. When MTE is used, the PAC cannot use the upper 8 bits
  and must be relocated to lower bits (typically bits 54:48 or 54:47).
- Other operating system constraints which are not fully clear.

### Four PAC spaces

The location and size of the PAC also depends on two additional independent factors:
- Instructions vs. data: The "instructions" addresses are signed by instructions
  PACIA and PACIB. The "data" addresses are signed by instructions PACDA and PACDB.
- Lower vs. upper addresses: Although no operating system use all 64 address bits,
  some systems use "lower" (addresses starting in 0x0000...) and "upper" (addresses
  starting in 0xFFFF...) spaces. The upper bits of the plain addresses are not identical.
  When they are overwritten by a PAC, the processor must keep the information of the
  original value of the upper bits, either 0x0000 or 0xFFFF.

This means that, on a given system, there are four different combinations of
instructions / data and lower / upper addresses. Each combination can have a
specific PAC size and location. Additionally, when several virtual machines run
on the same processor, each operating system (host and virtual machines) may have
its own specific combination.

### Locating the PAC in practice

Understanding the exact size and location of the PAC for a given address is not easy.

There is only one invariant: the bit 55 is never modified by a PACxx instruction.
For the record, bit 0 is the least significant one and bit 63 is the most significant
one. Bit 55 is consequently the last bit before the last byte. This bit is used to
differentiate lower 0x000... addresses and upper 0xFFFF... addresses. This bit is 0
in lower addresses and 1 in upper addresses. It is always left unchanged by the PACxx
instructions. Its value is used by the AUTxx instructions and other authentication
instructions to determine the original address range, lower or upper.

Note that the processor uses bit 55 and not bit 63 to differentiate between lower and
upper addresses. We can speculate the reason for this: when MTE is used, the upper byte
(bits 63:56) is used for the tag. In that case, bit 55 is the last bit before the tag.

The pseudo-code in the [Arm Architecture Reference Manual](https://developer.arm.com/documentation/ddi0487/latest)
is complex and depends on several system registers and optional architecture extensions.

The command `sysregs -p` from this project emulates the Arm pseudo-code for the
four combinations of instructions / data and lower / upper addresses and displays
the PAC location. Note that this command can predict the PAC location at EL0 and 1
only (user and kernel). The hypervisor (EL2) and monitor (EL3) have additional
mechanisms to trap the usage of PAC instructions and key registers, leading to
potential different behaviors.

On an Apple M1 chip (MacBook laptop), the command `sysregs -p` displays this in the macOS host system:
~~~
  Data  (lower): PAC size:  8 bits, bit range:       54:47 (top: 55, sel: 55, bottom: 47)
  Data  (upper): PAC size: 16 bits, bit range: 63:56,54:47 (top: 63, sel: 55, bottom: 47)
  Instr (lower): PAC size: 16 bits, bit range: 63:56,54:47 (top: 63, sel: 63, bottom: 47)
  Instr (upper): PAC size: 16 bits, bit range: 63:56,54:47 (top: 63, sel: 63, bottom: 47)
~~~

On the same machine with an Apple M1 chip, the same command displays this in a virtual machine
running Linux Ubuntu 23 and the Linux kernel 6.2:
~~~
  Data  (lower): PAC size:  7 bits, bit range:       54:48 (top: 55, sel: 55, bottom: 48)
  Data  (upper): PAC size:  7 bits, bit range:       54:48 (top: 55, sel: 55, bottom: 48)
  Instr (lower): PAC size:  7 bits, bit range:       54:48 (top: 55, sel: 55, bottom: 48)
  Instr (upper): PAC size: 15 bits, bit range: 63:56,54:48 (top: 63, sel: 55, bottom: 48)
~~~

In all cases, we see that the bit 55 is left unused.

The upper byte is unused in one case in the macOS host while it is unused on three
cases in the Linux virtual machine. Not using the upper byte for the PAC is required
when memory tagging (MTE) is used. However, MTE is not implemented in the Apple M1 chip.
The reason why the upper byte is not used by the PAC is some cases is unknown.

Another peculiarity is the number of virtual address bits. On macOS, the system uses
47 bits. On Linux, it uses 48 bits, reducing the entropy of the PAC by one bit.
The reason for this is unknown.

Even more peculiar, on the same machine with an Apple M1 chip, in a virtual machine
running Linux Debian 11 and an older Linux kernel 5.10, we get this:
~~~
  Data  (lower): PAC size:  7 bits, bit range:       54:48 (top: 55, sel: 55, bottom: 48)
  Data  (upper): PAC size: 15 bits, bit range: 63:56,54:48 (top: 63, sel: 55, bottom: 48)
  Instr (lower): PAC size:  7 bits, bit range:       54:48 (top: 55, sel: 55, bottom: 48)
  Instr (upper): PAC size: 15 bits, bit range: 63:56,54:48 (top: 63, sel: 55, bottom: 48)
~~~

The reason for using 15 bits instead of 7 for the PAC on upper data addresses, for different
versions of the  kernel, is also unknown.

Finally, still on the same MacBook machine with an Apple M1 chip, the command displays this
in a Windows 11 virtual machine:
~~~
  Data  (lower): PAC size: 16 bits, bit range: 63:56,54:47 (top: 63, sel: 63, bottom: 47)
  Data  (upper): PAC size: 16 bits, bit range: 63:56,54:47 (top: 63, sel: 63, bottom: 47)
  Instr (lower): PAC size: 16 bits, bit range: 63:56,54:47 (top: 63, sel: 63, bottom: 47)
  Instr (upper): PAC size: 16 bits, bit range: 63:56,54:47 (top: 63, sel: 63, bottom: 47)
~~~

The PAC is supposed to use its maximum size. However, the practice demonstrates that the PAC
instructions are inoperative. They leave the pointers unmodified, without signature.

### The PACGA instruction

We have seen two categories of signatures: pointers to instructions (PACIA and PACIB
instructions) and pointers to data (PACDA and PACDB instructions). There is third
category: the "generic" PAC computation, using the PACGA instruction.

The PACIx and PACDx instructions _modify_ a pointer value and overwrite its upper bits.
These upper bits must be initially unused or, more precisely, they must have a known value:
all 0 for lower addresses, all 1 for upper addresses. Consequently, these instructions
cannot sign an arbitrary 64-bit value without losing information in the upper bits.
They can only sign address values.

The PACGA instruction is used to compute a keyed hash over general purpose data.
It takes an arbitrary 64-bit value from a source register and generates a 32-bit
output value in a different destination register. For some reason, the 32-bit PAC
is written in the upper 32 bits of the destination register. The lower 32 bits of
the destination register are zeroed by PACGA.

To compute a keyed hash over a memory area, simply iterate PACGA over that area,
64 bits at a time, reinjecting the 32-bit PAC in the next iteration.

The previously mentioned rules about the PAC size and location do not apply to PACGA.
Its output is always a 32-bit value.

On Windows, the PACGA instruction works as expected. Only the PACIx and PACDx are inoperative.

## PAC computation principles

The pointer authentication code of a value is a _salted keyed hash_ of that value.

### PAC algorithms

Computing a PAC uses a symmetric encryption algorithm as base. This encryption algorithm uses a 128-bit symmetric key.

Additionally, all PAC instructions use a "salt" value, also called "modifier"
in the [Arm Architecture Reference Manual](https://developer.arm.com/documentation/ddi0487/latest),
or "discriminator" in the
[Apple LLVM project](https://github.com/apple/llvm-project/blob/apple/main/clang/docs/PointerAuthentication.rst),
or "tweak" in the [QARMA-64 algorithm](https://eprint.iacr.org/2016/444.pdf).
This salt / modifier / discriminator / tweak is a clear contextual value.

The Arm architecture leaves the choice of algorithm to the implementers of the CPU core.

Arm-designed cores use the [QARMA-64 algorithm](https://eprint.iacr.org/2016/444.pdf).
This is a public, low-latency, multi-round, symmetric encryption algorithm. The initial
Arm implementation uses QARMA5, the QARMA-64 algorithm with 5 rounds. The Arm architecture
also allows the use of QARMA3, the same algorithm with 3 rounds only. The latter is
faster but less secure than the former.

The Arm architecture also allows an "implementation-defined" algorithm. The Apple
M1 and M2 chips use Apple-designed cores which use their own private implementation-defined
algorithm for the PAC computation.

The algorithm is also displayed by the command `sysregs -p`, along with the
various extensions to the PAC features.

On an Apple M1 chip, macOS host or Linux VM, the command displays this.
We see that an implementation-defined algorithm is used.
~~~
Summary: PAC: yes, PACGA: yes
PAuth: yes, PAuth2: no, EPAC: yes, FPAC: no, FPACCOMBINE: no, CONSTPACFIELD: no
Algorithms: QARMA3: no, QARMA5: no, implementation-defined: yes
~~~

On an AWS Graviton3 chip, using an Arm-designed Neoverse V1 core, the same command
displays this. We see that Arm-designed cores use QARMA5.
~~~
Summary: PAC: yes, PACGA: yes
PAuth: yes, PAuth2: yes, EPAC: yes, FPAC: no, FPACCOMBINE: no, CONSTPACFIELD: no
Algorithms: QARMA3: no, QARMA5: yes, implementation-defined: no
~~~

### PAC keys

In the Arm architecture, there are 5 different key registers for PAC computation:
- Key IA, used by PACIA and AUTIA instructions.
- Key IB, used by PACIB and AUTIB instructions.
- Key DA, used by PACDA and AUTDA instructions.
- Key DB, used by PACDB and AUTDB instructions.
- The generic key, used by PACGA instruction.

These key registers are not accessible at EL0 (user mode). Typically, the kernel
allocates 5 random keys for each newly created process. Each time this process is
scheduled on a core, the 5 PAC key registers are set with these process-specific values.

On Linux, the PAC key registers are directly written by the kernel.

On macOS, an EL3 monitor configuration (probably using SCR_EL3, the Secure Configuration
Register) prevents the kernel from accessing the PAC key registers. Reading or writing
them at EL1 crashes the system, probably because the corresponding trap at EL3 is not
a valid key change request.

### PAC salt / modifier / discriminator / tweak

In each PACxx or AUTxx instruction, the modifier (let's call it this way from now on)
is explicitly provided through one of the following mechanisms:

- Zero. This constant hard-coded value is used by instructions such as PACIAZ, AUTIAZ
  or LDRAA. This is not used in practice in current compilers.
- The value from a register. This register is specified in the instruction and its
  value (the modifier) must have been computed by the generated code before executing
  the PACxx or AUTxx instruction.
- The stack pointer. This context-depended value is used by instructions such as PACIASP,
  AUTIASP or RETAA.

#### Stack diversity

When a pointer is pushed on the stack, it is vulnerable to a stack overflow attack.
Consequently, it is signed with a PAC. Each time a function is called, for instance,
the returned address is signed before being pushed on stack. To add some entropy to
the PAC, the value of the stack pointer _before pushing the address_ is used as PAC
modifier. Thus, the signature depends on the stack context and cannot be reused elsewhere.

For instance, the typical prolog and epilog of a function are illustrated here:
~~~
paciasp                        ; add a PAC to return address in x30 before pushing it on stack
                               ; (key = IA, mod = current stack pointer)
stp     x29, x30, [sp, #-16]!  ; push the stack frame (previous frame pointer x29, signed return address x30)
mov     x29, sp                ; update the frame pointer to current stack frame

....

ldp     x29, x30, [sp], #16    ; restore the previous frame pointer in x29 and signed returned address in x30
retaa                          ; authenticate the return address in x30 before jumping to it
                               ; (generate an invalid return address and/or generate an exception
                               ; if the value was overwritten during a stack overflow)
~~~

#### Address diversity and discriminator

Another common practice consists in using the address where a value is stored
as modifier when computing a PAC on that value. In other words, when a 64-bit
pointer value V is stored at address A and we want to compute a PAC for V,
we use A as modifier. The
[Apple LLVM article on pointer authentication](https://github.com/apple/llvm-project/blob/apple/main/clang/docs/PointerAuthentication.rst)
calls this technique _address diversity_.

Additionally, Apple recommends to use an additional _discriminator_ which depends
on the semantic of the signed address. Typically, a pointer to a C++ virtual function,
inside a vtable, is signed using a modifier which is built from the address where it
is stored in the vtable (address diversity) and an additional discriminator which is
built from the fully qualified names of the class and method.

Note that stack diversity is not exactly the same thing as address diversity since
the modifier is the value of the stack pointer _before_ pushing the value.

## Examples and demo

The program `demo-pac` from this project demonstrates the computation of pointer
authentication codes in various situations:

- Instructions vs. data, lower vs. upper addresses, to exhibit the PAC size and location.
- Executing the PACxx instructions in user mode (EL0) and kernel mode (EL1),
  to check if the same PAC key is used in both modes.
- If the PAC algorithm is QARMA5 or QARMA3 and the PAC key registers are readable from EL1,
  compare the signed address with a software encryption using that algorithm.

The results of three successive executions of this program on each platform are available
in the [collect](../collect) directory.

The following subsections are some observations from these results. The next section
contains a full comparison of results per platform.

### Common to all operating systems

- The PAC values are different for the same input values each time the program is
  executed. Conclusion: the kernel of all operating systems provides new PAC keys
  for new processes.
- The PAC values are different when using PACIA, PACIB, PACDA, PACDB. Conclusion:
  the PAC keys have different values in each process.
- We verified that AUTxx matches the corresponding PACxx. We also verified that
  corrupting a signed pointer results in an invalid address after AUTxx. With cores
  implementing the FPAC feature, this AUTxx instruction should raise an exception.
  This cannot be verified for now.
- The bit 55 of all addresses is preserved, in all cases.

### Specific to Linux

- The meaningful virtual address part of a pointer uses 48 bits, leaving 16 bits
  for PAC, MTE and selector bit.
- Most PAC values use 7 bits, except for pointers on upper addresses where the PAC
  uses either 7 or 15 bits, depending on the kernel version.
- Executing a PACxx instruction in user mode (EL0) and kernel mode (EL1) on the
  same input value gives the same result, except with PACIA. Conclusion: only the
  IA key is different between user and kernel. Each time an application switches
  from user mode to kernel mode or vice versa, the value of the PACIA key is changed.
  All other PAC keys remain unchanged.
  - This is consistent with another observation: if we change the value of the
    PACIA key using the kernel module of this project, the system crashes. All other
    PAC keys can be safely changed. In standard Ubuntu distributions for arm64, the
    kernel is now compiled with option `-mbranch-protection=pac-ret`, meaning that the
    call return addresses on stack are signed with the PACIA key. Changing this key
    while in kernel mode crashes on return.
  - As a final consequence, we may say that the kernel uses only one PAC key and
    updates it each time we enter kernel mode, leaving all other PACK keys unchanged.

### Specific to macOS

- The PAC key registers cannot be read or written in kernel mode (EL1). Trying to
  do so using the kernel extension of this project crashes the system. Access to
  these registers is probably configured at EL3 to trap at EL3.
- The meaningful virtual address part of a pointer uses 47 bits, leaving 17 bits
  for PAC, MTE and selector bit (compared to 48 and 16 bits, respectively, on Linux).
- Most PAC values use 16 bits, except for data pointers on lower addresses where the PAC use 8 bits.
- Unexpected note on the selector bit: in the case of pointer to instructions
  on macOS, the command `sysregs -p` displays that the selector bit is 63 instead
  of 55. However, we can see that the PAC computation on pointers to instructions
  sometimes change the bit 63 while it always preserves the bit 55. Maybe this is
  an interpretation error on the nature of the selector bit or in the implementation
  in `sysregs`.
- Executing any PACxx instruction in user mode (EL0) and kernel mode (EL1) on the
  same input value give distinct results. Conclusion: the 5 PAC keys are different
  between user and kernel. Each time an application switches from user mode to
  kernel mode or vice versa, the values of all PAC keys are changed.
  - As previously observed, this means than switching from EL0 to EL1 implies a
    detour through EL3 to reprogram the PAC key registers. And again when
    switching back from EL1 to EL0.
  - Note a difference with Linux here. On macOS using the "arm64e" platform, the
    generated code uses three PAC keys, IA, IB, DA, but not DB and GA. Since the
    kernel is compiled for "arm64e", it uses these three PAC registers. However,
    unlike the Linux kernel, the macOS kernel choses to change all PAC keys when
    switching to kernel mode, even those it doesn't use.

### Specific to Windows

- The PAC key registers can be read and modified. Their initial value in a process
  is zero. Modifying them is possible. The assigned value remains valid in the process.
- The PACIx and PACDx instructions are inoperative in practice. They leave the pointer
  unmodified.

### Specific to Arm-designed cores

- The computed PAC values match the QARMA5 software computation. This was expected
  but still nice to verify.

### Specific to Apple M1 chip

- The PAC computation uses an implementation-defined algorithm and it is not possible
  to anticipate a PAC value, even when the context is fully known. Whether this is a
  good or bad thing is left to the reader...

## Comparisons of platforms

The following table compares various forms of PAC computations on several platforms.

| Platform             | macOS host (M1) | Linux VM (M1)   | Linux VM (M1)   | Windows VM (M1) | Linux VM (G3)   |
| -------------------- | --------------- | --------------- | --------------- | --------------- | --------------- |
| OS                   | macOS           | Linux (Ubuntu)  | Linux (Debian)  | Windows 11      | Linux (Ubuntu)  |
| OS kernel version    | 13.2.1          | 6.2.0-20        | 5.10.0-23       | 10.0.22000      | 5.15.0-1030-aws |
| Virtualization       | Host            | VM              | VM              | VM              | VM              |
| Processor chip       | Apple M1        | Apple M1        | Apple M1        | Apple M1        | AWS Graviton 3  |
| CPU cores            | Apple Firestorm | Apple Firestorm | Apple Firestorm | Apple Firestorm | Arm Neoverse V1 |
| PAC algorithm        | private         | private         | private         | private         | QARMA5          |
| PAuth / PAuth2       | yes / no        | yes / no        | yes / no        | yes / no        | yes / yes       |
| EPAC / FPAC          | yes / no        | yes / no        | yes / no        | yes / no        | yes / no        |
| MTE tagging          | no              | no              | no              | no              | no              |
|                      |                 |                 |                 |                 |                 |
| **PAC size**         |                 |                 |                 |                 |                 |
| data, lower          | 8 bits          | 7 bits          | 7 bits          | 16 bits         | 7 bits          |
| data, upper          | 16 bits         | 7 bits          | 15 bits         | 16 bits         | 7 bits          |
| instruction, lower   | 16 bits         | 7 bits          | 7 bits          | 16 bits         | 7 bits          |
| instruction, upper   | 16 bits         | 15 bits         | 15 bits         | 16 bits         | 15 bits         |
|                      |                 |                 |                 |                 |                 |
| **PAC position**     |                 |                 |                 |                 |                 |
| data, lower          | 54:47           | 54:48           | 54:48           | 63:56,54:47     | 54:48           |
| data, upper          | 63:56,54:47     | 54:48           | 63:56,54:48     | 63:56,54:47     | 54:48           |
| instruction, lower   | 63:56,54:47     | 54:48           | 54:48           | 63:56,54:47     | 54:48           |
| instruction, upper   | 63:56,54:47     | 63:56,54:48     | 63:56,54:48     | 63:56,54:47     | 63:56,54:48     |
|                      |                 |                 |                 |                 |                 |
| **PAC selector bit** |                 |                 |                 |                 |                 |
| data, lower          | bit 55          | bit 55          | bit 55          | bit 63          | bit 55          |
| data, upper          | bit 55          | bit 55          | bit 55          | bit 63          | bit 55          |
| instruction, lower   | bit 63          | bit 55          | bit 55          | bit 63          | bit 55          |
| instruction, upper   | bit 63          | bit 55          | bit 55          | bit 63          | bit 55          |
|                      |                 |                 |                 |                 |                 |
| **EL0/EL1 PAC keys** |                 |                 |                 |                 |                 |
| DA                   | distinct keys   | same key        | same key        | zero            | same key        |
| DB                   | distinct keys   | same key        | same key        | zero            | same key        |
| IA                   | distinct keys   | distinct keys   | distinct keys   | zero            | distinct keys   |
| IB                   | distinct keys   | same key        | same key        | zero            | same key        |
| Generic (PACGA)      | distinct keys   | same key        | same key        | zero            | same key        |
|                      |                 |                 |                 |                 |                 |
| **TCR_EL1 register** |                 |                 |                 |                 |                 |
| TBI0                 | 1               | 1               | 1               | 0               | 1               |
| TBID0                | 1               | 0               | 0               | 0               | 0               |
| T0SZ                 | 17              | 16              | 16              | 17              | 16              |
| TBI1                 | 0               | 1               | 1               | 0               | 1               |
| TBID1                | 0               | 1               | 1               | 0               | 1               |
| T1SZ                 | 17              | 16              | 16              | 17              | 16              |
