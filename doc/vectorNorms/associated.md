## Associated Routines with vector_norms.c

- Subtract Vector:

**Description/Purpose:** 
This routine reduces every value of the first vector by the second vector.
Note that it does not change either of the vectors that were passed in,
but creates a new vector that must be `free()`ed when the use has been finished.

**Input:** 
- `float vector1[]` - The first vector
- `float vector2[]` - The second vector
- `int v_size` - The size of the vectors. Both vectors must be the same size.

**Output:** 
- `float *` - the new vector created by subtracting vector2 from vector1.

**Implementation**
```c
float *subtract_vector(float vector1[], float vector2[], int sizes) {
  float *new_vec = malloc(sizes * sizeof(float));

  for(int i = 0; i < sizes; i++) {
    new_vec[i] = vector1[i] - vector2[i];
  }

  return new_vec;

}
```
