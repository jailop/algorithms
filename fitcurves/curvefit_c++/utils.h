#ifndef _UTILS_H
#define _UTILS_H 0

#if defined(__cplusplus)
extern "C" {
#endif

#define BUFSIZE 64

void read_x_y(double **x, double **y, int *n);
void clean_x_y(double **x, double **y);

#if defined(__cplusplus)
}
#endif

#endif /* _UTILS_H */
