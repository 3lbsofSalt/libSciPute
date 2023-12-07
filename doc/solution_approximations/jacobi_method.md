```c
int jacobi_method(struct Matrix *A, double *b, double tol, int maxIter, double *x) {
  int iters = 0;
  double error = tol * 10;
  double* next_x = calloc(sizeof(double), A->rows);
  double* res = calloc(sizeof(double), A->rows);

  for(int i = 0; i < A->rows; i++) {
    x[i] = 0;
    next_x[i] = 0;
    res[i] = 0;
  }

  while(error > tol) {
    // Getting next x
    for(int i = 0; i < A->rows; i++) {
      double sum = b[i];
      for(int j = 0; j < A->rows; j++) {
        sum = sum - getMatrixData(A, i, j) * x[j];
      }
      next_x[i] = x[i] + sum / getMatrixData(A, i, i);
    }

    // Too many iterations?
    if(++iters > maxIter) {
      free(next_x);
      free(res);
      return -1;
    }

    // Get the next multiplication
    double* temp = calloc(sizeof(double), A->rows);
    temp = multiplyMatrixVector(A, x);

    for(int i = 0; i < A->rows; i++) {
      x[i] = next_x[i];
      res[i] = b[i] - temp[i];
    }

    free(temp);

    error = l2_norm(res, A->rows);
  }

  free(next_x);
  free(res);

  return 0;
}
```
