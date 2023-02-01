# Linux loadable kernel module `cpusysregs`

The file `cpusysregs.c` contains the source code of the kernel module. The module name is `cpusysregs`.
It creates a special device named `/dev/cpusysregs` which can be accessed from any userland process.
It is not possible to read or write on this device. We can only send a few `ioctl()`.
This is the way the system registers of the CPU are accessed.

Usage instructions:
- `make` : Build the kernel module.
- `make install` : Install the module in the kernel file tree (`sudo` inside).
- `make load` : Load the kernel module (`sudo` inside).
- `make unload` : Unload the kernel module (`sudo` inside).
- `make show` : Show the loaded kernel module (`lsmod`, no `sudo`).

The kernel module can be dynamically loaded and unloaded. This means that it is possible
to modify the module and reload it on the fly, without rebooting the system. This is not
the case with macOS.
