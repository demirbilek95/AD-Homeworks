#include "graph.h"

void init_graph(graph *g){
    size_t n = g->size;

    for (size_t i = 0; i < n; i++){
        (g->v[i]).id = i;
        (g->v[i]).d = INF;
        (g->v[i]).prev = NULL;
    }  
}

Node *get_node(graph *g, size_t id){
    Node *n = g->v;
    for (size_t i = 0; i < g->size; i++){
        if (n[i].id == id){
            return &n[i];
        }
        return NULL;
    }
    
}

double weight(graph *g, Node *a, Node *b){
    return g->weights[(a->id)*(g->size) + (b->id)];
}

size_t num_adj(graph *g, Node *v){
    size_t n = 0;
    for (size_t i = 0; i < g->size; i++){
        if (g->v[i].id == v->id){
            continue;
        }
        n+=(weight(g,v,&(g->v)[i])) < INF;
        
    }
    return n;
    
}

Node **adj(graph *g, Node *u, size_t n){
    Node **adj = (Node**) malloc(sizeof(Node*)*n);
    size_t a;
    for (size_t i = 0; i < g->size; i++){
        double w = weight(g,u,&(g->v)[i]);
        if (w < INF && weight(g,u,&(g->v)[i])){
            adj[a++] = &(g->v)[i];
        }
        
    }
    return adj;
    
}