**Routine Name:**           jacobi_method

**Author:** Max Ramsdell

**Language:** C
The code can be compiled using the GNU C compiler `gcc`

For example,

```
    gcc solution_approximations.c
```

will produce an executable `./a.exe` than can be executed. If you want a different name, the following will work a bit
better

```
    gcc -o solution_approximations solution_approximations.c
```

**Description/Purpose:** 
This routine approximates the solution to a system of equations. It converges slower
than the gauss-seidel method, but can be parallelized.

**Input:** 
- `struct Matrix* A` The matrix representing the system of equations
- `double* b` The b vector of the system of equations in "Ax = b"
- `double tol` The tolerance for the error in the answer to the system.
- `int maxIter` The maximum number of iterations to run the approximation. If the
`maxIter` value is reached then it will return an error value
- `double* x` The initial guess for the equation and the location of storage for
the approximation answer.

**Output:** 
- `int` An error value. Returns `0` if the function found a root. Returns `-1` if
it exceeds the `maxIter` number of iterations.

**Usage/Example:**

```c
#include <libscipute/solution_approximations.h>

main() {

    struct Matrix* A = create_matrix();
    double* x = calloc(sizeof(double), A->rows);
    double* b = calloc(sizeof(double), A->rows);
    // Set up system of equations ...
    int error = jacobi_method(A, b, 0.001, 1000, x);
    // x is the answer.
}
```

**Implementation/Code:** The following is the code for `jacobi_method()`

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
**Last Modified:** November/2023
