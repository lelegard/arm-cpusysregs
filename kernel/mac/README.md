# macOS kernel extension `cpusysregs`

The file `cpusysregs.c` contains the source code of the kernel extension. The extension name is `cpusysregs`.
It creates a system socket named `cpusysregs` which can be accessed from any userland process.
It is not possible to send or receive on this socket. We can only send a few `getsockopt()`
and `setsockopt()`. This is the way the system registers of the CPU are accessed.

## Usage instructions

- `make` : Build the kernel extension.
- `make install` : Install the extension in the system tree (`sudo` inside).
- `make load` : Load the kernel extension (`sudo` inside).
- `make unload` : Unload the kernel extension (`sudo` inside).
- `make show` : Show the loaded kernel extension (no `sudo`).

## Limitations

### Disable the system integrity protection

We assume here that we are not registered "Apple developers", meaning that we
have no "developer id", no developer certificate and we cannot sign a kernel
extension with a trusted signature.

The macOS system is highly protected against casual or malicious alterations.
Unlike permissive systems such as Linux, being `root` on macOS does not give us any
right to load an unauthenticated kernel extension. To test this module, we need to
downgrade the security of the system.

Disclaimer: Each new version of macOS tends to be even more secure than the
previous one. This note is applicable to macOS 13 (Ventura). Other versions
may need a different setup.

If we want to test our kernel extension, we must first disable the system integrity.
This puts our system at risks at should be done on test systems only.

Here is the initial procedure to prepare the system using the macOS "recovery mode".

- Shutdown the system. With power off. Do not simply restart the system. We are not
  allowed to disable the system integrity if the system was _restarted_ in recovery mode.
  The system must have booted in recovery mode from a power off state. This is a clever
  security precaution to make sure that the operation is manually performed by a human
  and not automatically triggered by some malware.
- Boot the system, keeping the finger on the power button to display the boot options.
- Select "Options", "Continue", select a user, "Next", enter our password.
- Open the "Boot Security Utility" from the "Utilities" top menu.
  - Allow users to manage kernel extensions.
- Open a terminal from the "Utilities" top menu.
  - Enter command `csrutil disable`. This command disables the System Integrity Protection"
    (SIP). It prompts for our user name and password again.
- Reboot the system.

When our tests are completed, it is recommended to restore the System Integrity Protection.
Use the same procedure as above, but enter `csrutil enable` instead of `disable`.

### Reboot on kernel extension update

The macOS "kernel extensions" are dynamically _loadable_ but not dynamically _replaceable_.
Each time we rebuild the kernel extension and install it, we need to rebind it into the
kernel and reboot.

More precisely, each time we run `make install`, a popup window requests to authorize the
replacement of the kernel extension using the "System Preferences" tool. Once authorized,
another popup proposes to reboot. Just do it. A message informs us that the system cache
is rebuilt and the system reboots.

Once the system is rebooted, the kernel extension is present in the system but not loaded.
It can be loaded and unloaded as many times as we want using `make load` and `make unload`.
Until we modify the extension and need to reboot.

### Reading the PAC key registers is not allowed

The pointer authentication (PAC) feature uses 5 keys: PACIA, PACIB (instruction), PACDA,
PACDB (data) and PACGA (generic).

The corresponding keys are stored in 5 pairs of system registers which are accessible
at EL1 (kernel mode). Typically, these keys are specific per process. The kernel generates
random values for these keys when a process is created. These values remain valid for the
life of that process. The PAC key registers are initialized with these values each time the
process is scheduled.

In the macOS kernel, trying to read any of these registers result in a fault, which then
crashes the system since we are in kernel mode.

This limitation is not hard-coded in the hardware of the CPU. When running a Linux
virtual machine on the same CPU, these registers are readable from the Linux kernel.
