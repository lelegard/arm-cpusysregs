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
#include "regview.h"

#include <iostream>
#include <cstddef>
#include <cstdlib>


//----------------------------------------------------------------------------
// Manipulate the PAC keys.
//----------------------------------------------------------------------------

void GetKey(RegAccess& regaccess, const std::string& title, csr_pair_t& key, int key_index)
{
    const auto& desc(RegView::getRegister(key_index));
    if (desc.features & RegView::READ) {
        regaccess.read(key_index, key);
        std::cout << Pad(title, 20) << " " << ToString(key) << std::endl;
    }
    else {
        std::cout << Pad(title, 20) << " Cannot read " << desc.name << " on this CPU" << std::endl;
    }
}

void SetKey(RegAccess& regaccess, const std::string& title, const csr_pair_t& key, int key_index)
{
    const auto& desc(RegView::getRegister(key_index));
    if (desc.features & RegView::WRITE) {
        std::cout << Pad(title, 20) << " " << ToString(key) << std::endl;
        regaccess.write(key_index, key);
    }
    else {
        std::cout << Pad(title, 20) << " Cannot write " << desc.name << " on this CPU" << std::endl;
    }
}

void GetKeyGA(RegAccess& regaccess, const std::string& title, csr_pair_t& key)
{
    GetKey(regaccess, title, key, CSR_REG2_APGAKEY);
}

void SetKeyGA(RegAccess& regaccess, const std::string& title, const csr_pair_t& key)
{
    SetKey(regaccess, title, key, CSR_REG2_APGAKEY);
}

void TestGA(const std::string& title, csr_u64_t value, csr_u64_t modifier)
{
    csr_u64_t result = 0x1111111111111111;
    asm("pacga %[res], %[val], %[mod]" : [res] "+r" (result) : [val] "r" (value), [mod] "r" (modifier));
    std::cout << Pad(title, 20) << " " << ToString(value) << " -> " << ToString(result) << std::endl;
}

void GetKeyDB(RegAccess& regaccess, const std::string& title, csr_pair_t& key)
{
    GetKey(regaccess, title, key, CSR_REG2_APDBKEY);
}

void SetKeyDB(RegAccess& regaccess, const std::string& title, const csr_pair_t& key)
{
    SetKey(regaccess, title, key, CSR_REG2_APDBKEY);
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
    RegAccess regaccess(true, true);

    std::cout << std::endl << "---- Generic key" << std::endl << std::endl;

    csr_u64_t modifier = 7;
    csr_pair_t key0;
    GetKeyGA(regaccess, "Initial GA key", key0);
    TestGA("PACGA", 0xFEDCBA9876543210, modifier);

    const csr_pair_t key1 {0xDEADBEEFBADC0FFE, 0x0123456789ABCDEF};
    SetKeyGA(regaccess, "Update GA key", key1);

    csr_pair_t key2;
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
