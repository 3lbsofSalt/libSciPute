**Routine Name:**           LUFactorization

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
This function takes in a square matrix "A" and factors it such that LU = A.
The matrix passed in as A will then become upper triangular U, and the function
returns a matrix L that is lower triangular. There is no guarantee that the new A will have
0's below the pivots, but treat it as if there are.

**Input:** 
- `struct Matrix* A` - The **square** matrix that will be factorized. The matrix will
be transformed to be the upper triangular portion of the matrix. Thus, if you 
wish to preserve the original matrix, ensure that you use the copyMatrix function
to keep a copy of the original matrix.

**Output:** 
- `struct Matrix*` - A matrix representing the L portion of the factorization.
Don't forget to call deleteMatrix on this matrix once you have finished using it.

**Usage/Example:**

```c
#include <libscipute/smaceps.h>

main() {
  struct Matrix* A = createMatrix(3, 3);
  // ... Populate matrix
  struct Matrix* L = LUFactorization(A);

}
```

**Implementation/Code:** The following is the code for `LUFactorization()`

```c
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
```

**Last Modified:** October/2023
