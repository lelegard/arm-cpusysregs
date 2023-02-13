//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// A class describing the features of an Arm64 processor as seen from
// userland, without accessing the kernel module, Linux and macOS.
//
//----------------------------------------------------------------------------

#include "userfeatures.h"

#if defined(__APPLE__)
    #include <sys/types.h>
    #include <sys/sysctl.h>
#endif


//----------------------------------------------------------------------------
// Get a boolean sysctl() on macOS.
//----------------------------------------------------------------------------

#if defined(__APPLE__)

bool GetBoolSysCtl(const char* name)
{
    int value = 0;
    size_t len = sizeof(value);
    return ::sysctlbyname(name, &value, &len, nullptr, 0) == 0 && value != 0;
}

#endif // __APPLE__


//----------------------------------------------------------------------------
// Macros to set a feature.
//----------------------------------------------------------------------------

#if defined(__linux__)
    #define SetFeature(variable,name) (variable) = false
#elif defined(__APPLE__)
    #define SetFeature(variable,name) (variable) = GetBoolSysCtl(name)
#endif


//----------------------------------------------------------------------------
// Processor features, using same names as Arm Architecture Reference Manual.
//----------------------------------------------------------------------------

bool UserFeatures::FEAT_AES()
{
    if (!_aes.loaded) {
        SetFeature(_aes.value, "hw.optional.arm.FEAT_AES");
        _aes.loaded = true;
    }
    return _aes.value;
}

bool UserFeatures::FEAT_BF16()
{
    if (!_bf16.loaded) {
        SetFeature(_bf16.value, "hw.optional.arm.FEAT_BF16");
        _bf16.loaded = true;
    }
    return _bf16.value;
}

bool UserFeatures::FEAT_BTI()
{
    if (!_bti.loaded) {
        SetFeature(_bti.value, "hw.optional.arm.FEAT_BTI");
        _bti.loaded = true;
    }
    return _bti.value;
}

bool UserFeatures::FEAT_CRC32()
{
    if (!_crc32.loaded) {
        SetFeature(_crc32.value, "hw.optional.armv8_crc32");
        _crc32.loaded = true;
    }
    return _crc32.value;
}

bool UserFeatures::FEAT_CSV2()
{
    if (!_csv2.loaded) {
        SetFeature(_csv2.value, "hw.optional.arm.FEAT_CSV2");
        _csv2.loaded = true;
    }
    return _csv2.value;
}

bool UserFeatures::FEAT_CSV3()
{
    if (!_csv3.loaded) {
        SetFeature(_csv3.value, "hw.optional.arm.FEAT_CSV3");
        _csv3.loaded = true;
    }
    return _csv3.value;
}

bool UserFeatures::FEAT_DIT()
{
    if (!_dit.loaded) {
        SetFeature(_dit.value, "hw.optional.arm.FEAT_DIT");
        _dit.loaded = true;
    }
    return _dit.value;
}

bool UserFeatures::FEAT_DotProd()
{
    if (!_dotprod.loaded) {
        SetFeature(_dotprod.value, "hw.optional.arm.FEAT_DotProd");
        _dotprod.loaded = true;
    }
    return _dotprod.value;
}

bool UserFeatures::FEAT_DPB()
{
    if (!_dpb.loaded) {
        SetFeature(_dpb.value, "hw.optional.arm.FEAT_DPB");
        _dpb.loaded = true;
    }
    return _dpb.value;
}

bool UserFeatures::FEAT_DPB2()
{
    if (!_dpb2.loaded) {
        SetFeature(_dpb2.value, "hw.optional.arm.FEAT_DPB2");
        _dpb2.loaded = true;
    }
    return _dpb2.value;
}

bool UserFeatures::FEAT_ECV()
{
    if (!_ecv.loaded) {
        SetFeature(_ecv.value, "hw.optional.arm.FEAT_ECV");
        _ecv.loaded = true;
    }
    return _ecv.value;
}

bool UserFeatures::FEAT_FCMA()
{
    if (!_fcma.loaded) {
        SetFeature(_fcma.value, "hw.optional.arm.FEAT_FCMA");
        _fcma.loaded = true;
    }
    return _fcma.value;
}

bool UserFeatures::FEAT_FHM()
{
    if (!_fhm.loaded) {
        SetFeature(_fhm.value, "hw.optional.arm.FEAT_FHM");
        _fhm.loaded = true;
    }
    return _fhm.value;
}

bool UserFeatures::FEAT_FlagM()
{
    if (!_flagm.loaded) {
        SetFeature(_flagm.value, "hw.optional.arm.FEAT_FlagM");
        _flagm.loaded = true;
    }
    return _flagm.value;
}

bool UserFeatures::FEAT_FlagM2()
{
    if (!_flagm2.loaded) {
        SetFeature(_flagm2.value, "hw.optional.arm.FEAT_FlagM2");
        _flagm2.loaded = true;
    }
    return _flagm2.value;
}

bool UserFeatures::FEAT_FP()
{
    if (!_fp.loaded) {
        SetFeature(_fp.value, ""); //@@@@
        _fp.loaded = true;
    }
    return _fp.value;
}

