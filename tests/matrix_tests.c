#include "minunit.h"
#include <scipute/matrix.h>
#include <stdio.h>

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

char *test_upper_triangular() {
  struct Matrix* m = create_matrix(3, 3);

  double mVals[9] = { 1, 2, 3, 3, 2, 1, 4, 10, 20};

  setMatrixDataFromArray(m, mVals);

  struct Matrix* u = upperTriangular(m);

  deleteMatrix(m);

  double correctVals[9] = { 1, 2, 3, 0, -4, -8, 0, 0, 15 };
  char* msg = check_matrix_values(u, correctVals);

  deleteMatrix(u);

  return msg;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_matrix_creation);
  mu_run_test(test_upper_triangular);

  return NULL;
}

RUN_TESTS(all_tests);
