#include "derivative_approx.h"

double forwardDifference(double val, double h, mathFunc func) {
  return (func(val + h) - func(val)) / h;
}

double backwardDifference(double val, double h, mathFunc func) {
  return (func(val) - func(val - h)) / h;
}

double centralDifference(double val, double h, mathFunc func) {
  double init = func(val + h) - func(val - h);
  return (init / (2 * h));
}
