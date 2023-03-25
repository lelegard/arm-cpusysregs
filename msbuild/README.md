# Building for Windows

**Warning:** Preliminary notes, this project is not ready yet for Windows.

As of this writing, Visual Studio 17.5.x is available on Windows 11 Arm64.
However, the Windows Driver Kit (WDK) is not. This means that, on Windows Arm64,
we can develop userland applications but not drivers. In 2023...

Question [asked here](https://stackoverflow.com/questions/75793332/how-to-natively-build-windows-11-device-drivers-for-arm64-on-an-arm64-system)
but no answer was received.

To build this project, we must use an Intel PC with Windows 11, Visual Studio,
including the Arm64 building tools, and the WDK. The Arm64 applications and
drivers can be compiled on the Intel PC and then moved to the Windows Arm64 system.

## Prerequisites

- Install the Windows Driver Kit (WDK).
  - See: https://learn.microsoft.com/en-us/windows-hardware/drivers/download-the-wdk
  - May need to install the latest Windows SDK first (link from same page).

- Disable driver signature validation.
  - Start Menu -> Settings -> System -> Recovery -> Advanced Startup -> Restart now
  - "Light blue" boot menu -> Troubleshoot -> Advanced options -> Startup settings -> Restart
  - Press F7 (for 7th option "Disable driver signature enforcement")
  - This settings may not always be persistent across reboots (to be confirmed).

- Disable secure boot on Windows 11 (may be necessary in some cases).
  - Start Menu -> Settings -> System -> Recovery -> Advanced Startup -> Restart now
  - "Light blue" boot menu -> Troubleshoot -> UEFI Firmware Settings.
  - Find the Secure Boot setting in your BIOS menu. If possible, set it to Disabled.
    This option is usually in either the Security tab, the Boot tab, or the Authentication tab.
    Save changes and exit => reboot

## Loading / unloading the driver

The driver must be explicitly loaded and unloaded using the script `loader.ps1`.
Administrator privileges are requested through UAC.

Once the driver has been loaded using an administrator account, the applications can be run from any account.
