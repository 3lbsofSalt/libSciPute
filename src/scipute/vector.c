#include "vector.h"
#include <math.h>
#include <stdio.h>

void copyVectors(double* from, double* to, int size) {
  for(int j = 0; j < size; j++) {
    to[j] = from[j];
  }
}

// Assumes two vectors of the same size
double dotProduct(double* vec1, double* vec2, int size) {
  double total = 0;

  for(int i = 0; i < size; i++) {
    total += vec1[i] * vec2[i];
  }

  return total;
}

void normalize(double* vec, int size) {
  double mag = magnitude(vec, size);
  for(int i = 0; i < size; i++) {
    vec[i] = vec[i] / mag;
  }
}

double magnitude(double* vec, int size) {
  return sqrt(dotProduct(vec, vec, size));
}

void printVector(double* vec, int size, char* msg) {
  for(int i = 0; i < size; i++) {
    printf("%s: %f\n", msg, vec[i]);
  }
}
