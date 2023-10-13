#include "minunit.h"
#include <scipute/linreg.h>
#include <stdio.h>
#include <assert.h>

char *test_linreg() {
  float vectorx[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 };
  float vectory[] = { 1.5, 3.8, 6.7, 9.0, 11.2, 13.6, 16.0};

  float *answer = linreg(vectorx, vectory, 7);
  mu_assert(float_eq(answer[0], 2.414284, 0.0001), "Incorrect slope!");
  mu_assert(float_eq(answer[1], -0.828565, 0.0001), "Incorrect slope!");

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_linreg);

  return NULL;
}

RUN_TESTS(all_tests);
