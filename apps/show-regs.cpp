//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Userland application to display the Arm64 CPU system registers.
//
//----------------------------------------------------------------------------

#include "cpusysregs.h"
#include "strutils.h"
#include "regaccess.h"
#include "regview.h"

#include <iostream>
#include <cstddef>
#include <cstdlib>


//----------------------------------------------------------------------------
// Program entry point
//----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    // Open the pseudo-device for the kernel module.
    RegAccess regaccess(true, true);

    // Loop on all supported registers.
    for (const auto& desc : RegView::AllRegisters) {

        csr_pair_t reg;

        // If the CPU does not have the required features for this register, or cannot read it, skip it.
        if (!(desc.features & RegView::READ) ||
            ((desc.features & RegView::NEED_PAC) && !regaccess.hasPAC()) ||
            ((desc.features & RegView::NEED_PACGA) && !regaccess.hasPACGA()) ||
            !regaccess.read(desc.csr_index, reg))
        {
            continue;
        }

        // Print the register content as a suite of 4-bit binary values.
        std::cout << std::endl << desc.name << ": ";
        if (CSR_REG_IS_PAIR(desc.csr_index)) {
            std::cout << ToBinary(reg.high) << std::endl << std::string(desc.name.length() + 2, ' ');
        }
        std::cout << ToBinary(reg.low) << std::endl << std::endl;
        std::cout << "  Arch. Ref. Manual section " << desc.section << std::endl;

        // Print the details of the register content.
        if (desc.fields.empty()) {
            // No bitfield defined, just display the value in hexadecimal.
            std::cout << "  Value: ";
            if (CSR_REG_IS_PAIR(desc.csr_index)) {
                std::cout << ToString(reg.high) << "-";
            }
            std::cout << ToString(reg.low) << std::endl;
        }
        else {
            // Print the various bit fields.
            for (const auto& bf : desc.fields) {
                // Value of the bitfield.
                const csr_u64_t bfval = bf.lsb >= 64 ?
                    ((reg.high << (127 - bf.msb)) >> (63 - bf.msb + bf.lsb)) :
                    ((reg.low << (63 - bf.msb)) >> (63 - bf.msb + bf.lsb));
                // Look for a name for this value.
                std::string name(bf.values.empty() ? Format("%lld", bfval) : "reserved");
                for (const auto& nm : bf.values) {
                    if (nm.value == bfval) {
                        name = nm.name;
                        break;
                    }
                }
                // Print the bitfield description.
                const int hexwidth = (bf.msb - bf.lsb) / 4 + 1;
                std::cout << "  " << bf.name << ": " << Format("0x%*llX", hexwidth, bfval) << " (" << name << ")" << std::endl;
            }
        }
    }
    std::cout << std::endl;

    // Summary of CPU features.
    std::cout << "Summary: PAC: " << YesNo(regaccess.hasPAC())
              << ", PACGA: " << YesNo(regaccess.hasPACGA())
              << ", BTI: " << YesNo(regaccess.hasBTI())
              << ", RME: " << YesNo(regaccess.hasRME())
              << std::endl << std::endl;

    return EXIT_SUCCESS;
}
