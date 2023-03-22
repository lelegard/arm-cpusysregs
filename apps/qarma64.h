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

#pragma once

#include <algorithm>
#include <cstddef>
#include <cinttypes>

//
// Implementation of the QARMA-64 algorithm.
// Defined at https://eprint.iacr.org/2016/444.pdf
//
class Qarma64
{
public:
    typedef uint64_t tweak_t;
    typedef uint64_t text_t;
    typedef uint64_t key_t;

    // Constructor.
    // 5 rounds means QARMA5, the default in Armv8.3-a.
    // SBOX index 2 is the default in Armv8.3-a.
    Qarma64(int rounds = 5, size_t sbox_index = 2);

    text_t encrypt(text_t plaintext, tweak_t tweak, key_t w0, key_t k0);
    text_t decrypt(text_t plaintext, tweak_t tweak, key_t w0, key_t k0);

    void setRounds(int rounds) { _rounds = std::max(rounds, 1); }
    size_t getRounds() { return _rounds; }

    void setSbox(size_t index) { _sbox_index = std::min<size_t>(index, 2); }
    size_t getSbox() { return _sbox_index; }

private:
    int    _rounds;
    size_t _sbox_index;

    typedef uint64_t const_t;
    typedef uint8_t cell_t;
    typedef uint8_t sbox_t[16];

    static void text2cell(cell_t* cell, text_t is);
    static text_t cell2text(cell_t* cell);
    static text_t pseudo_reflect(text_t is, key_t tk);
    text_t forward(text_t is, key_t tk, int r);
    text_t backward(text_t is, key_t tk, int r);
    static cell_t LFSR(cell_t x);
    static cell_t LFSR_inv(cell_t x);
    static key_t forward_update_key(key_t T);
    static key_t backward_update_key(key_t T);

    static constexpr size_t MAX_LENGTH = 64;
    static constexpr size_t m = MAX_LENGTH / 16;
    static constexpr const_t alpha = 0xC0AC29B7C97C50DD;
    static const const_t c[8];
    static const sbox_t sbox[3];
    static const sbox_t sbox_inv[3];
    static const int t[16];
    static const int t_inv[16];
    static const int h[16];
    static const int h_inv[16];
    static const cell_t M[16];
};
