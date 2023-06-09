EXECS = rop-attack-protected rop-attack-unprotected

default: $(EXECS) $(addsuffix .s,$(EXECS))
clean:
	rm -f rop-attack rop-attack-*protected *.s *.o *.d

# We explicitly overflow a buffer in the source to simulate the ROP attack, this is done on purpose.
CFLAGS += -Wno-stringop-overflow
PACFLAGS = -mbranch-protection=pac-ret

%-unprotected: %.c
	$(CC) $(CFLAGS) $< -o $@
%-protected: %.c
	$(CC) $(CFLAGS) $(PACFLAGS) $< -o $@
%-unprotected.s: %.c
	$(CC) $(CFLAGS) -S $< -o $@
%-protected.s: %.c
	$(CC) $(CFLAGS) $(PACFLAGS) -S $< -o $@
