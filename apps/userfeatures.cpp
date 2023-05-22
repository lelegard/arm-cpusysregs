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

#include "userfeatures.h"

#if defined(__linux__)
    #include <sys/auxv.h>
    #include <asm/hwcap.h>
    // Registers id_aa64isar2_el1 and id_aa64mmfr2_el1 are not defined in older compiler versions.
    // Not sure about which exact versions, adapt if necessary.
    #if defined(__clang__) && (__clang_major__ < 12)
        // Need clang 12.x and above ?
        #define NO_AA64ISAR2 1
    #elif !defined(__clang__) && (__GNUC__ < 11)
        // Need gcc 12.x and above ?
        #define NO_AA64ISAR2 1
    #endif
#elif defined(__APPLE__)
    #include <sys/types.h>
    #include <sys/sysctl.h>
#endif


//----------------------------------------------------------------------------
// Constructor.
//----------------------------------------------------------------------------

UserFeatures::UserFeatures()
#if defined(__linux__)
    : _reg_loaded(false), _isar0(0), _isar1(0), _isar2(0), _pfr0(0), _mmfr2(0)
#endif
{
}


//----------------------------------------------------------------------------
// Set a feature.
//----------------------------------------------------------------------------

#if defined(__linux__)

    #define FEATURE(feat,type,flag,name,eval) feature((feat), (type), (flag), (eval))

    bool UserFeatures::feature(InitBool& feat, unsigned long type, unsigned long flag, std::function<bool()> eval)
    {
        if (!feat.loaded) {
            // First time, feature not yet loaded.
            if (eval == nullptr) {
                // Use getauxval() to get the feature.
                feat.value = (::getauxval(type) & (flag)) != 0;
            }
            else {
                // Use system registers as emulated by Linux kernel at EL0.
                if (!_reg_loaded) {
                    // System registers not yet loaded.
                    asm("mrs %0, id_aa64pfr0_el1"  : "=r" (_pfr0));
                    asm("mrs %0, id_aa64isar0_el1" : "=r" (_isar0));
                    asm("mrs %0, id_aa64isar1_el1" : "=r" (_isar1));
                    #if defined(NO_AA64ISAR2)
                        _isar2 = _mmfr2 = 0;
                    #else
                        asm("mrs %0, id_aa64isar2_el1" : "=r" (_isar2));
                        asm("mrs %0, id_aa64mmfr2_el1" : "=r" (_mmfr2));
                    #endif
                    _reg_loaded = true;
                }
                // Call the lambda function to extract the feature from the register values.
                feat.value = eval();
            }
            feat.loaded = true;
        }
        return feat.value;
    }

#elif defined(__APPLE__)

    #define FEATURE(feat,type,flag,name,eval) feature((feat), (name))

    bool UserFeatures::feature(InitBool& feat, const char* name)
    {
        if (!feat.loaded) {
            // First time, feature not yet loaded.
            int val = 0;
            size_t len = sizeof(val);
            feat.value = ::sysctlbyname(name, &val, &len, nullptr, 0) == 0 && val != 0;
            feat.loaded = true;
        }
        return feat.value;
    }

#elif defined(WINDOWS)

    // No way to get ARM features in user mode on Windows.
    #define FEATURE(feat,type,flag,name,eval) (false)

#endif


//----------------------------------------------------------------------------
// Processor features.
//----------------------------------------------------------------------------

bool UserFeatures::FEAT_AES()
{
    return FEATURE(_aes, AT_HWCAP, HWCAP_AES, "hw.optional.arm.FEAT_AES", nullptr);
}

bool UserFeatures::FEAT_BF16()
{
    return FEATURE(_bf16, AT_HWCAP2, HWCAP2_BF16, "hw.optional.arm.FEAT_BF16", nullptr);
}

bool UserFeatures::FEAT_BTI()
{
    return FEATURE(_bti, AT_HWCAP2, HWCAP2_BTI, "hw.optional.arm.FEAT_BTI", nullptr);
}

bool UserFeatures::FEAT_CRC32()
{
    return FEATURE(_crc32, AT_HWCAP, HWCAP_CRC32, "hw.optional.armv8_crc32", nullptr);
}

bool UserFeatures::FEAT_CSV2()
{
    return FEATURE(_csv2, 0, 0, "hw.optional.arm.FEAT_CSV2", [this](){ return bool((_pfr0 >> 56) & 0x0F); });
}

bool UserFeatures::FEAT_CSV3()
{
    return FEATURE(_csv3, 0, 0, "hw.optional.arm.FEAT_CSV3", [this](){ return bool((_pfr0 >> 60) & 0x0F); });
}

bool UserFeatures::FEAT_DIT()
{
    return FEATURE(_dit, AT_HWCAP, HWCAP_DIT, "hw.optional.arm.FEAT_DIT", nullptr);
}

bool UserFeatures::FEAT_DotProd()
{
    return FEATURE(_dotprod, 0, 0, "hw.optional.arm.FEAT_DotProd", [this](){ return bool((_isar0 >> 44) & 0x0F); });
}

bool UserFeatures::FEAT_DPB()
{
    return FEATURE(_dpb, 0, 0, "hw.optional.arm.FEAT_DPB", [this](){ return (_isar1 & 0x0F) >= 1; });
}

bool UserFeatures::FEAT_DPB2()
{
    return FEATURE(_dpb2, 0, 0, "hw.optional.arm.FEAT_DPB2", [this](){ return (_isar1 & 0x0F) >= 2; });
}

bool UserFeatures::FEAT_ECV()
{
    return FEATURE(_ecv, AT_HWCAP2, HWCAP2_ECV, "hw.optional.arm.FEAT_ECV", nullptr);
}

