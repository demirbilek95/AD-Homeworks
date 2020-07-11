#ifndef __array__
#define __array__

#define INF 1000000000  
            
#include <stdlib.h>
#include "binheap.h"

typedef struct Node
{
    size_t id;  // id of node
    size_t pos; // position of array
    double d;   // distance from given source
    struct Node *prev; // pointer to previous node

}Node;

typedef struct Array {
  Node **A;
  size_t size;
} Array;

Array init_array(Node *array_nodes, const size_t n);
void relax_array(Array *a, Node *u, Node *v,double w);
// relaxation implementation for bin_heap data type
void relax_heap(binheap_type *h, Node *u, Node*v, double w);
size_t extract_min_A(Array *a);
void free_array(Array A);


#endif
