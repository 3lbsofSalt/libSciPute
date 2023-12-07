#include "vector_norms.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double *subtract_vector(double vector1[], double vector2[], int sizes) {
  double *new_vec = malloc(sizes * sizeof(double));

  for(int i = 0; i < sizes; i++) {
    new_vec[i] = vector1[i] - vector2[i];
  }

  return new_vec;

}

double l2_norm(double vector[], int v_size) {
  double total = 0.0;
  for(int i = 0; i < v_size; i++) {
    total = total + (vector[i] * vector[i]);
  }

  return sqrtf(total);
}

double l2_distance(double vector1[], double vector2[], int sizes) {
  double *new_vec = subtract_vector(vector1, vector2, sizes);
  double size = l2_norm(new_vec, sizes);
  free(new_vec);
  return size;
}

double l1_norm(double vector[], int v_size) {

  double total = 0.0;
  for(int i = 0; i < v_size; i++) {
    total = total + fabs(vector[i]);
  }

  return total;
}

double l1_distance(double vector1[], double vector2[], int sizes) {
  double *new_vec = subtract_vector(vector1, vector2, sizes);
  double size = l1_norm(new_vec, sizes);
  free(new_vec);
  return size;
}

double linf_norm(double vector[], int v_size) {
  double total = 0;
  for(int i = 0; i < v_size; i++) {
    if(fabs(vector[i]) > total) {
      total = fabs(vector[i]);
    }
  }

  return total;
}

double linf_distance(double vector1[], double vector2[], int sizes) {
  double *new_vec = subtract_vector(vector1, vector2, sizes);
  double size = linf_norm(new_vec, sizes);
  free(new_vec);
  return size;
}
