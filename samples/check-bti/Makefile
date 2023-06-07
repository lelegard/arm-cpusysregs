default: check-bti
asm: check-bti.s
test: check-bti
	./check-bti
clean:
	rm -f check-bti *.s *.o *.d

CFLAGS += -mbranch-protection=bti

# Rule to build assembly source files
%.s: %.c
	$(CC) $(CFLAGS) -S $< -o $@
