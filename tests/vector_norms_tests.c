#include "minunit.h"
#include <scipute/vector_norms.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

int float_eq(float f1, float f2) {
  return fabs(f1 - f2) < 0.00001;
}

char *test_one_norm() {
  float vector[] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
  mu_assert(float_eq(one_norm(vector, 5), 15.0), "Wrong number value.");

  float vector2[] = { -1, 2, -3, 4, -5 };
  mu_assert(float_eq(one_norm(vector2, 5), 15.0), "Wrong number value, it appears that the abs wasn't working.");

  return NULL;
}

char *test_one_norm_dist() {
  float vector[] = { 1, 2, 3, 4, 5, 0 };
  float vector2[] = { 1, 2, 3, 4, 5, -6 };

  mu_assert(float_eq(one_norm_distance(vector, vector2, 6), 6), "Incorrect distance");

  return NULL;
}

char *test_two_norm() {
  float vector[] = { 3, 4 };
  mu_assert(float_eq(two_norm(vector, 2), 5.0), "Wrong number value.");

  float vector2[] = { -3, 4 };
  mu_assert(float_eq(two_norm(vector2, 2), 5.0), "Wrong number value.");

  return NULL;
}

char *test_two_norm_dist() {
  float vector[] = { 3, 4 };
  float vector2[] = { 3, 0 };

  mu_assert(float_eq(two_norm_distance(vector, vector2, 2), 4), "Incorrect distance");

  return NULL;
}

char *test_infty_norm() {

  float vector[] = { 1, 2, 3, 4, 5 };
  mu_assert(float_eq(infty_norm(vector, 5), 5), "Wrong number value.");

  float vector2[] = { -1, 2, -3, 4, -5 };
  mu_assert(float_eq(infty_norm(vector2, 5), 5), "Wrong number value.");

  float vector3[] = { 1, -2, 3, -4, 5 };
  mu_assert(float_eq(infty_norm(vector3, 5), 5), "Wrong number value.");

  return NULL;
}

char *test_infty_norm_dist() {
  float vector[] = { 3, 4 };
  float vector2[] = { 3, 0 };

  mu_assert(float_eq(infty_norm_distance(vector, vector2, 2), 4), "Incorrect distance");

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_two_norm);
  mu_run_test(test_one_norm);
  mu_run_test(test_infty_norm);
  mu_run_test(test_two_norm_dist);
  mu_run_test(test_one_norm_dist);
  mu_run_test(test_infty_norm_dist);

  return NULL;
}

RUN_TESTS(all_tests);
