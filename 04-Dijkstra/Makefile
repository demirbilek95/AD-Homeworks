TEST = test.o 
CXX = gcc
MAIN = src/main.c     
ARRAY = src/array.c
BINHEAP = src/binheap.c
DISKSTRA = src/dijkstra.c
GRAPH = src/graph.c
TOTALORDER = src/total_orders.c
CXXFLAGS = -Wall -Wextra 
IFLAGS = -I include -lm -w

all: $(TEST)

$(TEST): $(MAIN) $(ARRAY) $(BINHEAP) $(DISKSTRA) $(GRAPH) $(TOTALORDER)
	$(CXX) -g -o $(TEST) $^ $(IFLAGS)

clean: 
	@rm -fr *.o docs/html docs/latex

.PHONY: all docs clean
