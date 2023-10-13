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
  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_forward_approx);

  return NULL;
}

RUN_TESTS(all_tests);
