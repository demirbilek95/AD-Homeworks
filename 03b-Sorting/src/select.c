#include "select.h"
#include "quick_sort.h"
#include "swap.h"

#define ADDR(A, j, elem_size)  ((A)+(j)*(elem_size))

struct tuple new_partition(void *A, size_t p, size_t l, size_t r,total_order leq,const size_t elem_size)
{

    swap(A+(p*elem_size),A+(l*elem_size),elem_size);
    p = l;
    l++;
    int count = 0; // variable which is going to count the equal elements to pivot
    int equal;

    while(l<=r)
    {
        equal = leq(ADDR(A,p,elem_size),ADDR(A,l,elem_size)) && leq(ADDR(A,l,elem_size),ADDR(A,p,elem_size));
        if(!equal){

            if((leq(A+(p*elem_size),A+(l*elem_size)))){                         //A[i] > A[p]
                swap(A+(l*elem_size),A+(r*elem_size),elem_size);                // place it in G
                r--;                                                            // increase G's size
            }
            else{                                                               // A[i] < A[p]
            swap(A+(l*elem_size),A+(p-count)*elem_size,elem_size);
            p = l;
            l++;
            }
        }

        else{
            p = l;
            l++;
            count++;
        }   
    }  

    swap(A+(p*elem_size), A+(r*elem_size),elem_size);
    struct tuple indices;
    indices.second = r-count; // position before repeated values
    indices.first = r; // pivot position
    return indices;
}

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
        swap(ADDR(A,c_l+2,elem_size),ADDR(A,c,elem_size),elem_size);    // place in the middle element
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

    unsigned int  p = selec_pivot(A,n,elem_size,leq);
    struct tuple indices = new_partition(A,p,0,n-1,leq,elem_size);

    if(i < indices.first) {
        return select_index(A,indices.first-1,i,elem_size,leq);
    }

    else if(i > indices.second){                
        return select_index(ADDR(A,indices.second,elem_size), n-indices.second-1,i,elem_size,leq);
    }

    else
    {
        return i;   
    }

}

void quick_sort_rec(void *A, size_t l,size_t r,total_order leq,const size_t elem_size)
{
    while(l<r){
        unsigned int pivot_idx = l + selec_pivot(ADDR(A,l,elem_size),r-l,elem_size,leq);
        struct tuple indices = new_partition(A,pivot_idx,l,r-1,leq,elem_size);
        quick_sort_rec(A,l,indices.first,leq,elem_size);
        l = indices.second +1 ;
    }
}

void quick_sort_select(void *A, const unsigned int n, 
                       const size_t elem_size, 
                       total_order leq)
{
   quick_sort_rec(A,0,n,leq,elem_size);
}