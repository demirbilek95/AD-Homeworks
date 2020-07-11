#ifndef __graph__
#define __graph__


#include "array.h"

typedef struct graph
{
    Node *v; // List of vertices
    unsigned int *weights;
    size_t size;
}graph;


// initializaiton of graph
void init_graph(graph *g);
// return a node from graph given id
Node *get_node(graph *g, size_t id);
// return the weight of the connecting edge given two node
double weight(graph *g, Node *a, Node *b);
// return the number of nodes which is adjacent to given node
size_t num_adj(graph *g, Node *n);
// return the nodes adjacent to given node and size
Node ** adj(graph *h, Node *u, size_t n);

#endif