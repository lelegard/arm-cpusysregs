#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# Makefile for Linux kernel module and userlan tools.
#
#----------------------------------------------------------------------------

# List of userland tools.
EXECS = show-regs
CXXFLAGS += -std=c++17

# Kernel module name.
MODULE = cpusysregs

# Build the kernel module and the tools.
default: module $(EXECS)

# All source files depend on the kernel module interface.
$(addsuffix .o,$(basename $(wildcard *.c))): $(MODULE).h

clean: clean-module
	rm -f *.o $(EXECS)


#----------------------------------------------------------------------------
# Kernel module.
#----------------------------------------------------------------------------

# Module name.
MODULE = cpusysregs

# Kernel module.
obj-m += $(MODULE).o

# Path to the kernel build utilities.
KBUILD=/lib/modules/$(shell uname -r)/build/

# Standard targets for kernel modules.
module:
	$(MAKE) -C $(KBUILD) M=$(PWD) modules
clean-module:
	$(MAKE) -C $(KBUILD) M=$(PWD) clean

# Load/unload kernel module for tests.
load:
	sudo insmod $(MODULE).ko || true
	lsmod | grep $(MODULE) || true
	sudo dmesg | tail -5
unload:
	sudo rmmod $(MODULE).ko || true
	lsmod | grep $(MODULE) || true
	sudo dmesg | tail -5
