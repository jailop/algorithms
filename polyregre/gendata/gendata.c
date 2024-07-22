/* Data generator
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_randist.h>

/**
 * In this case the function is defined as a macro
 */
#define f(x) (sin(2 * M_PI * (x)))

/** 
 * Generates (x, y) noised values for the given function
 *
 * The interval and the number of examples is required.
 * The sigma argument indicates the variance for a gaussian
 * random number generator.
 *
 */
void generate(double start, double end, int n, double sigma, int seed) {
    double x, y;
    double step = (end - start) / n;
    gsl_rng *r = gsl_rng_alloc(gsl_rng_taus);
    gsl_rng_set(r, seed);

    for (x = start; x <= end; x += step) {
        y = f(x) + gsl_ran_gaussian(r, sigma);
        printf("%g\t%g\n", x, y); 
    }
    gsl_rng_free(r);
}

int main(int argc, char **argv) {
    double start = 0.0;
    double end = 1.0;
    int n = 100;
    double sigma = 0.1;
    int seed = 1;
    
    int c;

    struct option long_options[] = {
        {"help",     no_argument,       0, 1},
        {"start",    required_argument, 0, 2},
        {"end",      required_argument, 0, 3},
        {"examples", required_argument, 0, 4},
        {"sigma",    required_argument, 0, 5},
        {"seed",     required_argument, 0, 6},
        {0,          0,                 0, 0}

    };

    while (1) {
        int option_index = 0;
        
        c = getopt_long(argc, argv, "", long_options, &option_index);
        
        if (c == -1)
            break;
        
        switch (c) {
            case 1:
                printf("Options:\n"
                       "  --help              : this help\n"
                       "  --start START_VALUE : default 0.0\n"
                       "  --end   END_VALUE   : default 1.0\n"
                       "  --examples NUM      : nummber of examples\n"
                       "                        default 100\n"
                       "  --sigma STD_VALUE   : standard deviation\n"
                       "  --seed SEED         : random generator setting\n"
                       "                        default 0.1\n");
                exit(EXIT_SUCCESS);
            case 2:
                start = atof(optarg);
                break;
            case 3:
                end = atof(optarg);
                break;
            case 4:
                n = atoi(optarg);
                break;
            case 5:
                sigma = atof(optarg);
                break;
            case 6:
                seed = atoi(optarg);
                break;
        }
    }

    generate(start, end, n, sigma, seed);

    return 0;
}