bool UserFeatures::FEAT_FP16()
{
    if (!_fp16.loaded) {
        SetFeature(_fp16.value, "hw.optional.arm.FEAT_FP16");
        _fp16.loaded = true;
    }
    return _fp16.value;
}

bool UserFeatures::FEAT_FPAC()
{
    if (!_fpac.loaded) {
        SetFeature(_fpac.value, "hw.optional.arm.FEAT_FPAC");
        _fpac.loaded = true;
    }
    return _fpac.value;
}

bool UserFeatures::FEAT_FRINTTS()
{
    if (!_frintts.loaded) {
        SetFeature(_frintts.value, "hw.optional.arm.FEAT_FRINTTS");
        _frintts.loaded = true;
    }
    return _frintts.value;
}

bool UserFeatures::FEAT_I8MM()
{
    if (!_i8mm.loaded) {
        SetFeature(_i8mm.value, "hw.optional.arm.FEAT_I8MM");
        _i8mm.loaded = true;
    }
    return _i8mm.value;
}

bool UserFeatures::FEAT_JSCVT()
{
    if (!_jscvt.loaded) {
        SetFeature(_jscvt.value, "hw.optional.arm.FEAT_JSCVT");
        _jscvt.loaded = true;
    }
    return _jscvt.value;
}

bool UserFeatures::FEAT_LRCPC()
{
    if (!_lrcpc.loaded) {
        SetFeature(_lrcpc.value, "hw.optional.arm.FEAT_LRCPC");
        _lrcpc.loaded = true;
    }
    return _lrcpc.value;
}

bool UserFeatures::FEAT_LRCPC2()
{
    if (!_lrcpc2.loaded) {
        SetFeature(_lrcpc2.value, "hw.optional.arm.FEAT_LRCPC2");
        _lrcpc2.loaded = true;
    }
    return _lrcpc2.value;
}

bool UserFeatures::FEAT_LSE()
{
    if (!_lse.loaded) {
        SetFeature(_lse.value, "hw.optional.arm.FEAT_LSE");
        _lse.loaded = true;
    }
    return _lse.value;
}

bool UserFeatures::FEAT_LSE2()
{
    if (!_lse2.loaded) {
        SetFeature(_lse2.value, "hw.optional.arm.FEAT_LSE2");
        _lse2.loaded = true;
    }
    return _lse2.value;
}

bool UserFeatures::FEAT_PAuth()
{
    if (!_pauth.loaded) {
        SetFeature(_pauth.value, "hw.optional.arm.FEAT_PAuth");
        _pauth.loaded = true;
    }
    return _pauth.value;
}

bool UserFeatures::FEAT_PAuth2()
{
    if (!_pauth2.loaded) {
        SetFeature(_pauth2.value, "hw.optional.arm.FEAT_PAuth2");
        _pauth2.loaded = true;
    }
    return _pauth2.value;
}

bool UserFeatures::FEAT_PMULL()
{
    if (!_pmull.loaded) {
        SetFeature(_pmull.value, "hw.optional.arm.FEAT_PMULL");
        _pmull.loaded = true;
    }
    return _pmull.value;
}

bool UserFeatures::FEAT_RDM()
{
    if (!_rdm.loaded) {
        SetFeature(_rdm.value, "hw.optional.arm.FEAT_RDM");
        _rdm.loaded = true;
    }
    return _rdm.value;
}

bool UserFeatures::FEAT_SB()
{
    if (!_sb.loaded) {
        SetFeature(_sb.value, "hw.optional.arm.FEAT_SB");
        _sb.loaded = true;
    }
    return _sb.value;
}

bool UserFeatures::FEAT_SHA1()
{
    if (!_sha1.loaded) {
        SetFeature(_sha1.value, "hw.optional.arm.FEAT_SHA1");
        _sha1.loaded = true;
    }
    return _sha1.value;
}

bool UserFeatures::FEAT_SHA256()
{
    if (!_sha256.loaded) {
        SetFeature(_sha256.value, "hw.optional.arm.FEAT_SHA256");
        _sha256.loaded = true;
    }
    return _sha256.value;
}

bool UserFeatures::FEAT_SHA512()
{
    if (!_sha512.loaded) {
        SetFeature(_sha512.value, "hw.optional.arm.FEAT_SHA512");
        _sha512.loaded = true;
    }
    return _sha512.value;
}

bool UserFeatures::FEAT_SHA3()
{
    if (!_sha3.loaded) {
        SetFeature(_sha3.value, "hw.optional.arm.FEAT_SHA3");
        _sha3.loaded = true;
    }
    return _sha3.value;
}

bool UserFeatures::FEAT_SPECRES()
{
    if (!_specres.loaded) {
        SetFeature(_specres.value, "hw.optional.arm.FEAT_SPECRES");
        _specres.loaded = true;
    }
    return _specres.value;
}

bool UserFeatures::FEAT_SSBS()
{
    if (!_ssbs.loaded) {
        SetFeature(_ssbs.value, "hw.optional.arm.FEAT_SSBS");
        _ssbs.loaded = true;
    }
    return _ssbs.value;
}


//----------------------------------------------------------------------------
// Descriptions of all features.
//----------------------------------------------------------------------------

const std::list<UserFeatures::Feature> UserFeatures::AllFeatures {
    // Automatically generated file:
    #include "_userfeatures.h"
};
