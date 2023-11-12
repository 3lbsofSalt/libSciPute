#ifndef LIB_SCI_PUTE_ROOT_FINDING
#define LIB_SCI_PUTE_ROOT_FINDING

#include "types.h"

int fixed_point(mathFunc func, double initVal, double tol, int maxIter, double* result);
int fixed_point_amplified(mathFunc func, double initVal, double tol, int maxIter, double* result);

#endif
