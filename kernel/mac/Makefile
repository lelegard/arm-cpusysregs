#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# Makefile for the macOS kernel extension.
#
#----------------------------------------------------------------------------

# This kernel extension.
KEXTNAME   = cpusysregs
KEXTBUNDLE = $(KEXTNAME).kext
KEXTBIN    = $(KEXTNAME)

# System location for kernel extensions.
KEXTPREFIX ?= /Library/Extensions

# Current SDK and tools.
SDKVERSION := $(shell xcrun --show-sdk-version)
CC         := $(shell xcrun --find cc)
CODESIGN   := $(shell xcrun --find codesign)
SDKPATH    := $(shell xcrun --show-sdk-path)
KFRAMEWORK := $(SDKPATH)/System/Library/Frameworks/Kernel.framework

# Build options. This kernel extension is specific to 64-bit Arm architecture.
ARCH      = arm64e
TARGET    = $(ARCH)-apple-macos$(SDKVERSION)
CPPFLAGS += -isysroot $(SDKPATH) -I$(KFRAMEWORK)/Headers -I$(KFRAMEWORK)/PrivateHeaders -I..
CPPFLAGS += -DKERNEL -DKERNEL_PRIVATE -DDRIVER_PRIVATE -DAPPLE -DNeXT
CFLAGS   += -target $(TARGET) -mkernel -nostdinc -std=gnu11
CFLAGS   += -fno-builtin -fno-common -fno-builtin -fstrict-aliasing
CFLAGS   += -Wall -Wextra -Wno-unused-parameter
LDFLAGS  += -target $(TARGET) -isysroot $(SDKPATH) -nostdlib
LDFLAGS  += -Xlinker -kext -Xlinker -export_dynamic -Xlinker -fatal_warnings
LDLIBS   += -lkmod -lcc_kext

# Build the kernel extension.
default: $(KEXTBUNDLE)

$(KEXTNAME).o: $(KEXTNAME).c ../cpusysregs.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(KEXTBIN): $(KEXTNAME).o
	$(CC) $(LDFLAGS) -static -o $@ $(LDLIBS) $^

$(KEXTBUNDLE): $(KEXTBIN) Info.plist.in
	mkdir -p $@/Contents/MacOS
	cp $(KEXTBIN) $@/Contents/MacOS
	grep -v __LIBS__ Info.plist.in >$@/Contents/Info.plist
	while IFS="" read line; do \
	    if [[ $$line == *__LIBS__* ]]; then \
	        kmutil libraries --xml -c -p $(KEXTBUNDLE) --sdk $(SDKPATH) | grep -v -e '^<' -e '^$$'; \
	    else \
	        echo "$$line"; \
	    fi; \
	done <Info.plist.in >$@/Contents/Info.plist.new
	mv $@/Contents/Info.plist.new $@/Contents/Info.plist
	$(CODESIGN) --force --sign - --timestamp=none --generate-entitlement-der $@
	touch $@

# Installation.
install: $(KEXTBUNDLE)
	sudo rm -rf $(KEXTPREFIX)/$(KEXTBUNDLE)
	sudo cp -rp $< $(KEXTPREFIX)/$(KEXTBUNDLE)
	sudo chown -R root:wheel $(KEXTPREFIX)/$(KEXTBUNDLE)
	sudo kmutil load -p $(KEXTPREFIX)/$(KEXTBUNDLE)
load:
	sudo kmutil load -b $(KEXTNAME)
unload:
	sudo kmutil unload -b $(KEXTNAME)
show:
	log show --info --last 2m | grep cpusysregs || true
	kmutil showloaded 2>&1 | grep -vi 'No variant specified, falling back to release' | grep $(KEXTNAME) || true
clean:
	rm -rf *.o $(KEXTBIN) $(KEXTBUNDLE)
