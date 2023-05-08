default: test-accel
test-accel: $(patsubst %.c,%.o,$(wildcard *.c))
clean:
	rm -f test-accel *.o *.d

CFLAGS += $(CFLAGS_TARGET)

# Compilation of modules containing specialized instructions or intrinsics.
# On Linux, we must compile them specifically. On macOS, support is implicit.
# We must limit this to specialized modules which are never called when these
# instructions are not supported. Other modules will explicitly check at run
# time if they are supported before using them.
# Warning: depending on the OS, "uname -m" displays "arm64" or "aarch64".

ifeq ($(subst aarch64,arm64,$(shell uname -s -m)),Linux arm64)
    crc_accel.o:    CFLAGS_TARGET = -march=armv8-a+crc
    aes_accel.o:    CFLAGS_TARGET = -march=armv8-a+crypto
    sha1_accel.o:   CFLAGS_TARGET = -march=armv8-a+crypto
    sha256_accel.o: CFLAGS_TARGET = -march=armv8-a+crypto+sha2
    sha512_accel.o: CFLAGS_TARGET = -march=armv8.2-a+crypto+sha2+sha3
endif

# Regenerate implicit dependencies.

ifeq ($(filter clean,$(MAKECMDGOALS)),)
    -include $(patsubst %.c,%.d,$(wildcard *.c))
endif
%.d: %.c
	$(CC) -MM $(CPPFLAGS) -MT $*.o -MT $@ $< >$@ || rm -f $@
