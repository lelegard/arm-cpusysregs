# Apple architectures `arm64` and `arm64e` on macOS

Recent Mac machines use so-called "Apple Silicon" chips, from the M1 or M2 families of chips. These chips are designed by Apple and use CPU cores implementing the 64-bit Arm Instruction Set Architecture (ISA), also called `arm64` in the Apple context and elsewhere.

The `arm64` ISA is described in details in the [Arm Architecture Reference Manual for A-profile architecture](https://developer.arm.com/documentation/ddi0487/latest). Be aware that this is a monstrous document of nearly 12,000 pages.

The name `arm64e` was recently introduced by Apple. This platform ABI is currently in "preview" on macOS. This note explores the differences between `arm64` and `arm64e`.

**Disclaimer:** I am not working for Apple or Arm. I have no internal information on the M1 or M2 chips, or macOS. Everything in this note is based on my observations and tests on a MacBook with an M1 chip. The explanations on how such or such feature is implemented in macOS are just **speculations**, based on a rational analysis of the technical possibilites. Moreover, all tests were performed on macOS 13 (Ventura). Future versions of macOS may behave differently. Specifically, the `arm64e` ABI, as defined by Apple, is still in preview mode and may evolve in the future.

**Contents:**

* [What is arm64e architecture, compared to arm64 ?](#what-is-arm64e-architecture-compared-to-arm64-)
  * [Arm defensive security features](#arm-defensive-security-features)
  * [What is the real version of Arm architecture in the M1 ?](#what-is-the-real-version-of-arm-architecture-in-the-m1-)
  * [What is the real difference of arm64e ?](#what-is-the-real-difference-of-arm64e-)
* [Default PAC configuration on macOS 13 (Ventura)](#default-pac-configuration-on-macos-13-ventura)
  * [PAC does not work by default on macOS 13 (Ventura)](#pac-does-not-work-by-default-on-macos-13-ventura)
  * [Trying the arm64e target platform](#trying-the-arm64e-target-platform)
* [Enabling arm64e on macOS 13 (Ventura)](#enabling-arm64e-on-macos-13-ventura)
* [Programming examples](#programming-examples)
  * [Mixing arm64 and arm64e applications and libraries](#mixing-arm64-and-arm64e-applications-and-libraries)
  * [Detecting arm64 vs\. arm64e compilation in the code](#detecting-arm64-vs-arm64e-compilation-in-the-code)
  * [Demo: mixing arm64 and arm64e](#demo-mixing-arm64-and-arm64e)
* [How does macOS control the PAC hardware ?](#how-does-macos-control-the-pac-hardware-)
  * [Accessing the PAC key registers](#accessing-the-pac-key-registers)
  * [Using PAC in a virtual machine on top of a macOS host](#using-pac-in-a-virtual-machine-on-top-of-a-macos-host)
  * [Running arm64 applications on an arm64e system](#running-arm64-applications-on-an-arm64e-system)
* [Code generation differences between arm64 and arm64e](#code-generation-differences-between-arm64-and-arm64e)
  * [C\+\+ vtables](#c-vtables)
  * [Generated code on Linux](#generated-code-on-linux)
  * [Generated code on macOS with arm64e platform](#generated-code-on-macos-with-arm64e-platform)
* [Conclusion](#conclusion)

**Additional information in this project:**

* [Reference documentation on the Arm64 architecture](references.md)
* [List of Arm features for A-Profile](features.md)
* [Arm features in the Apple M1 and M2 chips](apple-m1-features.md)
* [Pointer Authentication Code format](pac-format.md)

## What is `arm64e` architecture, compared to `arm64` ?

The Arm architecture defines several versions over the years. The Apple M1 and M2 chips are said to implement the version 8.5-A of the Arm architecture (which is not completely true in the case of the M1).

### Arm defensive security features

At this level of Arm architecture, several new instructions were defined to implement "defensive security" against malware code injection. This type of code injection usually starts with a buffer overflow (due to a bug in an application or library) and implements Return-Oriented Programing (ROP) techniques when it smashes the stack or Jump-Oriented Programming (JOP) when it smashes other types of data structure, typically in the heap.

The mitigation techniques which are implemented by the new Arm instructions are split into two classes:

- Pointer Code Authentication (PAC) : A deterministic but unpredictable short "signature" is added to code and data pointers to detect invalid injected code addresses. This signature is added in the 16 or 8 most significant bits of the 64-pointers, otherwise unused since no address space uses 2^64 bytes.

- Branch Target Identification (BTI) : Targets of valid jump and branch instructions are identified by a special instruction so that using any unexpected ROP or JOP gadget address results in an invalid instruction.

See the compilation option `-mbranch-protection` for gcc and clang to generate these instructions.

- The default is `-mbranch-protection=none`, PAC and BTI are not used.
- With `-mbranch-protection=bti`, BTI instructions and code page protection are used.
- With `-mbranch-protection=pac-ret`, Pointer Authentication is used on return addresses from function call.
- Using `-mbranch-protection=standard` is a combination of the two.

In the Arm architecture, the PAC and BTI techniques can be smoothly integrated into interoperable code modules, using a common ABI. However, there are some perculiarities with the Apple M1 chip.

### What is the real version of Arm architecture in the M1 ?

The first peculiarity concerns the level of Arm architecture and the corresponding features. On macOS, some of the supported Arm features can be inspected using the command `sysctl hw.optional.arm`.

Surprisingly, the M1 chip does not support BTI while the Arm architecture reference manual describes this as a mandatory feature at version 8.5-A. On the other hand, the M1 supports other Arm features such as FlagM2 and FRINTTS which are documented by Arm as new and mandatory in version 8.5-A also, just like BTI. Therefore, the M1 implements new features which were introduced by Arm in version 8.5-A, _without supporting other mandatory features of this version_ (namely BTI). Formally, this means that the M1 does not implement any valid version of the Arm architecture.

Not having BTI in the M1 is a surprise because Apple is deeply concerned with security, hardware security, and implements a very efficient usage of PAC.

The M2, however, implements BTI and a few other Armv8.5-A features which were missing in the M1. See [the list of Arm features in the Apple M1 and M2 chips](apple-m1-features.md) for a comparison of the two chips.

Nevertheless, the two chips M1 and M2 implement the Pointer Authentication Code (PAC) feature, which is the main improvement of the `arm64e` platform.

### What is the real difference of `arm64e` ?

To enable PAC, the gcc and clang compilers support the option `-mbranch-protection=pac-ret`. As the name suggests, Pointer Authentication is used on function return addresses only. This feature is consequently internal to each function, internal to each compilation unit. This means that modules which were compiled with and without this option can be linked into the same executable and remain interoperable.

However, this usage of PAC is suboptimal. There are many other additional usages of PAC, such as protecting data structures addresses or pointers to functions inside data structures (the most obvious usage is the C++ vtables). However, since these data structures are inherently shared between distinct compilation units, possibly compiled with different options, they would no longer be interoperable.

This is where Apple invented `arm64e`...

Defining a new ABI allows to use the full power of PAC, on data structure, C++ vtables, etc. As explained above, this breaks the interoperability between modules with different compilation options. This means that _all_ modules of an application or library shall be compiled with consistent options. In practice, this defines a new platform ABI, named `arm64e`.

Compiling a module with `-arch arm64e` marks the object code with that platform name. Building an application or library for `arm64e` requires that all compilation units were built for `arm64e`. This is why defining a new platform ABI is the solution to get the full power of PAC.

Mixing `arm64` and `arm64e` is only possible under strict conditions which are explained later in this note.

At the end of this note, there is a complete demonstration on how the code generation for `arm64e` extends the protection to JOP attacks, in addition to ROP attacks. Currently, it does not seem that this extended protection can be used on Linux, neither using gcc nor clang.

**Important note:** The option `-mbranch-protection=pac-ret` is a generic option for gcc and clang on all Arm64 platforms, Linux or macOS. On the other hand, `-arch arm64e` is specific to macOS and is available in the Apple version of clang only. Each of these two options defines its own way of generating PAC code. These two methods are _incompatible_ and shall not be used together. As of this writing, the Apple clang compiler does not prevent the simultaneous usage of the two options. Using them at the same time generates non-functional code which crashes at run time. A [bug report](https://github.com/llvm/llvm-project/issues/60239) has been filed for that.

## Default PAC configuration on macOS 13 (Ventura)

### PAC does not work by default on macOS 13 (Ventura)

In practice, the M1 has the required capabilities to implement full PAC. However, as of macOS 13 (Ventura), macOS boots in `arm64` mode. The CPU is configured so that the PAC instructions are inoperative. Even though the compiler generates them using the compilation option `-mbranch-protection=pac-ret`, these instructions do nothing. No PAC is generated or authenticated.

We can demonstrate this using the following simple source code `pacia.c`. To enforce the demonstration on PAC instructions, we do not use the compilation option `-mbranch-protection=pac-ret`. This option generates PAC instructions but they are transparent to the user and it is difficult to observe them. In our example, we explicitly use the PACIA and AUTIA instructions using `asm` directives and we display their result.

~~~
#include <stdio.h>
#include <inttypes.h>

// noinline for easier inspection of generated code in main
__attribute__((noinline)) void report(uint64_t value)
{
    printf("%016" PRIX64 "\n", value);
}

int main(int argc, char* argv[])
{
    uint64_t data = 0x12345678;
    uint64_t modifier = 2;
    report(data);
    asm("pacia %[reg], %[mod]" : [reg] "+r" (data) : [mod] "r" (modifier) : );
    report(data);
    asm("autia %[reg], %[mod]" : [reg] "+r" (data) : [mod] "r" (modifier) : );
    report(data);
}
~~~

The PACIA instruction should add a Pointer Authentication Code (PAC) into the most significant bits of the value 0x0000000012345678, using "modifier" 2 (a seed). The AUTIA instruction should restore the previous value.

However, if we build the application normally (in `arm64` mode), we can see that the PACIA instruction does nothing:

~~~
$ cc pacia.c -o pacia
$
$ file pacia
pacia: Mach-O 64-bit executable arm64
$
$ ./pacia
0000000012345678
0000000012345678  <---- should have been modified
0000000012345678
~~~

It is probably a surprise to discover that the PACIA and AUTIA instructions "do not work". They are just instructions which are executed by the hardware. Their behavior is not expected to depend on the way the application was compiled.

Does this mean that the M1 chip "does not work"? Not really.

Digging into the Arm architecture reference manual, there is a special control register named SCTLR_EL3, the System Control Register. When writing selected bits into this register it is possible to selectively enable or disable each category of PAC. When these bits are zero, PACIA, AUTIA and other PAC instructions become simple NOP's. Authenticated branch and load instructions perform their functional task without address authentication. For instance, RETAA becomes a simple RET.

However, this register is highly protected and accessible at EL3 only. For the record, EL means "Exception Level", EL0 is the user mode, EL1 the kernel mode, EL2 the hypervisor mode and EL3 the monitor mode. In most embedded systems, the EL3 monitor is part of the "Arm Trusted Firmware", provided by Arm.

**Speculation:** Apple probably developed their own EL3 monitor with specific features to control the way the PAC instructions behave, depending on the software target platform. When macOS boots in `arm64` mode, the EL3 monitor probably configures SCTLR_EL3 to disable the PAC features before booting outer levels.

### Trying the `arm64e` target platform

In order to enable the full PAC feature, we need to create an `arm64e` binary. This is done using the compilation and linker option `-arch arm64e`. The resulting binary is marked as `arm64e` instead of `arm64`. This can be checked using the command `file`.

However, an `arm64e` application is not allowed to run on an `arm64` system. Trying to run such an application immediately crashes with `Killed: 9`:

~~~
$ cc -arch arm64e pacia.c -o pacia
$
$ file pacia
pacia: Mach-O 64-bit executable arm64e
$
$ ./pacia
Killed: 9
~~~

Since all systems running macOS 13 (Ventura) boot in `arm64` mode, we cannot run our `arm64e` applications by default. We need to enable the `arm64e` mode first.

## Enabling `arm64e` on macOS 13 (Ventura)

To enable `arm64e` applications on macOS 13 (Ventura), we need to do two things:

- Boot macOS in `arm64e` mode.
- Disable system integrity.

Remember that, as of macOS 13 (Ventura), `arm64e` is in preview mode. The macOS system integrity feature currently prevents `arm64e` applications from running. Booting in `arm64e` mode with system integrity enabled still prevents the `arm64e` application from running.

More precisely, it prevents _third-party_ `arm64e` applications from running. All executables in `/bin` or `/usr/bin` are already built in `arm64e` mode and run correctly.

~~~
$ file /bin/ls
/bin/ls: Mach-O universal binary with 2 architectures: [x86_64:Mach-O 64-bit executable x86_64] [arm64e:Mach-O 64-bit executable arm64e]
/bin/ls (for architecture x86_64):   Mach-O 64-bit executable x86_64
/bin/ls (for architecture arm64e):   Mach-O 64-bit executable arm64e
~~~

A few system executables are even built for both architectures, `arm64` and `arm64e`:

~~~
$ file /usr/bin/file
/usr/bin/file: Mach-O universal binary with 3 architectures: [x86_64:Mach-O 64-bit executable x86_64] [arm64:Mach-O 64-bit executable arm64] [arm64e:Mach-O 64-bit executable arm64e]
/usr/bin/file (for architecture x86_64):   Mach-O 64-bit executable x86_64
/usr/bin/file (for architecture arm64):    Mach-O 64-bit executable arm64
/usr/bin/file (for architecture arm64e):   Mach-O 64-bit executable arm64e
~~~

However, if we build an application in `arm64e` mode ourselves, running it ends in `Killed: 9`. To be allowed to run an `arm64e` executable, it must be in the part of the file system which is protected by the system integrity. The following commands demonstrate that a system `arm64e` executable stops working when it is copied outside the system-protected area.

~~~
$ file /bin/echo
/bin/echo: Mach-O universal binary with 2 architectures: [x86_64:Mach-O 64-bit executable x86_64] [arm64e:Mach-O 64-bit executable arm64e]
/bin/echo (for architecture x86_64):    Mach-O 64-bit executable x86_64
/bin/echo (for architecture arm64e):    Mach-O 64-bit executable arm64e
$ /bin/echo hi
hi
$ cp /bin/echo .
$ ./echo hi
Killed: 9
~~~

If we want to test `arm64e` executables, we must first disable the system integrity. This puts our system at risks and should be done on test systems only.

To disable system integrity, we must reboot in "recovery mode":

- First, shutdown the system. With power off. Do not simply restart the system. We are not allowed to disable the system integrity if the system was _restarted_ in recovery mode. The system must have booted in recovery mode from a power off state. This is a clever security precaution to make sure that the operation is manually performed by a human and not automatically triggered by some malware.
- Boot the system, keeping the finger on the power button to display the boot options. Select "Options", "Continue", select a user, "Next", enter our password, open a terminal from the "Utilities" top menu.
- Enter command `csrutil disable`. This command prompts for our user name and password again.
- Reboot the system.

**Note:** To restore the system integrity after tests, perform the same recovery mode procedure with command `csrutil enable` instead of `disable`.

At that point, the `arm64e` mode is not enabled yet. We need to add the boot flag `-arm64e_preview_abi`:

~~~
sudo nvram boot-args=-arm64e_preview_abi
~~~

And then reboot the system to use that flag.

After the reboot, we can run our `arm64e` applications:

~~~
$ ./pacia
0000000012345678
917B000012345678
0000000012345678
$ ./pacia
0000000012345678
6258800012345678
0000000012345678
$ ./pacia
0000000012345678
5418800012345678
0000000012345678
~~~

We can notice that the PACIA instruction now works as expected. The 17 most significant bits of the 64-bit value are altered with a PAC. Using AUTIA on the same value, using the same "modifier", the previous value is correctly restored.

Looking carefully, we notice that 17 bits are altered, not 16. This is explained in details in another note of this project, about [Pointer Authentication Code format](pac-format.md).

Also note that the PAC value changes at each execution. This is due to the kernel assigning a different value for the PAC key in each process. Thus, if an attacker is able to learn the updated value for a pointer using a test, this value won't be valid in any other occurrence of the same program.

## Programming examples

### Mixing `arm64` and `arm64e` applications and libraries

The `arm64` executables and libraries can call `arm64e` libraries, but not the opposite. The `arm64e` libraries are secured against external code injections and can be called from non-secured applications.

Non-secured applications (`arm64`) do not expect any protection and do not care about the security of the libraries they call. This is why they can call both types of libraries.

Secured application (`arm64e`), on the other hand, expect protection against code injection. This is why they are not allowed to call non-secured libraries (`arm64`) because code injection could happen during the execution of one of these libraries.

On macOS 13 (Ventura), the system library cache contains `arm64e` binaries only, no `arm64`. All system libraries, as installed with macOS are secured against code injection, even before `arm64e` is officially supported for applications.

Content of the system library cache:

~~~
$ ls -l /System/Volumes/Preboot/Cryptexes/OS/System/DriverKit/System/Library/dyld
total 9088
-rwxr-xr-x  1 root  admin  6324224 Dec  2 12:37 dyld_shared_cache_arm64e
-rwxr-xr-x  1 root  admin   409600 Dec  2 12:37 dyld_shared_cache_arm64e.symbols
-rwxr-xr-x  1 root  admin  7012352 Dec  2 12:37 dyld_shared_cache_x86_64
-rwxr-xr-x  1 root  admin   393216 Dec  2 12:37 dyld_shared_cache_x86_64.symbols
~~~

### Detecting `arm64` vs. `arm64e` compilation in the code

The following C/C++ macros are predefined when compiled with `-arch arm64e`:

~~~
#define __PTRAUTH_INTRINSICS__ 1
#define __arm64e__ 1
#define __ptrauth_abi_version__ 0
~~~

Demonstration:

~~~
$ cc -E -x c -dM /dev/null >macros-arm64.txt
$ cc -E -arch arm64e -x c -dM /dev/null >macros-arm64e.txt
$ diff macros-arm64.txt macros-arm64e.txt 
239a240
> #define __PTRAUTH_INTRINSICS__ 1
379a381
> #define __arm64e__ 1
392a395
> #define __ptrauth_abi_version__ 0
$ 
~~~

### Demo: mixing `arm64` and `arm64e`

We are going to build a shared library and an application which calls it and try all possible combinations of `arm64` and `arm64e`.

File `libtest.h`:
~~~
#if !defined(LIBTEST_H)
#define LIBTEST_H 1

#if defined(__arm64e__)
    #define ARCH "arm64e"
#elif defined(__arm64__)
    #define ARCH "arm64"
#else
    #define ARCH "other"
#endif

void libtest();

#endif // LIBTEST_H
~~~

File `libtest.c`:
~~~
#include <stdio.h>
#include "libtest.h"

void libtest()
{
    printf("in libtest, arch is %s\n", ARCH);
}
~~~

File `main.c`:
~~~
#include <stdio.h>
#include "libtest.h"

int main(int argc, char* argv[])
{
    printf("enter main, arch is %s\n", ARCH);
    libtest();
    printf("leave main, arch is %s\n", ARCH);
}
~~~

We build the shared library in `arm64` mode:
~~~
$ cc -c libtest.c -o libtest.arm64.o
$ cc -shared libtest.arm64.o -o libtest.arm64.dylib
~~~

And then in `arm64e` mode:
~~~
$ cc -arch arm64e -c libtest.c -o libtest.arm64e.o
$ cc -arch arm64e -shared libtest.arm64e.o -o libtest.arm64e.dylib
~~~

Checking the result:
~~~
$ file libtest.*.dylib
libtest.arm64.dylib:  Mach-O 64-bit dynamically linked shared library arm64
libtest.arm64e.dylib: Mach-O 64-bit dynamically linked shared library arm64e
~~~

We build the application in `arm64` mode, in two versions: one calling the `arm64` library and the other one calling the `arm64e` library:
~~~
$ cc -c main.c -o main.arm64.o
$ cc main.arm64.o -L. -ltest.arm64 -o main.arm64
$ cc main.arm64.o -L. -ltest.arm64e -o main.arm64-to-64e
~~~

Checking the result of the build:
~~~
$ file main.arm64 main.arm64-to-64e
main.arm64:        Mach-O 64-bit executable arm64
main.arm64-to-64e: Mach-O 64-bit executable arm64
$
$ otool -L main.arm64 main.arm64-to-64e
main.arm64:
	libtest.arm64.dylib (compatibility version 0.0.0, current version 0.0.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1319.0.0)
main.arm64-to-64e:
	libtest.arm64e.dylib (compatibility version 0.0.0, current version 0.0.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1319.0.0)
~~~

Verifying that the right library is called in each case:
~~~
$ ./main.arm64
enter main, arch is arm64
in libtest, arch is arm64
leave main, arch is arm64
$
$ ./main.arm64-to-64e 
enter main, arch is arm64
in libtest, arch is arm64e
leave main, arch is arm64
~~~

Now, let's try to build the application in `arm64e` secured mode with both libraries:
~~~
$ cc -arch arm64e -c main.c -o main.arm64e.o
$ cc -arch arm64e main.arm64e.o -L. -ltest.arm64e -o main.arm64e
$ cc -arch arm64e main.arm64e.o -L. -ltest.arm64 -o main.arm64e-to-64
ld: warning: ignoring file ./libtest.arm64.dylib, building for macOS-arm64e but attempting to link with file built for macOS-arm64
Undefined symbols for architecture arm64e:
  "_libtest", referenced from:
      _main in main.arm64e.o
ld: symbol(s) not found for architecture arm64e
clang: error: linker command failed with exit code 1 (use -v to see invocation)
~~~

We can see that an `arm64e` application can be linked against `arm64e` libraries only. The linker emits an error when trying to link against an `arm64` library.

Verifying that the right library is called in the only case which works, full `arm64e`:
~~~
$ ./main.arm64e 
enter main, arch is arm64e
in libtest, arch is arm64e
leave main, arch is arm64e
~~~

## How does macOS control the PAC hardware ?

We have already demonstrated that macOS can enable or disable the pointer authentication in the PAC instructions, probably using a configuration of the special system register SCTLR_EL3 from a dedicated EL3 monitor.

Additionally, even in `arm64e` mode, the PAC hardware is configured in a way which is different from other platforms such as Linux (in a more secure way).

### Accessing the PAC key registers

The "signature" part of the authenticated pointers is generated from a "key". There are several PAC key registers (named APIAKey_EL1, APIBKey_EL1, APDAKey_EL1, APDBKeyEL1, APGAKey_EL1). Usually, the kernel of the operating system selects random PAC keys when a process is created and writes these keys into the PAC key registers each time the process is scheduled. As indicated in their names, the PAC key registers are accessible at EL1 (kernel).

This is demonstrated in this project which allows an application to manipulate some system registers which are normally accessible to the kernel only. To do this, a special kernel module was developed with Linux and macOS variants.

On Linux, we can change the value of the PAC keys inside a process and observe the impact on the PAC instructions. We can conclude that our special kernel module was allowed to read and write the PAC key registers.

However, on macOS, the same sample code crashes the system. Why? Again, another EL3 register named SCR_EL3, the Secure Configuration Register, can be configured to prevent access to the PAC key registers. In fact, it does not completely forbid access to these registers. Instead, accessing a PAC key register generates a trap at EL3.

**Speculation:** The Apple EL3 monitor probably includes specific traps for PAC key register access. When the macOS kernel schedules a process, it probably calls the EL3 monitor to configure the PAC keys registers on behalf of the kernel. The details of this process are unknown.

For the sake of completeness, there is another way to trap (to EL2) on access to the PAC key registers, using the bit APK in the register HCR_EL2, the Hypervisor Configuration Register. However, this register is clearly designed to support the virtualization. When running on the macOS host system, it appears that HCR_EL2 is still readable from EL1 on the M1, and we see that HCR_EL2.APK = 1, meaning "no trap on accessing the PAC key registers".

This way of accessing the PAC key registers is more secure than in Linux where the EL1 kernel is allowed to fully configure the PAC. Using macOS, the kernel is not even trusted. This is clever because, if an attacker takes control of a Linux kernel, it can completely control or disable the PAC. This is not possible on macOS. In practice, "taking control of the kernel to hack the PAC keys" is exactly what this project does. It succeeds on Linux and fails on macOS. On a security scale, macOS wins.

### Using PAC in a virtual machine on top of a macOS host

When a Linux virtual machine is run on the macOS host, Pointer Authentication returns to a simpler mechanism when used inside the virtual machine.

- The PAC instructions work as expected, even when the macOS host booted in `arm64` mode. These instructiosn are inoperative in the macOS host OS but work as expected in the Linux guest OS.
- The Linux kernel can fully control the PAC registers at EL1.

**Speculation:** The EL2 hypervisor probably emulates the PAC mechanism. HCR_EL2, the Hypervisor Configuration Register, contains two bits, API and APK, which can be configured as follow:

- HCR_EL2.API = 0 : any PAC instruction is trapped at EL2.
- HCR_EL2.APK = 0 : any access to the PAC registers is trapped at EL2.

Using this configuration, the EL2 hypervisor is able to take full control of the PAC inside the virtual machine, regardless of any implementation or configuration on the host.

### Running `arm64` applications on an `arm64e` system

Using the `pacia` small program, we have demonstrated that the PAC instructions are fully functional in an `arm64e` running on an `arm64e` system.

Using the small `libtest` library, we have also demonstrated how to mix `arm64` applications with `arm64e` libraries. What is the behavior of the PAC instructions in that context?

Let's add the following function to `libtest.h`. It displays the result of the PACIA and AUTIA instructions on one line. We use the `always_inline` attribute to ensure that the code is compiled as part of each compilation unit.

~~~
static inline __attribute__((always_inline)) void test_pacia(void)
{
    uint64_t modifier = 2;
    uint64_t data1 = 0x12345678;
    uint64_t data2 = data1;

    asm("pacia %[reg], %[mod]" : [reg] "+r" (data2) : [mod] "r" (modifier) : );
    uint64_t data3 = data2;
    asm("autia %[reg], %[mod]" : [reg] "+r" (data3) : [mod] "r" (modifier) : );
    printf("%016" PRIX64 " -> %016" PRIX64 " -> %016" PRIX64 "\n", data1, data2, data3);
}
~~~

We call the `test_pacia` function in the main application and in the library, right after each message.

Let's rebuild all variants and test them.

~~~
$ ./main.arm64
enter main, arch is arm64
0000000012345678 -> 0000000012345678 -> 0000000012345678
in libtest, arch is arm64
0000000012345678 -> 0000000012345678 -> 0000000012345678
leave main, arch is arm64
0000000012345678 -> 0000000012345678 -> 0000000012345678
$
$ ./main.arm64-to-64e
enter main, arch is arm64
0000000012345678 -> 0000000012345678 -> 0000000012345678
in libtest, arch is arm64e
0000000012345678 -> 0000000012345678 -> 0000000012345678
leave main, arch is arm64
0000000012345678 -> 0000000012345678 -> 0000000012345678
$
$ ./main.arm64e
enter main, arch is arm64e
0000000012345678 -> 6C75000012345678 -> 0000000012345678
in libtest, arch is arm64e
0000000012345678 -> 6C75000012345678 -> 0000000012345678
leave main, arch is arm64e
0000000012345678 -> 6C75000012345678 -> 0000000012345678
~~~

We can see that the PAC instructions are disabled when running an `arm64` application, even on an `arm64e` system. Additionally, when the `arm64` application calls an `arm64e` library, the PAC instructions are also disabled when running code inside the `arm64e` library. This is required since the `arm64e` library authenticates all pointers it manipulates. When called from an `arm64` application, the library receives plain unauthenticated pointers and the library should not fail when manipulating them.

Only in the last case, when an `arm64e` application is run, the PAC instructions are effective.

**Speculation:** When the macOS kernel schedules an `arm64` application on a core, it probably calls the EL3 monitor to reconfigure the SCTLR_EL3 register to disable the PAC instructions. In practice, each time a process is scheduled on a core, the EL3 monitor shall be called, either to configure the PAC key registers (`arm64e` application) or to disable the PAC instructions (`arm64` applications).

## Code generation differences between `arm64` and `arm64e`

This section demonstrates the differences between the `arm64` ABI with option `-mbranch-protection=pac-ret` as used on Linux and the Apple `arm64e` ABI.

In the Linux case, the added security only protects the function call return addresses on stack. This protection mitigates all basic ROP chains (Return-Oriented Programming), usually starting from a stack overflow.

However, this method does not protect against JOP attacks (Jump-Oriented Programming), starting from general buffer overflows on the heap. In the latter case, the corrupted addresses are in data structures, not necessarity on the stack. Object-oriented programming languages use a lot of structures containing pointers to code. In C++, this is called a "vtable". There is one per class (when the class contains virtual methods).

### C++ vtables

Hacking the C++ vtables has now become popular in malware injection. This is why we need to prevent these attacks. The Arm PAC technology is capable of this. However, this is not used in the `arm64` ABI with option `-mbranch-protection=pac-ret`. On the other hand, the Apple `arm64e` ABI does. Let's see how.

Consider this sample `test.cpp` code to call a C++ virtual method:

~~~
class C
{
public:
    virtual void f() const;
    virtual void g() const;
};

int test(const C& obj)
{
    obj.g();
    return 0; // to avoid tail call optimization
}
~~~

To understand the generated code, we need to review the standard way of implementing polymorphism through vtables in C++ (other object-oriented languages use similar techniques). Consider an object instance at address `O`, of class C. There is a unique vtable at address `V` for class C. Each object instance of that class points to the vtable of its exact class using a hidden or implicit field at the beginning of the object data structure.

~~~
         object instance         class C vtable
        +---------------+        +------------+
O ----->|+0:    V       |------->|+0:   F     |--------> C::f() code
        +---------------+        +------------+
        |+8:  other     |        |+8:   G     |--------> C::g() code
        |     object    |        +------------+
        |     fields    |
        +---------------+
~~~

### Generated code on Linux

On Linux Ubuntu 22.10 for arm64, we use gcc version 12.2.0 or clang version 15.0.2-1. The following commands display the generated code (with demangled names):

~~~
$ gcc -O2 -march=armv8.5-a -mbranch-protection=pac-ret test.cpp -S -o - | c++filt
$ clang -O2 -march=armv8.5-a -mbranch-protection=pac-ret test.cpp -S -o - | c++filt
~~~

The generated code for the `test()` function is exactly the same with the two compilers, except the allocation of registers (x1 with gcc, x8 with clang). The call to the virtual method has been isolated between dashed lines. The virtual call sequence uses 3 instructions.

~~~
paciasp              ; [*] add a PAC to return address in x30 before pushing it on stack (key = IA, mod = current stack pointer)
stp     x29, x30, [sp, #-16]!
mov     x29, sp
-----------------    ; x0 == first parameter of test() function == object address O
ldr     x8, [x0]     ; x8 = vtable address V, fetched at offset 0 in the object instance
ldr     x8, [x8, #8] ; x8 = virtual method address G, fetched at offset 8 in the vtable
blr     x8           ; 1) branch with link to method C::g()
                     ; 2) x0 still contains the object address (implicit first argument of a non-static method)
-----------------
mov     w0, wzr
ldp     x29, x30, [sp], #16
retaa                ; [*] authenticate the return address in x30 before jumping to it
~~~

The two lines which are marked with `[*]` result from the option `-mbranch-protection=pac-ret`.

Thanks to option `-march=armv8.5-a`, the return sequence has been optimized as one single `retaa` instruction. Without this option, in order to remain compatible with previous versions of the Arm architecture, the sequence uses two instructions: `autiasp` for the authentication alone, followed by a standard `ret`.

### Generated code on macOS with `arm64e` platform

On macOS 13.2, we use Apple clang version 14.0.0 and the command becomes:

~~~
$ clang -O2 -arch arm64e test.cpp -S -o - | c++filt
~~~

The generated code for the `test()` function is shown below. The stack protection is the same as on Linux, except that it uses the PAC key IB instead of IA, which does not make any difference in terms of security. However, unlike the Linux code, we can also see how the C++ vtable is protected.

In practice, we will see that 3 different PAC keys are used on macOS for 3 different types of protection. On Linux, only the last protection is used.

- IA : protects the content of C++ vtables (against JOP attacks).
- DA : protects the content of C++ object instances (intermediate step toward a JOP attack).
- IB : protects the return addresses on stack (against ROP attacks).

~~~
pacibsp
stp     x29, x30, [sp, #-16]!
mov     x29, sp
-----------------             ; x0 == first parameter of test() function == object address O
ldr     x16, [x0]             ; x16 = vtable address V with PAC, fetched at start of object instance
mov     x17, x0               ; x17 = object address O
movk    x17, #20692, lsl #48  ; tweak object address: store 20692 (0x50D4) in upper 16 bits of O
autda   x16, x17              ; authenticate vtable address in x16 (key = DA, mod = tweaked object address)
ldr     x8, [x16, #8]!        ; 1) x8 = virtual method address G with PAC, fetched at offset 8 in the vtable
                              ; 2) x16 = plain address of method address inside vtable (V+8)
mov     x9, x16               ; [*] useless intermediate step ?
mov     x17, x9               ; [*] x17 = plain address of method address inside vtable (still useless, could have kept x16)
movk    x17, #30081, lsl #48  ; tweak vtable address V+8: store #30081 (0x7581) in upper 16 bits of V+8
blraa   x8, x17               ; 1) authenticate method address in x8 (key = IA, mod = tweaked vtable address)
                              ; 2) branch with link to method C::g()
                              ; 3) x0 still contains the object address (implicit first argument of a non-static method)
-----------------
mov     w0, #0
ldp     x29, x30, [sp], #16
retab
~~~

This sequence uses 9 instructions instead of 3 in the unauthenticate method. However, there is some room for improvement. The two instructions which are marked with `[*]` are useless and the two registers x8 and x9 are allocated for nothing. But that would still make 7 instructions instead of 3. Using option `-O3` does not improve the code.

The code pattern which is recommended by Arm to call an authenticated virtual method is the following (x16 and x17 are arbitrary choices here).

~~~
ldr     x16, [x0]        ; x16 = vtable address V with PAC (x0 == object address == O)
ldraa   x17, [x16, #8]!  ; 1) authenticate vtable address in x16 (key = DA, mod = 0)
                         ; 2) x17 = virtual method address G with PAC, fetched at offset 8 in the vtable
                         ; 3) x16 = plain address of method address in vtable == V+8
blraa   x17, x16         ; 1) authenticate method address in x17 (key = IA, mod = address of method address in vtable)
                         ; 2) branch with link to virtual method
~~~

Using this method, calling an authenticated virtual method uses only 3 instructions, exactly the same number as an unauthenticated call.

However, there are differences between the two ABI:

- Recommended Arm method:
  - The vtable address (V) is authenticated using zero as modifier.
  - The virtual method address (G) is authenticated using a modifier which is the address of where G is stored in the vtable (V + some offset, modifier = V+8 in our example).
- Apple `arm64e` ABI:
  - The vtable address (V) is authenticated using a modifier which is the object instance address (O) with a 16-bit tweak (Tv) in the upper 2 bytes of the address O (modifier = Tv||O). Using several class types demonstrates that the value of Tv (20692 in the example) is different for each class. Since it must be consistent across compilation units, we can speculate that it is derived from the fully qualified name of the class.
  - The virtual method address (G) is authenticated using a modifier which is the address where it is stored inside the vtable (V+8 in the example) with a 16-bit tweak (Tm) in the upper 2 bytes of the address V+8 (modifier = Tm||(V+8)). Using several virtual methods for the same class and several class types demonstrates that the value of Tm (30081 in the example) is different for each virtual method of the same class and different from virtual methods in other classes at the same offset in the vtable.

Assuming that Apple clang is improved to use 7 instructions instead of 9 for the virtual method call, where do the remaining extra 4 instructions come from?

- 3 additional instructions to build the tweaks
- 1 additional instruction to load the method address from the vtable: `ldraa` uses modifier zero, we need to split this in `autda` and `ldr` if we use an explicit modifier.

Why this extra complexity in the Apple `arm64e` ABI?

- There is some benefit in using the object instance address as modifier for the vtable address. It mitigates some potential polymorphic attack. If we steal the vtable address of an object O1 of class C1 and overwrite the start of an object O2 of class C2 with that solen vtable address, then object O2 will behave as if it was of class C1 instead of C2. This could be a security risk which is not mitigated by the Arm recommended method.
- The benefit of adding tweaks in the modifier is explained in [this document from the Apple LLVM project](https://github.com/apple/llvm-project/blob/apple/main/clang/docs/PointerAuthentication.rst). They call this a "discriminator". The discriminator is a constant value which is derived from the fully qualified name of the class (for the pointer to the vtable) or the method (for pointers inside the vtable).

## Conclusion

The Pointer Authentication Code (PAC) Arm features are extremely powerful to mitigate current malware injection techniques, ROP and JOP. However, PAC must be used and properly used. The current mainstream versions of gcc and clang do not use PAC by default. Moreover, when they use it, they do not use the full power of PAC and only address the basic ROP attacks (smashing the return pointer on stack).

The Apple `arm64e` ABI, on the other hand, is carefully designed to use PAC in most possible situations. This platform ABI is currently used by default on iOS (iPhone and iPad) but not yet on macOS. We look forward to have `arm64e` enabled by default on macOS.

We also look forward to see a similar ABI with gcc and clang. This will be a new ABI, breaking the compatibility with previous ones. However, this is not the first time gcc will introduce a new level of ABI. The link constraints have been solved using dedicated `GLIBCXX_` symbols or similar tricks.
