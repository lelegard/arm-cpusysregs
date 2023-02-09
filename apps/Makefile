#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# Makefile for userland applications and tools.
#
#----------------------------------------------------------------------------

CPPFLAGS += -I../kernel
CXXFLAGS += -O2 -std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-unused-function -Werror
LDLIBS   += -lstdc++
ARFLAGS   = rc

SOURCES   := $(wildcard *.cpp)
HEADERS   := $(wildcard *.h)
EXECS     := $(filter-out $(basename $(HEADERS)),$(basename $(SOURCES)))
ALL_OBJS  := $(patsubst %.cpp,%.o,$(SOURCES))
EXEC_OBJS := $(addsuffix .o,$(EXECS))
LIB_OBJS  := $(addsuffix .o,$(filter $(basename $(HEADERS)),$(basename $(SOURCES))))
LIB_FILE  := libcpusysregs.a

default: $(EXECS)

$(EXECS): $(LIB_FILE)
demo-pac.o: CXXFLAGS += -march=armv8.3-a

armfeatures.d: _features.h
_features.h: armfeatures.h
	grep '^ *bool FEAT_' $^ | \
	    sed -e 's/^ *bool FEAT_\([^ (]*\) *().*$$/    {"FEAT_\1", \&ArmFeatures::FEAT_\1},/' | \
	    sort -d -f >$@

$(LIB_FILE): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^
clean:
	rm -f *.o *.a *.d _feat.h $(EXECS)

# Regenerate implicit dependencies.
ifneq ($(if $(MAKECMDGOALS),$(filter-out clean,$(MAKECMDGOALS)),true),)
    -include $(patsubst %.cpp,%.d,$(SOURCES))
endif
%.d: %.cpp
	$(CXX) -MM $(CPPFLAGS) -MT $*.o -MT $@ $< >$@ || rm -f $@
