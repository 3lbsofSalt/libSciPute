float maceps_single_precision() {
  float mac_eps = 1;

  while (mac_eps + 1 != 1) {
    mac_eps *= 0.5;
  }

  return mac_eps;
}

double maceps_double_precision() {
  double mac_eps = 1;

  while (mac_eps + 1 != 1) {
    mac_eps *= 0.5;
  }

  return mac_eps;
}