bool UserFeatures::FEAT_FCMA()
{
    return FEATURE(_fcma, AT_HWCAP, HWCAP_FCMA, "hw.optional.arm.FEAT_FCMA", nullptr);
}

bool UserFeatures::FEAT_FHM()
{
    return FEATURE(_fhm, 0, 0, "hw.optional.arm.FEAT_FHM", [this](){ return bool((_isar0 >> 48) & 0x0F); });
}

bool UserFeatures::FEAT_FlagM()
{
    return FEATURE(_flagm, AT_HWCAP, HWCAP_FLAGM, "hw.optional.arm.FEAT_FlagM", nullptr);
}

bool UserFeatures::FEAT_FlagM2()
{
    return FEATURE(_flagm2, AT_HWCAP2, HWCAP2_FLAGM2, "hw.optional.arm.FEAT_FlagM2", nullptr);
}

bool UserFeatures::FEAT_FP16()
{
    return FEATURE(_fp16, 0, 0, "hw.optional.arm.FEAT_FP16",
                   [this](){ uint64_t fp = (_pfr0 >> 16) & 0x0F; return fp > 0 && fp < 15; });
}

bool UserFeatures::FEAT_FPAC()
{
    return FEATURE(_fpac, 0, 0, "hw.optional.arm.FEAT_FPAC",
                   [this](){ return ((_isar1 >> 8) & 0x0F) >= 4 || ((_isar1 >> 4) & 0x0F) >= 4 || ((_isar2 >> 12) & 0x0F) >= 4; });
}

bool UserFeatures::FEAT_FRINTTS()
{
    return FEATURE(_frintts, 0, 0, "hw.optional.arm.FEAT_FRINTTS", [this](){ return bool((_isar1 >> 32) & 0x0F); });
}

bool UserFeatures::FEAT_I8MM()
{
    return FEATURE(_i8mm, AT_HWCAP2, HWCAP2_I8MM, "hw.optional.arm.FEAT_I8MM", nullptr);
}

bool UserFeatures::FEAT_JSCVT()
{
    return FEATURE(_jscvt, AT_HWCAP, HWCAP_JSCVT, "hw.optional.arm.FEAT_JSCVT", nullptr);
}

bool UserFeatures::FEAT_LRCPC()
{
    return FEATURE(_lrcpc, AT_HWCAP, HWCAP_LRCPC, "hw.optional.arm.FEAT_LRCPC", nullptr);
}

bool UserFeatures::FEAT_LRCPC2()
{
    return FEATURE(_lrcpc2, 0, 0, "hw.optional.arm.FEAT_LRCPC2", [this](){ return ((_isar1 >> 20) & 0x0F) >= 2; });
}

bool UserFeatures::FEAT_LSE()
{
    return FEATURE(_lse, 0, 0, "hw.optional.arm.FEAT_LSE", [this](){ return ((_isar0 >> 20) & 0x0F) >= 2; });
}

bool UserFeatures::FEAT_LSE2()
{
    return FEATURE(_lse2, 0, 0, "hw.optional.arm.FEAT_LSE2", [this](){ return ((_mmfr2 >> 32) & 0x0F) >= 1; });
}

bool UserFeatures::FEAT_PAuth()
{
    return FEATURE(_pauth, 0, 0, "hw.optional.arm.FEAT_PAuth",
                   [this](){ return ((_isar1 >> 8) & 0x0F) >= 1 || ((_isar1 >> 4) & 0x0F) >= 1 || ((_isar2 >> 12) & 0x0F) >= 1; });
}

bool UserFeatures::FEAT_PAuth2()
{
    return FEATURE(_pauth2, 0, 0, "hw.optional.arm.FEAT_PAuth2",
                   [this](){ return ((_isar1 >> 8) & 0x0F) >= 3 || ((_isar1 >> 4) & 0x0F) >= 3 || ((_isar2 >> 12) & 0x0F) >= 3; });
}

bool UserFeatures::FEAT_PMULL()
{
    return FEATURE(_pmull, AT_HWCAP, HWCAP_PMULL, "hw.optional.arm.FEAT_PMULL", nullptr);
}

bool UserFeatures::FEAT_RDM()
{
    return FEATURE(_rdm, 0, 0, "hw.optional.arm.FEAT_RDM", [this](){ return bool((_isar0 >> 28) & 0x0F); });
}

bool UserFeatures::FEAT_SB()
{
    return FEATURE(_sb, AT_HWCAP, HWCAP_SB, "hw.optional.arm.FEAT_SB", nullptr);
}

bool UserFeatures::FEAT_SHA1()
{
    return FEATURE(_sha1, AT_HWCAP, HWCAP_SHA1, "hw.optional.arm.FEAT_SHA1", nullptr);
}

bool UserFeatures::FEAT_SHA256()
{
    return FEATURE(_sha256, AT_HWCAP, HWCAP_SHA2, "hw.optional.arm.FEAT_SHA256", nullptr);
}

bool UserFeatures::FEAT_SHA512()
{
    return FEATURE(_sha512, AT_HWCAP, HWCAP_SHA512, "hw.optional.arm.FEAT_SHA512", nullptr);
}

bool UserFeatures::FEAT_SHA3()
{
    return FEATURE(_sha3, AT_HWCAP, HWCAP_SHA3, "hw.optional.arm.FEAT_SHA3", nullptr);
}

bool UserFeatures::FEAT_SPECRES()
{
    return FEATURE(_specres, 0, 0, "hw.optional.arm.FEAT_SPECRES", [this](){ return bool((_isar1 >> 40) & 0x0F); });
}

bool UserFeatures::FEAT_SSBS()
{
    return FEATURE(_ssbs, AT_HWCAP, HWCAP_SSBS, "hw.optional.arm.FEAT_SSBS", nullptr);
}
