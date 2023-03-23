#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# PowerShell script to build the driver and the applications.
#
#----------------------------------------------------------------------------

[CmdletBinding(SupportsShouldProcess=$true)]
param([switch]$NoPause = $false)

# Find MSBuild
Write-Output "Searching MSBuild..."
$MSRoots = @("C:\Program Files*\MSBuild", "C:\Program Files*\Microsoft Visual Studio")
$MSBuild = Get-ChildItem -Recurse -Path $MSRoots -Include MSBuild.exe -ErrorAction Ignore |
           ForEach-Object { $_.FullName} |
           Select-Object -Last 1

if (-not $MSBuild) {
    Write-Output "MSBuild not found"
}
else {
    # Build the project.
    Write-Output "MSBuild: $MSBuild"
    $SolutionFile = "$PSScriptRoot\cpusysregs.sln"
    & $MSBuild $SolutionFile /nologo /property:Configuration=Release /property:Platform=ARM64
}

if (-not $NoPause) {
    pause
}
