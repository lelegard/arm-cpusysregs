# Arm Architecture Specification

- Arm Architecture Reference Manual for A-profile architecture: https://developer.arm.com/documentation/ddi0487/latest
- Arm Architecture exploration tools: https://developer.arm.com/downloads/-/exploration-tools

The Arm Architecture exploration tools contain links to tarballs of machine-readable
definitions of the Arm Architecture: features, instruction set, system registers.
The specifications are defined in XML and JSON files.

The script `extract-arm-spec.py` downloads these tarballs and automatically updates
some text files in the project, C/C++ source files or markdown files.

The updated files are:

- `docs/features.md` : New features are added and marked as `???` in the `sysregs` column.
  For all features, optional and mandatory architecture levels are updated. The file
  `apps/armfeatures.h` is read to get which features are detectable by the project.
  The table is updated accordingly.

- `docs/registers.md` : New registers are added. Registers which can be read or written
  by the kernel module are marked accordingly.

- `docs/registers-fields.md` : All tables of bitfields per register are rebuilt.

- `kernel/cpusysregs.h` : The definitions of encoding of all system registers for MRS and MSR
  instructions (all `#define CSR_SREG_` lines) are updated. New registers are added.

- `apps/armfeatures.h` : For all registers which are accessed by the C++ class `ArmFeatures`,
  the C++ methods to access the various bitfields are generated.

Other generated files in this directory:

- `partial_regview.cpp` : Template structure for `apps/regview.cpp`. Not for direct integration
  but a useful source of copy/paste for new registers and new bitfields.

The script `extract-arm-spec.py` should be executed each time an update of the Arm architecture is published.
The modification (use `git diff`) should be inspected as follow:

- Any new interesting system register?
- Any new feature to detect?
