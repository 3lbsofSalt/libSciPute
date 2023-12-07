#ifndef LIB_SCI_PUTE_FIXED_POINT
#define LIB_SCI_PUTE_FIXED_POINT

#include "types.h"

int fixed_point(mathFunc func, double initVal, double tol, int maxIter, double* result);
int fixed_point_amplified(mathFunc func, double initVal, double tol, int maxIter, double* result);

#endif
