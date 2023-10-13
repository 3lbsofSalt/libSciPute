#include "linreg.h"
#include <stdio.h>
#include <stdlib.h>

float* linreg(float vectorx[], float vectory[], int size) {
  float sumx = 0;
  float sumxx = 0;
  float sumy = 0;
  float sumxy = 0;

  for(int i = 0; i < size; i++) {
    sumx += vectorx[i];
    sumxx += vectorx[i] * vectorx[i];
    sumy += vectory[i];
    sumxy += vectorx[i] * vectory[i];
  }

  float m = (size * sumxy - sumx * sumy) / (size * sumxx - sumx * sumx);
  float b = (sumy - m * sumx) / size;

  float *values = malloc(2 * sizeof(float));
  values[0] = m;
  values[1] = b;

  return values;
}
