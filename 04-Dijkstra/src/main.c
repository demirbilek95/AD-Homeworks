#include <stdio.h>
#include "graph.h"
#include "dijkstra.h"

int main()
{

    // Checking the correctness of algorithm
    unsigned int size = 6;
    unsigned int *adj_matrix = (unsigned int *)malloc(sizeof(unsigned int)*size*size);

    for (size_t i = 0; i < size*size; i++){
        adj_matrix[i] = INF;
    }

    adj_matrix[size*0+1] = 1;
    adj_matrix[size*0+2] = 5;
    adj_matrix[size*1+5] = 15;
    adj_matrix[size*2+3] = 2;
    adj_matrix[size*3+4] = 1;
    adj_matrix[size*4+5] = 3;

    graph g1;
    g1.size = size;
    g1.weights = adj_matrix;
    g1.v = (Node *)malloc(sizeof(Node)*size);
    init_graph(&g1);
    //print_graph(&g1);
    graph *gptr = &g1;

    Node *source = get_node(gptr,0);
    source->d = 0;
    printf("Distance of node source is:%i",source->d);

    Array A = init_array(gptr->v, gptr->size);
    Array *temp = &A;

    printf("\nSize of temp %li",temp->size);

    Node *u = extract_min_A(temp);
    printf("\nextracted min from temp is %i and its distance %ci",u->id,u->d);
    printf("\nSize of temp %li",temp->size);

    int n = num_adj(gptr,u);
    printf("\nNumber of neighbours: %i",n);

    Node **adj = (Node**) malloc(sizeof(Node*)*n);
    int w = weight(gptr,u,&(gptr->v)[1]);
    printf("\n\nW %i",w);

    
    
    //array_dijkstra(&g1,0);


    graph g2;
    g2.size = size;
    g2.weights = adj_matrix;
    g2.v = (Node *)malloc(sizeof(Node)*size);

    free(g1.v);
    free(g2.v);
    free(adj_matrix);




}