/**
 * Randomly permuted numbers
 *
 * This program randomly permutes a list of N sequential numbers.
 * It is based on the Fisher-Yates shuffle algorithm.
 *
 * (2021) Jaime Lopez <jailop AT thunix DOT net>
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <gsl/gsl_rng.h>

/**
 *  Return a vector of N indixes randomly permuted.
 *
 *  @param size
 *
 *  The memory of the returned vector must be freed.
 */
int *shuffled_indexes(int N, int seed) { 
    int i;
    int r, v;
    int *x = malloc(sizeof(int) * N);

    /* Random number generator allocation */
    gsl_rng *rndgen = gsl_rng_alloc(gsl_rng_taus);
    gsl_rng_set(rndgen, seed);
    
    /* Vector initialization */
    for (i = 0; i < N; i++)
        x[i] = i;
    
    /* Shuffling algorithm */
    for (i = N - 1; i > 0; i--) {
        r = gsl_rng_get(rndgen) % i;
        v = x[r];
        x[r] = x[i];
        x[i] = v;
    }
    
    /* Cleanning */
    gsl_rng_free(rndgen);
    return x;
}

void generate(int size, int seed) {
    int i;
    /* Getting the randomly permuted indexes */
    int *vec = shuffled_indexes((int) size, seed);
    /* Printing values */
    for (i = 0; i < size; i++) {
        fprintf(stdout, "%d\n", vec[i]);
    }
    /* Cleanning */
    free(vec);
}

int main(int argc, char **argv) {
    int seed = 1;
    int size = 10;
    int c;

    struct option long_options[] = {
        {"help",     no_argument,       0, 1},
        {"size",     required_argument, 0, 2},
        {"seed",     required_argument, 0, 3},
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
                       "  --help      : this help\n"
                       "  --size SIZE : default 10\n"
                       "  --seed SEED : random generator setting\n");
                exit(EXIT_SUCCESS);
            case 2:
                size = atoi(optarg);
                break;
            case 3:
                seed = atoi(optarg);
                break;
        }
    }
    generate(size, seed);
    return 0;
}
