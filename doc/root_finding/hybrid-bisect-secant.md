**Routine Name:**           hybrid_bisect_secant

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
This routine uses the bisection and secant methods to find a root between startVal and endVal

**Input:** 
- `mathFunc func` The function for which we are finding the root.
- `double startVal` one initial guess for the root.
- `double endVal` the other guess for the root, note that `startVal` and `endVal` must evaluate
to different signs
- `double tol` The desired error in the function. Must be > 0.
- `int maxIter` The maximum number of desired iterations for the secant method.
The bisection method will continue until the root is found.
- `double* result` the pointer that the result will be placed into. This is so that error values may be
returned from the function to know if the function performed correctly.

**Output:** 
- `int` An error value. Returns `0` if the function found a root. Returns `-1` if
the `startVal` and `endVal` evaluate to values with the same sign.

**Usage/Example:**

```c
#include <libscipute/root_finding.h>

double fofx(double val) {
    // Some f(x) = ...
    return //...
}

main() {
    double* result = malloc(sizeof(double));
    int error = hybrid_bisect_secant(fofx, -10, 10, 0.00001, 1000, result);
}
```

**Implementation/Code:** The following is the code for `hybrid_bisect_secant()`

```c
int hybrid_bisect_secant(mathFunc func, double startVal, double endVal, double tol, int maxIter, double *result) {
  double calculatedStart = func(startVal);
  double calculatedEnd = func(endVal);

  if((calculatedStart > 0 && calculatedEnd > 0) || (calculatedStart < 0 && calculatedEnd < 0)) {
    return -1;
  } 

  if(fabs(func(startVal)) <= tol) {
    *result = startVal;
    return 0;
  } else if(fabs(endVal) <= tol) {
    *result = endVal;
    return 0;
  }

  double mid = 0;
  double res = 0;

  int error = 1;

  while(error) {
    for(int i = 0; i <= 4; i++) {
      mid = (endVal + startVal) / 2;

      res = func(mid);

      if(fabs(res) < tol) {
        *result = mid;
        return 0;
      }

      if((res < 0 && func(endVal) < 0) || (res > 0 && func(endVal) > 0)) {
        endVal = mid;
      } else {
        startVal = mid;
      }
    }

    // The next value for the secant will be within the range so we're going to try
    // the secant method. It is still possible for it to fail so we can still fall
    // back to the bisection method
    if((res > endVal && res < startVal) || (res < endVal && res > startVal)) {
      error = secant(func, startVal, endVal, tol, maxIter, result);
    }
  }
  return error;
}
```

**Last Modified:** November/2023
