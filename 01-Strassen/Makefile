CXX = gcc
OPT = -O4
CXXFLAGS = -w -lm -I.

all: strassen_test.x

strassen_test.x: main.c matrix.c strassen.c improved_strassen.c
	$(CXX) $(OPT) -o $@ $^ $(CXXFLAGS)

clean:
	@rm *.x

.PHONY: clean all
