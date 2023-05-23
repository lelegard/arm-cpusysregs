#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# PowerShell script to collect various standard information on the
# current platform.
#
#----------------------------------------------------------------------------


[CmdletBinding(SupportsShouldProcess=$true)]
param(
    [parameter(mandatory=$true)][string]$DestDir,
    [string]$BinDir = ""
)

# Search binary in build directory and in same directory as this script.
if (-not $BinDir) {
    $BinDir = (Split-Path -Parent $PSScriptRoot) + "\msbuild\ARM64\Release"
}
if (-not (Test-Path "$BinDir\sysregs.exe")) {
    $BinDir = $PSScriptRoot
}
if (-not (Test-Path "$BinDir\sysregs.exe")) {
    Write-Output "sysregs.exe not found, specify -BinDir"
    exit 1
}

# Destination directory.
if (-not (Test-Path -PathType Container $DestDir)) {
    [void](New-Item -ItemType Directory $DestDir)
}

# Generate result files.
echo "Creating cpusysregs-* files"
$OS = (Get-WmiObject -class Win32_OperatingSystem)
Write-Output "Windows version $($OS.Version)" | Out-File -Encoding ascii "$DestDir\cpusysregs-system.txt"
Write-Output $OS.Caption | Out-File -Encoding ascii -Append "$DestDir\cpusysregs-system.txt"

. $BinDir\sysregs -s    | Out-File -Encoding ascii "$DestDir\cpusysregs-features.txt"
. $BinDir\sysregs -p    | Out-File -Encoding ascii "$DestDir\cpusysregs-pac.txt"
. $BinDir\sysregs -a -v | Out-File -Encoding ascii "$DestDir\cpusysregs-registers.txt"
. $BinDir\demo-pac      | Out-File -Encoding ascii "$DestDir\cpusysregs-demo-pac-1.txt"
. $BinDir\demo-pac      | Out-File -Encoding ascii "$DestDir\cpusysregs-demo-pac-2.txt"
. $BinDir\demo-pac      | Out-File -Encoding ascii "$DestDir\cpusysregs-demo-pac-3.txt"
. $BinDir\demo-userfeatures | Out-File -Encoding ascii "$DestDir\cpusysregs-user-features.txt"
. $BinDir\collect           | Out-File -Encoding ascii "$DestDir\cpusysregs-pac-md.txt"

Get-ChildItem $DestDir/cpusysregs-*.txt
