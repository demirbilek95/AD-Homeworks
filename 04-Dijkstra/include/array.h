#ifndef __array__
#define __array__

#define INF 1000000000  
            
#include <stdlib.h>

typedef struct Node
{
    int id;  // id of node
    int pos; // position of array
    int d;   // distance from given source
    struct Node *prev; // pointer to previous node

}Node;

typedef struct Array {
  Node **A;
  size_t size;
} Array;

Array init_array(Node *array_nodes, const size_t n);
void relax(Node *u, Node *v,unsigned int w);
Node *extract_min_A(Array *a);
void free_array(Array A);


#endif
