#ifndef LIB_SCI_PUTE_DERIV_APPROX
#define LIB_SCI_PUTE_DERIV_APPROX

#include "types.h"

double forwardDifference(double val, double h, mathFunc func);
double backwardDifference(double val, double h, mathFunc func);
double centralDifference(double val, double h, mathFunc func);

#endif
