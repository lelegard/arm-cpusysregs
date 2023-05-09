# How to build applications using specific Arm features

**Contents:**

* [The problem](#the-problem)
* [Classes of optional instructions](#classes-of-optional-instructions)
  * [Hints](#hints)
  * [Non\-replaceable instructions](#non-replaceable-instructions)
  * [Accelerated instructions](#accelerated-instructions)
* [Building with accelerated instructions](#building-with-accelerated-instructions)
  * [The problems of gcc and clang](#the-problems-of-gcc-and-clang)
    * [Inconsistent feature naming](#inconsistent-feature-naming)
    * [Side\-effects on code generation](#side-effects-on-code-generation)
  * [Possible improvements in compilers](#possible-improvements-in-compilers)
  * [Proposed solution with current compilers](#proposed-solution-with-current-compilers)
  * [Complete example](#complete-example)

## The problem

The Arm64 architecture has more than 240 [optional features](features.md).
Some of them define additional instructions which are specific to this feature.
Using them on a CPU which does not implement the corresponding feature does nothing
at best or crashes the application on an "illegal instruction" fault at worst.

Some of these specific instructions bring a significant performance improvement.
This is the case for the "accelerated cryptographic instructions" for CRC, AES,
SHA-1, SHA-256, SHA-512, SHA-3. When available, these instructions may accelerate the
corresponding algorithm by a factor or 10 or even 20. It is consequently
important to use them when available.

The gcc and clang compilers have options to specify the target CPU, its level
of architecture and the Arm optional features. Depending on these options, the
compiler will generate - or refuse to generate - the instructions which are
specific to an Arm feature.

This approach is acceptable in an embedded computing environment, the original
domain where Arm CPU's were used first. In such a context, the application is
compiled for a dedicated unique target. It is consequently possible to fine-tune
the compilation options for a specific target.

However, as Arm CPU's are now frequently used in server environments, this
approach is no longer acceptable. On a generic server or even a laptop, there are
no longer dedicated targets. The end-user purchases a machine and installs
generic software on it. The binaries for the operating system and applications
are simply downloaded and installed. Think in terms of "Linux distribution"
and "package management". A single binary shall be installed and capable to
run on any Arm64 machine and get the best of it (i.e. use the appropriate
optimizations when available).

This note explores some aspects of this problem and how to solve it.

## Classes of optional instructions

There are at least three distinct classes of optional instructions in the
Arm64 architecture. Each of them shall be treated differently in the
perspective of a generic build.

### Hints

In the Arm64 instruction set, there is a whole range of encoding for _hint_
instructions. Functionally, these instructions do nothing. They do not change
the semantics of the program. By default, they act as a NOP. They are silently
ignored by the execution unit.

However, some of these hint instructions are used in specific Arm features
to define hints on the execution when a CPU implements the corresponding
optional features.

Examples of these instructions are PACIA, AUTIA (pointer authentication) or
BTI (branch target identification).

When FEAT_PAuth is implemented, PACIA adds a pointer authentication code - or signature -
to a pointer. AUTIA verifies the validity of a signed pointer and, when the signature
is valid, restores the original value. When FEAT_PAuth is not implemented, these
instructions are just hints, they do nothing, the pointer is not modified.

Although PACIA alone actually modifies the value of a register containing a pointer,
a well-formed sequence of PACIA - AUTIA is transparent. It adds security robustness
against malware injection but it does not modifies the semantics or execution flow
of the application (in the absence of malicious attack).

Optional instructions in the hint range can consequently be generated in generic
binaries. The binary runs on all levels of Arm64 architecture. The overhead of the
"unused" instructions is negligible on CPU's which do not implement the corresponding
Arm feature. On the other hand, the security benefit of these instructions is very
significant to mitigate malware injection on CPU's which implement it.

The recommended strategy is to always compile with these instructions.

### Non-replaceable instructions

A few optional instructions implement small optimizations which affect the semantics
of the program. These instructions raise an "illegal instruction" fault on CPU's which
do not implement the corresponding Arm feature.

In the set of pointer authentication instructions, this is the case of the RETAA
instruction. It is equivalent to a sequence of AUTIASP and RET. This instruction
has an important semantics, it "returns", meaning it branches to the code address
in register X30 (after validating the pointer's signature). This cannot be ignored
or guessed by older CPU's.

Let's illustrate this. On Linux, using `gcc -mbranch-protection=pac-ret`, the generated
code for a function prolog and epilog is:
~~~
    paciasp
    ...
    autiasp
    ret
~~~
This code is generic and works with or without FEAT_PAuth. Without this feature, the
instructions PACIASP and AUTIASP act as NOP.

However, using `gcc -mbranch-protection=pac-ret -march=armv8.3-a`, the code sequence becomes:
~~~
    paciasp
    ...
    retaa
~~~
We have informed the compiler that the target implements at least Armv8.3-a. At this level
of architecture, FEAT_PAuth is mandatory and the instruction RETAA is always implemented.
However, running this binary at lower levels of the architecture will raise an "illegal
instruction" fault.

For dedicated targets, it is tempting to use the fine-tuned options and generate the most
optimized instructions. However, for generic binaries, the overhead of using two instructions
instead of one at the end of each function is negligible.

The recommended strategy is to not use these instructions on generic binaries.

### Accelerated instructions

Other optional instructions provide a much more significant performance improvement,
speeding up standard algorithms such as AES by a factor of 10 or even 20.
It is not possible to avoid them when they are available. 

However, this is not just a matter of two levels of architectures, with or without
accelerated instructions. Each feature is individually selectable and it is not acceptable
to produce dedicated binaries for all possible combinations of FEAT_AES, FEAT_SHA1, FEAT_SHA256,
FEAT_SHA512, FEAT_SHA3, FEAT_CRC32.

The recommended strategy is to implement the two versions of critical algorithms in
the same universal binary. One version is "portable". It can be executed on
all architectures and uses standard instructions only. The second version explicitly
uses the accelerated instructions, either using `asm()` directives or the equivalent
compiler intrinsics.

At run time, the program tests the availability of the corresponding Arm feature and,
depending on the result, branches to one implementation or the other.

Although it is simple in principle, the devil is in the details and the lack of
flexibility of the gcc and clang compilers may introduce fatal issues. The next
section explains in details what are these issues and how to solve them using
practical examples.

## Building with accelerated instructions

### The problems of gcc and clang

In principle, using accelerated instructions in a generic binary is simple.

The vast majority of the code is written in portable C/C++ and the compiler
generates instructions which, in the absence of specific `-march` or `-target`
option, run on all Arm64 CPU's.

In some specific branches of code, we explicitly use specific instructions in
`asm()` directives or specific compiler intrinsics. In these cases, we do not
request the compiler to generate the most appropriate instructions based on
the target. We just tell the compiler which precise instructions to insert in
the binary. We could expect the compiler to simply translate this into binary
without complaining.

That would be too simple.

The two compilers refuse to generate _explicit_ instructions when the specified
target does not implement them by default. We must specify a precise level
of architecture and options on the command line.

This introduces two distinct problems: inconsistent naming and combinations of
Arm features and unexpected side effects on code generation.

#### Inconsistent feature naming

In the early days of the Arm architecture, the level of architecture (7.0, 7.1, etc)
defined a set of features. This is no longer the case. Each feature is uniquely
identified by a name FEAT_xxx and can be implemented at various levels of architectures.

There are of course a number of dependencies which are mandatory but the
principle is that each feature is individually identified.

However, gcc and clang do not follow that scheme. Many features are still bound
to an explicit level of architecture, as in the old days. Additional features must
be specified in the `-march` options but their naming and combinations are
inconsistent with the Arm naming.

See some examples below:

- To start with the only consistent one, FEAT_CRC32 is activated using option
  `-march=armv8-a+crc`.

- More questionable, FEAT_AES and FEAT_SHA1 are activated using `-march=armv8-a+crypto`.
  These two features are distinct but cannot be individually handled by the compiler.
  The compiler only knows some "crypto" feature (which only covers a small part of the
  cryptographic instructions, AES and SHA-1).

- It starts to become weird with FEAT_SHA256. It can be activated only with
  `-march=armv8-a+crypto+sha2`. Why `crypto+sha2` and not only `sha2`?
  Moreover, SHA-256 and SHA-512 are both part of the SHA-2 family but FEAT_SHA256
  and FEAT_SHA512 are distinct features.

- Finally, it becomes completely insane with FEAT_SHA512. It requires the options
  `-march=armv8.2-a+crypto+sha2+sha3`. Note the required combination of `crypto+sha2+sha3`
  which is particulary insane since SHA-512 is part of SHA-2, not SHA-3. And
  the Arm architecture also defines a specific FEAT_SHA3 which is completely distinct.

In the last case, also note the required `-march=armv8.2-a` to get access
to FEAT_SHA512. This creates very unconvenient side effects.

#### Side-effects on code generation

Based on the observations of the previous section, we are tempted to specify
some "wide" compilation option which accepts all the specialized instructions
and intrinsics that we explicitly use in the code.

In the case of FEAT_SHA512, for instance, this means using `-march=armv8.2-a+crypto+sha2+sha3`.
However, note the required `armv8.2-a`. This has a very nasty effect on generic
binaries. The compiler feels free to generate any kind of instruction which
is new in Armv8.2 or 8.1, independently of the explicit instructions
we use in our code.

This is not a theoretical threat. That happened for real in practical code.
An application was compiled with that option because some dedicated branch
of code used specialized instructions for SHA-512. The code used to run fine
on recent Arm CPU cores until it was run on a Raspberry Pi 4 where it crashed
with an "illegal instruction" fault. This system uses Cortex A72 cores, based
on Armv8.0. An analysis of the core dump exibited that the program stopped on
an atomic add instruction which is defined in the FEAT_LSE feature (introduced in Armv8.1).
Because of the required `-march=armv8.2-a` for FEAT_SHA512, the compiler decided to
use the FEAT_LSE instructions in unrelated parts of the code.

### Possible improvements in compilers

The use case we expect the compilers to address is the following: compile generic
binaries with specialized parts using explicit instructions or intrinsics.

This is a requirement for the adoption of the Arm64 in the server ecosystem.
But we have just seen that this not easy to implement in practice.

Several possible improvements are suggested here for gcc and clang.

- Accept explicit instructions and intrinsics without explicit specification
  of a precise target. It is recommended to issue a warning when these instructions
  or intrinsics do not match the explicit targets. Developers doing this on
  purpose will mute this specific warnings in the corresponding branches of
  code using pragmas.

- Maybe more complicated, allow a temporary change of target using pragmas,
  just like warning pragmas. For instance:
~~~
    if (sha512_supported_on_this_cpu()) {
        #pragma target push
        #pragma target march=armv8.2-a+crypto+sha2+sha3
        ...
        #pragma target pop
    }
~~~

- Disconnect Arm features from the Arm architecture level. The problem which
  was described in the previous section is due to the fact that gcc requires
  to specify Armv8.2 to use FEAT_SHA512 and Armv8.2 implicitely activates FEAT_LSE
  (and many other features). It should be possible to specify `-march=armv8-a+sha512`.

- Adopt a more Arm-compatible feature segmentation and naming. Requiring `crypto+sha2+sha3` for
  FEAT_512 is particularly insane. These specific features should be individually
  selectable, as in `-march=armv8-a+crc+aes+sha1+sha256+sha512+sha3`.

Of course, these rules only apply to specific Arm features which are required to
build generic binaries with optimal implementation.
Most features which are marked as mandatory at a given level of architecture will continue
to be implicitely activated. For instance, `-march=armv8.1-a` is sufficient to
activate FEAT_LSE. This feature is not one that brings a significant improvement
in generic binaries.

### Proposed solution with current compilers

As a lesson from the previously described problem, we must be very careful to
never execute any part of a compilation unit which was built with non-generic `-march`
option on a CPU which does not implement it.

Within the limitations of the current compilers, the proposed solution is
the following:

- Restructure the source files in the application.
- Isolate the specialized branches of code in dedicated source files ("compilation units").
- Compile each of these specialized modules with the exact compilation options it needs.
- Compile all other modules without explicit `-march` option (or simply `-march=armv8-a`
  in the case of cross-compilation).
- Check the availability of the Arm features at run time in the generic modules
  and call dedicated functions in the specialized modules only when the check succeeds.

### Complete example

A complete example is proposed in the directory [samples/compile-accel](../samples/compile-accel).

This is the skeleton of an application which uses CRC-32, AES, SHA-1, SHA-256, SHA-512.
The cryptographic algorithms are replaced by simple `printf()`. This example only illustrates
the source code structure and build procedures.

The individual algorithms are (hypothetically) implemented in several source files:
`aes.c`, `crc.c`, `sha1.c`, `sha256.c`, `sha512.c`. These modules contain the portable
implementation of their respective algorithm.

The accelerated versions, using specialized instructions or intrinsics, are (hypothetically)
implemented in distinct source files: `aes_accel.c`, `crc_accel.c`, `sha1_accel.c`,
`sha256_accel.c`, `sha512_accel.c`. The compilation of these modules uses the specific
fine-tuned options for the specialized instructions or intrinsics they use.

This part of the makefile looks like this:
~~~
CFLAGS += $(CFLAGS_TARGET)

ifeq ($(subst aarch64,arm64,$(shell uname -s -m)),Linux arm64)
    crc_accel.o:    CFLAGS_TARGET = -march=armv8-a+crc
    aes_accel.o:    CFLAGS_TARGET = -march=armv8-a+crypto
    sha1_accel.o:   CFLAGS_TARGET = -march=armv8-a+crypto
    sha256_accel.o: CFLAGS_TARGET = -march=armv8-a+crypto+sha2
    sha512_accel.o: CFLAGS_TARGET = -march=armv8.2-a+crypto+sha2+sha3
    sha3_accel.o:   CFLAGS_TARGET = -march=armv8-a+sha3
endif
~~~

Notes:
- We need this on Linux only. On macOS, the support for the Arm features
  is implicit because all supported Arm cores are above Armv8.5.
- Depending on the system, `uname -m` may return `aarch64` or `arm64`.

The individual Arm features are tested at run-time in the generic modules (e.g. `aes.c`).
We do not use the kernel module from this educational project. Instead, we use some
OS-specific features which extract a few features from the kernel. Fortunately, the
features we need are among them.

On Linux, we use `getauxval()`. On macOS, we use `sysctlbyname()`.

Sample execution on a MacBook M1, Armv8.5 CPU, implementing all cryptographic accelerations,
macOS host or Linux virtual machine:
~~~
crc(): accelerated implementation
aes(): accelerated implementation
sha1(): accelerated implementation
sha256(): accelerated implementation
sha512(): accelerated implementation
sha3(): accelerated implementation
~~~

Execution of the same Linux binary on a Raspberry Pi 4, BCM2711 SoC, Cortex A72 core, Armv8.0,
implementing FEAT_CRC32 only:
~~~
crc(): accelerated implementation
aes(): portable implementation
sha1(): portable implementation
sha256(): portable implementation
sha512(): portable implementation
sha3(): portable implementation
~~~

We can see that the same generic binary runs on different levels of CPU but takes
advantage of the features of each of them.

For the record, the same set of source files can be built and executed on a non-Arm
system. Execution example on an Intel x86_64 CPU:
~~~
crc(): portable implementation
aes(): portable implementation
sha1(): portable implementation
sha256(): portable implementation
sha512(): portable implementation
sha3(): portable implementation
~~~
