# Demo applications and utilities

The C++ application `sysregs` is a generic tool to read and write the system registers.
With option `-v` (verbose), most system registers are structured using bit-fields of various
sizes and interpretation.
~~~
Syntax: sysregs [options]

  -a : read all supported Arm64 system registers
  -b : display register value in binary (default: hex)
  -f : force read/write register, even if not supposed to (risk of system crash)
  -h : display this help text
  -l : list all supported Arm64 system registers
  -r name : read the content of the named register
  -s : summary of CPU features
  -w name hex-value : write the value in the named register
  -v : verbose, display register analysis and fields
~~~

The C++ application `demo-pac` demonstrates some usages of the pointer authentication features.
