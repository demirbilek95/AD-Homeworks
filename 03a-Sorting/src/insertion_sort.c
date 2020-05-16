#include "insertion_sort.h"
#include "swap.h"

#define ADDR(A, j, elem_size)  ((A)+(j)*(elem_size))


void insertion_sort(void *A, const unsigned int n, 
                    const size_t elem_size, 
                    total_order leq)
{

    size_t j;
    for (size_t i = 1; i < n; i++)
    {
        j = i;
        while(j > 0 && leq(ADDR(A,j,elem_size), ADDR(A,j-1,elem_size)))
        {
            swap(ADDR(A,j,elem_size),ADDR(A,j-1,elem_size), elem_size);
            j = j-1;
        }
    }
    
}
