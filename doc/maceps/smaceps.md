**Routine Name:**           smaceps

**Author:** Max Ramsdell

**Language:** C
The code can be compiled using the GNU C compiler `gcc`

For example,

    gcc maceps.c

will produce an executable `./a.exe` than can be executed. If you want a different name, the following will work a bit
better

    gfortran -o maceps maceps.c

**Description/Purpose:** 
This routine computes the smallest single precision value that can be represesnted
on the architecture it is ran on. This is otherwise known as the "machine epsilon".

**Input:** 
No input in this case.

**Output:** 
- `float` - the smallest value that can be represented by a single precision on
this architecture.

**Usage/Example:**

```c
#include <libscipute/smaceps.h>

main() {
    float maceps = smaceps();
    printf("Single Precision Machine Epsilon: %f", maceps);
    return 0;
}
```

**Implementation/Code:** The following is the code for `smaceps()`

**Last Modified:** October/2023
