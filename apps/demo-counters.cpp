//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Demo program: access timer and counter registers.
//
//----------------------------------------------------------------------------

#include "strutils.h"
#include "regaccess.h"
#include "armfeatures.h"
#include <iostream>
#include <string>
#include <list>
#include <clocale>
#include <chrono>
#include <thread>
#include <cinttypes>
#include <clocale>

// Display a timer access permission.
void print_access(const char* name, bool enabled)
{
    std::cout << "EL0 access to " << name << " registers: " << (enabled ? "enabled" : "trapped") << std::endl;
}

// Format a counter value. Including time difference with previous counter, ifthere is one.
std::string CounterString(csr_u64_t counter, csr_u64_t previous = 0, csr_u64_t freq = 0)
{
    std::string s(ToHexa(counter) + Format(" (%'" PRIu64, counter));
    if (previous > 0 && previous < counter && freq > 0) {
        s += Format(" => %'" PRIu64 " micro-sec", ((counter - previous) * 1000000) / freq);
    }
    s += ")";
    return s;
}

// Program entry point
int main(int argc, char* argv[])
{
    // Make sure printf knows how to format integers.
    setlocale(LC_ALL, "en_US.UTF-8");

    // Open the pseudo-device for the kernel module.
    RegAccess regs(true, true);
    ArmFeatures feat(regs);

    // Get counter-timer kernel control register.
    csr_u64_t cntkctl = 0;
    regs.read(CSR_REGID_CNTKCTL_EL1, cntkctl);
    const bool eventis = (cntkctl & (1 << 17)) != 0;
    const int eventi = ((cntkctl >> 4) & 0x0F) + (feat.FEAT_ECV() && eventis ? 8 : 0);
    const int eventdir = (cntkctl >> 3) & 0x01;
    const bool el0pten = (cntkctl & (1 << 9)) != 0;
    const bool el0vten = (cntkctl & (1 << 8)) != 0;
    const bool el0vcten = (cntkctl & (1 << 1)) != 0;
    const bool el0pcten = (cntkctl & 1) != 0;

    print_access("physical timer", el0pten);
    print_access("virtual timer", el0vten);
    print_access("physical counter", el0pcten);
    print_access("virtual counter", el0vcten);

    std::cout << "Counter event stream: ";
    if (cntkctl & (1 << 2)) {
        std::cout << "enabled on CNTVCT_EL0 bit " << eventi << " from " << eventdir << " to " << (eventdir ^ 1);
    }
    else {
        std::cout << "disabled";
    }
    std::cout << std::endl;

    // Get counter frequency.
    csr_u64_t freq = 0;
    asm("mrs %0, cntfrq_el0" : "=r" (freq));
    std::cout << std::endl << "Counter frequency: " << Format("%'" PRIu64, freq) << " Hz" << std::endl;

    // Get physical counters.
    csr_u64_t el0_phys1 = 0, el1_phys1 = 0;
    std::cout << std::endl << "EL0 physical counter: ";
    if (el0pcten) {
        asm volatile("isb \n mrs %0, cntpct_el0" : "=r" (el0_phys1));
        std::cout << CounterString(el0_phys1);
    }
    else {
        std::cout << "disabled";
    }
    regs.read(CSR_REGID_CNTPCT_EL0, el1_phys1);
    std::cout << std::endl << "EL1 physical counter: " << CounterString(el1_phys1) << std::endl;

    // Get virtual counters.
    csr_u64_t el0_virt1 = 0, el1_virt1 = 0;
    std::cout << std::endl << "EL0 virtual counter:  ";
    if (el0vcten) {
        asm volatile("isb \n mrs %0, cntvct_el0" : "=r" (el0_virt1));
        std::cout << CounterString(el0_virt1);
    }
    else {
        std::cout << "disabled";
    }
    regs.read(CSR_REGID_CNTVCT_EL0, el1_virt1);
    std::cout << std::endl << "EL1 virtual counter:  " << CounterString(el1_virt1) << std::endl;

    std::cout << std::endl << "Waiting one second ..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Get physical counters again.
    csr_u64_t el0_phys2 = 0, el1_phys2 = 0;
    std::cout << std::endl << "EL0 physical counter: ";
    if (el0pcten) {
        asm volatile("isb \n mrs %0, cntpct_el0" : "=r" (el0_phys2));
        std::cout << CounterString(el0_phys2, el0_phys1, freq);
    }
    else {
        std::cout << "disabled";
    }
    regs.read(CSR_REGID_CNTPCT_EL0, el1_phys2);
    std::cout << std::endl << "EL1 physical counter: " << CounterString(el1_phys2, el1_phys1, freq) << std::endl;

    // Get virtual counters again.
    csr_u64_t el0_virt2 = 0, el1_virt2 = 0;
    std::cout << std::endl << "EL0 virtual counter:  ";
    if (el0vcten) {
        asm volatile("isb \n mrs %0, cntvct_el0" : "=r" (el0_virt2));
        std::cout << CounterString(el0_virt2, el0_virt1, freq);
    }
    else {
        std::cout << "disabled";
    }
    regs.read(CSR_REGID_CNTVCT_EL0, el1_virt2);
    std::cout << std::endl << "EL1 virtual counter:  " << CounterString(el1_virt2, el1_virt1, freq) << std::endl;

    return EXIT_SUCCESS;
}
