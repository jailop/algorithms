#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void read_x_y(double **x, double **y, int *n)
{
    double x_val, y_val;
    double *aux;
    int i = 0;
    *n = BUFSIZE;
    *x = malloc(sizeof(double) * BUFSIZE);
    *y = malloc(sizeof(double) * BUFSIZE);
    while (fscanf(stdin, "%lf\t%lf\n", &x_val, &y_val) != EOF) {
        if (i == *n) {
            *n *= 2;
           aux = realloc(*x, sizeof(double) * *n);
           *x = aux;
           aux = realloc(*y, sizeof(double) * *n);
           *y = aux;
        }
        *x[i] = x_val;
        *y[i] = y_val;
        i++;
    }
    *n = i;
}

void clean_x_y(double **x, double **y)
{
    free(*x);
    free(*y);
}
