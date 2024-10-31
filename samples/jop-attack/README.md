# Sample JOP attack

This sample code illustrates an over-simplified Jump-Oriented-Programming (JOP)
attack. We simulate a buffer overflow bug in an application which, when carefully
exploited by hackers, allows a restricted object to gain excessive privileges.

This is a simplified version of a classical C++ vtable hacking. The simplification
consists in directly patching the vtable address of a C++ object instance instead
of producing the same effect through a buffer overflow.

## Sample code structure

In the sample code, the C++ class A implements highly privileged objects. These
objects may have a security impact on the system. Using them shall be done with caution.

The C++ class B implements unprivileged objects. Objects of class B are harmless and
can be used anywhere without risk.

The sample code structure is shown below. The `test()` function is called several
times with an unprivileged object of class B.

As usual in security vulnerabilities, a breach is triggered in the presence of some
form of input (usually invalid input). Here, the "invalid input" is the presence of
a command line parameter, any parameter, we just test if `argc > 1`.

The hypothetical buffer overflow bug is triggered between two calls to the `test()`
function. We can see in the second call that the object of class B now behaves
as a privileged object of class A, creating a potential security breach.

~~~
B b;

test(b);

if (argc > 1) {
    function_with_buffer_overflow(b);
}

test(b);
~~~

The sample scenario below demonstrates the attack, at least when the application
is compiled without Pointer Authentication Code (PAC) protection.

When the application is called without parameter, the two calls `test(b)` behave
identically, using the unprivileged features of an object of class B. But when a
command line parameter is provided (simulating some "invalid input"), the internal
supposed buffer overflow bug is triggered and overwrites some part of the `b` object.
As a consequence, during the second call to `test(b)`, the object has gained
elevated privileges.

~~~
$ clang++ jop-attack.cpp -o jop-attack
$
$ ./jop-attack
calling b.harmless()
in B::harmless(), a harmless restricted method
calling b.harmless()
in B::harmless(), a harmless restricted method
$
$ ./jop-attack foo
calling b.harmless()
in B::harmless(), a harmless restricted method
calling b.harmless()
in A::danger(), a dangerously privileged method
~~~

## Mitigating the attack on macOS

On macOS, we now compile the application with option `-arch arm64e`. In this context,
all code and data pointers are protected using PAC. Moreover, the signature of each
pointer is performed using address diversity plus semantic diversity.

~~~
$ clang++ -arch arm64e jop-attack.cpp -o jop-attack-protected
$
$ ./jop-attack-protected
calling b.harmless()
in B::harmless(), a harmless restricted method
calling b.harmless()
in B::harmless(), a harmless restricted method
$
$ ./jop-attack-protected foo
calling b.harmless()
in B::harmless(), a harmless restricted method
calling b.harmless()
Segmentation fault: 11
~~~

To understand how it works, let's have a look at how the compiler generates code
for calling virtual methods. Let's start from the following source code:

~~~
A a;
B b;
a.danger();
b.harmless();
~~~

The generated code on macOS with option `-arch arm64e` is the following.
We see that the pointer to C++ vtables (at start of object) is authenticated
with address diversity plus semantic diversity. The pointers to virtual methods
are authenticated using the same principles. The hard-coded constants
which are added for semantic diversity are different, depending on fully
qualified names of class and virtual method.

~~~
ldr	x0, [sp, #8]           ; load address of object a
ldr	x16, [x0]              ; load address of vtable for class A
mov	x8, x0
mov	x17, x8                ; address diversity in authentication of vtable address
movk	x17, #62866, lsl #48   ; add semantic diversity
autda	x16, x17               ; authenticate pointer to vtable
ldr	x8, [x16]              ; address of virtual method
mov	x9, x16
mov	x17, x9                ; address diversity in authentication of virtual method address
movk	x17, #1848, lsl #48    ; add semantic diversity
blraa	x8, x17                ; authenticate pointer to virtual table (abd call it)

ldr	x0, [sp]               ; load address of object b
ldr	x16, [x0]              ; similar call sequence...
mov	x8, x0
mov	x17, x8
movk	x17, #28965, lsl #48
autda	x16, x17
ldr	x8, [x16]
mov	x9, x16
mov	x17, x9
movk	x17, #44159, lsl #48
blraa	x8, x17
~~~

## Failing to mitigate the attack on Linux

On Linux, the same attack works identically without PAC protection.

With PAC protection, the attacks succeeds as well because gcc and clang
only protect the function calls return pointers on stack. They do not
authenticate data pointers and function pointers, such as C++ vtables.

On Linux, gcc and clang protect against ROP, but not against JOP.

~~~
$ g++ -mbranch-protection=pac-ret jop-attack.cpp -o jop-attack-protected
$
$ ./jop-attack-protected
calling b.harmless()
in B::harmless(), a harmless restricted method
calling b.harmless()
in B::harmless(), a harmless restricted method
$
$ ./jop-attack-protected foo
calling b.harmless()
in B::harmless(), a harmless restricted method
calling b.harmless()
in A::danger(), a dangerously privileged method
~~~

Even though we provided the only available compilation option for PAC insertion,
we see that no authentication is provided for pointers to C++ vtables and
virtual methods. Consequently, the JOP attack remains possible.

~~~
ldr     x0, [sp, 24]      ; load address of object a
ldr     x0, [x0]          ; load address of vtable for class A
ldr     x1, [x0]          ; address of virtual method
ldr     x0, [sp, 24]      ; "this" parameter
blr     x1                ; call virtual method

ldr     x0, [sp, 16]      ; load address of object b
ldr     x0, [x0]          ; similar call sequence...
ldr     x1, [x0]
ldr     x0, [sp, 16]
blr     x1
~~~
