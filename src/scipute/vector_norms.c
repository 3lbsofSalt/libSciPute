#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float *subtract_vector(float vector1[], float vector2[], int sizes) {
  float *new_vec = malloc(sizes * sizeof(float));

  for(int i = 0; i < sizes; i++) {
    new_vec[i] = vector1[i] - vector2[i];
  }

  return new_vec;

}

float two_norm(float vector[], int v_size) {
  float total = 0.0;
  for(int i = 0; i < v_size; i++) {
    total = total + (vector[i] * vector[i]);
  }

  return sqrtf(total);
}

float two_norm_distance(float vector1[], float vector2[], int sizes) {
  float *new_vec = subtract_vector(vector1, vector2, sizes);
  float size = two_norm(new_vec, sizes);
  free(new_vec);
  return size;
}

float one_norm(float vector[], int v_size) {

  float total = 0.0;
  for(int i = 0; i < v_size; i++) {
    total = total + fabs(vector[i]);
  }

  return total;
}

float one_norm_distance(float vector1[], float vector2[], int sizes) {
  float *new_vec = subtract_vector(vector1, vector2, sizes);
  float size = one_norm(new_vec, sizes);
  free(new_vec);
  return size;
}

float infty_norm(float vector[], int v_size) {
  float total = 0;
  for(int i = 0; i < v_size; i++) {
    if(fabs(vector[i]) > total) {
      total = fabs(vector[i]);
    }
  }

  return total;
}

float infty_norm_distance(float vector1[], float vector2[], int sizes) {
  float *new_vec = subtract_vector(vector1, vector2, sizes);
  float size = infty_norm(new_vec, sizes);
  free(new_vec);
  return size;
}
