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
EXECS = show-regs demo-pac
CXXFLAGS += -std=c++17
LDLIBS += -lstdc++

# Build the kernel module and the tools.
default: module apps
apps: $(EXECS)

demo-pac: CXXFLAGS += -march=armv8.3-a

show-regs: show-regs.o apputils.o
demo-pac: demo-pac.o apputils.o
show-regs.o: cpusysregs.h apputils.h
demo-pac.o: cpusysregs.h apputils.h
apputils.o: apputils.h

clean: clean-module
	rm -f *.o $(EXECS)


#----------------------------------------------------------------------------
# Kernel module.
#----------------------------------------------------------------------------

cpusysregs.o: cpusysregs.h defsysregs.h

# Kernel module.
obj-m += cpusysregs.o

# Path to the kernel build utilities.
KBUILD=/lib/modules/$(shell uname -r)/build/

# Standard targets for kernel modules.
module:
	$(MAKE) -C $(KBUILD) M=$(PWD) modules
clean-module:
	$(MAKE) -C $(KBUILD) M=$(PWD) clean

# Load/unload kernel module for tests.
load:
	sudo insmod cpusysregs.ko || true
	lsmod | grep cpusysregs || true
	sudo dmesg | tail -5
unload:
	sudo rmmod cpusysregs.ko || true
	lsmod | grep cpusysregs || true
	sudo dmesg | tail -5
