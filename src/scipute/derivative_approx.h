#ifndef LIB_SCI_PUTE_DERIV_APPROX
#define LIB_SCI_PUTE_DERIV_APPROX

typedef double (*mathFunc) (double val);

double forwardDifference(double val, double h, mathFunc func);
double backwardDifference(double val, double h, mathFunc func);
double centralDifference(double val, double h, mathFunc func);

#endif
