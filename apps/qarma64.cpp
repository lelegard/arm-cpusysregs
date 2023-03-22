//----------------------------------------------------------------------------
//
// QARMA implementation from https://github.com/Phantom1003/QARMA64
// Refactored as a C++ class by Thierry Lelegard
//
//----------------------------------------------------------------------------
//
// MIT License
//
// Copyright (c) 2019-2022 Phantom1003
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//----------------------------------------------------------------------------

#include "qarma64.h"

Qarma64::Qarma64(int rounds, size_t sbox_index) :
    _rounds(rounds),
    _sbox_index(sbox_index)
{
}

const Qarma64::const_t Qarma64::c[8] = {
    0x0000000000000000, 0x13198A2E03707344, 0xA4093822299F31D0, 0x082EFA98EC4E6C89,
    0x452821E638D01377, 0xBE5466CF34E90C6C, 0x3F84D5B5B5470917, 0x9216D5D98979FB1B
};

const Qarma64::sbox_t Qarma64::sbox[3] = {
    { 0, 14,  2, 10,  9, 15,  8, 11,  6,  4,  3,  7, 13, 12,  1,  5},
    {10, 13, 14,  6, 15,  7,  3,  5,  9,  8,  0, 12, 11,  1,  2,  4},
    {11,  6,  8, 15, 12,  0,  9, 14,  3,  7,  4,  5, 13,  2,  1, 10}
};

const Qarma64::sbox_t Qarma64::sbox_inv[3] = {
    { 0, 14,  2, 10,  9, 15,  8, 11,  6,  4,  3,  7, 13, 12,  1,  5},
    {10, 13, 14,  6, 15,  7,  3,  5,  9,  8,  0, 12, 11,  1,  2,  4},
    { 5, 14, 13,  8, 10, 11,  1,  9,  2,  6, 15,  0,  4, 12,  7,  3}
};

const int Qarma64::t[16]     = { 0, 11,  6, 13, 10,  1, 12,  7,  5, 14,  3,  8, 15,  4,  9,  2 };
const int Qarma64::t_inv[16] = { 0,  5, 15, 10, 13,  8,  2,  7, 11, 14,  4,  1,  6,  3,  9, 12 };
const int Qarma64::h[16]     = { 6,  5, 14, 15,  0,  1,  2,  3,  7, 12, 13,  4,  8,  9, 10, 11 };
const int Qarma64::h_inv[16] = { 4,  5,  6,  7, 11,  1,  0,  8, 12, 13, 14, 15,  9, 10,  2,  3 };

#define Q     Qarma64::M
#define M_inv Qarma64::M

const Qarma64::cell_t Qarma64::M[16] = {
    0, 1, 2, 1,
    1, 0, 1, 2,
    2, 1, 0, 1,
    1, 2, 1, 0
};

void Qarma64::text2cell(cell_t* cell, text_t is)
{
    char* byte_ptr = (char*)&is;
    for (size_t i = 0; i < MAX_LENGTH / 8; i++) {
        char byte = byte_ptr[i];
        cell[2 * (7 - i) + 0] = (byte & 0xF0) >> 4;
        cell[2 * (7 - i) + 1] = byte & 0xF;
    }
}

Qarma64::text_t Qarma64::cell2text(cell_t* cell)
{
    text_t is = 0;
    for (size_t i = 0; i < MAX_LENGTH / 8; i++) {
        text_t byte = 0;
        byte = (cell[2 * i] << 4) | cell[2 * i + 1];
        is = is | (byte << (7 - i) * 8UL);
    }
    return is;
}

Qarma64::text_t Qarma64::pseudo_reflect(text_t is, key_t tk)
{
    cell_t cell[16];
    text2cell(cell, is);

    // ShuffleCells
    cell_t perm[16];
    for (int i = 0; i < 16; i++)
        perm[i] = cell[t[i]];

    // MixColumns
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            cell_t temp = 0;
            for (int j = 0; j < 4; j++) {
                const int b = Q[4 * x + j];
                if (b) {
                    cell_t a = perm[4 * j + y];
                    temp ^= ((a << b) & 0x0F) | (a >> (4 - b));
                }
            }
            cell[4 * x + y] = temp;
        }
    }

    // AddRoundTweakey
    for (int i = 0; i < 16; i++) {
        cell[i] ^= (tk >> (4 * (15 - i))) & 0xF;
    }

    // ShuffleCells invert
    for (int i = 0; i < 16; i++) {
        perm[i] = cell[t_inv[i]];
    }

    return cell2text(perm);
}

Qarma64::text_t Qarma64::forward(text_t is, key_t tk, int r)
{
    is ^= tk;
    cell_t cell[16];
    text2cell(cell, is);

    if (r != 0) {
        // ShuffleCells
        cell_t perm[16];
        for (int i = 0; i < 16; i++)
            perm[i] = cell[t[i]];

        // MixColumns
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                cell_t temp = 0;
                for (int j = 0; j < 4; j++) {
                    int b = M[4 * x + j];
                    if (b) {
                        cell_t a = perm[4 * j + y];
                        temp ^= ((a << b) & 0x0F) | (a >> (4 - b));
                    }
                }
                cell[4 * x + y] = temp;
            }
        }
    }

    // SubCells
    for (int i = 0; i < 16; i++) {
        cell[i] = sbox[_sbox_index][cell[i]];
    }
    is = cell2text(cell);
    return is;
}

