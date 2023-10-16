#include "minunit.h"
#include <scipute/vector_norms.h>
#include <stdio.h>
#include <assert.h>

char *test_l1_norm() {
  float vector[] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
  mu_assert(float_eq(l1_norm(vector, 5), 15.0, 0.00001), "Wrong number value.");

  float vector2[] = { -1, 2, -3, 4, -5 };
  mu_assert(float_eq(l1_norm(vector2, 5), 15.0, 0.00001), "Wrong number value, it appears that the abs wasn't working.");

  return NULL;
}

char *test_l1_norm_dist() {
  float vector[] = { 1, 2, 3, 4, 5, 0 };
  float vector2[] = { 1, 2, 3, 4, 5, -6 };

  mu_assert(float_eq(l1_distance(vector, vector2, 6), 6, 0.00001), "Incorrect distance");

  return NULL;
}

char *test_l2_norm() {
  float vector[] = { 3, 4 };
  mu_assert(float_eq(l2_norm(vector, 2), 5.0, 0.00001), "Wrong number value.");

  float vector2[] = { -3, 4 };
  mu_assert(float_eq(l2_norm(vector2, 2), 5.0, 0.00001), "Wrong number value.");

  return NULL;
}

char *test_l2_norm_dist() {
  float vector[] = { 3, 4 };
  float vector2[] = { 3, 0 };

  mu_assert(float_eq(l2_distance(vector, vector2, 2), 4, 0.00001), "Incorrect distance");

  return NULL;
}

char *test_linf_norm() {

  float vector[] = { 1, 2, 3, 4, 5 };
  mu_assert(float_eq(linf_norm(vector, 5), 5, 0.00001), "Wrong number value.");

  float vector2[] = { -1, 2, -3, 4, -5 };
  mu_assert(float_eq(linf_norm(vector2, 5), 5, 0.00001), "Wrong number value.");

  float vector3[] = { 1, -2, 3, -4, 5 };
  mu_assert(float_eq(linf_norm(vector3, 5), 5, 0.00001), "Wrong number value.");

  return NULL;
}

char *test_linf_norm_dist() {
  float vector[] = { 3, 4 };
  float vector2[] = { 3, 0 };

  mu_assert(float_eq(linf_distance(vector, vector2, 2), 4, 0.00001), "Incorrect distance");

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_l2_norm);
  mu_run_test(test_l1_norm);
  mu_run_test(test_linf_norm);
  mu_run_test(test_l2_norm_dist);
  mu_run_test(test_l1_norm_dist);
  mu_run_test(test_linf_norm_dist);

  return NULL;
}

RUN_TESTS(all_tests);
