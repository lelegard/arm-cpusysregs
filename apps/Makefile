#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# Makefile for userland applications and tools.
#
#----------------------------------------------------------------------------

CXXFLAGS += -std=c++17 -I../kernel
CXXFLAGS += -Wall -Wextra -Wno-unused-parameter -Wno-unused-function -Werror
LDLIBS   += -lstdc++

SOURCES   := $(wildcard *.cpp)
HEADERS   := $(wildcard *.h)
EXECS     := $(filter-out $(basename $(HEADERS)),$(basename $(SOURCES)))
ALL_OBJS  := $(patsubst %.cpp,%.o,$(SOURCES))
UTIL_OBJS := $(addsuffix .o,$(filter $(basename $(HEADERS)),$(basename $(SOURCES))))
EXEC_OBJS := $(addsuffix .o,$(EXECS))

default: $(EXECS)

$(EXECS): $(UTIL_OBJS)
$(ALL_OBJS): strutils.h ../kernel/cpusysregs.h
$(EXEC_OBJS) regaccess.o: regaccess.h
demo-pac.o: CXXFLAGS += -march=armv8.3-a

clean:
	rm -f *.o $(EXECS)
