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
#include "armfeatures.h"
#include "strutils.h"
#include "regaccess.h"
#include "regview.h"
#include "qarma64.h"

#include <functional>
#include <iostream>
#include <cstddef>
#include <cstdlib>

#define WIDTH 25

// Profile of a lambda function which executes one PACxx or AUTxx instruction.
typedef std::function<void(csr_u64_t& data, csr_u64_t modifier)> pac_func_t;


//----------------------------------------------------------------------------
// Manipulate the PAC keys.
//----------------------------------------------------------------------------

void GetKey(RegAccess& regaccess, const std::string& title, csr_pair_t& key, int regid)
{
    const auto& desc(RegView::getRegister(regid));
    if (desc.features & RegView::READ) {
        regaccess.read(regid, key);
        std::cout << Pad(title, WIDTH) << " " << ToHexa(key) << std::endl;
    }
    else {
        std::cout << Pad(title, WIDTH) << " Cannot read " << desc.name << " on this CPU" << std::endl;
    }
}

void SetKey(RegAccess& regaccess, const std::string& title, const csr_pair_t& key, int regid)
{
    const auto& desc(RegView::getRegister(regid));
    if (desc.features & RegView::WRITE) {
        std::cout << Pad(title, WIDTH) << " " << ToHexa(key) << std::endl;
        regaccess.write(regid, key);
    }
    else {
        std::cout << Pad(title, WIDTH) << " Cannot write " << desc.name << " on this CPU" << std::endl;
    }
}


//----------------------------------------------------------------------------
// Test using the generic key.
//----------------------------------------------------------------------------

void TestGA(RegAccess& regaccess, const std::string& title, const csr_pair_t& key, csr_u64_t value, csr_u64_t modifier)
{
    csr_instr_t args;
    args.value = value;
    args.modifier = modifier;

    csr_u64_t result = 0x1111111111111111;
    csr_pacga(result, value, modifier);
    std::cout << Pad(title + " (user)", WIDTH) << " " << ToHexa(result) << std::endl;

    regaccess.executeInstr(CSR_INSTR_PACGA, args);
    std::cout << Pad(title + " (kernel)", WIDTH) << " " << ToHexa(args.value) << std::endl;

    ArmFeatures features(regaccess);
    const int qarma_rounds = features.pacQARMA();
    if (qarma_rounds > 0) {
        Qarma64 qarma(qarma_rounds);
        std::cout << Pad(Format("QARMA%d (soft)", qarma_rounds), WIDTH) << " "
                  << ToHexa(qarma.encrypt(value, modifier, key.high, key.low)) << std::endl;
    }
}


//----------------------------------------------------------------------------
// Test using one of the 4 specialized keys.
//----------------------------------------------------------------------------

std::string Status(csr_u64_t value, csr_u64_t expected)
{
    return ToHexa(value) + (value == expected ? " (passed)" : " (failed)");
}

void TestKeyOneValue(RegAccess& regaccess, const std::string& keyname, int regid, csr_u64_t value, csr_u64_t modifier,
                     int pac_instr, int aut_instr, pac_func_t pac_func, pac_func_t aut_func)
{
    const bool upper = value & 0x8000000000000000;
    std::cout << std::endl << "---- Testing key " << keyname
              << " (" << (upper ? "upper" : "lower") << " addresses)" << std::endl << std::endl;

    csr_pair_t key;
    GetKey(regaccess, "Initial " + keyname + " key", key, regid);

    csr_u64_t data1 = value;
    std::cout << Pad("Before PAC" + keyname, WIDTH) << " " << ToHexa(data1) << std::endl;
    pac_func(data1, modifier);
    std::cout << Pad("After PAC" + keyname + " (user)", WIDTH) << " " << ToHexa(data1) << std::endl;

    csr_u64_t corrupted = data1 ^ 1;
    aut_func(data1, modifier);
    std::cout << Pad("After AUT" + keyname + " (user)", WIDTH) << " " << Status(data1, value) << std::endl;

    csr_instr_t args;
    args.value = value;
    args.modifier = modifier;
    regaccess.executeInstr(pac_instr, args);
    std::cout << Pad("After PAC" + keyname + " (kernel)", WIDTH) << " " << ToHexa(args.value) << std::endl;
    regaccess.executeInstr(aut_instr, args);
    std::cout << Pad("After AUT" + keyname + " (kernel)", WIDTH) << " " << Status(args.value, value) << std::endl;

    ArmFeatures features(regaccess);
    const int qarma_rounds = features.pacQARMA();
    if (qarma_rounds > 0) {
        Qarma64 qarma(qarma_rounds);
        std::cout << Pad(Format("QARMA%d (soft)", qarma_rounds), WIDTH) << " "
                  << ToHexa(qarma.encrypt(value, modifier, key.high, key.low)) << std::endl;
    }

    std::cout << Pad("Corrupted (user)", WIDTH) << " " << ToHexa(corrupted) << std::endl;
    aut_func(corrupted, modifier);
    std::cout << Pad("After AUT" + keyname + " (user)", WIDTH) << " " << Status(corrupted, value) << std::endl;
}

