#include <binheap.h>
#include <string.h>
#include <stdio.h>

// node is the index (i)
//since indexing starts from 0 in C
#define PARENT(node) ((node-1)/2) 
#define LEF_CHILD(node) (2*(node)+1)
#define RIGHT_CHILD(node) (2*(node+1))

#define VALID_NODE(H,node) ((H)->num_of_elem>(node))

#define ADDR(H,node) ((H)->A+(node)*H->key_size)
#define ADDR_KEY(H, pos) ((H)->key_pos+(pos))
#define ADDR_REV(H, pos) ((H)->rev_pos+(pos))


#define INDEX_OF(H, addr) (((addr)-((H)->A))/(H)->key_size)

int is_heap_empty(const binheap_type *H)
{
    return H->num_of_elem==0;
}

const void *min_value(const binheap_type *H)
{
    if(is_heap_empty(H)){
        return NULL;
    }

    // minimum is stored in the heap, root a.k.a A[0]
    return ADDR(H,H->key_pos[0]);  //very first element of the array
}

void swap_keys(binheap_type *H, unsigned int n_a, unsigned int n_b)
{

    // Here the idea is using key_pos, rev_pos arrays to swap the keys without using A
    // First swap the position of the keys of the nodes
    unsigned int *p_a = ADDR_KEY(H,n_a);
    unsigned int *p_b = ADDR_KEY(H,n_b);
    
    // swap using xor operator (https://www.programmingsimplified.com/c-program-swap-two-numbers)

    *p_a = *p_a ^ *p_b;
    *p_b = *p_a ^ *p_b;
    *p_a = *p_a ^ *p_b;

    // swap elements of rev_pos array
    unsigned int *r_a = ADDR_REV(H,*p_a);
    unsigned int *r_b = ADDR_REV(H,*p_b);

    *r_a = *r_a ^ *r_b;
    *r_b = *r_a ^ *r_b;
    *r_a = *r_a ^ *r_b;
    
}

void heapify(binheap_type *H, unsigned int node)
{
    unsigned int dst_node=node, child;

    do
    {
        node = dst_node;
        // find the min among node
        // and its children
        child = RIGHT_CHILD(node);
        // now heapify will be performed by using key_pos array
        if(VALID_NODE(H,child) && 
                H->leq(ADDR(H,H->key_pos[child]),ADDR(H,H->key_pos[dst_node]))) {
            dst_node = child;            
        } 
        child = LEF_CHILD(node);
        if(VALID_NODE(H,child) && 
                H->leq(ADDR(H,H->key_pos[child]),ADDR(H,H->key_pos[dst_node]))) {
            dst_node = child;            
        }
        // if the minimum is not in node
        // swap the keys
        if (dst_node != node) {
            swap_keys(H,dst_node, node);
        }
    } while (dst_node != node);
    
}


void *extract_min(binheap_type *H)
{
    if(is_heap_empty(H)){
        return NULL;
    }
    // swapping the keys among the root (A[0])
    // and the right most leaf of the 
    // last level (A[num_of_elem-1])
    swap_keys(H,0,H->num_of_elem-1); // swaping the last element and root
    
    // deleting the right-most leaf of the
    // last level (A[num_of_elem-1])
    H->num_of_elem--;

    heapify(H,0);

    return ADDR(H, H->key_pos[H->num_of_elem+1]);
}

const void *find_the_max(void *A, 
                         const unsigned int num_of_elem, 
                         const size_t key_size, 
                         total_order_type leq)
{
    if(num_of_elem == 0){
        return NULL;
    }

    // for all the values in A
    const void *max_value = A;
    for(const void *addr=A+key_size; 
        addr!= A+num_of_elem*key_size;
        addr+=key_size)
    {
        // if addr > max_value
        if(!leq(addr, max_value)) {
            max_value = addr;
        }
    }
    return max_value;
}

