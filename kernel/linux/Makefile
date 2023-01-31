#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# Makefile for the Linux kernel module.
#
#----------------------------------------------------------------------------

default: module

# Kernel module.
obj-m += cpusysregs.o

# Kernel interface header is upstairs.
cpusysregs.o: ../cpusysregs.h
ccflags-y := -I$(PWD)/..

# Path to the kernel build utilities.
KBUILD=/lib/modules/$(shell uname -r)/build/

# Standard targets for kernel modules.
module:
	$(MAKE) -C $(KBUILD) M=$(PWD) modules
clean:
	$(MAKE) -C $(KBUILD) M=$(PWD) clean

# Installation.
install:
	sudo $(MAKE) -C $(KBUILD) M=$(PWD) modules_install
	sudo depmod
load:
	sudo modprobe cpusysregs || true
	lsmod | grep cpusysregs || true
	sudo dmesg | tail -5
unload:
	sudo rmmod cpusysregs || true
	lsmod | grep cpusysregs || true
	sudo dmesg | tail -5
show:
	lsmod | grep cpusysregs || true
