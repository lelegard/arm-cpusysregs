# Only one source file here
EXEC := $(firstword $(notdir $(basename $(wildcard *.c))))

default: $(EXEC)
asm: $(EXEC).s
test: $(EXEC)
	./$(EXEC)
clean:
	rm -f $(EXEC) *.s *.o *.d

CFLAGS += -mbranch-protection=bti

# Rule to build assembly source files
%.s: %.c
	$(CC) $(CFLAGS) -S $< -o $@
