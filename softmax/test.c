#include <stdio.h>
#include "softmax.h"

#define N 4

int main() {
  double x[N] = {1.0, 2.0, 3.0, 4.0};
  double y[N]; // softmax output
  double dy[N * N]; // derivative of softmax output
  // compute softmax
  softmax(y, x, N);
  // print softmax output
  printf("Softmax:\n");
  for (int i = 0; i < N; i++)
    printf("%10f = %10f\n", x[i], y[i]);
  printf("Derivative:\n");
  // compute derivative of softmax
  derivative_softmax(dy, y, N);
  // print derivative of softmax output
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++)
      printf("%10f ", dy[i * N + j]);
    printf("\n");
  }
  return 0;
}
