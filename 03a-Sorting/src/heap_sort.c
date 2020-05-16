#include "heap_sort.h"
#include <binheap.h>
#include "swap.h"

#define ADDR(A, j, elem_size) ((A)+(j)*(elem_size))

void heap_sort(void *A, const unsigned int n, 
               const size_t elem_size, 
               total_order leq)
{
    binheap_type *H = build_heap(A,n,n,elem_size,geq_int); // the root is the max??

    for(size_t i = n ; i>1; i-- ){
        
        swap(ADDR(A,i,elem_size),extract_min(H),elem_size);
        
    }
}
