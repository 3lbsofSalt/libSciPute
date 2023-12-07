#include "minunit.h"
#include "scipute/eigenvalues.h"
#include "scipute/matrix.h"
#include "scipute/vector.h"
#include <stdio.h>
#include <assert.h>

double tol = 0.000001;

char *test_power_iteration() {
  double result = 0;

  {
    struct Matrix* A = create_matrix(2, 2);
    // Eigenvalues 1, 3
    double vals[4] = {2, -1, -1, 2};

    setMatrixDataFromArray(A, vals);
    int error = power_iteration(A, 1000, tol, &result);

    mu_assert(error == 0, "There was an error in the power iteration test. It seems like it was unable to find your eigenvalue.");
    mu_assert(float_eq(result, 3.0, tol), "The method returned the incorrect eigenvalue.");
    deleteMatrix(A);
  }

  {
    struct Matrix* A = create_matrix(3, 3);
    // Eigenvalues 1, 2, 21
    double vals[9] = {2, 1, 3, 1, 2, 3, 3, 3, 20};

    setMatrixDataFromArray(A, vals);
    int error = power_iteration(A, 1000, tol, &result);

    mu_assert(error == 0, "There was an error in the power iteration test. It seems like it was unable to find your eigenvalue.");
    mu_assert(float_eq(result, 21.0, tol), "The method returned the incorrect eigenvalue.");
  }

  return NULL;
}

char *test_inverse_power_iteration() {
  double result = 0;

  {
    struct Matrix* A = create_matrix(2, 2);
    // Eigenvalues 1, 3
    double vals[4] = {2, -1, -1, 2};

    setMatrixDataFromArray(A, vals);
    int error = inverse_power_iteration(A, 1000, tol, &result);

    mu_assert(error == 0, "There was an error in the power iteration test. It seems like it was unable to find your eigenvalue.");
    mu_assert(float_eq(result, 1.0, tol), "The first inverse power method returned the incorrect eigenvalue.");
    deleteMatrix(A);
  }

  {
    struct Matrix* A = create_matrix(3, 3);
    // Eigenvalues 1, 2, 21
    double vals[9] = {2, 1, 3, 1, 2, 3, 3, 3, 20};

    setMatrixDataFromArray(A, vals);
    int error = inverse_power_iteration(A, 1000, tol, &result);

    mu_assert(error == 0, "There was an error in the power iteration test. It seems like it was unable to find your eigenvalue.");
    mu_assert(float_eq(result, 1.0, tol), "The second inverse power method returned the incorrect eigenvalue.");
    deleteMatrix(A);
  }

  return NULL;
}

char *test_shifted_power_method() {
  {
    struct Matrix* A = create_matrix(3, 3);
    // Eigenvalues 1, 2, 21
    double vals[9] = {2, 1, 3, 1, 2, 3, 3, 3, 20};
    double result = 0;

    setMatrixDataFromArray(A, vals);
    int error = shifted_power_iteration(A, 1000, 11.0, tol, &result);

    mu_assert(error == 0, "There was an error in the power iteration test. It seems like it was unable to find your eigenvalue.");
    mu_assert(float_eq(result, 2.0, tol * 1000), "The first shifted power method returned the incorrect eigenvalue.");
  }

  {
    struct Matrix* A = create_matrix(3, 3);
    // Eigenvalues: 1, 2, 4
    double vals[9] = {0, 11, -5, -2, 17, -7, -4, 26, -10};
    double result = 0;

    setMatrixDataFromArray(A, vals);
    int error = shifted_power_iteration(A, 1000, 3.101, tol, &result);

    mu_assert(error == 0, "There was an error in the power iteration test. It seems like it was unable to find your eigenvalue.");
    mu_assert(float_eq(result, 4.0, tol * 100), "The second shifted power method returned the incorrect eigenvalue.");
  }

  {
    struct Matrix* A = create_matrix(3, 3);
    // Eigenvalues: 1, 2, 4
    double vals[9] = {0, 11, -5, -2, 17, -7, -4, 26, -10};
    double result = 0;

    setMatrixDataFromArray(A, vals);
    int error = shifted_power_iteration(A, 1000, 1.6, tol, &result);

    mu_assert(error == 0, "There was an error in the power iteration test. It seems like it was unable to find your eigenvalue.");
    mu_assert(float_eq(result, 2.0, tol * 10), "The THIRD shifted power method returned the incorrect eigenvalue.");
  }

  return NULL;
}

char *test_power_method_leslie_matrix() {
  struct Matrix* A = create_matrix(3, 3);
  double vals[9] = { 4, 6, 2, .5, 0, 0, 0, .5, 0 };
  // Largest Eigenvalue = 4.666
  
  double result = 0;

  setMatrixDataFromArray(A, vals);
  int error = power_iteration_leslie_matrix(A, 1000, tol, &result);

  mu_assert(error == 0, "There was an error in the power iteration test. It seems like it was unable to find your eigenvalue."); 
  mu_assert(float_eq(result, 4.66593, tol * 100), "The method returned the incorrect eigenvalue.");
  deleteMatrix(A);


  return NULL;
}

char* test_find_all_eigenvalues() {
  {
    struct Matrix* A = create_matrix(3, 3);
    // Eigenvalues 1, 2, 21
    double vals[9] = {2, 1, 3, 1, 2, 3, 3, 3, 20};
    double result[3] = {0, 0, 0};

    setMatrixDataFromArray(A, vals);
    int error = find_all_eigenvalues(A, 1000, tol, result);
    printVector(result, 3, "Vector 1");
  }

  {
    struct Matrix* A = create_matrix(4, 4);
    // Vals = -1.14667, 0.948311, 3.97205, 22.2263
    double vals[16] = { 1, 2, 3, 4, 3, 2, 1, 4, 2, 1, 3, 2, 1, 6, 4, 20 };
    double result[4] = { 0, 0, 0, 0 };

    setMatrixDataFromArray(A, vals);

    int error = find_all_eigenvalues(A, 1000, tol, result);
    printVector(result, 4, "Result Vec 2");

    deleteMatrix(A);
  }
  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_power_iteration);
  mu_run_test(test_inverse_power_iteration);
  mu_run_test(test_shifted_power_method);
  mu_run_test(test_power_method_leslie_matrix);
  mu_run_test(test_find_all_eigenvalues);

  return NULL;
}

RUN_TESTS(all_tests);