binheap_type *build_heap(void *A, 
                         const unsigned int num_of_elem,
                         const unsigned int max_size,  
                         const size_t key_size, 
                         total_order_type leq)
{
    binheap_type *H = (binheap_type *)malloc(sizeof(binheap_type));

    H->A = A;
    H->num_of_elem = num_of_elem;
    H->max_size = max_size;
    H->key_size = key_size;
    H->leq = leq;
    H->max_order_value = malloc(key_size);
    H->key_pos = (unsigned int *)malloc(max_size*(sizeof(unsigned int)));
    H->rev_pos = (unsigned int *)malloc(max_size*(sizeof(unsigned int)));


    //A[i] =  A[key_pos[rev_pos[i]]]

    for (size_t i = 0; i < num_of_elem; i++)
    {
        H->key_pos[i] = i;
    }

    for (size_t i = 0; i < num_of_elem; i++)
    {
        unsigned int idx = H->key_pos[i];
        H->rev_pos[idx] = i;
    }
    

    if(num_of_elem==0) {
        return H;
    }

    // get the maximum among A[:num_of_elem-1]
    // and store in in max_order_value
    const void *value = find_the_max(A, num_of_elem, 
                                     key_size,leq);

    memcpy(H->max_order_value, value, key_size);

    // fix the heap property from second last
    // level up to the root
    for(unsigned int i = num_of_elem/2; i>0; i--){
        heapify(H,i); // call heapify level qby level starting from lowest level
    }
    heapify(H,0);

    return H;
}

void delete_heap(binheap_type *H)
{
    free(H->max_order_value);
    free(H->key_pos);
    free(H->rev_pos);
    free(H);
}

const void *decrease_key(binheap_type *H, void *node, const void *value)
{
    unsigned int node_idx = INDEX_OF(H,node);
    unsigned int *node_key = ADDR_KEY(H,node_idx);

    // if node does not belong to H or *value>=*node
    // return NULL
    if(!VALID_NODE(H,node_idx) || !(H->leq(value, ADDR(H, *node_key)))){
        return NULL;
    }

    memcpy(ADDR(H,*node_key), value, H->key_size);

    unsigned int parent_idx = PARENT(node_idx);
    unsigned int *node_parent = ADDR_KEY(H,parent_idx);
    //void *parent = ADDR(H, parent_idx);

    // while node != root and *parent > *node
    while ((node_idx != 0) && (!H->leq(ADDR(H,*node_parent), ADDR(H,*node_key))))
    {
        // swap parent and node keys
        swap_keys(H, parent_idx, node_idx);

        // focus on the node's parent
        node_idx = parent_idx;
        node_key = node_parent;

        parent_idx = PARENT(node_idx);
        node_parent = ADDR_KEY(H, parent_idx);
    }
    

    return ADDR(H,*node_key);
}

const void *insert_value(binheap_type *H, const void *value)
{
    // if the heap is already full
    if(H->max_size == H->num_of_elem){
        return NULL;
    }
    // if the new value > *max_order_value
    if(H->num_of_elem == 0 || !H->leq(value, H->max_order_value)){
        memcpy(H->max_order_value, value, H->key_size);
    }
    // get the position of the new node
    void *new_node_addr = ADDR(H,H->num_of_elem);
    memcpy(new_node_addr, H->max_order_value,H->key_size);

    unsigned int *new_node = ADDR_KEY(H,H->num_of_elem);
    *new_node = H->num_of_elem; 

    H->rev_pos[H->num_of_elem] = H->num_of_elem;
    // increase the size of the heap
    H->num_of_elem++;

    //decrease the key of the new node
    return decrease_key(H,new_node_addr, value);
}

void print_heap(const binheap_type *H, 
                void (*key_printer)(const void *value))
{
    unsigned int node = 0;
    unsigned int nex_level_node = 1; // stores the idx of the
                                     // left-most of the 
                                     // next level 
    for(unsigned int node = 0; node < H->num_of_elem; node++){
        if(node ==nex_level_node){
            printf("\n");
            nex_level_node = LEF_CHILD(node);
        }
        else {
            printf("\t");
        }

        key_printer(ADDR(H,H->key_pos[node]));
    }
    printf("\n");
}   