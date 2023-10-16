## Matrix Usage

In order to perform matrix operations I had to write my own implementation of
a matrix. It is as follows.

```c
struct Matrix {
  int rows;
  int cols;
  double* data;
};

struct Matrix* create_matrix(int n_rows, int n_cols) {
  struct Matrix* matrix = malloc(sizeof(struct Matrix));
  matrix->rows = n_rows;
  matrix->cols = n_cols;

  matrix->data = calloc(n_rows*n_cols, sizeof(double));

  return matrix;
}
```
Please only create matrices using the create_matrix function.

I then included some helper functions:

### Getting and Setting Matrix Data
```c
double getMatrixData(struct Matrix* matrix, int i, int j) {
  return matrix->data[i*(matrix->cols) + j];
}

void setMatrixData(struct Matrix* matrix, int i, int j, double val) {
  matrix->data[i*(matrix->rows) + j] = val;
}
```

These two functions get data and set data in the matrix that gets provided to them.
Do not try to access the matrix data without using these two functions.

### Easy Population

The below function populates the entire matrix with data from an array "vals".
The size of the array is implicitly assumed to be `m->cols * m->rows`.

```c
void setMatrixDataFromArray(struct Matrix* m, double vals[]) {
  for(int i = 0; i < m->rows; i++)  {
    for(int j = 0; j < m->cols; j++) {
      setMatrixData(m, i, j, vals[i*m->cols + j]);
    }
  }
}
```

**Usage Example**: 
```c
main() {
  struct Matrix* m = createMatrix(3, 4);
  double vals[12] = { 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4 };
  setMatrixDataFromArray(m, vals);
}
```
The resulting matrix should have 3 rows, where each row is 1, 2, 3, 4.


### Printing Matrix 
The following code prints the entire matrix for debugging purposes
```c
void printMatrix(struct Matrix* m) {
  for(int i = 0; i < m->rows; i++) {
    for(int j = 0; j < m->cols; j++) {
      printf("%f ", getMatrixData(m, i, j));
    }
    printf("\n");
  }
}
```

### Multiplying A Vector and Matrix
To multiply a matrix and some vector use the `multiplyMatrixVector` function as 
described below:
```c
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
```

Note that `vec` is assumed to have the same number of entries as `m` has columns, and
that the vector that is returned will have the same number of entries as `m` has rows.


### Deleting Matrices
When you are finished with any `struct Matrix*` variable, use this function
to free up the memory and prevent memory leaks.
```c
void deleteMatrix(struct Matrix* matrix) {
  free(matrix->data);
  free(matrix);
}
```

