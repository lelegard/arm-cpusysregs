#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
#----------------------------------------------------------------------------

# System is either "linux" or "mac".
SYSTEM := $(subst Linux,linux,$(subst Darwin,mac,$(shell uname -s)))

MAKEFLAGS += --no-print-directory

PYTHON = $(firstword $(shell which python3 2>/dev/null) $(shell which python 2>/dev/null))

.PHONY: default kernel apps markdown clean install load unload show
default: kernel apps markdown
kernel:
	$(MAKE) -C kernel/$(SYSTEM)
apps:
	$(MAKE) -C apps
markdown:
	$(PYTHON) ./build-md-toc.py *.md */*.md */*/*.md
clean:
	$(MAKE) $@ -C kernel
	$(MAKE) $@ -C kernel/$(SYSTEM)
	$(MAKE) $@ -C apps
	$(MAKE) $@ -C samples/compile-accel
install load unload show:
	$(MAKE) $@ -C kernel/$(SYSTEM)
