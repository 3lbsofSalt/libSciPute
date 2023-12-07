#include "matrix.h"

int power_iteration(struct Matrix* A, int max_iter, double tol, double* result);
int inverse_power_iteration(struct Matrix* A, int max_iter, double tol, double* result);
int power_iteration_leslie_matrix(struct Matrix* A, int max_iter, double tol, double* result);
int shifted_power_iteration(struct Matrix* A, int max_iter, double shift, double tol, double* result);
int find_all_eigenvalues(struct Matrix* A, int max_iter, double tol, double* result);
