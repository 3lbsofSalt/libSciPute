**Routine Name:**           l1_distance

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
This routine will calculate the L1 distance between two vectors of the same size.

**Input:** 
- `float vector1[]` - The first vector
- `float vector2[]` - The second vector
- `int v_size` - The size of the vectors. Both vectors must be the same size.

**Output:** 
- `float` - the l1 distance of the vectors that were passed in

**Usage/Example:**

```c
#include <libscipute/vector_norms.h>

main() {
    float vector[] = { 3, 5, 7 };
    float vector2[] = { 4, 6, 8 };
    float l1 = l1_distance(vector, vector2, 3);
    printf("L1 Distance: %f", l1);
    return 0;
}
```

**Implementation/Code:** The following is the code for `l1_norm()`

```c
float l1_distance(float vector1[], float vector2[], int sizes) {
  // Get the difference betwee the vectors.
  float *new_vec = subtract_vector(vector1, vector2, sizes);
  // Calculate the norm of the distance
  float size = l1_norm(new_vec, sizes);
  free(new_vec);
  return size;
}
```

**Last Modified:** October/2023
