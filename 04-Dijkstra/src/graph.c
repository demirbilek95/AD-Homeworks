#include "graph.h"

void init_graph(graph *g){
    size_t n = g->size;

    for (size_t i = 0; i < n; i++){
        (g->v[i]).id = i;
        (g->v[i]).d = INF;
        (g->v[i]).prev = NULL;
    }  
}

Node *get_node(graph *g, int id){
    Node *n = g->v;
    for (size_t i = 0; i < g->size; i++){
        if (n[i].id == id) return &n[i];
    return NULL;
        }
    }
    

int weight(graph *g, Node *a, Node *b){
    return g->weights[(a->id)*(g->size) + (b->id)];
}

int num_adj(graph *g, Node *v){
    int n = 0;
    for (size_t i = 0; i < g->size; i++){
        if ((g->v)[i].id == v->id){
            continue;
        }
        n+=(weight(g,v,&(g->v)[i])) < INF;
        
    }
    return n;
    
}

Node **adj(graph *g, Node *u, int n){
    Node **adj = (Node**) malloc(sizeof(Node*)*n);
    int a = 0;
    for (int i = 0; i < g->size; i++){
        int w = weight(g,u,&(g->v)[i]);
        if (w < INF && (g->v)[i].id != u->id){
            adj[a++] = &(g->v)[i];
        }
    }
    return adj;
    
}

void print_graph(graph *g){
    int size = g->size;
    printf("Size of graph is %i \n", size);

    for (size_t i = 0; i < size; i++){
        for (size_t j = 0; j < size; j++){
            if(g->weights[size*i+j] == INF){
                printf("NIL\t");
            }
            else{                            
                printf("%d\t", g->weights[size*i+j]);
            }
        }
        printf("\n");
    } 

    printf("\nNodes of the graph:");
    for (size_t i = 0; i < size; i++){
        Node node = g->v[i];

        printf("\nnode %d: dist=%d", node.id, node.d);
        if((node.prev)!=NULL)
            printf(", pred=%d", node.prev->id);
        else
            printf(", ");
    }
    printf("\n");     
}
    