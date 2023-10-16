float maceps_single_precision() {
  float mac_eps = 1;

  // Check the next value, if the next value overflows,
  // then the current value is the correct machine epsilon
  while ((mac_eps * 0.5) + 1 != 1) {
    mac_eps *= 0.5;
  }

  return mac_eps;
}

double maceps_double_precision() {
  double mac_eps = 1;

  // Check the next value, if the next value overflows,
  // then the current value is the correct machine epsilon
  while ((mac_eps * 0.5) + 1 != 1) {
    mac_eps *= 0.5;
  }

  return mac_eps;
}

