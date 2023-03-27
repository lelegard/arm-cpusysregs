# Windows kernel driver `cpusysregs`

The file `cpusysregs.c` contains the source code of the kernel driver.

It creates a special device named `\\.\cpusysregs` which can be accessed from any userland process.
It is not possible to read or write on this device. We can only send a few `DeviceIoControl()`.
This is the way the system registers of the CPU are accessed.

Additional notes and usage instructions: see [msbuild directory](../../msbuild).
