//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Compute a PAC using the generic key.
// Display the 32 upper bits of the result.
//
// Syntax: pacga 128-bit-key 32-bit-modifier 32-bit-value
//
//----------------------------------------------------------------------------

#include "regaccess.h"
#include "regview.h"
#include "qarma64.h"
#include "armfeatures.h"
#include "strutils.h"

#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cstring>

int main(int argc, char* argv[])
{
    csr_pair_t key;
    csr_u64_t modifier;
    csr_u64_t value;

    // Read command line arguments.
    if (argc < 4 || !DecodeHexa(key, argv[1]) || !DecodeHexa(modifier, argv[2]) || !DecodeHexa(value, argv[3])) {
        std::cerr << "Usage: " << argv[0] << " 128-bit-key 32-bit-modifier 32-bit-value" << std::endl;
        return EXIT_FAILURE;
    }

    RegAccess regaccess(true, true);

    // Check PAC capabilities.
    ArmFeatures features(regaccess);
    if (!features.FEAT_PAuth()) {
        std::cerr << "Pointer authentication is not supported on this CPU" << std::endl;
        return EXIT_FAILURE;
    }

    const auto& desc(RegView::getRegister(CSR_REGID2_APGAKEY));
    if ((desc.features & (RegView::READ | RegView::WRITE)) != (RegView::READ | RegView::WRITE)) {
        std::cerr << "PAC key registers are not accessible on this platform" << std::endl;
        return EXIT_FAILURE;
    }

    // Display input data.
    std::cout << "Algorithm: " << features.pacAlgo() << std::endl
              << "Key:       " << ToHexa(key) << std::endl
              << "Modifier:  " << ToHexa(modifier) << std::endl
              << "Value:     " << ToHexa(value) << std::endl;

    // Set PACGA key, then verify it.
    regaccess.write(CSR_REGID2_APGAKEY, key);
    csr_pair_t check;
    regaccess.read(CSR_REGID2_APGAKEY, check);
    if (::memcmp(&check, &key, sizeof(key))) {
        std::cerr << "Key verification failed, APGAKEY register = " << ToHexa(check) << std::endl;
        return EXIT_FAILURE;
        
    }

    // Compute PACGA in user mode.
    csr_u64_t result = 0x1111111111111111;
    csr_pacga(result, value, modifier);
    std::cout << "PACGA (u): " << ToHexa(result) << std::endl;

    // Compute PACGA in kernel mode.
    csr_instr_t args;
    args.value = value;
    args.modifier = modifier;
    regaccess.executeInstr(CSR_INSTR_PACGA, args);
    std::cout << "PACGA (k): " << ToHexa(args.value) << std::endl;

    // Check it on software qarma.
    const int qarma_rounds = features.pacQARMA();
    if (qarma_rounds > 0) {
        Qarma64 qarma(qarma_rounds);
        csr_u64_t soft = qarma.encrypt(value, modifier, key.high, key.low);
        std::cout << "QARMA" << qarma_rounds << ":    " << ToHexa(soft);
        if (result != (soft & 0xFFFFFFFF00000000)) {
            std::cout << "  FAIL";
        }
        std::cout << std::endl;
    }
    return EXIT_SUCCESS;
}
