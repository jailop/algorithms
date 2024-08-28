// To generate gaussian noised values of
// the function sin(2 * PI * x)
// for 0 <= x <= 1
//
// Arguments:
//   -m MEAN
//   -d STANDARD_DEVIATION
//   -n NUMBER_OF_SAMPLES

#include <iostream>
#include <random>
#include <cmath>
#include "getopt.h"

const double PI = std::acos(-1);

int main(int argc, char** argv)
{
    double mean, stddev;
    int n_samples;
    double x, y, y_noised;
    std::random_device rd;
    std::mt19937 gen(rd());
    options(argc, argv, &mean, &stddev, &n_samples);
    std::normal_distribution<> d(mean, stddev);
    for (int i = 0; i < n_samples; i++) {
        x = i * 1.0 / (n_samples - 1);
        y = std::sin(2 * PI * x);
        y_noised = y + d(gen);
        std::cout << x << '\t' << y_noised << std::endl;
    }
}
