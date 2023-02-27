# Reference documentation on the Arm64 architecture

**Contents:**

* [Arm documentation](#arm-documentation)
* [Third party documentation](#third-party-documentation)
* [Bug reports](#bug-reports)

## Arm documentation

- [Arm Architecture Reference Manual for A-profile architecture](https://developer.arm.com/documentation/ddi0487/latest)
- [Feature names in A-profile architecture](https://developer.arm.com/downloads/-/exploration-tools/feature-names-for-a-profile)
- [Arm ISA and system registers XML reference](https://developer.arm.com/downloads/-/exploration-tools)

## Third party documentation

- [Pointer Authentication implementation](https://github.com/apple/llvm-project/blob/apple/main/clang/docs/PointerAuthentication.rst) (Apple LLVM project)
- [Pointer Authentication on ARMv8.3 - Design and Analysis of the New Software Security Instructions](https://www.qualcomm.com/content/dam/qcomm-martech/dm-assets/documents/pointer-auth-v7.pdf) (Qualcomm)
- [The QARMA-64 algorithm](https://eprint.iacr.org/2016/444.pdf) (used in pointer authentication codes)
- [QARMA-64 reference implementation](https://github.com/Phantom1003/QARMA64) (shared by Phantom1003 on GitHub)

## Bug reports

While working on this project, a few defects were found in the clang (LLVM) compiler for Arm64.

- [LLVM clang bug report](https://github.com/llvm/llvm-project/issues/60239), incorrect generated code with options `-arch arm64e -mbranch-protection=pac-bti`, don't use them together.
- [Apple LLVM clang bug report](https://github.com/apple/llvm-project/issues/6307), request to reduce call sequences of C++ virtual functions from 9 to 7 instructions in `arm64e` mode.
