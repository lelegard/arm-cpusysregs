# Arm Architecture Specification

- Arm Architecture Reference Manual for A-profile architecture: https://developer.arm.com/documentation/ddi0487/latest
- Arm Architecture exploration tools: https://developer.arm.com/downloads/-/exploration-tools

The Arm Architecture exploration tools contain links to tarballs of machine-readable
definitions of the Arm Architecture: features, instruction set, system registers.
The specifications are defined in XML and JSON files.

The script `extract-arm-spec.py` downloads these tarballs and automatically regenerates partial
texts to be included in various source files in the project.

The generated files are:

- `partial_cpusysregs.h` : The definitions of encoding of all system registers for MRS and MSR instructions,
  as defined in `kernel/cpusysregs.h` (all `#define CSR_SREG_` lines).
- `partial_armfeatures.h` : To be integrated in file `apps/armfeatures.h`. The C++ class `ArmFeatures`
  detects the presence of all features in the current CPU. The implementation uses various fields from
  configuration registers. The generated file contains all functions to access those fields.
- `partial_regview.cpp` : Template structure for `regview.cpp`. Not for direct integration but a useful
  source of copy/paste for new registers and new bitfields.
- `partial_registers.md` : To be integrated in `docs/registers.md`.
- `partial_features.md` : To be integrated in `docs/features.md`. The generated file contains a copy of
  the table in `docs/features.md` with updated information. New features are marked as `???` in the
  `sysregs` column. The C++ class `ArmFeatures` should then be updated to detect those features.

The script `extract-arm-spec.py` should be executed each time an update of the Arm architecture is published.
The modification (use `git diff`) should be inspected as follow:

- Any new interesting system register?
- Any new feature to detect?
