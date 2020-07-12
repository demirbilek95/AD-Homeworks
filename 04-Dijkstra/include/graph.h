#ifndef __graph__
#define __graph__


#include "array.h"

typedef struct graph
{
    Node *v; // List of vertices
    int *weights;
    int size;
}graph;


// initializaiton of graph
void init_graph(graph *g);
// return a node from graph given id
Node *get_node(graph *g, int id);
// return the weight of the connecting edge given two node
int weight(graph *g, Node *a, Node *b);
// return the number of nodes which is adjacent to given node
int num_adj(graph *g, Node *n);
// return the nodes adjacent to given node and size
Node ** adj(graph *h, Node *u, int n);

void print_graph(graph *g);

#endif