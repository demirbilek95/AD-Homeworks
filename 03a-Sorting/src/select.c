#include "select.h"
#include "swap.h"
#include "quick_sort.h"

#define ADDR(A, j, elem_size)  ((A)+(j)*(elem_size))

unsigned int selec_pivot(void *A, const unsigned int n, 
                          const size_t elem_size, 
                          total_order leq)
{
    if(n <= 10) {
        quick_sort(A,n,elem_size,leq);
        return n/2;
    }

    unsigned int chunks = n/5;
    unsigned int c_l;
    //unsigned int c_r;
    for (size_t c = 0; c < chunks; c++)
    {
        c_l = c*5;
        //c_r = 5 * c*5;
        quick_sort(ADDR(A,c_l,elem_size),5,elem_size,leq);              // sort it
        swap(ADDR(A,c_l+2,elem_size),ADDR(A,c,elem_size),elem_size);    // place in the middle eleme
    }                                                                   // at the beginning of A

    return select_index(A,chunks,chunks/2,elem_size,leq);

}

unsigned int select_index(void *A, const unsigned int n, 
                          const unsigned int i,
                          const size_t elem_size, 
                          total_order leq)
{
    if (n <= 10) {          // r-l = n-0 --> base case
        quick_sort(A,n,elem_size,leq);
        return i;
    }

    unsigned int  j = selec_pivot(A,n,elem_size,leq);
    unsigned int  k = partition(A,j,0,n-1,elem_size,leq);

    if(i==k) {              // dichotomic search
        return k;
    }

    if(i<k){                //  search in S
        return select_index(A,k-1,i,elem_size,leq);
    }

    // search in G
    return select_index(A,k+1,i,elem_size,leq);    

}

void quick_sort_aux(void *A, size_t l,size_t r,total_order leq,const size_t elem_size)
{
    while(l<r){
        size_t j = partition(A,l,l,r,leq,elem_size);
        quick_sort_aux(A,l,j,leq,elem_size);
        l=j+1;
    }
}

void quick_sort_select(void *A, const unsigned int n, 
                       const size_t elem_size, 
                       total_order leq)
{
   quick_sort_aux(A,0,n,leq,elem_size);
}
