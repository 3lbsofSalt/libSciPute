#include "minunit.h"
#include "scipute/solution_approximations.h"
#include "scipute/vector_norms.h"
#include <scipute/matrix.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void test_solvers() {
  struct Matrix* A = create_matrix(5, 5);
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

  int ops = 0;

  double y[A->rows];
  for(int i = 0; i < A->rows; i++) {
    y[i] = 1;
  }
  double one_norm = l2_norm(y, A->rows);
  double* b = multiplyMatrixVector(A, y);
  double* x = calloc(sizeof(double), A->rows);

  jacobi_method(A, b, 0.0001, 1000, x, &ops);
  double j_norm = l2_norm(x, A->rows);

  int Gops = 0;
  for(int i = 0; i < A->rows; i++) {
    x[i] = 0;
  }
  gauss_seidel_method(A, b, 0.00001, 1000, x, &Gops);
  double G_norm = l2_norm(x, A->rows);

  int LUops = 0;

  struct Matrix* L = LUFactorization(A, &LUops);
  double* a = LU_solve_system(A, L, b, &LUops);
  double LU_norm = l2_norm(a, A->rows);

  printf("Operations | %d | %d | %d |", ops, Gops, LUops);
  printf("Error | %.10f | %.10f | %.10f |", j_norm - one_norm, G_norm - one_norm, LU_norm - one_norm);
  

  free(a);
  free(x);
  free(b);
  deleteMatrix(A);
  deleteMatrix(L);
}

char *all_tests() {
  mu_suite_start();

  test_solvers();

  return NULL;
}

RUN_TESTS(all_tests);
