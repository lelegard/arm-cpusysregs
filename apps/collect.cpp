//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Collect tabular data about the PAC format. The output format is compatible
// with the table at the end of docs/pac-format.md.
//
//----------------------------------------------------------------------------

#include "cpusysregs.h"
#include "armfeatures.h"
#include "armpseudocode.h"
#include "regview.h"
#include "strutils.h"

#include <iostream>
#include <cstddef>
#include <cstdlib>

#define WIDTH 15


//----------------------------------------------------------------------------
// Formatting functions.
//----------------------------------------------------------------------------

std::string Str(const std::string& s)
{
    return Pad(s, WIDTH, ' ') + " |";
}

std::string Bool(bool b)
{
    return Pad(YesNo(b), WIDTH, ' ') + " |";
}

std::string Bool(bool b1, bool b2)
{
    return Pad(YesNo(b1) + " / " + YesNo(b2), WIDTH, ' ') + " |";
}

std::string Int(int i, const char* prefix = "", const char* suffix = "")
{
    return Pad(Format("%s%d%s", prefix, i, suffix), WIDTH, ' ') + " |";
}

std::string PacBits(ArmPseudoCode& code, csr_u64_t address, bool is_instr)
{
    const int top = code.pacTopBit(address, is_instr);
    const int bottom = code.pacBottomBit(address, is_instr);
    if (bottom < 55 && 55 < top) {
        return Str(Format("%d:56,54:%d", top, bottom));
    }
    else {
        return Str(Format("%d:%d", top == 55 ? 54 : top, bottom == 55 ? 56 : bottom));
    }
}


//----------------------------------------------------------------------------
// Check if PAC keys are identical in EL0 and EL1.
//----------------------------------------------------------------------------

std::string PacKeys(RegAccess& regs, int regid)
{
    // Check if PAC is implemented.
    ArmFeatures feat(regs);
    if (!feat.FEAT_PAuth()) {
        return Str("none");
    }

    const csr_u64_t modifier = 47;
    const csr_u64_t value = 0x12345678;
    csr_u64_t value_pac = value;
    int instr = CSR_INSTR_INVALID;

    // Execute PAC in user mode, get instruction id for kernel mode.
    switch (regid) {
        case CSR_REGID2_APIAKEY_EL1:
            csr_pacia(value_pac, modifier);
            instr = CSR_INSTR_PACIA;
            break;
        case CSR_REGID2_APIBKEY_EL1:
            csr_pacib(value_pac, modifier);
            instr = CSR_INSTR_PACIB;
            break;
        case CSR_REGID2_APDAKEY_EL1:
            csr_pacda(value_pac, modifier);
            instr = CSR_INSTR_PACDA;
            break;
        case CSR_REGID2_APDBKEY_EL1:
            csr_pacdb(value_pac, modifier);
            instr = CSR_INSTR_PACDB;
            break;
        case CSR_REGID2_APGAKEY_EL1:
            csr_pacga(value_pac, value, modifier);
            instr = CSR_INSTR_PACGA;
            break;
    }

    // Check if PAC instructions are inactive.
    if (value == value_pac) {
        return Str("inactive");
    }

    // Execute in kernel mode.
    csr_instr_t args;
    args.value = value;
    args.modifier = modifier;
    regs.executeInstr(instr, args);

    // Check if EL0 and EL1 use distinct keys.
    if (value_pac != args.value) {
        return Str("distinct keys");
    }

    // Check if we can read the key and non-zero.
    bool zero = false;
    if (RegView::getRegister(regid).features & RegView::READ) {
        csr_pair_t key;
        regs.read(regid, key);
        zero = key.high == 0 && key.low == 0;
    }
    return Str(zero ? "zero" : "same key");
}


//----------------------------------------------------------------------------
// Program entry point.
//----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    RegAccess regs(true, true);
    ArmFeatures feat(regs);
    ArmPseudoCode code(regs);

    const char* algo = (feat.FEAT_PACQARMA5() ? "QARMA5" : (feat.FEAT_PACQARMA3() ? "QARMA3" : (feat.FEAT_PACIMP() ? "private" : "none")));

    std::cout << "| PAC algorithm        | " << Str(algo) << std::endl
              << "| PAuth / PAuth2       | " << Bool(feat.FEAT_PAuth(), feat.FEAT_PAuth2()) << std::endl
              << "| EPAC / FPAC          | " << Bool(feat.FEAT_EPAC(), feat.FEAT_FPAC()) << std::endl
              << "| MTE tagging          | " << Bool(feat.addressTaggingEnabled()) << std::endl
              << "|                      | " << Str("") << std::endl
              << "| **PAC size**         | " << Str("") << std::endl
              << "| data, lower          | " << Int(code.pacSize(0, false), "", " bits") << std::endl
              << "| data, upper          | " << Int(code.pacSize(~0ull, false), "", " bits") << std::endl
              << "| instruction, lower   | " << Int(code.pacSize(0, true), "", " bits") << std::endl
              << "| instruction, upper   | " << Int(code.pacSize(~0ull, true), "", " bits") << std::endl
              << "|                      | " << Str("") << std::endl
              << "| **PAC position**     | " << Str("") << std::endl
              << "| data, lower          | " << PacBits(code, 0, false) << std::endl
              << "| data, upper          | " << PacBits(code, ~0ull, false) << std::endl
              << "| instruction, lower   | " << PacBits(code, 0, true) << std::endl
              << "| instruction, upper   | " << PacBits(code, ~0ull, true) << std::endl
              << "|                      | " << Str("") << std::endl
              << "| **PAC selector bit** | " << Str("") << std::endl
              << "| data, lower          | " << Int(code.pacSelBit(0, false), "bit ") << std::endl
              << "| data, upper          | " << Int(code.pacSelBit(~0ull, false), "bit ") << std::endl
              << "| instruction, lower   | " << Int(code.pacSelBit(0, true), "bit ") << std::endl
              << "| instruction, upper   | " << Int(code.pacSelBit(~0ull, true), "bit ") << std::endl
              << "|                      | " << Str("") << std::endl
              << "| **EL0/EL1 PAC keys** | " << Str("") << std::endl
              << "| DA                   | " << PacKeys(regs, CSR_REGID2_APDAKEY_EL1) << std::endl
              << "| DB                   | " << PacKeys(regs, CSR_REGID2_APDBKEY_EL1) << std::endl
              << "| IA                   | " << PacKeys(regs, CSR_REGID2_APIAKEY_EL1) << std::endl
              << "| IB                   | " << PacKeys(regs, CSR_REGID2_APIBKEY_EL1) << std::endl
              << "| Generic (PACGA)      | " << PacKeys(regs, CSR_REGID2_APGAKEY_EL1) << std::endl
              << "|                      | " << Str("") << std::endl
              << "| **TCR_EL1 register** | " << Str("") << std::endl
              << "| TBI0                 | " << Int(feat.TCR_EL1_TBI0()) << std::endl
              << "| TBID0                | " << Int(feat.TCR_EL1_TBID0()) << std::endl
              << "| T0SZ                 | " << Int(feat.TCR_EL1_T0SZ()) << std::endl
              << "| TBI1                 | " << Int(feat.TCR_EL1_TBI1()) << std::endl
              << "| TBID1                | " << Int(feat.TCR_EL1_TBID1()) << std::endl
              << "| T1SZ                 | " << Int(feat.TCR_EL1_T1SZ()) << std::endl;
    return EXIT_SUCCESS;
}
