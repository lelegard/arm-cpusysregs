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
#include "armpseudocode.h"
#include "strutils.h"
#include "regaccess.h"
#include "regview.h"
#include "qarma64.h"

#include <functional>
#include <iostream>
#include <cstddef>
#include <cstdlib>

#define WIDTH 25


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
// Passed/failed status.
//----------------------------------------------------------------------------

std::string Status(bool passed)
{
    return passed ? " (passed)" : " (failed)";
}

std::string Status(csr_u64_t value, csr_u64_t expected)
{
    return ToHexa(value) + Status(value == expected);
}


//----------------------------------------------------------------------------
// Test using the generic key.
//----------------------------------------------------------------------------

void TestGA(RegAccess& regaccess, const std::string& title, const csr_pair_t& key, csr_u64_t value, csr_u64_t modifier)
{
    ArmFeatures features(regaccess);
    ArmPseudoCode code(regaccess);

    // PACGA in user mode.
    csr_u64_t result = 0x1111111111111111;
    csr_pacga(result, value, modifier);
    std::cout << Pad(title + " (user)", WIDTH) << " " << ToHexa(result) << std::endl;

    // PACGA in kernel mode.
    csr_instr_t args;
    args.value = value;
    args.modifier = modifier;
    regaccess.executeInstr(CSR_INSTR_PACGA, args);
    std::cout << Pad(title + " (kernel)", WIDTH) << " " << ToHexa(args.value) << std::endl;

    // If PAC algo is QARMA, verify using software emulation.
    // We need to compare with the value which was computed in kernel mode since the key was fetched in kernel mode.
    const int qarma_rounds = features.pacQARMA();
    if (qarma_rounds > 0) {

        // Direct 64-bit QARMA encryption.
        Qarma64 qarma(qarma_rounds);
        const csr_u64_t encrypted = qarma.encrypt(value, modifier, key.high, key.low);
        const csr_u64_t pac_mask = ArmPseudoCode::Bits(63, 32);
        std::cout << Pad(Format("QARMA%d (soft)", qarma_rounds), WIDTH) << " " << ToHexa(encrypted)
                  << Status((encrypted & pac_mask) == (args.value & pac_mask)) << std::endl;

        // Using emulation of Arm pseudo-code.
        const csr_u64_t pacga = code.AddPACGA(value, modifier, key);
        std::cout << Pad("AddPACGA (soft)", WIDTH) << " " << Status(pacga, args.value) << std::endl;
    }
}


//----------------------------------------------------------------------------
// Test using one of the 4 specialized keys.
//----------------------------------------------------------------------------

