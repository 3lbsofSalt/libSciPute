**Routine Name:**           inverse_power_iteration

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
Given a square matrix it will attempt to find all of the eigenvalues in the matrix.
Note that this method assumes all unique, non-zero, real eigenvalues.

**Input:** 
- `struct Matrix* A` - The **square** matrix for which the eigenvalue is to be found.
It is assumed that the largest eigenvalue is unique and not zero.
- `int max_iter` - The largest number of iterations to be performed before quitting
- `double tol` - The tolerance before stopping iteration and deciding that the eigenvalue
- `double* result` - An array of size **n** where **n** is the number of rows and columns in the matrix. 
Note that the values will not necessarily be ordered.

**Output:** 
- `int` - An error value. If the value is 0, then the algorithm succeeded.

**Usage/Example:**

```c
// Assumes that result is a matrix of n size and that A is a square matrix having n rows and n columns.
int find_all_eigenvalues(struct Matrix *A, int max_iter, double tol, double *result) {

  struct Queue* queue = create_queue();

  for(int i = 0; i < A->rows; i++) {
    result[i] = 0;
  }

  double upperBound = 0;
  int error = power_iteration(A, max_iter, tol, &upperBound);
  if(error != 0) return error;
  result[A->rows - 1] = upperBound;

  double lowerBound = 0;
  error = inverse_power_iteration(A, max_iter, tol, &lowerBound);
  if(error != 0) return error;
  result[0] = lowerBound;

  enqueue(queue, upperBound, lowerBound);
  double res = 0;

  printMatrix(A);
  while(!is_empty(queue)) {
    struct QueueNode* next = dequeue(queue);
    double midPoint = (next->upperBound - next->lowerBound) / 2 + next->lowerBound;
    res = 0;

    error = shifted_power_iteration(A, max_iter, midPoint, tol, &res);
    if(error == 0) {
      int firstZero = -1;

      for(int i = 0; i < A->rows; i++) {
        if(result[i] == 0) firstZero = i;
        if(fabs(result[i] - res) < tol * 100) {
          firstZero = -2;
        }
      }

      if(firstZero == -1) return 0;
      result[firstZero] = res;
    }

    double newLower = (midPoint - next->lowerBound) / 2 + next->lowerBound;
    double newUpper = (next->upperBound - midPoint) / 2 + midPoint;

    if(fabs(newLower - midPoint) > tol) {
      enqueue(queue, midPoint, lowerBound);
    }

    if(fabs(newUpper - midPoint) > tol) {
      enqueue(queue, newUpper, midPoint);
    }

    free(next);
  }

  return 0;
}
```

**Last Modified:** October/2023
