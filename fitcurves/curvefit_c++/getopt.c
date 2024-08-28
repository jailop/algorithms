#include <stdlib.h>
#include <unistd.h>

void options(int argc, char** argv, double *mean, double *stddev, int *n_samples)
{
    int opt;
    *mean = 0.0;
    *stddev = 1.0;
    *n_samples = 10;
    while ((opt = getopt(argc, argv, "m:d:n:")) != -1) {
        switch (opt) {
            case 'm':
                *mean = atof(optarg);
                break;
            case 'd':
                *stddev = atof(optarg);
                break;
            case 'n':
                *n_samples = atoi(optarg);
                break;
        }
    }
}
