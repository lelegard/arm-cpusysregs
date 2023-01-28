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
#include "apputils.h"

#include <iostream>
#include <cstdio>
#include <cstddef>
#include <cstdlib>

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>


//----------------------------------------------------------------------------
// Manipulate the generic key.
//----------------------------------------------------------------------------

void GetKeyGA(int fd, const std::string& title, csr_pac_key_t& key)
{
    // Read all system registers.
    csr_registers_t regs;
    if (ioctl(fd, CSR_IOCTL_GET_REGS, &regs) < 0) {
        perror("ioctl get regs");
    }
    else {
        std::cout << Pad(title, 20) << " " << ToString(regs.apgakeyhi_el1, regs.apgakeylo_el1) << std::endl;
    }
}

void SetKeyGA(int fd, const std::string& title, const csr_pac_key_t& key)
{
    std::cout << Pad(title, 20) << " " << ToString(key) << std::endl;
    if (ioctl(fd, CSR_IOCTL_SET_KEYGA, &key) < 0) {
        perror("ioctl set key");
    }
}

void TestGA(const std::string& title, csr_u64_t value, csr_u64_t modifier)
{
    csr_u64_t result = 0x1111111111111111;
    asm("pacga %[res], %[val], %[mod]" : [res] "+r" (result) : [val] "r" (value), [mod] "r" (modifier));
    std::cout << Pad(title, 20) << " " << ToString(value) << " -> " << ToString(result) << std::endl;
}


//----------------------------------------------------------------------------
// Manipulate the data pointer key B.
//----------------------------------------------------------------------------

void GetKeyDB(int fd, const std::string& title, csr_pac_key_t& key)
{
    // Read all system registers.
    csr_registers_t regs;
    if (ioctl(fd, CSR_IOCTL_GET_REGS, &regs) < 0) {
        perror("ioctl get regs");
    }
    else {
        std::cout << Pad(title, 20) << " " << ToString(regs.apdbkeyhi_el1, regs.apdbkeylo_el1) << std::endl;
    }
}

void SetKeyDB(int fd, const std::string& title, const csr_pac_key_t& key)
{
    std::cout << Pad(title, 20) << " " << ToString(key) << std::endl;
    if (ioctl(fd, CSR_IOCTL_SET_KEYDB, &key) < 0) {
        perror("ioctl set key");
    }
}

void TestDB(const std::string& title, csr_u64_t& value, csr_u64_t modifier)
{
    csr_u64_t result = 0x1111111111111111;
    asm("pacga %[res], %[val], %[mod]" : [res] "+r" (result) : [val] "r" (value), [mod] "r" (modifier));
    std::cout << Pad(title, 20) << " " << ToString(value) << " -> " << ToString(result) << std::endl;
}


//----------------------------------------------------------------------------
// Program entry point
//----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    // Open the pseudo-device for the kernel module.
    const int fd = open(CSR_DEVICE_PATH, O_RDONLY);
    if (fd < 0) {
        perror(CSR_DEVICE_PATH);
        return EXIT_FAILURE;
    }

    std::cout << std::endl << "---- Generic key" << std::endl << std::endl;

    csr_u64_t modifier = 7;
    csr_pac_key_t key0;
    GetKeyGA(fd, "Initial GA key", key0);
    TestGA("PACGA", 0xFEDCBA9876543210, modifier);

    const csr_pac_key_t key1 {0xDEADBEEFBADC0FFE, 0x0123456789ABCDEF};
    SetKeyGA(fd, "Update GA key", key1);

    csr_pac_key_t key2;
    GetKeyGA(fd, "Updated GA key", key2);
    TestGA("PACGA", 0xFEDCBA9876543210, modifier);

    SetKeyGA(fd, "Restore GA key", key0);
    GetKeyGA(fd, "Restored GA key", key2);
    TestGA("PACGA", 0xFEDCBA9876543210, modifier);

    std::cout << std::endl << "---- Data pointer key B" << std::endl << std::endl;

    GetKeyDB(fd, "Initial DB key", key0);

    modifier = 47;
    csr_u64_t data = 0x123456789A;
    std::cout << Pad("Before PACDB", 20) << " " << ToString(data) << std::endl;
    asm("pacdb %[dat], %[mod]" : [dat] "+r" (data) : [mod] "r" (modifier));
    std::cout << Pad("After PACDB", 20) << " " << ToString(data) << std::endl;
    csr_u64_t corrupted = data ^ 1;

    asm("autdb %[dat], %[mod]" : [dat] "+r" (data) : [mod] "r" (modifier));
    std::cout << Pad("After AUTDB", 20) << " " << ToString(data) << std::endl;

    std::cout << Pad("Corrupted", 20) << " " << ToString(corrupted) << std::endl;
    asm("autdb %[dat], %[mod]" : [dat] "+r" (corrupted) : [mod] "r" (modifier));
    std::cout << Pad("After AUTDB", 20) << " " << ToString(corrupted) << std::endl;

    std::cout << std::endl;
    close(fd);
    return EXIT_SUCCESS;
}
