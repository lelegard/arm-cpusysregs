# Arm architecture specification

- Arm Architecture Reference Manual for A-profile architecture: https://developer.arm.com/documentation/ddi0487/latest
- Arm Architecture exploration tools: https://developer.arm.com/downloads/-/exploration-tools

The Arm Architecture exploration tools contain links to tarballs of machine-readable
definitions of the Arm Architecture: features, instruction set, system registers.
The specifications are defined in XML and JSON files.

The script `download-arm-spec.sh` downloads one of these tarballs.
Use option `--help` for the list of options.

The script `extract-sreg-definitions.sh` automatically generates the `CSR_SREG_xxx` definitions
of all Arm system registers, as used in `kernel/cpusysregs.h`. The definition of all registers is based
on reference XML files on the Arm public web site. This script may be executed each time an update
of the Arm architecture is published.
