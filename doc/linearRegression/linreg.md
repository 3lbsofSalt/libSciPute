**Routine Name:**           linreg

**Author:** Max Ramsdell

**Language:** C
The code can be compiled using the GNU C compiler `gcc`

For example,

```
    gcc linreg.c
```

will produce an executable `./a.exe` than can be executed. If you want a different name, the following will work a bit
better

```
    gcc -o linreg linreg.c
```

**Description/Purpose:** 
This routine will calculate the L Infinity distance between two vectors of the same size.

**Input:** 
- `float vectorx[]` - A vector representing all of the x values on a graph
- `float vectory[]` - A vector with the corresponding y values of the graph
Note that vectorx and vectory should have a relationship such that a tuple is
formed between every value in the same index representing a point on a graph,
e.g.: (vectorx[1], vectory[1]) is a valid point, (vectorx[1], vectory[2]) is not.
- `int v_size` - The size of the vectors. Both vectors must be the same size.

**Output:** 
- `float` - an array where the first value is the slope "m" and the second one
is the y-intercept "b". This array must be `free()`ed after use.

**Usage/Example:**

```c
#include <libscipute/vector_norms.h>

main() {
    float vector[] = { 3, 5, 7 };
    float vector2[] = { 4, 6, 8 };
    float* linreg = linreg(vector, vector2, 3);
    printf("Slope (m): %f", linreg[0]);
    printf("Intercept (b): %f", linreg[1]);
    return 0;
}
```

**Implementation/Code:** The following is the code for `linreg()`

```c
float* linreg(float vectorx[], float vectory[], int size) {
  // Initialize some values
  float sumx = 0;
  float sumxx = 0;
  float sumy = 0;
  float sumxy = 0;

  // Calculated the values
  for(int i = 0; i < size; i++) {
    sumx += vectorx[i];
    sumxx += vectorx[i] * vectorx[i];
    sumy += vectory[i];
    sumxy += vectorx[i] * vectory[i];
  }

  // Use the linear regression equations to calculate the slope and intercept
  float m = (size * sumxy - sumx * sumy) / (size * sumxx - sumx * sumx);
  float b = (sumy - m * sumx) / size;

  // allocate an array to pass back
  float *values = malloc(2 * sizeof(float));
  values[0] = m;
  values[1] = b;

  return values;
}
```

**Last Modified:** October/2023
