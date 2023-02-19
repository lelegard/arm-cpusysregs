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

#define WIDTH 25


//----------------------------------------------------------------------------
// Manipulate the PAC keys.
//----------------------------------------------------------------------------

void GetKey(RegAccess& regaccess, const std::string& title, csr_pair_t& key, int key_index)
{
    const auto& desc(RegView::getRegister(key_index));
    if (desc.features & RegView::READ) {
        regaccess.read(key_index, key);
        std::cout << Pad(title, WIDTH) << " " << ToHexa(key) << std::endl;
    }
    else {
        std::cout << Pad(title, WIDTH) << " Cannot read " << desc.name << " on this CPU" << std::endl;
    }
}

void SetKey(RegAccess& regaccess, const std::string& title, const csr_pair_t& key, int key_index)
{
    const auto& desc(RegView::getRegister(key_index));
    if (desc.features & RegView::WRITE) {
        std::cout << Pad(title, WIDTH) << " " << ToHexa(key) << std::endl;
        regaccess.write(key_index, key);
    }
    else {
        std::cout << Pad(title, WIDTH) << " Cannot write " << desc.name << " on this CPU" << std::endl;
    }
}

void TestGA(RegAccess& regaccess, const std::string& title, csr_u64_t value, csr_u64_t modifier)
{
    csr_instr_t args;
    args.value = value;
    args.modifier = modifier;

    csr_u64_t result = 0x1111111111111111;
    csr_pacga(result, value, modifier);
    std::cout << Pad(title + " (user)", WIDTH) << " " << ToHexa(value) << " -> " << ToHexa(result) << std::endl;

    regaccess.executeInstr(CSR_INSTR_PACGA, args);
    std::cout << Pad(title + " (kernel)", WIDTH) << " " << ToHexa(value) << " -> " << ToHexa(args.value) << std::endl;
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
    GetKey(regaccess, "Initial GA key", key0, CSR_REGID2_APGAKEY);
    TestGA(regaccess, "PACGA", 0xFEDCBA9876543210, modifier);

    const csr_pair_t key1 {0xDEADBEEFBADC0FFE, 0x0123456789ABCDEF};
    SetKey(regaccess, "Update GA key", key1, CSR_REGID2_APGAKEY);

    csr_pair_t key2;
    GetKey(regaccess, "Updated GA key", key2, CSR_REGID2_APGAKEY);
    TestGA(regaccess, "PACGA", 0xFEDCBA9876543210, modifier);

    SetKey(regaccess, "Restore GA key", key0, CSR_REGID2_APGAKEY);
    GetKey(regaccess, "Restored GA key", key2, CSR_REGID2_APGAKEY);
    TestGA(regaccess, "PACGA", 0xFEDCBA9876543210, modifier);

    std::cout << std::endl << "---- Data pointer key B" << std::endl << std::endl;

    GetKey(regaccess, "Initial DB key", key0, CSR_REGID2_APDBKEY);

    modifier = 47;
    const csr_u64_t data = 0x123456789A;

    csr_u64_t data1 = data;
    std::cout << Pad("Before PACDB (user)", WIDTH) << " " << ToHexa(data1) << std::endl;
    csr_pacdb(data1, modifier);    
    std::cout << Pad("After PACDB (user)", WIDTH) << " " << ToHexa(data1) << std::endl;
    csr_u64_t corrupted = data1 ^ 1;

    csr_autdb(data1, modifier);
    std::cout << Pad("After AUTDB (user)", WIDTH) << " " << ToHexa(data) << std::endl;

    std::cout << Pad("Corrupted", WIDTH) << " " << ToHexa(corrupted) << std::endl;
    csr_autdb(corrupted, modifier);
    std::cout << Pad("After AUTDB (user)", WIDTH) << " " << ToHexa(corrupted) << std::endl;

    csr_instr_t args;
    args.value = data;
    args.modifier = modifier;
    std::cout << Pad("Before PACDB (kernel)", WIDTH) << " " << ToHexa(args.value) << std::endl;
    regaccess.executeInstr(CSR_INSTR_PACDB, args);
    std::cout << Pad("After PACDB (kernel)", WIDTH) << " " << ToHexa(args.value) << std::endl;
    regaccess.executeInstr(CSR_INSTR_AUTDB, args);
    std::cout << Pad("After AUTDB (kernel)", WIDTH) << " " << ToHexa(args.value) << std::endl;
    
    std::cout << std::endl;
    return EXIT_SUCCESS;
}
