//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// A class describing the features of an Arm64 processor as seen from
// userland, without accessing the kernel module, Linux and macOS.
// This module is independent from the rest of this project.
//
//----------------------------------------------------------------------------

#pragma once
#include <functional>
#include <cstdint>

//
// A class describing the features of an Arm64 processor as seen from
// userland, without accessing the kernel module, Linux and macOS.
//
class UserFeatures
{
public:
    // Constructor.
    UserFeatures();

    // Processor features, using same names as Arm Architecture Reference Manual.
    bool FEAT_AES();
    bool FEAT_BF16();
    bool FEAT_BTI();
    bool FEAT_CRC32();
    bool FEAT_CSV2();
    bool FEAT_CSV3();
    bool FEAT_DIT();
    bool FEAT_DotProd();
    bool FEAT_DPB();
    bool FEAT_DPB2();
    bool FEAT_ECV();
    bool FEAT_FCMA();
    bool FEAT_FHM();
    bool FEAT_FlagM();
    bool FEAT_FlagM2();
    bool FEAT_FP16();
    bool FEAT_FPAC();
    bool FEAT_FRINTTS();
    bool FEAT_I8MM();
    bool FEAT_JSCVT();
    bool FEAT_LRCPC();
    bool FEAT_LRCPC2();
    bool FEAT_LSE();
    bool FEAT_LSE2();
    bool FEAT_PAuth();
    bool FEAT_PAuth2();
    bool FEAT_PMULL();
    bool FEAT_RDM();
    bool FEAT_SB();
    bool FEAT_SHA1();
    bool FEAT_SHA256();
    bool FEAT_SHA512();
    bool FEAT_SHA3();
    bool FEAT_SPECRES();
    bool FEAT_SSBS();

private:
    // Each feature is loaded once.
    struct InitBool {
        bool loaded;
        bool value;
        InitBool() : loaded(false), value(false) {}
    };

    // List of features.
    InitBool _aes;
    InitBool _bf16;
    InitBool _bti;
    InitBool _crc32;
    InitBool _csv2;
    InitBool _csv3;
    InitBool _dit;
    InitBool _dotprod;
    InitBool _dpb;
    InitBool _dpb2;
    InitBool _ecv;
    InitBool _fcma;
    InitBool _fhm;
    InitBool _flagm;
    InitBool _flagm2;
    InitBool _fp16;
    InitBool _fpac;
    InitBool _frintts;
    InitBool _i8mm;
    InitBool _jscvt;
    InitBool _lrcpc;
    InitBool _lrcpc2;
    InitBool _lse;
    InitBool _lse2;
    InitBool _pauth;
    InitBool _pauth2;
    InitBool _pmull;
    InitBool _rdm;
    InitBool _sb;
    InitBool _sha1;
    InitBool _sha256;
    InitBool _sha512;
    InitBool _sha3;
    InitBool _specres;
    InitBool _ssbs;

    // On Linux, some selected registers are available at EL0.
    // Some Arm features are only available there.
#if defined(__linux__)
    bool     _reg_loaded;
    uint64_t _isar0;
    uint64_t _isar1;
    uint64_t _isar2;
    uint64_t _pfr0;
    uint64_t _mmfr2;
#endif

    // Initialize a feature.
#if defined(__linux__)
    bool feature(InitBool& feat, unsigned long type, unsigned long flag, std::function<bool()> eval);
#elif defined(__APPLE__)
    bool feature(InitBool& feat, const char* name);
#endif
};
