#ifndef __MATRIX__
#include <stdlib.h>

void naive_matrix_multiplication(float **C, float const *const *const A,
                                float const *const *const B,
                                const size_t A_f_row,const size_t A_f_col,
                                const size_t B_f_col);

int same_matrix(float const *const *const A, float const *const *const B,
                const size_t rows, const size_t cols);

float **allocate_matrix(const size_t rows, const size_t cols);
void deallocate_matrix(float **A, const size_t rows);

float **allocate_random_matrix(const size_t rows, const size_t cols);

// Function that prints the matrix
void print_matrix(float **A,const size_t r, const size_t c);

// Function that pad the given matrix M by using "allocate_matrix_zeros" simply using existing elements and rest will be 0 automatically
float **pad_matrix(float const* const* const M,const size_t Mrows, const size_t Mcols,const size_t Nrows,
                const size_t Ncols, const size_t RowSeek, const size_t ColSeek);

//Reverse of pad function, unpad the given padded matrix
void unpad(float** padded_matrix, float const* const* const M, const size_t Mrows, const size_t Mcols, const size_t Nrows,
           const size_t Ncols, const size_t FromRow, const size_t FromCol);

#endif //__MATRIX__
