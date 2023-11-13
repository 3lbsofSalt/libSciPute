#include "root_finding.h"
#include "scipute/types.h"
#include "maceps.h"
#include "derivative_approx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int bisection(mathFunc func, double startVal, double endVal, double tol, double* result) {

  *result = 0;

  double calculatedStart = func(startVal);
  double calculatedEnd = func(endVal);

  // If the start value and end value have the same sign then there is not guaranteed to be a root between them.
  // Exit with  an error
  if((calculatedStart > 0 && calculatedEnd > 0) || (calculatedStart < 0 && calculatedEnd < 0)) {
    return -1;
  } 

  // Check if either value currently constitutes a root
  if(fabs(func(startVal)) <= tol) {
    *result = startVal;
    return 0;
  } else if(fabs(endVal) <= tol) {
    *result = endVal;
    return 0;
  }

  double mid = 0;
  double res = 0;

  while(fabs(endVal - startVal) > tol) {
    // Find the midpoint;
    mid = (endVal + startVal) / 2;
    // Evaluate it
    res = func(mid);

    // Check it
    if(fabs(res) < tol) {
      *result = mid;
      return 0;
    }

    // Set the midpoint as the correct value
    if((res < 0 && func(endVal) < 0) || (res > 0 && func(endVal) > 0)) {
      endVal = mid;
    } else {
      startVal = mid;
    }

  }

  // The values converged to be not as wide as the tolerance. This should probably
  // never happen 
  return -2;
}

int newtons(mathFunc func, double initial, double tol, int maxIter, double* result) {

  int i = 0;

  while(i++ < maxIter) {
    double y = func(initial);
    double yder = centralDifference(initial, 0.00001, func);

    if(fabs(yder) < tol) {
      return -1;
    }

    double next_x = initial - y / yder;

    if(fabs(next_x - initial) < tol) {
      return -3;
    }

    if(fabs(func(next_x)) < tol) {
      *result = next_x;
      return 0;
    }

    initial = next_x;

  }

  return -2;
}

int secant(mathFunc func, double startVal, double endVal, double tol, int maxIter, double *result) {
  
  int i = 0;
  *result = 0;

  double new = 0;

  while (i++ <= maxIter) {
    new = endVal - func(endVal) * (endVal - startVal) / (func(endVal) - func(startVal));
    startVal = endVal;
    endVal = new;

    if(fabs(func(new)) <= tol) {
      *result = new;
      return 0;
    }

    if(fabs(startVal - endVal) < tol) {
      return -2;
    }
  }

  return -1;
}

int hybrid_bisect_secant(mathFunc func, double startVal, double endVal, double tol, int maxIter, double *result) {
  double calculatedStart = func(startVal);
  double calculatedEnd = func(endVal);

  if((calculatedStart > 0 && calculatedEnd > 0) || (calculatedStart < 0 && calculatedEnd < 0)) {
    return -1;
  } 

  if(fabs(func(startVal)) <= tol) {
    *result = startVal;
    return 0;
  } else if(fabs(endVal) <= tol) {
    *result = endVal;
    return 0;
  }

  double mid = 0;
  double res = 0;

  int error = 1;

  while(error) {
    for(int i = 0; i <= 4; i++) {
      mid = (endVal + startVal) / 2;

      res = func(mid);

      if(fabs(res) < tol) {
        *result = mid;
        return 0;
      }

      if((res < 0 && func(endVal) < 0) || (res > 0 && func(endVal) > 0)) {
        endVal = mid;
      } else {
        startVal = mid;
      }
    }

    // The next value for the secant will be within the range so we're going to try
    // the secant method. It is still possible for it to fail so we can still fall
    // back to the bisection method
    if((res > endVal && res < startVal) || (res < endVal && res > startVal)) {
      error = secant(func, startVal, endVal, tol, maxIter, result);
    }
  }
  return error;
}
