**Routine Name:**           newtons

**Author:** Max Ramsdell

**Language:** C
The code can be compiled using the GNU C compiler `gcc`

For example,

```
    gcc root_finding.c
```

will produce an executable `./a.exe` than can be executed. If you want a different name, the following will work a bit
better

```
    gcc -o root_finding root_finding.c
```

**Description/Purpose:** 
This routine uses the newton method to find a root near the `initial` value.

**Input:** 
- `mathFunc func` The function for which we are finding the root.
- `double initial` the initial guess for the root.
- `double tol` The desired error in the function. Must be > 0.
- `int maxIter` The maximum number of desired iterations. Important for newtons method
as it is possible for the initial guess to be bad and it may get stuck at a local minima.
- `double* result` the pointer that the result will be placed into. This is so that error values may be
returned from the function to know if the function performed correctly.

**Output:** 
- `int` An error value. Returns `0` if the function found a root. Returns `-1` if
newton's method ever guesses a value where the derivative is `0`. Returns `-2`
if the function passes the maximum number of iterations allowed. Returns `-3` if
the difference between this guess and the last guess is too small.

**Usage/Example:**

```c
#include <libscipute/root_finding.h>

double fofx(double val) {
    // Some f(x) = ...
    return //...
}

main() {
    double* result = malloc(sizeof(double));
    int error = newtons(fofx, 10, 0.00001, 1000, result);
}
```

**Implementation/Code:** The following is the code for `newtons()`

```c
int newtons(mathFunc func, double initial, double tol, int maxIter, double* result) {

  int i = 0;

  while(i++ < maxIter) {
    double y = func(initial);
    double yder = centralDifference(initial, 0.00001, func);

    if(fabs(yder) < tol) {
      return -1;
    }

    double next_x = initial - y / yder;

    if(fabs(next_x - initial) < tol) {
      return -3;
    }

    if(fabs(func(next_x)) < tol) {
      *result = next_x;
      return 0;
    }

    initial = next_x;

  }

  return -2;
}
```

**Last Modified:** November/2023
