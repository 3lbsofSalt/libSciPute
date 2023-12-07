#include "minunit.h"
#include "scipute/solution_approximations.h"
#include <scipute/matrix.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int test_jacobi_iteration() {
  struct Matrix* A = create_matrix(100, 100);
  srand(time(0));
  // Turn m into a diagonally dominant matrix,
  // guaranteeing that there is a solution
  // to whatever system of equations is produced.
  float multiplicative = 5.0;
  for(int i = 0; i < A->rows; i++) {
    for(int j = 0; j < A->cols; j++) {
      double val = ((double)rand() / RAND_MAX) * multiplicative;
      setMatrixData(A, i, j, val);
    }
  }

  for(int i = 0; i< A->rows; i++) {
    double sum = 0.0;
    for(int j = 0; j< A->cols; j++) {
      sum = sum + fabs(getMatrixData(A, i, j));
    }
    setMatrixData(A, i, i, getMatrixData(A, i, i) + sum);
  }

  int* ops = 0;

  double y[A->rows];
  for(int i = 0; i < A->rows; i++) {
    y[i] = 1;
  }
  double* b = multiplyMatrixVector(A, y);
  double* x = calloc(sizeof(double), A->rows);

  int error = jacobi_method(A, b, 0.0001, 1000, x);

  free(b);
  free(x);
  deleteMatrix(A);

  return *ops;
}

int test_gauss_seidel() {
  struct Matrix* A = create_matrix(100, 100);
  srand(time(0));
  // Turn m into a diagonally dominant matrix,
  // guaranteeing that there is a solution
  // to whatever system of equations is produced.
  for(int i = 0; i < A->rows; i++) {
    for(int j = 0; j < A->cols; j++) {
      double val = (double)rand() / RAND_MAX;
      setMatrixData(A, i, j, val);
    }

    setMatrixData(A, i, i, 11);
  }

  int* ops = 0;
  double y[A->rows];
  for(int i = 0; i < A->rows; i++) {
    y[i] = 1;
  }
  double* b = multiplyMatrixVector(A, y);
  double* x = calloc(sizeof(double), 100);

  int error = gauss_seidel_method(A, b, 0.00001, 1000, x);

  free(b);
  free(x);
  deleteMatrix(A);

  return *ops;
}

char *all_tests() {

  test_gauss_seidel();
  test_jacobi_iteration();


  return NULL;
}

RUN_TESTS(all_tests);
