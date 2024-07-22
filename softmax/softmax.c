#include <math.h>

void softmax(double *y, double *x, int n) {
  double sum = 0.0;
  // Compute the exponential values for each element.
  // Also find the sum of all these values.
  for (int i = 0; i < n; i++) {
    y[i] = exp(x[i]);
    sum += y[i];
  }
  // Divide each value by the sum.
  for (int i = 0; i < n; i++) {
    y[i] /= sum;
  }
}

void derivative_softmax(double *y, double *x, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (i == j) {
        y[i * n + j] = x[i] * (1 - x[i]);
        y[j * n + i] = y[i * n + j];
      } else {
        y[i * n + j] = -x[i] * x[j];
        y[j * n + i] = y[i * n + j];
      }
    }
  }
}
