CXXFLAGS := -std=c++20 -fno-exceptions -I.

EXAMPLES := $(subst .cpp,,$(wildcard examples/*.cpp))

all: $(EXAMPLES)

examples/%: examples/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^
