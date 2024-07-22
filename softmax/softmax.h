#ifndef _SOFTMAX_H_
#define _SOFTMAX_H_ 1

/**
 * @brief Softmax function
 * @param y Output vector
 * @param x Input vector
 * @param n Size of the input vector
 */
void softmax(double *y, double *x, int n);

/**
 * @brief Derivative of the softmax function
 * @param y Output matrix (n x n)
 * @param x Input vector
 * @param n Size of the input vector
 */
void derivative_softmax(double *y, double *x, int n);

#endif /* _SOFTMAX_H_ */
