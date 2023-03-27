#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# PowerShell script to build the driver and the applications for ARM64
# and package an archive. Useful when cross-building from a Windows Intel
# machine (as long as the WDK is not natively supported in Windows ARM64).
#
#----------------------------------------------------------------------------


[CmdletBinding(SupportsShouldProcess=$true)]
param([switch]$NoPause = $false)

# Build driver and applications.
& "$PSScriptRoot\build.ps1" -NoPause

# Build archive.
Compress-Archive -Force -DestinationPath "$PSScriptRoot\arm-cpusysregs.zip" @(
    "$PSScriptRoot\loader.ps1",
    "$PSScriptRoot\loader-unload.ps1",
    "$PSScriptRoot\..\collect\collect.ps1",
    "$PSScriptRoot\ARM64\Release\cpusysregs.sys",
    "$PSScriptRoot\ARM64\Release\*.exe"
)

if (-not $NoPause) {
    pause
}
