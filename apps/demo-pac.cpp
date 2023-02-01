//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Pointer authentication demo.
//
// We play with the value of a PAC key. Initially tried with instruction
// pointer key A (PACIA) and it crashes the system. Some instruction may
// have been authenticated in kernel and changing the corresponding PAC
// crashes the kernel.
//
//----------------------------------------------------------------------------

#include "cpusysregs.h"
#include "strutils.h"
#include "regaccess.h"

#include <iostream>
#include <cstddef>
#include <cstdlib>


//----------------------------------------------------------------------------
// Manipulate the generic key.
//----------------------------------------------------------------------------

void GetKeyGA(RegAccess& regaccess, const std::string& title, csr_pac_key_t& key)
{
    // Read all system registers.
    csr_registers_t regs;
    regaccess.read(regs);
    std::cout << Pad(title, 20) << " " << ToString(regs.apgakeyhi_el1, regs.apgakeylo_el1) << std::endl;
}

void SetKeyGA(RegAccess& regaccess, const std::string& title, const csr_pac_key_t& key)
{
    std::cout << Pad(title, 20) << " " << ToString(key) << std::endl;
    regaccess.setKeyGA(key);
}

void TestGA(const std::string& title, csr_u64_t value, csr_u64_t modifier)
{
    csr_u64_t result = 0x1111111111111111;
    asm("pacga %[res], %[val], %[mod]" : [res] "+r" (result) : [val] "r" (value), [mod] "r" (modifier));
    std::cout << Pad(title, 20) << " " << ToString(value) << " -> " << ToString(result) << std::endl;
}


//----------------------------------------------------------------------------
// Manipulate the data pointer key B.
//----------------------------------------------------------------------------

void GetKeyDB(RegAccess& regaccess, const std::string& title, csr_pac_key_t& key)
{
    // Read all system registers.
    csr_registers_t regs;
    regaccess.read(regs);
    std::cout << Pad(title, 20) << " " << ToString(regs.apdbkeyhi_el1, regs.apdbkeylo_el1) << std::endl;
}

void SetKeyDB(RegAccess& regaccess, const std::string& title, const csr_pac_key_t& key)
{
    std::cout << Pad(title, 20) << " " << ToString(key) << std::endl;
    regaccess.setKeyDB(key);
}

void TestDB(const std::string& title, csr_u64_t& value, csr_u64_t modifier)
{
    csr_u64_t result = 0x1111111111111111;
    asm("pacga %[res], %[val], %[mod]" : [res] "+r" (result) : [val] "r" (value), [mod] "r" (modifier));
    std::cout << Pad(title, 20) << " " << ToString(value) << " -> " << ToString(result) << std::endl;
}


//----------------------------------------------------------------------------
// Program entry point
//----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    // Open the pseudo-device for the kernel module.
    // Fail application on error, don't need to check for success.
    RegAccess regaccess(true);

    std::cout << std::endl << "---- Generic key" << std::endl << std::endl;

    csr_u64_t modifier = 7;
    csr_pac_key_t key0;
    GetKeyGA(regaccess, "Initial GA key", key0);
    TestGA("PACGA", 0xFEDCBA9876543210, modifier);

    const csr_pac_key_t key1 {0xDEADBEEFBADC0FFE, 0x0123456789ABCDEF};
    SetKeyGA(regaccess, "Update GA key", key1);

    csr_pac_key_t key2;
    GetKeyGA(regaccess, "Updated GA key", key2);
    TestGA("PACGA", 0xFEDCBA9876543210, modifier);

    SetKeyGA(regaccess, "Restore GA key", key0);
    GetKeyGA(regaccess, "Restored GA key", key2);
    TestGA("PACGA", 0xFEDCBA9876543210, modifier);

    std::cout << std::endl << "---- Data pointer key B" << std::endl << std::endl;

    GetKeyDB(regaccess, "Initial DB key", key0);

    modifier = 47;
    csr_u64_t data = 0x123456789A;
    std::cout << Pad("Before PACDB", 20) << " " << ToString(data) << std::endl;
    asm("pacdb %[dat], %[mod]" : [dat] "+r" (data) : [mod] "r" (modifier));
    std::cout << Pad("After PACDB", 20) << " " << ToString(data) << std::endl;
    csr_u64_t corrupted = data ^ 1;

    asm("autdb %[dat], %[mod]" : [dat] "+r" (data) : [mod] "r" (modifier));
    std::cout << Pad("After AUTDB", 20) << " " << ToString(data) << std::endl;

    std::cout << Pad("Corrupted", 20) << " " << ToString(corrupted) << std::endl;
    asm("autdb %[dat], %[mod]" : [dat] "+r" (corrupted) : [mod] "r" (modifier));
    std::cout << Pad("After AUTDB", 20) << " " << ToString(corrupted) << std::endl;

    std::cout << std::endl;
    return EXIT_SUCCESS;
}
