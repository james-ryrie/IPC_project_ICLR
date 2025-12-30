# Compiler and flags
CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic -MMD -MP
LDFLAGS  :=
LDLIBS   :=


# Example: CXXFLAGS += -Iinclude
# CXXFLAGS += -Iinclude

# Sources
COMMON_SRCS := udp_p2p.cpp
SIM_SRCS    := udp_simulator_client.cpp $(COMMON_SRCS)

# Derived objects and dependencies
ITL_OBJS := $(ITL_SRCS:.cpp=.o)
SIM_OBJS := $(SIM_SRCS:.cpp=.o)

ITL_DEPS := $(ITL_OBJS:.o=.d)
SIM_DEPS := $(SIM_OBJS:.o=.d)

# Targets
TARGETS := udp_simulator_client

# Default goal
all: $(TARGETS)

udp_simulator_client: $(SIM_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBRNP_A) $(LDLIBS)

# Generic compile rule (works for subdirectories too; ensures output dir exists)
%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(TARGETS) $(ITL_OBJS) $(SIM_OBJS) $(ITL_DEPS) $(SIM_DEPS)

# Auto-generated dependencies
-include $(ITL_DEPS) $(SIM_DEPS).PHONY: all clean
