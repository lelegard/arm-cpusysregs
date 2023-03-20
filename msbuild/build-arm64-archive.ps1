# Build the driver and the applications for ARM64 and package an archive.

[CmdletBinding(SupportsShouldProcess=$true)]
param([switch]$NoPause = $false)

# Build driver and applications.
& "$PSScriptRoot\build.ps1" -NoPause

# Build archive.
Compress-Archive -DestinationPath "$PSScriptRoot\arm-cpusysregs.zip" @(
    "$PSScriptRoot\ARM64\Release\cpusysregs.sys"    
)

if (-not $NoPause) {
    pause
}
