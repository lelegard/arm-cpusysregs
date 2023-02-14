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
EXCLUDE := $(subst Linux,mac,$(subst Darwin,linux,$(shell uname -s)))

CPPFLAGS += -I../kernel
CXXFLAGS += -O2 -std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-unused-function -Werror
LDLIBS   += -lstdc++
ARFLAGS   = rc

SOURCES   := $(filter-out $(EXCLUDE)-%.cpp,$(wildcard *.cpp))
HEADERS   := $(filter-out $(EXCLUDE)-%.h,$(wildcard *.h))
EXECS     := $(filter-out $(basename $(HEADERS)),$(basename $(SOURCES)))
ALL_OBJS  := $(patsubst %.cpp,%.o,$(SOURCES))
EXEC_OBJS := $(addsuffix .o,$(EXECS))
LIB_OBJS  := $(addsuffix .o,$(filter $(basename $(HEADERS)),$(basename $(SOURCES))))
LIB_FILE  := libcpusysregs.a

default: $(EXECS)

$(EXECS): $(LIB_FILE)
demo-pac.o: CXXFLAGS += -march=armv8.3-a

$(LIB_FILE): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^
clean:
	rm -f *.o *.a *.d _*.h $(EXECS)

# A few headers are automatically generated from list of features.
sysregs.d: _armfeatures.h
_armfeatures.h: armfeatures.h
	grep '^ *bool FEAT_' $^ | \
	    sed -e 's/^ *bool FEAT_\([^ (]*\) *().*$$/    {"FEAT_\1", \&ArmFeatures::FEAT_\1},/' | \
	    sort -d -f >$@

demo-userfeatures.d: _userfeatures.h
_userfeatures.h: userfeatures.h
	grep '^ *bool FEAT_' $^ | \
	    sed -e 's/^ *bool FEAT_\([^ (]*\) *().*$$/    {"FEAT_\1", \&UserFeatures::FEAT_\1},/' | \
	    sort -d -f >$@

linux-hwcaps.d: _hwcaps.h
_hwcaps.h: $(wildcard /usr/include/*/bits/hwcap.h)
	(grep '^#define[[:space:]]* HWCAP_' $^ | \
	    sed -e 's/^#define[[:space:]]* HWCAP_\([^ \t]*\).*$$/    {"\1", AT_HWCAP, HWCAP_\1},/'; \
	 grep '^#define[[:space:]]* HWCAP2_' $^ | \
	    sed -e 's/^#define[[:space:]]* HWCAP2_\([^ \t]*\).*$$/    {"\1", AT_HWCAP2, HWCAP2_\1},/') | \
	 sort -u -d -f >$@

mac-sysctl.d: _sysctl.h
_sysctl.h:
	sysctl hw | grep arm | sed -e 's/^\(.*\)\.\([^\.]*\):.*$$/    {"\2", "\1.\2"},/' | sort -u -d -f >$@

# Regenerate implicit dependencies.
ifneq ($(if $(MAKECMDGOALS),$(filter-out clean,$(MAKECMDGOALS)),true),)
    -include $(patsubst %.cpp,%.d,$(SOURCES))
endif
%.d: %.cpp
	$(CXX) -MM $(CPPFLAGS) -MT $*.o -MT $@ $< >$@ || rm -f $@
