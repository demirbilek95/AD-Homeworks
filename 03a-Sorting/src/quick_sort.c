#include "quick_sort.h"
#include "swap.h"

size_t partition(void *A, size_t p, size_t l, size_t r,total_order leq,const size_t elem_size)
{

    swap(A+(p*elem_size),A+(l*elem_size),elem_size);
    int j = r - 1;
    int i = l + 1;

    while(i<=j)
    {
        if(!(leq(A+(i*elem_size),A+(p*elem_size)))){
            swap(A+(i*elem_size),A+(j*elem_size),elem_size);
            j--;
        }
        else{
            i++;
        }
    }
        
    swap(A+(l*elem_size), A+(j*elem_size),elem_size);
    return j;
}


void quick_sort_rec(void *A, size_t l,size_t r,total_order leq,const size_t elem_size)
{
    while(l<r){
        size_t j = partition(A,l,l,r,leq,elem_size);
        quick_sort_rec(A,l,j,leq,elem_size);
        l=j+1;
    }
}

void quick_sort(void *A, const unsigned int n,
                const size_t elem_size,
                total_order leq)
{
    quick_sort_rec(A,0,n,leq,elem_size);
}
