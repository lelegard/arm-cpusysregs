# Kernel modules for Linux, macOS, Windows

This directory contains the kernel modules for Linux, macOS, Windows, in their respective subdirectories.
In all cases, the name of the module is `cpusysregs`.

The header file `cpusysregs.h` defines the interface between the kernel module and the userland.
This file is included in the sources of the kernel modules (Linux, macOS, Windows) and in the applications.

Due to the architectures of the kernel modules interfaces in the various OS, the details of the interfaces
are slightly different.

- On Linux, the kernel module creates a special device named `/dev/cpusysregs`. Accessing the CPU
  system registers is done using `ioctl()` on this device.
- On macOS, the kernel extension uses the system socket communication. It defines a system socket
  named `cpusysregs`. Accessing the CPU system registers is done using `getsockopt()` and `setsockopt()`
  on this socket.
- On Windows, the kernel driver creates a special device named `\\.\cpusysregs`. Accessing the CPU
  system registers is done using `DeviceIoControl()` on this device.

In the `apps` directory, the C++ class named `RegAccess` (files `regaccess.h` and `.cpp`)
encapsulates these differences to provide a higher-level of abstraction.

The script `extract-sreg-definitions.sh` automatically generates the `CSR_SREG_xxx` definitions
of all Arm system registers, as used in `cpusysregs.h`. The definition of all registers is based
on reference XML files on the Arm public web site. This script may be executed each time an update
of the Arm architecture is published.
