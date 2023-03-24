#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# PowerShell script to cleanup all generated files
#
#----------------------------------------------------------------------------

[CmdletBinding(SupportsShouldProcess=$true)]
param([switch]$NoPause = $false)

Get-ChildItem $PSScriptRoot -Recurse -Include @("ARM64", ".vs", "*.vcxproj.user", "*.zip") -Force | Remove-Item -Recurse -Force -Verbose

if (-not $NoPause) {
    pause
}
