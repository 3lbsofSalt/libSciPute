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

