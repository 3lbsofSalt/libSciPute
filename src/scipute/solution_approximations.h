#ifndef LIB_SCI_PUTE_SOLUTION_APPROXIMATIONS
#define LIB_SCI_PUTE_SOLUTION_APPROXIMATIONS

#include "matrix.h"
int jacobi_method(struct Matrix* A, double* b, double tol, int maxIter, double* x);
int jacobi_method_leslie(struct Matrix* A, double* b, double tol, int maxIter, double* x);
int gauss_seidel_method(struct Matrix* A, double* b, double tol, int maxIter, double* x);

#endif
