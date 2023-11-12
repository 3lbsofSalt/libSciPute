#include "minunit.h"
#include "scipute/root_finding.h"
#include <stdio.h>
#include <assert.h>

double test_function(double val) {
  return val * val - 5 * val + 6;
}

char *test_bisection() {
  double* result = malloc(sizeof(double));

  int error = bisection(test_function, 1.5, 2.5, 0.00001, 1000, result);
  printf("Result: %d %f\n", error, *result);

  error = bisection(test_function, 4.5, 2.5, 0.00001, 1000, result);
  printf("Result: %d %f\n", error, *result);

  return NULL;
}

char *test_newton() {
  double* result = malloc(sizeof(double));

  int error = newtons(test_function, 1.5, 0.00001, 1000, result);
  printf("Newton's Result: %d %f\n", error, *result);

  error = newtons(test_function, 3.5, 0.00001, 1000, result);
  printf("Newton's Result: %d %f\n", error, *result);

  return NULL;
}

char *test_secant() {
  double* result = malloc(sizeof(double));

  int error = secant(test_function, 1.5, 2.5, 0.000001, 1000, result);
  printf("Secant's Result: %d %f\n", error, *result);

  error = secant(test_function, 2.25, 3.5, 0.000001, 1000, result);
  printf("Secant's Result: %d %f\n", error, *result);

  return NULL;
}

char *test_hybrid() {
  double* result = malloc(sizeof(double));

  int error = hybrid(test_function, 1.5, 2.5, 0.000001, 1000, result);
  printf("Hybrid's Result: %d %f\n", error, *result);

  error = hybrid(test_function, 2.25, 3.5, 0.000001, 1000, result);
  printf("Hybrid's Result: %d %f\n", error, *result);

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_bisection);
  mu_run_test(test_newton);
  mu_run_test(test_secant);
  mu_run_test(test_hybrid);

  return NULL;
}


RUN_TESTS(all_tests);
