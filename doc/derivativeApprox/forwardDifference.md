**Routine Name:**           forwardDifference

**Author:** Max Ramsdell

**Language:** C
The code can be compiled using the GNU C compiler `gcc`

For example,

```
    gcc derivative_approx.c
```

will produce an executable `./a.exe` than can be executed. If you want a different name, the following will work a bit
better

```
    gcc -o derivative_approx derivative_approx.c
```

**Description/Purpose:** 
This routine approximates a derivative of a function 
using the Forward Difference Approximation.

**Input:** 
- `double val` - The value at which the derivative should be approximated
- `double h` - The 'h' value used to divide the approximation. 
Must be greater than 0, but note that the smaller the value, the better the approximation.
A good value could be the value returned by `dmaceps()` in the [machine epsilon](../maceps/dmaceps.md)
functions
- `mathFunc func` - The function whose derivative will be approximated. The
`mathFunc` type is a function pointer type created so that a new `forwardDifference`
function would not have to be created for every function we desire to approximate.
Read more about the type in the [associated functions](associated.md) document

**Output:** 
- `double` - An approximation of the derivative of `func` at the value `val`.

**Usage/Example:**

```c
#include <libscipute/derivative_approx.h>

double xCubed(double val) {
  return val * val * val;
}

main() {
    float approx = forwardDifference(10, 0.001, xCubed);
    return 0;
}
```

**Implementation/Code:** The following is the code for `forwardDifference`

```c
double forwardDifference(double val, double h, mathFunc func) {
  // This is merely an implementation of the forward difference equation
  // Note that the function func is used to get the values for reusability
  return (func(val + h) - func(val)) / h;
}
```

**Last Modified:** October/2023
