**Routine Name:**           gaussianElimination

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
This routine uses gaussian elimination to find an upper triangular matrix and
modify an associated vector as if they were part of an augmented matrix.

**Input:** 
- `struct Matrix* A` - The **square** matrix that the elimination will be performed
on.
- `double b[]` - A vector that is assumed to be the same height as A. Note that the vector
will be transformed using the same eliminations on A.

**Output:** 
- None. The output is the effect of the changes on A and b. Note that A will not have
any values below the pivots change, but that they should all be considered to be 0's.

**Usage/Example:**

```c
#include <libscipute/smaceps.h>

main() {
  struct Matrix* A = createMatrix(3, 3);
  // ... Populate matrix
  double vals[3] = { 1, 3, 4 };
  gaussianElimination(A, vals);
  // Note that A and vals have now changed
}
```

**Implementation/Code:** The following is the code for `gaussianElimination()`

```c
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
```

**Last Modified:** October/2023
