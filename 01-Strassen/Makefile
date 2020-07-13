TEST = strassen_test.x
CXX = gcc
OPT = -O4
MAIN = src/main.c     
MATRIX = src/matrix.c
STRASSEN = src/strassen.c
IMP_STRASSEN = src/improved_strassen.c
CXXFLAGS = -Wall -Wextra 
IFLAGS = -I include -lm

all: $(TEST)

$(TEST): $(MAIN) $(MATRIX) $(STRASSEN) $(IMP_STRASSEN)
	$(CXX) -g -o $(TEST) $^ $(IFLAGS)

clean: 
	@rm -fr *.x docs/html docs/latex

.PHONY: all docs clean
