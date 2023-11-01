**Routine Name:**           lowerTriBackSub

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
This uses back substitution to solve an equation of the form Lx = c, where
L is a lower triangular square matrix and c is a known vector.

**Input:** 
- `struct Matrix* L` - The **square** lower triangular matrix that the 
back substitution will act on. Note that the matrix does not actually have to
be lower triangular, but it will be treated as if all values above the pivots are
0's. Note that every single pivot value must be non zero, or there will be an error.
- `double c[]` - A vector that is assumed to be the same height as L. 

**Output:** 
- `double*` - A vector representing the solution x to the system of equations.

**Usage/Example:**

```c
#include <libscipute/smaceps.h>

main() {
  struct Matrix* A = createMatrix(3, 3);
  // ... Populate matrix
  double vals[3] = { 1, 3, 4 };
  // Assume the transformation of A into a lower triangular L
  // Note that vals has now changed
  double* x = upperTriBackSub(L, vals);
  // x is now the answer to Ax = b
}
```

**Implementation/Code:** The following is the code for `upperTriBackSub()`

```c
// Assume U is an upper-triangular square matrix
double* upperTriBackSub(struct Matrix* U, double c[]) {
  double* x = calloc(U->cols, sizeof(double));

  for(int i = 0; i < L->rows; i++) {
    x[i] = c[i];

    for(int j = 0; j < i; j++) {
      x[i] -= getMatrixData(L, i, j) * x[j];
    }
    x[i] /= getMatrixData(L, i, i);
  }

  return x;
}
```

**Last Modified:** October/2023
