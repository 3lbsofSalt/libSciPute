#include "minunit.h"
#include "scipute/root_finding.h"
#include <stdio.h>
#include <assert.h>

double test_function(double val) {
  return val * val - 5 * val + 6;
}

double tol = 0.00001;

char *test_bisection() {
  double* result = malloc(sizeof(double));

  int error = bisection(test_function, 1.5, 2.5, tol, result);
  mu_assert(error == 0, "There was an error in the first bisection root finding test!");
  mu_assert(float_eq(*result, 2, tol), "Incorrect root found in the first bisection root finding test.");

  error = bisection(test_function, 4.5, 2.5, tol, result);
  mu_assert(error == 0, "There was an error in the second bisection root finding test!");
  mu_assert(float_eq(*result, 3, tol), "Incorrect root found in the second bisection root finding test.");

  free(result);

  return NULL;
}

char *test_newton() {
  double* result = malloc(sizeof(double));

  int error = newtons(test_function, 1.5, 0.00001, 1000, result);
  mu_assert(error == 0, "There was an error in the first Newton's root finding test!");
  mu_assert(float_eq(*result, 2, tol), "Incorrect root found in the first Newton's root finding test.");

  error = newtons(test_function, 3.5, 0.00001, 1000, result);
  mu_assert(error == 0, "There was an error in the second Newton's root finding test!");
  mu_assert(float_eq(*result, 3, tol), "Incorrect root found in the second Newton's root finding test.");

  free(result);

  return NULL;
}

char *test_secant() {
  double* result = malloc(sizeof(double));

  int error = secant(test_function, 1.5, 2.5, 0.000001, 1000, result);
  mu_assert(error == 0, "There was an error in the first secant root finding test!");
  mu_assert(float_eq(*result, 2, tol), "Incorrect root found in the first secant root finding test.");

  error = secant(test_function, 2.25, 3.5, 0.000001, 1000, result);
  mu_assert(error == 0, "There was an error in the second secant root finding test!");
  mu_assert(float_eq(*result, 3, tol), "Incorrect root found in the second secant root finding test.");

  free(result);

  return NULL;
}

char *test_hybrid_bisect_secant() {
  double* result = malloc(sizeof(double));

  int error = hybrid_bisect_secant(test_function, 1.5, 2.5, 0.000001, 1000, result);
  mu_assert(error == 0, "There was an error in the first hybrid_b_s root finding test!");
  mu_assert(float_eq(*result, 2, tol), "Incorrect root found in the first hybrid_b_s root finding test.");

  error = hybrid_bisect_secant(test_function, 2.25, 3.5, 0.000001, 1000, result);
  mu_assert(error == 0, "There was an error in the second hybrid_b_s root finding test!");
  mu_assert(float_eq(*result, 3, tol), "Incorrect root found in the second hybrid_b_s root finding test.");

  free(result);

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_bisection);
  mu_run_test(test_newton);
  mu_run_test(test_secant);
  mu_run_test(test_hybrid_bisect_secant);

  return NULL;
}

RUN_TESTS(all_tests);
