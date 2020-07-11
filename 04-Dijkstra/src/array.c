#include "array.h"

Array init_array(Node *array_nodes, const size_t n){
    Node **node_p = (Node **)malloc(sizeof(Node *) * n);
    for (size_t i = 0; i < n; i++){
        node_p[i] = &(array_nodes[i]);
    }
    Array a;
    a.A = node_p;
    a.size =n;

    return a;    
}

void relax_array(Array *a, Node *u, Node *v,double w){
    if (u->d + w < v->d){
        u->d = u->d + w;
        v->prev = u;
    }
}

void update_distance(binheap_type *h, Node *n, double w){
    decrease_key(h,n, &(w));
}

void relax_heap(binheap_type *h, Node *u, Node*v, double w){
    if (u->d + w < v->d){
        update_distance(h,v, u->d+w);
        v->prev = u;
    }   
}

size_t extract_min_A(Array *a){
    size_t min_idx = 0;
    int min = a->A[0]->d;

    for (size_t i = 0; i < a->size; i++){
        if(a->A[i]->d < min){
            min_idx = i;
            min = a->A[i]->d;
        }
    }

    Node *n = a->A[min_idx];

    // remove the min by swapping with the last 
    // element and reducing size
    Node *m = a->A[min_idx];
    Node *last = a->A[a->size-1];

    Node *temp = m;
    m = last;
    last = temp;

    a->size--;    

    return n;
}

void free_array(Array a) {free(a.A);}