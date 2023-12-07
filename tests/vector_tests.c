#include "minunit.h"
#include "scipute/vector.h"
#include <stdio.h>
#include <assert.h>


char *test_copy_vector() {
  double from[3] = { 1, 2, 3 };
  double to[3] = { 0, 0, 0 };

  copyVectors(from, to, 3);
  mu_assert(to[0] == 1, "First Element Incorrect");
  mu_assert(to[1] == 2, "Second Element Incorrect");
  mu_assert(to[2] == 3, "Third Element Incorrect");

  return NULL;
}

char *test_dotProduct() {
  double vec1[3] = { 1, 2, 3 };
  double vec2[3] = { -2, 0, 5 };

  double result = dotProduct(vec1, vec2, 3);
  mu_assert(float_eq(result, 13, 0.0001), "The dot product was incorrect.");

  return NULL;
}

char *test_normalize() {
  double vec1[2] = { 3, 4 };
  normalize(vec1, 2);
  mu_assert(float_eq(vec1[0], 3.0/5, 0.00001), "The normalization of the first element was incorrect.");
  mu_assert(float_eq(vec1[1], 4.0/5, 0.00001), "The normalization of the second element was incorrect.");

  return NULL;
}

char *test_magnitude() {
  double vec[2] = { 3, 4 };
  double result = magnitude(vec, 2);

  mu_assert(float_eq(result, 5, 0.00001), "There was an error with the magnitude function.");

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_copy_vector);

  return NULL;
}

RUN_TESTS(all_tests);

