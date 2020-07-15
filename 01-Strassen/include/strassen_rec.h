/*
For improving strassen algorithm implementation, all the operations that involved S matrices
can be handled by 2 allocation instead of 10, this lead to smaller execution times
*/


#ifndef __IMPROVED_STRASSEN__

void improved_strassen_matrix_multiplication(float **C, float const *const *const A,
                                    float const *const *const B,
                                    const size_t A_f_row,const size_t A_f_col,
                                    const size_t B_f_col);
#endif //__IMPROVED_STRASSEN__
