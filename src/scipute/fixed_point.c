#include "fixed_point.h"
#include "derivative_approx.h"
#include <math.h>
#include <stdio.h>

int fixed_point(mathFunc func, double initVal, double tol, int maxIter, double *result) {
  int funcMult = 0;

  if(fabs(1 + centralDifference(initVal, 0.001, func)) < 1) {
    funcMult = 1;
  } else if (fabs(1 - centralDifference(initVal, 0.001, func)) < 1) {
    funcMult = -1;
  } else {
    return -1;
  }

  int i = 0;

  while(fabs(func(initVal)) > tol) {
    initVal = initVal + funcMult * func(initVal);
    if(i++ >= maxIter) return -2;
  }

  *result = initVal;

  return 0;
}


/**
 * PLEASE NOTE THAT THIS FUNCTION WAS WRITTEN FOR ACADEMIC PURPOSES ONLY, YOU SHOULD NOT USE IT.
 */
int fixed_point_amplified(mathFunc func, double initVal, double tol, int maxIter, double *result) {
  if (fabs(1 - centralDifference(initVal, 0.000001, func)) >= 1) {
    return -1;
  }

  int i = 0;

  while(fabs(func(initVal)) > tol) {
    initVal = initVal - func(initVal);
    if(i++ >= maxIter) return -2;
  }

  *result = initVal;

  return 0;
}
