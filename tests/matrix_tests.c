#include "minunit.h"
#include <scipute/matrix.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

char *check_matrix_values(struct Matrix* m, double vals[]) {
  for(int i = 0; i < m->rows; i++) {
    for(int j = 0; j < m->cols; j++) {
      mu_assert(float_eq(getMatrixData(m, i, j), vals[i*m->cols + j], 0.00001), "Incorrect matrix value");
    }
  }

  return NULL;
}

char *test_matrix_creation() {
  struct Matrix* m = create_matrix(3, 3);

  for(int i = 0; i < m->rows; i++) {
    for(int j = 0; j < m->cols; j++) {
      setMatrixData(m, i, j, (i+1) * (j+2));
    }
  }

  double vals[9] = { 2, 3, 4, 4, 6, 8, 6, 9, 12 };
  char* msg = check_matrix_values(m, vals);

  deleteMatrix(m);

  return msg;
}

char *test_gaussian() {
  struct Matrix* m = create_matrix(3, 3);

  double mVals[9] = { 1, 2, 3, 3, 2, 1, 4, 10, 20 };
  double bVals[3] = { 1, 1, 1 };

  setMatrixDataFromArray(m, mVals);
  gaussianElimination(m, bVals);

  double correctVals[9] = { 1, 2, 3, 0, -4, -8, 0, 0, 4 };
  char* msg = check_matrix_values(m, correctVals);
  if(msg != NULL) {
    return msg;
  }

  deleteMatrix(m);

  return NULL;
}

char *test_back_sub() {

  struct Matrix* U = create_matrix(3, 3);
  double vals[9] = { 1, 0, -1, 0, 1, 2, 0, 0, 4 };
  double c[3] = { 0, 0.5, -4 };

  setMatrixDataFromArray(U, vals);

  double* x = upperTriBackSub(U, c);

  mu_assert(float_eq(x[0], -1, 0.00001), "First value in the back sub incorrect.");
  mu_assert(float_eq(x[1], 2.5, 0.00001), "Second value in the back sub incorrect.");
  mu_assert(float_eq(x[2], -1, 0.00001), "Third value in the back sub incorrect.");

  return NULL;
}

char *test_multiply_matrix() {
  struct Matrix* A = create_matrix(2, 2);
  double vals[4] = { 1, 2, 3, 4 };
  double x[2] = { 1, 2 };

  setMatrixDataFromArray(A, vals);

  double* ans = multiplyMatrixVector(A, x);

  mu_assert(ans[0] == 5, "The first value in the resulting matrix was incorrect");
  mu_assert(ans[1] == 11, "The second value in the resulting matrix was incorrect");

  return NULL;
}

char *test_solve_system() {
  struct Matrix* A = create_matrix(10, 10);
  srand(time(0));
  // Turn m into a diagonally dominant matrix,
  // guaranteeing that there is a solution
  // to whatever system of equations is produced.
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      double val = (double)rand() / RAND_MAX;
      setMatrixData(A, i, j, val);
    }

    setMatrixData(A, i, i, 11);
  }

  double y[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
  double* b = multiplyMatrixVector(A, y);

  gaussianElimination(A, b);

  double* x = upperTriBackSub(A, b);

  float total = 0;
  for(int i = 0; i < 10; i++) {
    mu_assert(float_eq(x[i], 1, 0.00001), "Something went wrong with solving the system of equations.");
    total += x[i] * x[i];
  }

  printf("Abs error: %f\n", fabs(10 - total));

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_matrix_creation);
  mu_run_test(test_multiply_matrix);
  mu_run_test(test_gaussian);
  mu_run_test(test_back_sub);
  mu_run_test(test_solve_system);

  return NULL;
}

RUN_TESTS(all_tests);
