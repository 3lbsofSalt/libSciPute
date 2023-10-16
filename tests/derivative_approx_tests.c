#include "minunit.h"
#include <scipute/derivative_approx.h>
#include <assert.h>

double dOfxCubed(double val) { // mathFunc
  return val * val * 3;
} 

double xCubed(double val) { // mathFunc
  return val * val * val;
}

char *test_forward_approx() {
  double approx = forwardDifference(10, 0.00001, xCubed);
  double exact = dOfxCubed(10);
  mu_assert(float_eq(approx, exact, 0.001), "Forward approximation is incorrect");

  return NULL;
}

char *test_backward_approx() {
  double approx = backwardDifference(10, 0.00001, xCubed);
  double exact = dOfxCubed(10);
  mu_assert(float_eq(approx, exact, 0.001), "Backward approximation is incorrect");

  return NULL;
}

char *test_central_approx() {
  double approx = centralDifference(10, 0.00001, xCubed);
  double exact = dOfxCubed(10);
  mu_assert(float_eq(approx, exact, 0.001), "Central approximation is incorrect");

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_forward_approx);
  mu_run_test(test_backward_approx);
  mu_run_test(test_central_approx);

  return NULL;
}

RUN_TESTS(all_tests);
