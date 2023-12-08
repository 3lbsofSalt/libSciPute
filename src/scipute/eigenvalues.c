#include "eigenvalues.h"
#include "scipute/matrix.h"
#include "scipute/vector.h"
#include "queue.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

// https://services.math.duke.edu/~jtwong/math361-2019/lectures/Lec10eigenvalues.pdf
int power_iteration(struct Matrix* A, int max_iter, double tol, double* result) {
  double* vector = calloc(A->rows, sizeof(double));
  srand(time(NULL));
  for(int i = 0; i < A->rows; i++) {
    // Reduces the chance that my eigenvector is orthogonal to the eigenvalue's eigenvector I'm attempting to find.
    vector[i] = ((double)rand() / RAND_MAX) + 1; 
  }

  normalize(vector, A->rows);
  double* next_vec = multiplyMatrixVector(A, vector);
  double eigenvalue = 0;
  double nextEig = dotProduct(vector, next_vec, A->rows);

  for(int i = 0; i < max_iter; i++) {
    copyVectors(next_vec, vector, A->rows);
    eigenvalue = nextEig;

    normalize(vector, A->rows);
    free(next_vec);
    next_vec = multiplyMatrixVector(A, vector);
    nextEig = dotProduct(vector, next_vec, A->rows);

    if(fabs(eigenvalue - nextEig) < tol) {
      *result = nextEig;
      free(vector);
      free(next_vec);
      if(nextEig == 0) return -2;
      return 0;
    }
  }

  free(vector);
  free(next_vec);
  return -1;
}

int inverse_power_iteration(struct Matrix* A, int max_iter, double tol, double* result) {
  struct Matrix* temp = create_matrix(A->rows, A->cols);
  copyMatrix(A, temp);

  double* vector = calloc(temp->rows, sizeof(double));
  srand(time(NULL));
  for(int i = 0; i < temp->rows; i++) {
    // Reduces the chance that my eigenvector is orthogonal to the eigenvalue's eigenvector I'm attempting to find.
    vector[i] = ((double)rand() / RAND_MAX) + 1; 
  }

  normalize(vector, temp->rows);


  // Rather than finding the determinant of the matrix to make it inverse, we just solve for the next
  // Eigenvector rather than multiply for it. It does the same thing: A^-1 * x = x1 <=> Ax1 = x. Solve for x1
  int ops = 0;
  struct Matrix* L = LUFactorization(temp, &ops);

  double* next_vec = LU_solve_system(temp, L, vector, &ops);
  double eigenvalue = 0;
  double nextEig = dotProduct(vector, next_vec, temp->rows);

  for(int i = 0; i < max_iter; i++) {
    copyVectors(next_vec, vector, temp->rows);
    eigenvalue = nextEig;

    normalize(vector, temp->rows);
    free(next_vec);
    next_vec = LU_solve_system(temp, L, vector, &ops);
    nextEig = dotProduct(vector, next_vec, temp->rows);

    if(fabs(eigenvalue - nextEig) < tol) {
      *result = nextEig;
      free(vector);
      free(next_vec);
      deleteMatrix(L);
      deleteMatrix(temp);
      if(nextEig == 0) return -2;
      return 0;
    }
  }

  free(vector);
  free(next_vec);
  deleteMatrix(temp);
  deleteMatrix(L);
  return -1;
}

int shifted_power_iteration(struct Matrix* A, int max_iter, double shift, double tol, double* result) {
  for(int i = 0; i < A->rows; i++) {
    setMatrixData(A, i, i, getMatrixData(A, i, i) - shift);
  }

  int error = inverse_power_iteration(A, max_iter, tol, result);
  for(int i = 0; i < A->rows; i++) {
    setMatrixData(A, i, i, getMatrixData(A, i, i) + shift);
  }
  if(fabs(*result) < 0.00001) return -3;
  *result = (1.0 / *result) + shift;


  return error;
}


// Assumes that result is a matrix of n size and that A is a square matrix having n rows and n columns.
int find_all_eigenvalues(struct Matrix *A, int max_iter, double tol, double *result) {

  struct Queue* queue = create_queue();

  for(int i = 0; i < A->rows; i++) {
    result[i] = 0;
  }

  double upperBound = 0;
  int error = power_iteration(A, max_iter, tol, &upperBound);
  if(error != 0) return error;
  result[A->rows - 1] = upperBound;

  double lowerBound = 0;
  error = inverse_power_iteration(A, max_iter, tol, &lowerBound);
  if(error != 0) return error;
  result[0] = lowerBound;

  enqueue(queue, upperBound, lowerBound);
  double res = 0;

  printMatrix(A);
  while(!is_empty(queue)) {
    struct QueueNode* next = dequeue(queue);
    double midPoint = (next->upperBound - next->lowerBound) / 2 + next->lowerBound;
    res = 0;

    error = shifted_power_iteration(A, max_iter, midPoint, tol, &res);
    if(error == 0) {
      int firstZero = -1;

      for(int i = 0; i < A->rows; i++) {
        if(result[i] == 0) firstZero = i;
        if(fabs(result[i] - res) < tol * 100) {
          firstZero = -2;
        }
      }

      if(firstZero == -1) return 0;
      result[firstZero] = res;
    }

    double newLower = (midPoint - next->lowerBound) / 2 + next->lowerBound;
    double newUpper = (next->upperBound - midPoint) / 2 + midPoint;

    if(fabs(newLower - midPoint) > tol) {
      enqueue(queue, midPoint, lowerBound);
    }

    if(fabs(newUpper - midPoint) > tol) {
      enqueue(queue, newUpper, midPoint);
    }

    free(next);
  }

  return 0;
}

double* multiplyLeslieMatrixByVector(struct Matrix* A, double vec[]) {
  double* result = calloc(A->rows, sizeof(double));
  double total = 0;
  for(int i = 0; i < A->cols; i++) {
    total += vec[i] * getMatrixData(A, 0, i);
  }
  result[0] = total;
  for(int i = 1; i < A->rows; i++) {
    result[i] = vec[i-1] * getMatrixData(A, i, i-1);
  }

  return result;
}

// https://services.math.duke.edu/~jtwong/math361-2019/lectures/Lec10eigenvalues.pdf
int power_iteration_leslie_matrix(struct Matrix* A, int max_iter, double tol, double* result) {
  double* vector = calloc(A->rows, sizeof(double));
  srand(time(NULL));
  for(int i = 0; i < A->rows; i++) {
    // Reduces the chance that my eigenvector is orthogonal to the eigenvalue's eigenvector I'm attempting to find.
    vector[i] = ((double)rand() / RAND_MAX) + 1; 
  }

  normalize(vector, A->rows);
  double* next_vec = multiplyLeslieMatrixByVector(A, vector);
  double eigenvalue = 0;
  double nextEig = dotProduct(vector, next_vec, A->rows);

  for(int i = 0; i < max_iter; i++) {
    copyVectors(next_vec, vector, A->rows);
    eigenvalue = nextEig;

    normalize(vector, A->rows);
    free(next_vec);
    next_vec = multiplyLeslieMatrixByVector(A, vector);
    nextEig = dotProduct(vector, next_vec, A->rows);

    if(fabs(eigenvalue - nextEig) < tol) {
      *result = nextEig;
      free(vector);
      free(next_vec);
      if(nextEig == 0) return -2;
      return 0;
    }
  }

  return -1;
}