void TestKeyOneValue(RegAccess& regaccess, int regid, csr_u64_t value, csr_u64_t modifier)
{
    ArmFeatures features(regaccess);
    ArmPseudoCode code(regaccess);

    std::string keyname;
    const bool upper = value & 0x8000000000000000;
    bool is_instr = false;
    int pac_instr = 0;
    int aut_instr = 0;
    csr_u64_t value_pac = value;
    csr_u64_t value_aut = 0;
    csr_u64_t corrupted = 0;
    csr_u64_t corrupted_aut = 0;

    // Verify that a corrupted signed pointer (lsb flipped) is not authenticated.
    // But don't do that if FEAT_FPAC is implemented because it would raise an exception.
    const bool fpac = features.FEAT_FPAC() || features.FEAT_FPACCOMBINE();

    // Compute PAC and AUT in user mode, depending on the key register id.
    switch (regid) {
        case CSR_REGID2_APIAKEY_EL1:
            // Constants for future usages.
            keyname = "IA";
            is_instr = true;
            pac_instr = CSR_INSTR_PACIA;
            aut_instr = CSR_INSTR_AUTIA;
            // Compute PAC, AUT and corrupted AUT in user mode.
            csr_pacia(value_pac, modifier);
            value_aut = value_pac;
            csr_autia(value_aut, modifier);
            corrupted = corrupted_aut = value_pac ^ 1;
            if (!fpac) {
                csr_autia(corrupted_aut, modifier);
            }
            break;
        case CSR_REGID2_APIBKEY_EL1:
            // Constants for future usages.
            keyname = "IB";
            is_instr = true;
            pac_instr = CSR_INSTR_PACIB;
            aut_instr = CSR_INSTR_AUTIB;
            // Compute PAC, AUT and corrupted AUT in user mode.
            csr_pacib(value_pac, modifier);
            value_aut = value_pac;
            csr_autib(value_aut, modifier);
            corrupted = corrupted_aut = value_pac ^ 1;
            if (!fpac) {
                csr_autib(corrupted_aut, modifier);
            }
            break;
        case CSR_REGID2_APDAKEY_EL1:
            // Constants for future usages.
            keyname = "DA";
            is_instr = false;
            pac_instr = CSR_INSTR_PACDA;
            aut_instr = CSR_INSTR_AUTDA;
            // Compute PAC, AUT and corrupted AUT in user mode.
            csr_pacda(value_pac, modifier);
            value_aut = value_pac;
            csr_autda(value_aut, modifier);
            corrupted = corrupted_aut = value_pac ^ 1;
            if (!fpac) {
                csr_autda(corrupted_aut, modifier);
            }
            break;
        case CSR_REGID2_APDBKEY_EL1:
            // Constants for future usages.
            keyname = "DB";
            is_instr = false;
            pac_instr = CSR_INSTR_PACDB;
            aut_instr = CSR_INSTR_AUTDB;
            // Compute PAC, AUT and corrupted AUT in user mode.
            csr_pacdb(value_pac, modifier);
            value_aut = value_pac;
            csr_autdb(value_aut, modifier);
            corrupted = corrupted_aut = value_pac ^ 1;
            if (!fpac) {
                csr_autdb(corrupted_aut, modifier);
            }
            break;
    }

    std::cout << std::endl
              << "---- Testing key " << keyname << " (" << (upper ? "upper" : "lower") << " addresses)"
              << std::endl << std::endl;

    csr_pair_t key;
    GetKey(regaccess, "Initial " + keyname + " key", key, regid);

    // Display PAC usage in user mode (already computed in switch above).
    std::cout << Pad("Before PAC" + keyname, WIDTH) << " " << ToHexa(value) << std::endl;
    std::cout << Pad("After PAC" + keyname + " (user)", WIDTH) << " " << ToHexa(value_pac) << std::endl;
    std::cout << Pad("After AUT" + keyname + " (user)", WIDTH) << " " << Status(value_aut, value) << std::endl;

    // Display PAC usage in kernel mode.
    csr_instr_t args;
    args.value = value;
    args.modifier = modifier;
    regaccess.executeInstr(pac_instr, args);
    std::cout << Pad("After PAC" + keyname + " (kernel)", WIDTH) << " " << ToHexa(args.value) << std::endl;
    const csr_u64_t k_value_pac = args.value;
    regaccess.executeInstr(aut_instr, args);
    std::cout << Pad("After AUT" + keyname + " (kernel)", WIDTH) << " " << Status(args.value, value) << std::endl;

    // Display PAC mask and size.
    std::cout << Pad("PAC" + keyname + " mask", WIDTH) << " " << ToHexa(code.pacMask(value, is_instr))
              << " (" << code.pacSize(value, is_instr) << " bits)" << std::endl;

    // If PAC algo is QARMA, verify using software emulation.
    // We need to compare with the value which was computed in kernel mode since the key was fetched in kernel mode.
    const int qarma_rounds = features.pacQARMA();
    if (qarma_rounds > 0) {

        // Direct 64-bit QARMA encryption.
        // May not directly match since PAC computation can be complex and xor'ed.
        Qarma64 qarma(qarma_rounds);
        const csr_u64_t encrypted = qarma.encrypt(value, modifier, key.high, key.low);
        std::cout << Pad(Format("QARMA%d (soft)", qarma_rounds), WIDTH) << " " << ToHexa(encrypted) << std::endl;

        // Using emulation of Arm pseudo-code. Must match.
        const csr_u64_t pac = code.AddPAC(value, modifier, key, !is_instr);
        std::cout << Pad("AddPAC (soft)", WIDTH) << " " << Status(pac, k_value_pac) << std::endl;
    }

    // Verify that a corrupted signed pointer (lsb flipped) is not authenticated.
    if (!fpac) {
        std::cout << Pad("Corrupted (user)", WIDTH) << " " << ToHexa(corrupted) << std::endl;
        std::cout << Pad("After AUT" + keyname + " (user)", WIDTH) << " " << Status(corrupted_aut, value) << std::endl;
    }
}

void TestKey(RegAccess& regaccess, int regid)
{
    TestKeyOneValue(regaccess, regid, 0x000000123456789A, 47);
    TestKeyOneValue(regaccess, regid, 0xFFFFFF123456789A, 47);
}


//----------------------------------------------------------------------------
// Program entry point.
//----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    // Open the pseudo-device for the kernel module.
    RegAccess regaccess(true, true);

    TestKey(regaccess, CSR_REGID2_APIAKEY_EL1);
    TestKey(regaccess, CSR_REGID2_APIBKEY_EL1);
    TestKey(regaccess, CSR_REGID2_APDAKEY_EL1);
    TestKey(regaccess, CSR_REGID2_APDBKEY_EL1);

    std::cout << std::endl << "---- Testing key GA" << std::endl << std::endl;
    const csr_u64_t value = 0xFEDCBA9876543210;
    const csr_u64_t modifier = 7;

    csr_pair_t key0;
    GetKey(regaccess, "Initial GA key", key0, CSR_REGID2_APGAKEY_EL1);
    std::cout << Pad("Input value", WIDTH) << " " << ToHexa(value) << std::endl;
    TestGA(regaccess, "PACGA", key0, value, modifier);

    const csr_pair_t key1 {0xDEADBEEFBADC0FFE, 0x0123456789ABCDEF};
    SetKey(regaccess, "Update GA key", key1, CSR_REGID2_APGAKEY_EL1);

    csr_pair_t key2;
    GetKey(regaccess, "Updated GA key", key2, CSR_REGID2_APGAKEY_EL1);
    TestGA(regaccess, "PACGA", key2, value, modifier);

    SetKey(regaccess, "Restore GA key", key0, CSR_REGID2_APGAKEY_EL1);
    GetKey(regaccess, "Restored GA key", key2, CSR_REGID2_APGAKEY_EL1);
    TestGA(regaccess, "PACGA", key2, value, modifier);

    std::cout << std::endl;
    return EXIT_SUCCESS;
}
