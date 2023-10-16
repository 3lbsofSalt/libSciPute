**Routine Name:**           linf_norm

**Author:** Max Ramsdell

**Language:** C
The code can be compiled using the GNU C compiler `gcc`

For example,

```
    gcc vector_norms.c
```

will produce an executable `./a.exe` than can be executed. If you want a different name, the following will work a bit
better

```
    gcc -o vector_norms vector_norms.c
```

**Description/Purpose:** 
This routine will calculate the L infinity norm of a vector.

**Input:** 
- `float vector[]` - The vector in question.
- `int v_size` - The size of the vector. Required for safe array usage in C.

**Output:** 
- `float` - the l infinity norm of the vector that was passed in

**Usage/Example:**

```c
#include <libscipute/vector_norms.h>

main() {
    float vector[] = { 3, 5, 7 };
    float linf = linf_norm(vector, 3);
    printf("L Infinity Norm: %f", l1);
    return 0;
}
```

**Implementation/Code:** The following is the code for `l1_norm()`

```c
float linf_norm(float vector[], int v_size) {
  float total = 0;
  // The l infinity norm of a vector is just the largest absolute value in the vector
  for(int i = 0; i < v_size; i++) {
    if(fabs(vector[i]) > total) {
      total = fabs(vector[i]);
    }
  }

  return total;
}
```

**Last Modified:** October/2023
