**Routine Name:**           upperTriBackSub

**Author:** Max Ramsdell

**Language:** C
The code can be compiled using the GNU C compiler `gcc`

For example,

```
    gcc maceps.c
```

will produce an executable `./a.exe` than can be executed. If you want a different name, the following will work a bit
better

```
    gcc -o matrix matrix.c
```

**Description/Purpose:** 
This uses back substitution to solve an equation of the form Ux = c, where
U is an upper triangular square matrix and c is a known vector.

**Input:** 
- `struct Matrix* U` - The **square** upper triangular matrix that the 
back substitution will act on. Note that the matrix does not actually have to
be upper triangular, but it will be treated as if all values below the pivots are
0's.
- `double c[]` - A vector that is assumed to be the same height as U. 

**Output:** 
- `double*` - A vector representing the solution x to the system of equations.

**Usage/Example:**

```c
#include <libscipute/smaceps.h>

main() {
  struct Matrix* A = createMatrix(3, 3);
  // ... Populate matrix
  double vals[3] = { 1, 3, 4 };
  struct Matrix* U = gaussianElimination(A, vals);
  // Note that vals has now changed
  double* x = upperTriBackSub(U, vals);
  // x is now the answer to Ax = b
}
```

**Implementation/Code:** The following is the code for `upperTriBackSub()`

```c
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
```

**Last Modified:** October/2023
