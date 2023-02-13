# Demo applications and utilities

## Sample usages of the `cpusysregs` kernel module

`sysregs` is a generic tool to read and write the system registers.

On Linux, `demo-pac` demonstrates some usages of the pointer authentication
features. It should be used on Linux only. On macOS, the PAC key registers
are protected from kernel access and using this program crashes the system.

## Sample Arm features without using the kernel module

On Linux, `linux-hwcaps.cpp` demonstrates how to determine a subset of the Arm
features using `getauxval()` from userland.

On macOS, `mac-sysctl` demonstrates how to determine a subset of the Arm
features using `sysctl()` from userland.
