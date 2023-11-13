#ifndef LIB_SCI_PUTE_ROOT_FINDING
#define LIB_SCI_PUTE_ROOT_FINDING

#include "types.h"

int bisection(mathFunc func, double startVal, double endVal, double tol, double* result);
int newtons(mathFunc func, double initial, double tol, int maxIter, double* result);
int secant(mathFunc func, double startVal, double endVal, double tol, int maxIter, double* result);
int hybrid_bisect_secant(mathFunc func, double startVal, double endVal, double tol, int maxIter, double* result);

#endif
