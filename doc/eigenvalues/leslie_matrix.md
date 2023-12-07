**Routine Name:**           power_iteration_leslie_matrix

**Author:** Max Ramsdell

**Language:** C
The code can be compiled using the GNU C compiler `gcc`

For example,

```
    gcc eigenvalues.c
```

will produce an executable `./a.exe` than can be executed. If you want a different name, the following will work a bit
better

```
    gcc -o eigenvalues eigenvalues.c
```

**Description/Purpose:** 
Given a square leslie matrix it will find the largest eigenvalue of the matrix.
This program was written with the sparseness of the leslie matrix in mind and will
be significantly faster than just using the regular power method for leslie matrices.

**Input:** 
- `struct Matrix* A` - The **square** **leslie** matrix for which the eigenvalue is to be found.
It is assumed that the largest eigenvalue is unique and not zero.
- `int max_iter` - The largest number of iterations to be performed before quitting
- `double tol` - The tolerance before stopping iteration and deciding that the eigenvalue
- `double* result` - The variable to put the final result in

**Output:** 
- `int` - An error value. If the value is 0, then the algorithm succeeded.

**Usage/Example:**

```c
#include <libscipute/eigenvalue.h>

main() {
  struct Matrix* A = createMatrix(3, 3);
  // ... Populate matrix AS A LESLIE MATRIX
  double result = 0;
  int error = power_iteration_leslie_matrix(A, 100, 0.0001, &result);

  return 0;
}
```

**Implementation/Code:** The following is the code for `upperTriBackSub()`

```c
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
```

**Last Modified:** October/2023
