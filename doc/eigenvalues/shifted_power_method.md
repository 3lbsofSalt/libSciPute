**Routine Name:**           shifted_power_iteration

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
Given a square matrix it will find an eigenvalue of the matrix. Note that the shift
value is incredibly important. Given a shift value of zero it is the same as the inverse_power_method,
and will find the smallest eigenvalue.

**Input:** 
- `struct Matrix* A` - The **square** matrix for which the eigenvalue is to be found.
It is assumed that the largest eigenvalue is unique and not zero.
- `int max_iter` - The largest number of iterations to be performed before quitting
- `double shift` - The initial guess for the eigenvalue.
- `double tol` - The tolerance before stopping iteration and deciding that the eigenvalue
- `double* result` - The variable to put the final result in

**Output:** 
- `int` - An error value. If the value is 0, then the algorithm succeeded.

**Usage/Example:**

```c
#include <libscipute/eigenvalue.h>

main() {
  struct Matrix* A = createMatrix(3, 3);
  // ... Populate matrix
  double result = 0;
  int error = shifted_power_iteration(A, 100, 2.23, 0.0001, &result);

  return 0;
}
```

**Implementation/Code:** The following is the code for `upperTriBackSub()`

```c
int shifted_power_iteration(struct Matrix* A, int max_iter, double shift, double tol, double* result) {
  for(int i = 0; i < A->rows; i++) {
    setMatrixData(A, i, i, getMatrixData(A, i, i) - shift);
  }

  int error = inverse_power_iteration(A, max_iter, tol, result);
  if(fabs(*result) < 0.00001) return -3;
  *result = (1.0 / *result) + shift;


  return error;
}
```

**Last Modified:** October/2023
