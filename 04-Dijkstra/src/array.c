#include "array.h"
#include "binheap.h"

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

void relax(Node *u, Node *v,unsigned int w){
    if (u->d + w < v->d){
        v->d = u->d + w;
        v->prev = u;
    }
}

void update_distance(binheap_type *h, Node *n, unsigned int d)
{
    decrease_key(h, (void*) n, &(d));
}

void relax_heap(binheap_type *h, Node *u, Node *v,unsigned int w){
    if (u->d + w < v->d){
        update_distance(h,v,u->d+w);
        v->prev = u;
    }
}

void array_swap(Node **a, Node **b){
    Node *temp = *a;
    *a = *b;
    *b = temp;
}

void array_remove(Array *a, int i){
    array_swap(&a->A[i], &a->A[a->size-1]);
    a->size--;
}


Node *extract_min_A(Array *a){
    int min = a->A[0]->d;
    int min_idx = 0;

    for (size_t i = 0; i < a->size; i++){
        if(a->A[i]->d < min){
            min = a->A[i]->d;
            min_idx = i;
        }
    }

    // remove the min by swapping with the last 
    // element and reducing size
    Node *n = a->A[min_idx];
    array_remove(a,min_idx); 

    return n;
}

void free_array(Array a) {free(a.A);}