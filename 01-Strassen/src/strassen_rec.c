#include <stdio.h>
#include <math.h>
#include "matrix.h"
#include "strassen.h"

void sub_matrix_blocks_rec(float **C, float const *const *const A,
                       float const *const * const B,
                       const size_t C_f_row, const size_t C_f_col,
                       const size_t A_f_row, const size_t A_f_col,
                       const size_t B_f_row, const size_t B_f_col,
                       const size_t nr,const size_t nc)
{
    for (size_t y = 0; y < nr; y++) {
      for (size_t x = 0; x < nc; x++) {
          C[y+C_f_row][x+C_f_col] =
               A[y+A_f_row][x+A_f_col] - B[y+B_f_row][x+B_f_col];
      }
    }
}


void sum_matrix_blocks_rec(float **C, float const *const *const A,
                       float const *const * const B,
                       const size_t C_f_row, const size_t C_f_col,
                       const size_t A_f_row, const size_t A_f_col,
                       const size_t B_f_row, const size_t B_f_col,
                       const size_t nr,const size_t nc)

{
    for (size_t y = 0; y < nr; y++) {
      for (size_t x = 0; x < nc; x++) {
          C[y+C_f_row][x+C_f_col] =
               A[y+A_f_row][x+A_f_col] + B[y+B_f_row][x+B_f_col];
      }
    }
}


void strassen_aux_rec(float **C, float const *const *const A,
                  float const *const * const B,
                  const size_t C_f_row, const size_t C_f_col,
                  const size_t A_f_row, const size_t A_f_col,
                  const size_t B_f_row, const size_t B_f_col,
                  const size_t nrA,const size_t ncA,
                  const size_t nrB,const size_t ncB)
                  
