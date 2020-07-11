TEST = test.o 
CXX = gcc
TESTSRC = src/main.c 
CXXFLAGS = -Wall -Wextra -lm
IFLAGS = -I include

all: $(TEST) $(BENCHMARK)

$(TEST): $(TESTSRC)
	$(CXX) -g $< -o $(TEST) $(CXXFLAGS) $(IFLAGS) $(DFLAGS)

clean: 
	@rm -fr *.o docs/html docs/latex

.PHONY: all docs clean
