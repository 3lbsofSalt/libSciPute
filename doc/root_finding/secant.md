**Routine Name:**           secant

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
- `double startVal` one of the guesses for the root
- `double endVal` the other guess for the root
- `double tol` The desired error in the function. Must be > 0.
- `int maxIter` The maximum number of desired iterations. Important for secant method as it might not find your root
- `double* result` the pointer that the result will be placed into. This is so that error values may be
returned from the function to know if the function performed correctly.

**Output:** 
- `int` An error value. Returns `0` if the function found a root. Returns `-1` if
the maximum number of iterations is exceeded. Returns `-2`
if the difference between this guess and the last guess is too small.

**Usage/Example:**

```c
#include <libscipute/root_finding.h>

double fofx(double val) {
    // Some f(x) = ...
    return //...
}

main() {
    double* result = malloc(sizeof(double));
    int error = secant(fofx, -10, 10, 0.00001, 1000, result);
}
```

**Implementation/Code:** The following is the code for `upperTriBackSub()`

```c
int secant(mathFunc func, double startVal, double endVal, double tol, int maxIter, double *result) {
  
  int i = 0;
  *result = 0;

  double new = 0;

  while (i++ <= maxIter) {
    new = endVal - func(endVal) * (endVal - startVal) / (func(endVal) - func(startVal));
    startVal = endVal;
    endVal = new;

    if(fabs(func(new)) <= tol) {
      *result = new;
      return 0;
    }

    if(fabs(startVal - endVal) < tol) {
      return -2;
    }
  }

  return -1;
}
```

**Last Modified:** November/2023
