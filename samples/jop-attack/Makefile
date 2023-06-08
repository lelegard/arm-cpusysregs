EXECS = jop-attack-protected jop-attack-unprotected

default: $(EXECS) $(addsuffix .s,$(EXECS))
test: $(EXECS)
	-./jop-attack-unprotected
	-./jop-attack-unprotected foo
	-./jop-attack-protected
	-./jop-attack-protected foo
clean:
	rm -f $(EXECS) *.s *.o *.d

ifeq ($(shell uname -s),Darwin)
    # Force arm64e architecture when enabled on the current system.
    PACFLAGS += $(if $(shell (uname -m | grep arm64e) || ((csrutil status | grep disabled) && (nvram -p | grep '^boot-args.*-arm64e_preview_abi'))),-arch arm64e)
else
    PACFLAGS += -mbranch-protection=pac-ret
endif

%-unprotected: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
%-protected: %.cpp
	$(CXX) $(CXXFLAGS) $(PACFLAGS) $< -o $@
%-unprotected.s: %.cpp
	$(CXX) $(CXXFLAGS) -S $< -o /dev/stdout | c++filt >$@
%-protected.s: %.cpp
	$(CXX) $(CXXFLAGS) $(PACFLAGS) -S $< -o /dev/stdout | c++filt >$@
