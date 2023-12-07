
```c
int gauss_seidel_method(struct Matrix *A, double *b, double tol, int maxIter, double *x) {
  int iters = 0;
  double error = tol * 10;
  for(int i = 0; i < A->rows; i++) {
    x[i] = 0;
  }

  while(error > tol) {
    for(int i = 0; i < A->rows; i++) {
      double sum = 0;
      for(int j = 0; j < A->rows; j++) {
        if(i == j) {
          continue;
        }
        sum += getMatrixData(A, i, j) * x[j];
      }
      x[i] = (b[i] - sum) / getMatrixData(A, i, i);
    }
    if(++iters > maxIter) {
      return -1;
    }

    double* temp = calloc(sizeof(double), A->rows);
    temp = multiplyMatrixVector(A, x);

    double* err_vec = calloc(sizeof(double), A->rows);
    for(int i = 0; i < A->rows; i++) {
      err_vec[i] = b[i] - temp[i];
    }

    free(temp);
    free(err_vec);

    error = l2_norm(err_vec, A->rows);
  }

  return 0;
}
```
