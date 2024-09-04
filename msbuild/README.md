# Building for Windows

**Contents:**

* [No native Arm64 driver development on Windows so far](#no-native-arm64-driver-development-on-windows-so-far)
* [Prerequisites](#prerequisites)
  * [Build system setup](#build-system-setup)
  * [Arm64 target system setup](#arm64-target-system-setup)
* [Building the driver and the applications](#building-the-driver-and-the-applications)
* [Loading / unloading the driver](#loading--unloading-the-driver)
* [Additional notes](#additional-notes)
  * [Lack of ARM64 assembler support](#lack-of-arm64-assembler-support)
  * [Accessing some system registers crashes the system](#accessing-some-system-registers-crashes-the-system)
  * [PAC instructions are disabled](#pac-instructions-are-disabled)

## No native Arm64 driver development on Windows so far

As of this writing, Visual Studio 17.5.x is available on Windows 11 Arm64.
However, the Windows Driver Kit (WDK) is not. This means that, on Windows Arm64,
you can develop userland applications but not drivers.

The question was [asked here](https://stackoverflow.com/questions/75793332/how-to-natively-build-windows-11-device-drivers-for-arm64-on-an-arm64-system)
but no answer was received.

To build this project, you must use an Intel PC with Windows 10 or 11, Visual Studio,
including the Arm64 building tools, and the WDK. The Arm64 driver and the applications
can be compiled on the Intel PC and then moved to the Windows Arm64 system.

To facilitate this process, the script `build-arm64-archive.ps1` can be used on the
development system. It builds the drivers and the applications. Then, it packages the
binaries and the loader scripts in one single archive `arm-cpusysregs.zip` in this
directory. Just move the archive on the target Arm64 Windows 11 system.

## Prerequisites

### Build system setup

- Install or update Visual Studio. Make sure that the latest version of the `ARM64/AMR64EC`
  build tools are installed.
  - To update your Visual Studio installation, start the "Visual Studio Installer" application.
  - Update first if your Visual Studio is not up-to-date. Wait for the update to complete.
  - Click "Modify" -> select the "Individual components" tab.
  - Scroll down to "Compilers, build tools, and runtimes" section.
  - Select "MSVC v143 - VS 2022 C++ ARM64/ARM64EC build tools (latest)"
    (may be different on newer versions).
  - Select "MSVC v143 - VS 2022 C++ ARM64/ARM64EC Spectre-mitigated libs (latest)".
    Although we do not require Spectre mitigation, it has been observed that the driver
    fails to compile without this component.
  - Click "Modify" (lower right corner). Wait for the update to complete.

- Install the Windows Driver Kit (WDK) on the development system.
  - See: https://learn.microsoft.com/en-us/windows-hardware/drivers/download-the-wdk
  - You may need to install the latest Windows SDK first (link from same page).

- Check some permissions on the build system.
  - Make sure that the developer has write access to the directory
    `C:\ProgramData\Microsoft\Crypto\RSA\MachineKeys`. Grant access if necessary.
    It has been observed that the build procedure creates a file here during the
    signature of the binary of the driver. Even though this is a self-signature,
    it creates a file there. If your build fails with "Access is denied" while
    signing the driver, the problem is probably there.

### Arm64 target system setup

- Disable driver signature validation on the target Arm64 Windows 11 system.
  - Start Menu -> Settings -> System -> Recovery -> Advanced Startup -> Restart now
  - "Light blue" boot menu -> Troubleshoot -> Advanced options -> Startup settings -> Restart
  - Press F7 (for 7th option "Disable driver signature enforcement")
  - By default, this settings is not persistent across reboots. If the system is restarted
    (or if it crashed in the driver...), you have to go through this procedure again.
    To make this settings permanent, you have to disable secure boot.

- Disable secure boot on the target Arm64 Windows 11 system
  (if you want to permanently disable driver signature enforcement).
  - Start Menu -> Settings -> System -> Recovery -> Advanced Startup -> Restart now
  - "Light blue" boot menu -> Troubleshoot -> UEFI Firmware Settings.
  - Find the Secure Boot setting in your BIOS menu. If possible, set it to Disabled.
    This option is usually in either the Security tab, the Boot tab, or the Authentication tab.
    Save changes and exit => reboot.
  - Some systems (such as UTM/Qemu virtual machines) do not have an option to
    disable secure boot in their (virtual) BIOS. In that case, there is no other
    option than disabling driver signature enforcement after each reboot...

## Building the driver and the applications

First option: Use the Visual Studio IDE, open solution file `cpusysregs.sln`,
select "Release" configuration, build the solution. Note that this project is
specific to the ARM64 platform and has no option for Intel platforms, x86 or x64.

Second option: Run the PowerShell script `build.ps1`.
- It can be directly started from the Windows Explorer (right-click on the script
  and select "Run with PowerShell" if this is not the default).
- When run from a PowerScript windows or from another PowerShell script, use option
  `-NoPause` to avoid the user confirmation at the end of the build.

In all cases, the binaries for the driver (`cpusysregs.sys`) and the applications are
left in the `msbuild\ARM64\Release` directory.

## Loading / unloading the driver

The driver must be explicitly loaded and unloaded using the script `loader.ps1`.

Once the driver has been loaded using an administrator account, the applications
can be run from any account.

Options:
~~~
-Load     Load the driver (the default)
-Unload   Unload the driver
-Show     Show the state of the driver
-NoPause  Do not wait for user input at end (for use in other scripts)
~~~

By default, double-clicking on `loader.ps1` from the Windows Explorer loads
the driver and waits for user input before closing the created PowerShell window.
Administrator privileges are requested through UAC if necessary.

The script `loader-unload.ps1` is a shortcut for `loader.ps1 -Unload`. It is
provided to unload the driver using a double-click on this script from the
Windows Explorer.

## Additional notes

### Lack of ARM64 assembler support

On Windows, it is currently not supported to embed inline `__asm` directives
in C code for ARM64 targets. This is possible for Intel assembler only.

In the Linux and macOS implementations of this project, inline assembly is
used for MSR, MRS, PACxx and AUTxx instructions. On Windows, MSR and MRS
can be replaced with intrinsics. However, there is no equivalent for
PACxx and AUTxx instructions.

To implement PACxx and AUTxx instructions, a separate assembler source
file [kernel\windows\pac.asm](../kernel/windows/pac.asm) contains small
helper functions for these instructions.

This assembler file is separately compiled and linked for the driver and
the applications. At that point, there is a new difficulty: the ARM64
assembler is not integrated in MSBuild and Visual Studio IDE. The
integration is done using the three files [armasm.props](armasm.props),
[armasm.targets](armasm.targets), and [armasm.xml](armasm.xml). Arm64
assembler files can then be integrated using `<ARMASM>` XML directives
in project files.

### Accessing some system registers crashes the system

Accessing any of the following system registers from the Windows driver
crashes the system: `CTR_EL0`,  `TPIDRRO_EL0`,  `TPIDR_EL0`,  `TPIDR_EL1`.
They are disabled by default in `sysregs -a`.

### PAC instructions are disabled

PAC and AUT instructions are "disabled". PAC instructions (except PACGA)
do nothing. The pointer is not modified, no signature is inserted.

All key registers are reset to zero in all processes. You may modify
them, the content will be retained for the rest of the process.
But the PAC instructions remain ineffective.

Only PACGA seems to work as expected.