void TestKey(RegAccess& regaccess, const std::string& keyname, int regid,
             int pac_instr, int aut_instr, pac_func_t pac_func, pac_func_t aut_func)
{
    TestKeyOneValue(regaccess, keyname, regid, 0x000000123456789A, 47, pac_instr, aut_instr, pac_func, aut_func);
    TestKeyOneValue(regaccess, keyname, regid, 0xFFFFFF123456789A, 47, pac_instr, aut_instr, pac_func, aut_func);
}


//----------------------------------------------------------------------------
// Program entry point.
//----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    // Open the pseudo-device for the kernel module.
    RegAccess regaccess(true, true);

    TestKey(regaccess, "IA", CSR_REGID2_APIAKEY, CSR_INSTR_PACIA, CSR_INSTR_AUTIA,
            [](csr_u64_t& data, csr_u64_t mod) { csr_pacia(data, mod); },
            [](csr_u64_t& data, csr_u64_t mod) { csr_autia(data, mod); });

    TestKey(regaccess, "IB", CSR_REGID2_APIBKEY, CSR_INSTR_PACIB, CSR_INSTR_AUTIB,
            [](csr_u64_t& data, csr_u64_t mod) { csr_pacib(data, mod); },
            [](csr_u64_t& data, csr_u64_t mod) { csr_autib(data, mod); });

    TestKey(regaccess, "DA", CSR_REGID2_APDAKEY, CSR_INSTR_PACDA, CSR_INSTR_AUTDA,
            [](csr_u64_t& data, csr_u64_t mod) { csr_pacda(data, mod); },
            [](csr_u64_t& data, csr_u64_t mod) { csr_autda(data, mod); });

    TestKey(regaccess, "DB", CSR_REGID2_APDBKEY, CSR_INSTR_PACDB, CSR_INSTR_AUTDB,
            [](csr_u64_t& data, csr_u64_t mod) { csr_pacdb(data, mod); },
            [](csr_u64_t& data, csr_u64_t mod) { csr_autdb(data, mod); });

    std::cout << std::endl << "---- Testing key GA" << std::endl << std::endl;
    const csr_u64_t value = 0xFEDCBA9876543210;
    const csr_u64_t modifier = 7;

    csr_pair_t key0;
    GetKey(regaccess, "Initial GA key", key0, CSR_REGID2_APGAKEY);
    std::cout << Pad("Input value", WIDTH) << " " << ToHexa(value) << std::endl;
    TestGA(regaccess, "PACGA", key0, value, modifier);

    const csr_pair_t key1 {0xDEADBEEFBADC0FFE, 0x0123456789ABCDEF};
    SetKey(regaccess, "Update GA key", key1, CSR_REGID2_APGAKEY);

    csr_pair_t key2;
    GetKey(regaccess, "Updated GA key", key2, CSR_REGID2_APGAKEY);
    TestGA(regaccess, "PACGA", key2, value, modifier);

    SetKey(regaccess, "Restore GA key", key0, CSR_REGID2_APGAKEY);
    GetKey(regaccess, "Restored GA key", key2, CSR_REGID2_APGAKEY);
    TestGA(regaccess, "PACGA", key2, value, modifier);

    std::cout << std::endl;
    return EXIT_SUCCESS;
}
