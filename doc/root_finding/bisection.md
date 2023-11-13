**Routine Name:**           bisection

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
This routine uses the bisection method to find a root between the `startVal` and `endVal`.
It is guaranteed to find a root if the startVal and endVal meet the criteria.

**Input:** 
- `mathFunc func` The function for which we are finding the root.
- `double startVal` The value where we begin the range where we are looking for the root
- `double endVal` The value where we end our range that we are looking in.
- `double tol` The desired error in the function. Must be > 0.
- `double* result` the pointer that the result will be placed into. This is so that error values may be
returned from the function to know if the function performed correctly.

**Output:** 
- `int` An error value. Returns `0` if the function found a root. Returns `-1` if
your start value and end value evaluate to values with the same sign. Returns `-2`
if the function passes the maximum number of iterations allowed.

**Usage/Example:**

```c
#include <libscipute/root_finding.h>

double fofx(double val) {
    // Some f(x) = ...
    return //...
}

main() {
    double* result = malloc(sizeof(double));
    int error = bisection(fofx, -10, 10, 0.00001, result);
}
```

**Implementation/Code:** The following is the code for `bisection()`

```c
int bisection(mathFunc func, double startVal, double endVal, double tol, double* result) {

  *result = 0;

  double calculatedStart = func(startVal);
  double calculatedEnd = func(endVal);

  // If the start value and end value have the same sign then there is not guaranteed to be a root between them.
  // Exit with  an error
  if((calculatedStart > 0 && calculatedEnd > 0) || (calculatedStart < 0 && calculatedEnd < 0)) {
    return -1;
  } 

  // Check if either value currently constitutes a root
  if(fabs(func(startVal)) <= tol) {
    *result = startVal;
    return 0;
  } else if(fabs(endVal) <= tol) {
    *result = endVal;
    return 0;
  }

  double mid = 0;
  double res = 0;

  while(fabs(endVal - startVal) > tol) {
    // Find the midpoint;
    mid = (endVal + startVal) / 2;
    // Evaluate it
    res = func(mid);

    // Check it
    if(fabs(res) < tol) {
      *result = mid;
      return 0;
    }

    // Set the midpoint as the correct value
    if((res < 0 && func(endVal) < 0) || (res > 0 && func(endVal) > 0)) {
      endVal = mid;
    } else {
      startVal = mid;
    }

  }

  // The values converged to be not as wide as the tolerance. This should probably
  // never happen 
  return -2;
}
```

**Last Modified:** November/2023
