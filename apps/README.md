# Demo applications and utilities

**Contents:**

* [Sample usages of the cpusysregs kernel module](#sample-usages-of-the-cpusysregs-kernel-module)
* [Demo applications](#demo-applications)
* [Sample Arm features without using the kernel module](#sample-arm-features-without-using-the-kernel-module)

## Sample usages of the `cpusysregs` kernel module

`sysregs` is a generic tool to read and write the system registers.

## Demo applications

These applications attempt to read or write the PAC key registers and
should be used on Linux only. On macOS, the PAC key registers are protected
from kernel access and the demo can only run with the current PAC keys,
without reading or modifying them.

- `demo-pac` demonstrates some usages of the pointer authentication features.
- `pacga` computes PAC values using specified keys and values.

## Sample Arm features without using the kernel module

On Linux, `linux-hwcaps.cpp` demonstrates how to determine a subset of the Arm
features using `getauxval()` from userland.

On macOS, `mac-sysctl` demonstrates how to determine a subset of the Arm
features using `sysctl()` from userland.

The program `demo-userfeatures` demonstrates the usage of the C++ class
`UserFeatures` which returns the most important Arm features in a portable way,
independently of the rest of this project, without the help of a kernel module.
The class can be reused in any project. It works well on macOS. On Linux, however,
some less used features are incorrectly reported by the kernel (incomplete MRS emulation).
