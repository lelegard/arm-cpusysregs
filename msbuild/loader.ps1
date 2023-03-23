#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# PowerShell script to load and unload the driver.
#
# Options:
#   -Load     Load the driver (the default)
#   -Unload   Unload the driver
#   -Show     Show the state of the driver
#   -NoPause  Do not wait for user input at end (for use in other scripts)
#
#----------------------------------------------------------------------------

[CmdletBinding(SupportsShouldProcess=$true)]
param(
    [switch]$Load = $false,
    [switch]$Unload = $false,
    [switch]$Show = $false,
    [switch]$NoPause = $false
)

# -Load is the default.
$Load = $Load -or ((-not $Unload) -and (-not $Show))

# Driver description. Search binary in build directory and in same directory.
$DriverName = "cpusysregs"
$DriverSys = "$PSScriptRoot\ARM64\Release\$DriverName.sys"
if (-not (Test-Path $DriverSys)) {
    $DriverSys = "$PSScriptRoot\$DriverName.sys"
}

# Must be admin.
$IsAdmin = ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)

if (-not $IsAdmin) {
    # Recurse the current script in administrator mode.
    Write-Output "Must be administrator to continue, trying to restart as administrator ..."
    $cmd = "& '" + $MyInvocation.MyCommand.Path + "'"
    if ($Load) {
        $cmd += " -Load"
    }
    if ($Unload) {
        $cmd += " -Unload"
    }
    if ($Show) {
        $cmd += " -Show"
    }
    if ($NoPause) {
        $cmd += " -NoPause"
    }
    Start-Process -Wait -Verb runas -FilePath PowerShell.exe -ArgumentList @("-ExecutionPolicy", "RemoteSigned", "-Command", $cmd)
}
else {
    if ($Load) {
        Write-Output ""
        Write-Output "Creating kernel driver service $DriverName..."
        sc.exe create "$DriverName" "displayname=$DriverName" "binpath=$DriverSys" type=kernel start=demand error=normal
        Write-Output "Starting service $DriverName..."
        sc.exe start "$DriverName"
        Write-Output ""
    }
    if ($Show) {
        Write-Output ""
        sc.exe query "$DriverName"
        Write-Output ""
    }
    if ($Unload) {
        Write-Output ""
        Write-Output "Stopping service $DriverName..."
        sc.exe stop "$DriverName"
        Write-Output "Deleting service $DriverName..."
        sc.exe delete "$DriverName"
        Write-Output ""
    }
}

if (-not $NoPause) {
    pause
}
