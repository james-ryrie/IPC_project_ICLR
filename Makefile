# Compiler and flags
CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic -MMD -MP
LDFLAGS  :=
LDLIBS   :=

# Targets
TARGETS := udp_client_active udp_client

# Default goal
all: $(TARGETS)

# Link rules
udp_client_active: udp_client_active.o udp_p2p.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

udp_client: udp_client.o udp_p2p.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Compile rule (generates.o and.d)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(TARGETS) *.o *.d

# Include auto-generated dependency files
-include $(patsubst %.o,%.d,$(wildcard *.o)).PHONY: all clean
