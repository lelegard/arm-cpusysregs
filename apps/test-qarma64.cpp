//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Test program for QARMA implementation.
// Test vectors from https://eprint.iacr.org/2016/444.pdf
//
//----------------------------------------------------------------------------

#include "qarma64.h"
#include "strutils.h"
#include <iostream>

static const char* Status(uint64_t value, uint64_t expected)
{
    return value == expected ? "ok" : "FAIL";
}

int main()
{
    const uint64_t w0 = 0x84BE85CE9804E94B;
    const uint64_t k0 = 0xEC2802D4E0A488E9;
    const uint64_t tweak = 0x477D469DEC0B8762;
    const uint64_t plaintext = 0xFB623599DA6E8127;
    const uint64_t ciphertext[3][3] = {
        {0x3EE99A6C82AF0C38, 0x9F5C41EC525603C9, 0xBCAF6C89DE930765},  // sbox 0
        {0x544B0AB95BDA7C3A, 0xA512DD1E4E3EC582, 0xEDF67FF370A483F2},  // sbox 1
        {0xC003B93999B33765, 0x270A787275C48D10, 0x5C06A7501B63B2FD},  // sbox 2
    };

    std::cout << "Key       = " << ToHexa(w0, k0) << std::endl
              << "Tweak     = " << ToHexa(tweak) << std::endl
              << "Plaintext = " << ToHexa(plaintext) << std::endl
              << std::endl;

    Qarma64 qarma;

    for (size_t sbox = 0; sbox <= 2; sbox++) {

        qarma.setSbox(sbox);
        std::cout << "------ SBOX " << qarma.getSbox() << " test ------" << std::endl;

        for (int rounds = 5; rounds <= 7; rounds++) {

            qarma.setRounds(rounds);
            const uint64_t cipher = qarma.encrypt(plaintext, tweak, w0, k0);
            const uint64_t plain = qarma.decrypt(cipher, tweak, w0, k0);

            std::cout << "QARMA" << qarma.getRounds()
                      << " encrypt: " << ToHexa(cipher) << "  " << Status(cipher, ciphertext[sbox][rounds - 5]) << std::endl
                      << "       decrypt: " << ToHexa(plain) << "  " << Status(plain, plaintext) << std::endl
                      << std::endl;
        }
    }
}
