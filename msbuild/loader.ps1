# Driver loader / unloader from PowerShell.
#
# There are two methods to load / unload the driver:
# 1) PowerShell: this script
# 2) C++ application: see loader.cpp

[CmdletBinding(SupportsShouldProcess=$true)]
param(
    [switch]$Load = $false,
    [switch]$Unload = $false,
    [switch]$Query = $false,
    [switch]$NoPause = $false
)

# -Load is the default.
$Load = $Load -or ((-not $Unload) -and (-not $Query))

# Local architecture is x64 or ARM64
$Arch = if ((Get-CimInstance Win32_OperatingSystem).OSArchitecture -match "arm") {"AMR64"} else {"x64"}

# Driver description. Search binary in build directory and in same directory.
$DriverName = "cpusysregs"
$DriverSys = "$PSScriptRoot\$Arch\Release\$DriverName.sys"
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
    if ($Query) {
        $cmd += " -Query"
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
    if ($Query) {
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
