# How to build applications using specific Arm features

**Contents:**

## The problem

The Arm64 architecture has more than 240 [optional features](features.md).
Some of them define additional instructions which are specific to this feature.
Using them on a CPU which does not implement the corresponding feature does nothing
at best or crashes the application on an "illegal instruction" fault at worst.

Some of these specific instructions bring a significant performance improvement.
This is the case for the "accelerated cryptographic instructions" for CRC, AES,
SHA-1, SHA-256, SHA-512. When available, these instructions may accelerate the
corresponding algorithm with a factor or 10 or even 20. It is consequently
important to use them when available.

The gcc and clang compilers have options to specify the target CPU, its level
of architecture and the Arm optional features. Depending on these options, the
compiler will generate - or refuse to generate - the instructions which are
specific to an Arm feature.

This approach is acceptable in an embedded computing environment, the original
domain where Arm CPU were used first. In such a context, the application is
compiled for a dedicated unique target. It is consequently possible to fine-tume
the compilation options for a specific target.

However, as Arm CPU's are now frequently used in server environments, this
approach is no longer acceptable. On a generic server or laptop, there is
no longer dedicated targets. The end-user purchases a machine and installs
generic software on it. The binaries for the operating system and applications
are simply downloaded and installed. Think in terms of "Linux distribution"
and "package management". A single binary shall be installed and capable to
run on any Arm64 machine and get the best of it (ie. use the appropriate
optimizations when available).

This note explores some aspects of this problem and how to solve it.

## Classes of optional instructions

There are at least three distinct classes of optional instructions in the
Arm64 architecture. Each of them shall be treated differently in the
perspective of a generic build.

### Hints

In the Arm64 instruction set, there is a whole range of encoding for "hint"
instructions. Functionally, these instructions do nothing. They do not change
the semantics of the program. By default, they act as a NOP. They are silently
ignored by the execution unit.

However, some of these hint instructions are used in specific Arm features
to define "hints" on the execution when a CPU implements the corresponding
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
binaries


### Non-replaceable instructions

### Accelerated instructions



[samples/compile-accel](../samples/compile-accel)

~~~
crc(): accelerated implementation
aes(): accelerated implementation
sha1(): accelerated implementation
sha256(): accelerated implementation
sha512(): accelerated implementation
~~~
