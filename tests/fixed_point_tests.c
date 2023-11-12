#include "minunit.h"
#include <scipute/fixed_point.h>
#include <stdio.h>
#include <assert.h>

double test_function(double val) {
  return val * val - 5 * val + 6;
}

double epsilon_test_function(double val) {
  return 2 * test_function(val);
}

char *test_fixed_point() {
  double *result = malloc(sizeof(double));
  int error = fixed_point(test_function, 1.5, 0.0001, 1000, result);
  printf("%d %f\n", error, *result);
  error = fixed_point(test_function, 3.10, 0.0001, 1000, result);
  printf("%d %f\n", error, *result);
 return NULL;
}

char *test_fixed_point_amplified() {
  double *result = malloc(sizeof(double));
  int error = fixed_point_amplified(epsilon_test_function, 2.59, 0.0001, 10000000, result);
  printf("%d %f\n", error, *result);
  error = fixed_point_amplified(epsilon_test_function, 1.49999, 0.0001, 1000, result);
  printf("%d %f\n", error, *result);

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_fixed_point);
  mu_run_test(test_fixed_point_amplified);

  return NULL;
}

RUN_TESTS(all_tests);