{
    if ((nrA <= 5) || (ncA <= 5) || (nrB <= 5) || (ncB <= 5) ) {
        naive_matrix_multiplication(C, A, B,
                                    A_f_row, A_f_col,
                                    B_f_row);

        return;
    }

    size_t nrA2 = nrA/2; // This is the size of the blocks
    size_t ncA2 = ncA/2;
    size_t nrB2 = nrB/2;
    size_t ncB2 = ncB/2;

    // Here allocated S matrices were decreased to reduce the memory allocation same procedure can be done 
    // for P matrices (3-4 allocation is sufficient) but for simplicity allocation of P matrices are left as it is

    float ***S = (float ***)malloc(sizeof(float **) * 10);

    for (size_t i = 0; i < 5; i++) {
        S[i] = allocate_matrix(nrA2, ncA2);
    }

    for (size_t i = 5; i < 10; i++) {
        S[i] = allocate_matrix(nrB2, ncB2);
    }

    float ***P = (float ***)malloc(sizeof(float **) * 7);
    for (size_t i = 0; i < 7; i++) {
        P[i] = allocate_matrix(nrA2, ncB2);
    }


    // S1 = B12 - B22
    sub_matrix_blocks_rec(S[5], B, B,
                      0, 0,
                      B_f_row, B_f_col + ncB2,
                      B_f_row + nrB2, B_f_col + ncB2,
                      nrB2,ncB2);

    printf("S1 Matrisi\n");
    print_matrix(S[5],nrB2,ncB2);

    // P1 = A11 x S1
    strassen_aux_rec(P[0], A, (const float* const *const) S[5],
                 0, 0,
                 A_f_row, A_f_col,
                 0, 0,
                 nrA2,ncA2,nrB2,ncB2);

    printf("\nP1 Matrisi\n");
    print_matrix(P[0],nrA2,nrA2);

    // S2 = A11 + A12
    sum_matrix_blocks_rec(S[0], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row, A_f_col + ncA2,
                      nrA2,ncA2);

   // print_matrix(S[0],n2,n2);

    // P2 = S2 x B22
    strassen_aux_improved(P[1], (const float* const *const) S[0], B,
                 0, 0,
                 0, 0,
                 B_f_row + nrB2, B_f_col + ncB2,
                 nrA2,ncA2,nrB2,ncB2);

    /*printf("\nP2 Matrisi\n");
    print_matrix(P[1],n2,n2);  */

    // S3 = A21 + A22
    sum_matrix_blocks_rec(S[1], A, A,
                      0, 0,
                      A_f_row + nrA2, A_f_col,
                      A_f_row + nrA2, A_f_col + ncA2,
                      nrA2,ncA2);

    // P3 = S3 x B11
    strassen_aux_improved(P[2], (const float* const *const) S[1], B,
                 0, 0,
                 0, 0,
                 B_f_row, B_f_col,
                 nrA2,ncA2,nrB2,ncB2);

    // S4 = B21 - B11
    sub_matrix_blocks_rec(S[6], B, B,
                      0, 0,
                      B_f_row + nrB2, B_f_col,
                      B_f_row, B_f_col,
                      nrB2,ncB2);

    // P4 = A22 x S4
    strassen_aux_improved(P[3], A, (const float* const *const) S[6],
                 0, 0,
                 A_f_row + nrA2, A_f_col + ncA2,
                 0, 0,
                 nrA2,ncA2,nrB2,ncB2);

    // S5 = A11 + A22
    sum_matrix_blocks_rec(S[2], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row + nrA2, A_f_col + ncA2,
                      nrA2,ncA2);

    // S6 = B11 + B22
    sum_matrix_blocks_rec(S[7], B, B,
                      0, 0,
                      B_f_row, B_f_col,
                      B_f_row + nrB2, B_f_col + ncB2,
                      nrB2,ncB2);

    // P5 = S5 x S6
    strassen_aux_improved(P[4], (const float* const *const) S[2],
                 (const float* const *const) S[7],
                 0, 0,
                 0, 0,
                 0, 0,
                 nrA2,ncA2,nrB2,ncB2);

    // S7 = A12 - A22
    sub_matrix_blocks_rec(S[3], A, A,
                      0, 0,
                      A_f_row, A_f_col + ncA2,
                      A_f_row + nrA2, A_f_col + ncA2,
                      nrA2,ncA2);

    // S8 = B21 + B22
    sum_matrix_blocks_rec(S[8], B, B,
                      0, 0,
                      B_f_row + nrB2, B_f_col,
                      B_f_row + nrB2, B_f_col + ncB2,
                      nrB2,ncB2);

    // P6 = S7 x S8
    strassen_aux_improved(P[5], (const float* const *const) S[3],
                 (const float* const *const) S[8],
                 0, 0,
                 0, 0,
                 0, 0,
                 nrA2,ncA2,nrB2,ncB2);

    // S9 = A11 - A21
    sub_matrix_blocks_rec(S[4], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row + nrA2, A_f_col,
                      nrA2,ncA2);

    // S10 = B11 + B12
    sum_matrix_blocks_rec(S[9], B, B,
                      0, 0,
                      B_f_row, B_f_col,
                      B_f_row, B_f_col + ncB2,
                      nrB2,ncB2);

    // P7 = S9 x S10
    strassen_aux_improved(P[6], (const float* const *const) S[4],
                 (const float* const *const) S[9],
                 0, 0,
                 0, 0,
                 0, 0,
                 nrA2,ncA2,nrB2,ncB2);

    // C11 = P5 + P4 - P2 + P6
    sum_matrix_blocks_rec(C, (const float* const *const) P[4],
                      (const float* const *const) P[3],
                      C_f_row, C_f_col,
                      0, 0,
                      0, 0,
                      nrA2,ncB2);
    sub_matrix_blocks_rec(C, (const float* const *const) C,
                      (const float* const *const) P[1],
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      nrA2,ncB2);
    sum_matrix_blocks_rec(C, (const float* const *const) C,
                      (const float* const *const) P[5],
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      nrA2,ncB2);

    // C12 = P1 + P2
    sum_matrix_blocks_rec(C, (const float* const *const) P[0],
                      (const float* const *const) P[1],
                      C_f_row, C_f_col+nrA2,
                      0, 0,
                      0, 0,
                      nrA2,ncB2);

    // C21 = P3 + P4
    sum_matrix_blocks_rec(C, (const float* const *const) P[2],
                      (const float* const *const) P[3],
                      C_f_row+nrA2, C_f_col,
                      0, 0,
                      0, 0,
                      nrA2,ncB2);

    // C22 = P5 + P1 - P3 - P7
    sum_matrix_blocks_rec(C, (const float* const *const) P[4],
                      (const float* const *const) P[0],
                      C_f_row+nrA2, C_f_col+ncB2,
                      0, 0,
                      0, 0,
                      nrA2,ncB2);
    sub_matrix_blocks_rec(C, (const float* const *const) C,
                      (const float* const *const) P[2],
                      C_f_row+nrA2, C_f_col+ncB2,
                      C_f_row+nrA2, C_f_col+ncB2,
                      0, 0,
                      nrA2,ncB2);
    sub_matrix_blocks_rec(C, (const float* const *const) C,
                      (const float* const *const) P[6],
                      C_f_row+nrA2, C_f_col+ncB2,
                      C_f_row+nrA2, C_f_col+ncB2,
                      0, 0,
                      nrA2,ncB2);
    
    for (size_t i = 0; i < 5; i++) {
      deallocate_matrix(S[i], nrA2);
    }

    for (size_t i = 5; i < 10; i++) {
      deallocate_matrix(S[i], nrB2);
    }


    free(S);
    
    for (size_t i = 0; i < 7; i++) {
      deallocate_matrix(P[i], nrA2);
    }
    free(P);   
}

