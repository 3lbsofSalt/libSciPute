**Routine Name:**           dmaceps

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
    gcc -o maceps maceps.c
```

**Description/Purpose:** 
This routine computes the smallest double precision value that can be represesnted
on the architecture it is ran on. This is otherwise known as the "machine epsilon".

**Input:** 
No input in this case.

**Output:** 
- `double` - the smallest value that can be represented by a double precision 
variable on this architecture.

**Usage/Example:**

```c
#include <libscipute/dmaceps.h>

main() {
    float maceps = dmaceps();
    printf("Single Precision Machine Epsilon: %f", maceps);
    return 0;
}
```

**Implementation/Code:** The following is the code for `dmaceps()`

```c
double maceps_double_precision() {
  double mac_eps = 1;

  // The machine epsilon is the last value before addition overflows it into a 1
  // Therefore, the loop goes as long as this doesn't happen. If it does happen
  // in this case, the value doesn't need to be changed because the next value
  // has already been checked
  while ((mac_eps * 0.5) + 1 != 1) {
    mac_eps *= 0.5;
  }

  return mac_eps;
}
```

**Last Modified:** October/2023
