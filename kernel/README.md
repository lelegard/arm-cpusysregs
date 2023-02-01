# Kernel modules for Linux and macOS

This directory contains the kernel modules for Linux and macOS, in their respective subdirectories.
On both cases, the name of the module is `cpusysregs`.

The header file `cpusysregs.h` defines the interface between the kernel module and the userland.
This file is included in the sources of the kernel modules (Linux and macOS) and in the applications.

Due to the architectures of the kernel modules interfaces in the two OS, the details of the interfaces
are slightly different on Linux and macOS.

- On Linux, the kernel module creates a special device named `/dev/cpusysregs`. Accessing the CPU
  system registers is done using `ioctl()` on this device.
- On macOS, the kernel extension uses the system socket communication. It defines a system socket
  named `cpusysregs`. Accessing the CPU system registers is done using `getsockopt()` and `setsockopt()`
  on this socket.

In the `apps` directory, the C++ class named `RegAccess` (files `regaccess.h` and `.cpp`)
encapsulates these differences to provide a higher-level of abstraction.