Qarma64::text_t Qarma64::backward(text_t is, key_t tk, int r)
{
    cell_t cell[16];
    text2cell(cell, is);

    // SubCells
    for (int i = 0; i < 16; i++) {
        cell[i] = sbox_inv[_sbox_index][cell[i]];
    }

    if (r != 0) {
        cell_t mixc[16];
        // MixColumns
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                cell_t temp = 0;
                for (int j = 0; j < 4; j++) {
                    int b = M_inv[4 * x + j];
                    if (b) {
                        cell_t a = cell[4 * j + y];
                        temp ^= ((a << b) & 0x0F) | (a >> (4 - b));
                    }
                }
                mixc[4 * x + y] = temp;
            }
        }

        // ShuffleCells
        for (int i = 0; i < 16; i++)
            cell[i] = mixc[t_inv[i]];
    }

    is = cell2text(cell);
    is ^= tk;
    return is;
}

Qarma64::cell_t Qarma64::LFSR(cell_t x)
{
    cell_t b0 = (x >> 0) & 1;
    cell_t b1 = (x >> 1) & 1;
    cell_t b2 = (x >> 2) & 1;
    cell_t b3 = (x >> 3) & 1;

    return ((b0 ^ b1) << 3) | (b3 << 2) | (b2 << 1) | (b1 << 0);
}

Qarma64::cell_t Qarma64::LFSR_inv(cell_t x)
{
    cell_t b0 = (x >> 0) & 1;
    cell_t b1 = (x >> 1) & 1;
    cell_t b2 = (x >> 2) & 1;
    cell_t b3 = (x >> 3) & 1;

    return ((b0 ^ b3) << 0) | (b0 << 1) | (b1 << 2) | (b2 << 3);
}

Qarma64::key_t Qarma64::forward_update_key(key_t T)
{
    cell_t cell[16], temp[16];
    text2cell(cell, T);

    // h box
    for (int i = 0; i < 16; i++) {
        temp[i] = cell[h[i]];
    }

    // w LFSR
    temp[0] = LFSR(temp[0]);
    temp[1] = LFSR(temp[1]);
    temp[3] = LFSR(temp[3]);
    temp[4] = LFSR(temp[4]);
    temp[8] = LFSR(temp[8]);
    temp[11] = LFSR(temp[11]);
    temp[13] = LFSR(temp[13]);

    return cell2text(temp);
}

Qarma64::key_t Qarma64::backward_update_key(key_t T)
{
    cell_t cell[16], temp[16];
    text2cell(cell, T);

    // w LFSR invert
    cell[0] = LFSR_inv(cell[0]);
    cell[1] = LFSR_inv(cell[1]);
    cell[3] = LFSR_inv(cell[3]);
    cell[4] = LFSR_inv(cell[4]);
    cell[8] = LFSR_inv(cell[8]);
    cell[11] = LFSR_inv(cell[11]);
    cell[13] = LFSR_inv(cell[13]);

    // h box
    for (int i = 0; i < 16; i++) {
        temp[i] = cell[h_inv[i]];
    }
    return cell2text(temp);
}

Qarma64::text_t Qarma64::encrypt(text_t plaintext, tweak_t tweak, key_t w0, key_t k0)
{
    key_t w1 = ((w0 >> 1) | (w0 << (64 - 1))) ^ (w0 >> (16 * m - 1));
    key_t k1 = k0;
    text_t is = plaintext ^ w0;

    for (int i = 0; i < _rounds; i++) {
        is = forward(is, k0 ^ tweak ^ c[i], i);
        tweak = forward_update_key(tweak);
    }

    is = forward(is, w1 ^ tweak, 1);
    is = pseudo_reflect(is, k1);
    is = backward(is, w0 ^ tweak, 1);

    for (int i = _rounds - 1; i >= 0; i--) {
        tweak = backward_update_key(tweak);
        is = backward(is, k0 ^ tweak ^ c[i] ^ alpha, i);
    }

    is ^= w1;
    return is;
}

Qarma64::text_t Qarma64::decrypt(text_t plaintext, tweak_t tweak, key_t w0, key_t k0)
{
    key_t w1 = w0;
    w0 = ((w0 >> 1) | (w0 << (64 - 1))) ^ (w0 >> (16 * m - 1));

    cell_t k0_cell[16], k1_cell[16];
    text2cell(k0_cell, k0);
    // MixColumns
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            cell_t temp = 0;
            for (int j = 0; j < 4; j++) {
                int b = Q[4 * x + j];
                if (b) {
                    cell_t a = k0_cell[4 * j + y];
                    temp ^= ((a << b) & 0x0F) | (a >> (4 - b));
                }
            }
            k1_cell[4 * x + y] = temp;
        }
    }
    key_t k1 = cell2text(k1_cell);

    k0 ^= alpha;

    text_t is = plaintext ^ w0;

    for (int i = 0; i < _rounds; i++) {
        is = forward(is, k0 ^ tweak ^ c[i], i);
        tweak = forward_update_key(tweak);
    }

    is = forward(is, w1 ^ tweak, 1);
    is = pseudo_reflect(is, k1);
    is = backward(is, w0 ^ tweak, 1);

    for (int i = _rounds - 1; i >= 0; i--) {
        tweak = backward_update_key(tweak);
        is = backward(is, k0 ^ tweak ^ c[i] ^ alpha, i);
    }

    is ^= w1;
    return is;
}
