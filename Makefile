# List of userland tools.
EXECS = show-regs

# Kernel module name.
MODULE = cpusysregs

# Build the kernel module and the tools.
default: module $(EXECS)

# All source files depend on the kernel module interface.
$(addsuffix .o,$(basename $(wildcard *.c))): $(MODULE).h

# Kernel module
obj-m += $(MODULE).o

# Path to the kernel build utilities.
KBUILD=/lib/modules/$(shell uname -r)/build/

# Standard targets for kernel modules.
module:
	$(MAKE) -C $(KBUILD) M=$(PWD) modules
clean:
	$(MAKE) -C $(KBUILD) M=$(PWD) clean
	rm -rf $(EXECS)

# Load/unload kernel module for tests.
load:
	-sudo insmod $(MODULE).ko
	-lsmod | grep $(MODULE)
	-sudo dmesg | tail -5
unload:
	-sudo rmmod $(MODULE).ko
	-lsmod | grep $(MODULE)
	-sudo dmesg | tail -5
