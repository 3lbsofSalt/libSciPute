#include "minunit.h"
#include <scipute/maceps.h>
#include <stdio.h>

/* 
 * This just prints out the values because in all reality the most
 * accurate way to get your maceps is to look at a 
 * table of maceps for your machine for different data types.
 */

char *test_single() {
  printf("Single Precision: %e\n", maceps_single_precision());

  return NULL;
}

char *test_double() {
  printf("Double Precision: %e\n", maceps_double_precision());

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_single);
  mu_run_test(test_double);

  return NULL;
}

RUN_TESTS(all_tests);
