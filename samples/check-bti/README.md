# Check the effectiveness of the BTI instruction

This sample program demonstrates how trying to bypass BTI fails on Armv8.5-A and higher.

When we compile a function f() with the default options, the function prolog is the following:
~~~
f:
  stp  x29, x30, [sp, -size]!
  mov  x29, sp
~~~

When BTI is used (gcc option `-mbranch-protection=bti`), a BTI instruction is added:
~~~
f:
  bti  c
  stp  x29, x30, [sp, -size]!
  mov  x29, sp
~~~

With BTI, the code is in a _guarded_ page. On Armv8.5-A and higher, any indirect branch
(through a register, a code pointer) into a guarded page must land at a BTI instruction.
Otherwise, a branch target exception is generated and the program fails.

In this sample code, we force an indirect branch at the second instruction (the `stp`),
simulating the corruption of a pointer to function, possibly a JOP attack to insert
malware.

On Armv8.5-A and higher, this program should fail.

At a lower level of architecture, it simply succeeds as follow:
~~~
$ make test
cc -mbranch-protection=bti    check-bti.c   -o check-bti
./check-bti
start of main(), calling f(1)
in f(1)
next call should fail if BTI is supported on this CPU
in f(47)
end of main()
~~~

Note: as of this writing, the branch target exception could not be demonstrated
because of the lack of a true Armv8.5-A CPU core. The Apple M1 chip has a non-standard
architecture level, roughly equivalent to Armv8.5-A, but without FEAT_BTI. See more
details in the file [arm64e-on-macos.md](../../docs/arm64e-on-macos.md).

Call for contribution: If you read this note and have access to a true Armv8.5-A
chip such as an Apple M2, please test this program and open an issue in this
repository to report the results.
