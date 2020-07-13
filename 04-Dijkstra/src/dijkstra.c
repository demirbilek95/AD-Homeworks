#include "dijkstra.h"
#include "binheap.h"
#include "total_orders.h"

void array_dijkstra(graph *g, size_t s){
    init_graph(g);
    // source
    Node *source = get_node(g,s);
    source->d = 0;

    Array A = init_array(g->v, g->size);
    Array *temp = &A;

    while (!(temp->size == 0)){
        Node *u = extract_min_A(temp);
        int n = num_adj(g,u);
        Node **v = adj(g,u,n);

        for (size_t i = 0; i < n; i++){
            relax(u,v[i],weight(g,u,v[i]));
        }
        free(v);
        
    }
    free_array(A);
}
    
void heap_dijkstra(graph *g, size_t s){
    init_graph(g);
    // source
    Node *source = get_node(g,s);
    source->d = 0;

    binheap_type *heap = build_heap(g->v,g->size,g->size,sizeof(Node),leq_node);

    while (!is_heap_empty(heap))
    {
        Node *u = (Node *)extract_min(heap);
        int n = num_adj(g,u);
        Node **v = adj(g,u,n);

        for (size_t i = 0; i < n; i++){
            relax_heap(heap,u,v[i],weight(g,u,v[i]));
        }
        heapify(heap,0);
        free(v);
    }
    delete_heap(heap);
}
