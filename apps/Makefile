#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# Makefile for userland applications and tools.
#
#----------------------------------------------------------------------------

# EXCLUDE is either "linux" or "mac", other systems to exclude.
SYSTEM  := $(subst Linux,linux,$(subst Darwin,mac,$(shell uname -s)))
EXCLUDE := $(filter-out $(SYSTEM),linux mac)

# Force arm64e architecture when enabled on the current system.
ifeq ($(SYSTEM),mac)
    ARCHFLAGS := $(if $(shell (uname -m | grep arm64e) || ((csrutil status | grep disabled) && (nvram -p | grep '^boot-args.*-arm64e_preview_abi'))),-arch arm64e)
else
    ARCHFLAGS :=
endif

CPPFLAGS += -I../kernel
CXXFLAGS += $(ARCHFLAGS) -O2 -std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-unused-function -Werror
LDFLAGS  += $(ARCHFLAGS)
LDLIBS   += -lstdc++
ARFLAGS   = rc
SORT      = LC_ALL=C sort -d -f

SOURCES   := $(filter-out $(EXCLUDE)-%.cpp,$(wildcard *.cpp))
HEADERS   := $(filter-out $(EXCLUDE)-%.h,$(wildcard *.h))
EXECS     := $(filter-out $(basename $(HEADERS)),$(basename $(SOURCES)))
ALL_OBJS  := $(patsubst %.cpp,%.o,$(SOURCES))
EXEC_OBJS := $(addsuffix .o,$(EXECS))
LIB_OBJS  := $(addsuffix .o,$(filter $(basename $(HEADERS)),$(basename $(SOURCES))))
LIB_FILE  := libcpusysregs.a

default: $(EXECS)

$(EXECS): $(LIB_FILE)

$(LIB_FILE): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^
clean:
	rm -f *.o *.a *.d _*.h $(EXECS)

# A few headers are automatically generated from list of features.
sysregs.d: _armfeatures.h
_armfeatures.h: armfeatures.h
	grep '^ *bool FEAT_' $^ | \
	    sed -e 's/^ *bool FEAT_\([^ (]*\) *().*$$/    {"FEAT_\1", \&ArmFeatures::FEAT_\1},/' | \
	    $(SORT) >$@

demo-userfeatures.d: _userfeatures.h
_userfeatures.h: userfeatures.h
	grep '^ *bool FEAT_' $^ | \
	    sed -e 's/^ *bool FEAT_\([^ (]*\) *().*$$/    {"FEAT_\1", \&UserFeatures::FEAT_\1},/' | \
	    $(SORT) >$@

linux-hwcaps.d: _hwcaps.h
_hwcaps.h: $(wildcard /usr/include/*/bits/hwcap.h)
	(grep '^#define[[:space:]]* HWCAP_' $^ | \
	    sed -e 's/^#define[[:space:]]* HWCAP_\([^ \t]*\).*$$/    {"\1", AT_HWCAP, HWCAP_\1},/'; \
	 grep '^#define[[:space:]]* HWCAP2_' $^ | \
	    sed -e 's/^#define[[:space:]]* HWCAP2_\([^ \t]*\).*$$/    {"\1", AT_HWCAP2, HWCAP2_\1},/') | \
	 $(SORT) -u >$@

mac-sysctl.d: _sysctl.h
_sysctl.h:
	sysctl hw | grep arm | sed -e 's/^\(.*\)\.\([^\.]*\):.*$$/    {"\2", "\1.\2"},/' | sort -u -d -f >$@

# Regenerate implicit dependencies.
ifneq ($(if $(MAKECMDGOALS),$(filter-out clean,$(MAKECMDGOALS)),true),)
    -include $(patsubst %.cpp,%.d,$(SOURCES))
endif
%.d: %.cpp
	$(CXX) -MM $(CPPFLAGS) -MT $*.o -MT $@ $< >$@ || rm -f $@
