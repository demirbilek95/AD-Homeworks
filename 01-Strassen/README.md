# DSSC - Algorithmic Design - Strassen's Algorithm
This repository contains some code to simplify the implementation and the testing of the Strassen's algorithm and its for matrix multiplication.

In order to test the differences in term of execution-time between the naive algorithm and the Strassen's algorithm, you need to implement both the algorithms. The former must be implementated by the function `naive_matrix_multiplication` in the file [matrix.c](matrix.c) and the latter by the function `strassen_matrix_multiplication` in the file [strassen.c](strassen.c).

A Makefile can be produced by using [cmake](https://cmake.org/) as follows:
```bash
cmake -G "Unix Makefiles" CMakeLists.txt
```
Afterwards you can compile the code by executing `make`. This produces an executable named `strassen_test` which can be executed in POSIX systems by using the command:
```bash
./strassen_test 
n Naive Alg.  Strassen's Alg.	Improved Strassen 	Same result
1	0.000000	0.000000	0.000000		1
2	0.000000	0.000000	0.000000		1
4	0.000000	0.000000	0.000000		1
8	0.000000	0.000000	0.000000		1
16	0.000000	0.000000	0.000000		1
32	0.000000	0.000000	0.000000		1
64	0.000000	0.000000	0.000000		1
128	0.000000	0.000000	0.000000		1
256	0.000000	0.000000	0.000000		1
512	0.000000	0.000000	0.000000		1
1024	0.000000	0.000000	0.000000		1
2048	0.000000	0.000000	0.000000		1
4096	0.000000	0.000000	0.000000		1
```

