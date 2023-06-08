#include <iostream>
#include <cstdlib>

// The class A implements highly privileged objects. These objects may have a
// security impact on the system. Using them shall be done with caution.
class A
{
public:
    virtual void danger() const;
};

void A::danger() const
{
    std::cout << "in A::danger(), a dangerously privileged method" << std::endl;
}

// The class B implements unprivileged objects. They can be used anywhere without risk.
class B
{
public:
    virtual void harmless() const;
};

void B::harmless() const
{
    std::cout << "in B::harmless(), a harmless restricted method" << std::endl;
}

// An innocent test function working on unprivileged objects.
void test(const B& b)
{
    std::cout << "calling b.harmless()" << std::endl;
    b.harmless();
}

// This intermediate function is supposed to have some buffer overflow issue and may
// overwirte part of the read-only B object. This is the root cause of the JOP attack.
void function_with_buffer_overflow(const B& b)
{
    // We emulate the buffer overflow by directly replacing the vtable pointer
    // of b by the one from a. This means that object b, supposed to be unprivileged,
    // will now behave as an object of class A, with more privileges.
    A a;
    *(void**)(&b) = *(void**)(&a);
}

// This unused function can be used to compare the generated code sequences for
// calling the two virtual functions in the two classes. Use the compilation option
// "-S" to view the generated code.
void look_at_the_generated_code(A& a, B& b)
{
    a.danger();
    b.harmless();    
}

// Attack scenario.
int main(int argc, char* argv[])
{
    B b;

    // We call the test method with an unprivileged object of class B.
    test(b);

    // If the application is fed with some specific input (here, the presence of a
    // command line parameter), we run through a buggy method with a buffer overflow.
    if (argc > 1) {
        function_with_buffer_overflow(b);
    }

    // We call the test method again with the unprivileged object.
    // Or at least we think that the object is still unprivileged...
    test(b);

    return EXIT_SUCCESS;
}
