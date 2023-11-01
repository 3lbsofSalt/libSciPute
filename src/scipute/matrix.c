#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

// Code modeled after that of this stack overflow post:
// https://stackoverflow.com/questions/41128608/c-matrix-struct
struct Matrix* create_matrix(int n_rows, int n_cols) {
  struct Matrix* matrix = malloc(sizeof(struct Matrix));
  matrix->rows = n_rows;
  matrix->cols = n_cols;

  matrix->data = calloc(n_rows*n_cols, sizeof(double));

  return matrix;
}


double getMatrixData(struct Matrix* matrix, int i, int j) {
  return matrix->data[i*(matrix->cols) + j];
}

void setMatrixData(struct Matrix* matrix, int i, int j, double val) {
  matrix->data[i*(matrix->rows) + j] = val;
}

void setMatrixDataFromArray(struct Matrix* m, double vals[]) {
  for(int i = 0; i < m->rows; i++)  {
    for(int j = 0; j < m->cols; j++) {
      setMatrixData(m, i, j, vals[i*m->cols + j]);
    }
  }
}

// Assume same size for both matrices
// Set matrix m2 to be a copy of m1
void copyMatrix(struct Matrix* m1, struct Matrix* m2) {
  for(int i = 0; i < m1->rows; i++) {
    for(int j = 0; j < m1->cols; j++) {
      setMatrixData(m2, i, j, getMatrixData(m1, i, j));
    }
  }
}

void printMatrix(struct Matrix* m) {
  for(int i = 0; i < m->rows; i++) {
    for(int j = 0; j < m->cols; j++) {
      printf("%f ", getMatrixData(m, i, j));
    }
    printf("\n");
  }
}

void deleteMatrix(struct Matrix* matrix) {
  free(matrix->data);
  free(matrix);
}

double* multiplyMatrixVector(struct Matrix* m, double vec[]) {
  double* result = calloc(m->rows, sizeof(double));
  for(int i = 0; i < m->rows; i++) {
    double total = 0;
    for(int j = 0; j < m->cols; j++) {
      total += getMatrixData(m, i, j) * vec[j];
    }

    result[i] = total;
  }

  return result;
}

void gaussianElimination(struct Matrix* A, double b[]) {
  struct Matrix* U = create_matrix(A->rows, A->cols);

  // Don't need to compute the first row, just move it over.
  for(int j = 0; j < A->cols; j++) {
    setMatrixData(U, 0, j, getMatrixData(A, 0, j));
  }

  for(int j = 0; j < A->cols; j++) { // Trying to get every column below pivot to 0
    for(int iw = j + 1; iw < A->rows; iw++) { // iw for working row, start below the pivot
      double ratio = getMatrixData(A, iw, j) / getMatrixData(A, j, j); // Using U here to get updated pivot value
      for(int jw = j; jw < A->cols; jw++) {
        setMatrixData(A, iw, jw, getMatrixData(A, iw, jw) - getMatrixData(A, j, jw) * ratio);
      }
      b[iw] = b[iw] - (b[j] * ratio);
    }
  }

}

// Assume U is an upper-triangular square matrix
double* upperTriBackSub(struct Matrix* U, double c[]) {
  double* x = calloc(U->cols, sizeof(double));

  // Start at the bottom of the matrix
  for(int i = U->rows - 1; i >= 0; i--) {
    // Set x with an intermediate value
    x[i] = c[i];
    // Because we know that the matrix is upper triangular we can
    // can start at the end of the row and substitute until we reach the pivot
    for(int j = U->cols - 1; j > i; j--) {
      // Substitute in the values and transform x accordingly
      x[i] -= getMatrixData(U, i, j) * x[j];
    }
    x[i] /= getMatrixData(U, i, i);
  }

  return x;
}

// Assume L is a lower triangular square matrix
double* lowerTriBackSub(struct Matrix* L, double c[]) {
  double* x = calloc(L->cols, sizeof(double));

  for(int i = 0; i < L->rows; i++) {
    x[i] = c[i];

    for(int j = 0; j < i; j++) {
      x[i] -= getMatrixData(L, i, j) * x[j];
    }
    x[i] /= getMatrixData(L, i, i);
  }

  return x;
}

struct Matrix* LUFactorization(struct Matrix* A) {
  struct Matrix* L = create_matrix(A->rows, A->cols);

  // Setting all of the L pivots to 1 in preparation for the calculation
  for(int i = 0; i < L->rows; i++) {
    setMatrixData(L, i, i, 1);
  }


  // Dummy array so that I can get the elimination of A.
  double* b = calloc(A->rows, sizeof(double));

  struct Matrix* Acpy = create_matrix(A->rows, A->cols);
  copyMatrix(A, Acpy);
  gaussianElimination(A, b); // A henceforth will act as U, while Acpy will act as the original A matrix
  free(b); // Get rid of dummy array


  for(int j = 0; j < Acpy->cols; j++) {
    for(int i = j + 1; i < Acpy->rows; i++) {
      // i,j is the cell in L that we are calculating
      double final = getMatrixData(Acpy, i, j);
      // Reduce eq by the known values of L * U. (for this row and column)
      // Note that we only know the values up to j for L, but the values past j
      // are 0, so we don't need to worry about them.
      for(int x = 0; x < j; x++) {
        final -= getMatrixData(L, i, x) * getMatrixData(A, x, j);
      }

      final /= getMatrixData(A, j, j);
      setMatrixData(L, i, j, final);
    }
  }

  deleteMatrix(Acpy);

  return L;
}
