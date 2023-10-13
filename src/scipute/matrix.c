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

struct Matrix* upperTriangular(struct Matrix* A) {
  struct Matrix* U = create_matrix(A->rows, A->cols);

  // Don't need to compute the first row, just move it over.
  for(int j = 0; j < A->cols; j++) {
    setMatrixData(U, 0, j, getMatrixData(A, 0, j));
  }

  for(int j = 0; j < A->cols; j++) {
    for(int i = j; i < A->rows; i++) {
      // i2 
      for(int i2 = i+1; i2 < A->rows; i2++) { // i2 represents the working 
        double ratio = getMatrixData(A, i2, j) / getMatrixData(A, i, j);
        
        // j2 is used to go through the rest of the row to use the ratio to subtract the
        // values determined by the ratio from the rest of the row
        // note that any of the values below the pivot will not be set to 0,
        // there is no need to waste the computation time
        for(int j2 = j; j2 < A->cols; j2++) {
          setMatrixData(U, i2, j2, getMatrixData(A, i2, j2) - getMatrixData(A, i, j2) * ratio);
        }
      }
    }
  }

  return U;
}

void back_sub(struct Matrix* U, double b[]) {

}

