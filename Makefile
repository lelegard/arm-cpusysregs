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

default:
	./build-md-toc.sh *.md
	$(MAKE) -C kernel/$(SYSTEM)
	$(MAKE) -C apps
	$(MAKE) -C docs

clean:
	$(MAKE) $@ -C kernel/$(SYSTEM)
	$(MAKE) $@ -C apps

install load unload show:
	$(MAKE) $@ -C kernel/$(SYSTEM)
