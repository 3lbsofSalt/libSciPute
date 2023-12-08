#include "solution_approximations.h"
#include "scipute/matrix.h"
#include "scipute/vector.h"
#include "vector_norms.h"
#include <stdio.h>
#include <stdlib.h>

int jacobi_method(struct Matrix *A, double *b, double tol, int maxIter, double *x) {
  int iters = 0;
  double error = tol * 10;
  double* next_x = calloc(sizeof(double), A->rows);
  double* res = calloc(sizeof(double), A->rows);

  for(int i = 0; i < A->rows; i++) {
    x[i] = 0;
    next_x[i] = 0;
    res[i] = 0;
  }

  while(error > tol) {
    // Getting next x
    for(int i = 0; i < A->rows; i++) {
      double sum = b[i];
      for(int j = 0; j < A->rows; j++) {
        sum = sum - getMatrixData(A, i, j) * x[j];
      }
      next_x[i] = x[i] + sum / getMatrixData(A, i, i);
    }

    // Too many iterations?
    if(++iters > maxIter) {
      free(next_x);
      free(res);
      return -1;
    }

    // Get the next multiplication
    double* temp = calloc(sizeof(double), A->rows);
    temp = multiplyMatrixVector(A, x);

    for(int i = 0; i < A->rows; i++) {
      x[i] = next_x[i];
      res[i] = b[i] - temp[i];
    }

    free(temp);

    error = l2_norm(res, A->rows);
  }

  free(next_x);
  free(res);

  return 0;
}

int gauss_seidel_method(struct Matrix *A, double *b, double tol, int maxIter, double *x) {
  int iters = 0;
  double error = tol * 10;
  for(int i = 0; i < A->rows; i++) {
    x[i] = 0;
  }

  while(error > tol) {
    for(int i = 0; i < A->rows; i++) {
      double sum = 0;
      for(int j = 0; j < A->rows; j++) {
        if(i == j) {
          continue;
        }
        sum += getMatrixData(A, i, j) * x[j];
      }
      x[i] = (b[i] - sum) / getMatrixData(A, i, i);
    }
    if(++iters > maxIter) {
      return -1;
    }

    double* temp = calloc(sizeof(double), A->rows);
    temp = multiplyMatrixVector(A, x);

    double* err_vec = calloc(sizeof(double), A->rows);
    for(int i = 0; i < A->rows; i++) {
      err_vec[i] = b[i] - temp[i];
    }

    free(temp);

    error = l2_norm(err_vec, A->rows);
    free(err_vec);
  }

  return 0;
}