// get the smallest power of 2 which is higher than given paramter (will be used for padding)
int smallest_pow_two(const int r)
{
  int i = 0;
  int p = pow(2,i);
  while(p<r)
  {
    p = pow(2,i);
    i++;
  }
  return p;
}

/*
 * this functions is exclusively meant to provide an
 * easy to use API
 */
void improved_strassen_matrix_multiplication(float **C, float const *const *const A,
                                    float const *const *const B,
                                    const size_t A_f_row,const size_t A_f_col,
                                    const size_t B_f_col)

{
    // Here we find the needed row and column for padding process simply finding the smallest power of 2 which is higher than given parameter
    size_t Apad_row = pow_two(A_f_row);
    size_t Apad_col = pow_two(A_f_col);
    size_t Bpad_col = pow_two(B_f_col);
    /*printf("BpadCol: %ld\n",BpadCol);
    printf(" ApadRow: %ld\n ApadCol: %ld\n BpadCol: %ld",ApadRow,ApadCol,BpadCol);*/

    float** Apad = pad_matrix(A, A_f_row, A_f_col, Apad_row, Apad_col, 0, 0);
    float** Bpad = pad_matrix(B, A_f_col, B_f_col, Apad_col, Bpad_col, 0, 0);
    float** Ctemp = allocate_matrix(Apad_row, Bpad_col);

    /*printf("Padded Matrix A:\n");
    print_matrix(Apad,ApadRow,ApadCol);

    printf("Padded Matrix B:\n");
    print_matrix(Bpad,ApadCol,BpadCol);*/

    size_t ntemp = Apad_row < Apad_col ? Apad_row : Apad_col;
    size_t n = ntemp < Bpad_col ? ntemp : Bpad_col;
   // printf("N:%ld",n);

    // Calculating the multp. result on padded matrix which is suitable for our template
    strassen_aux_improved(Ctemp, Apad, Bpad,0,0,0,0,0,0,Apad_row,Apad_col,Apad_col,Bpad_col);

    /*printf("MAtrix Ctemp\n");
    print_matrix(Ctemp,ApadRow, BpadCol);*/

    // Unpading the the matrix to get the result
    unpad(C, (const float* const* const)Ctemp, Apad_row, Bpad_col, A_f_row, B_f_col, 0, 0);

    deallocate_matrix(Apad, Apad_row);
    deallocate_matrix(Bpad, Apad_col);
    deallocate_matrix(Ctemp, Apad_row);

}