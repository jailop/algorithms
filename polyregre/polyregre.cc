#include <vector>
#include <algorithm>
#include <gsl/gsl_rng.h>

using namespace std;

class PolyRegre {
    public:
        PolyRegre() {};
        PolyRegre(int seed) : _seed(seed) {};
        void fit(vector<double> x, vector<double> y, int grade);
        vector<double> predict(vector<double> x);
    private:
        double compute(double& x);
        int _seed;
        vector<double> _w;
};

vector<double> diff(vector<double> a, vector<double> b) {
    vector<double> c(a.size());
    for (int i = 0; i < a.size(); i++)
        c[i] = a[i] - b[i];
    return c;
}

void PolyRegre::fit(vector<double> x, vector<double> y, int grade) {
    _w = vector<double>(grade + 1);
    gsl_rng *r = gsl_rng_alloc(gsl_rng_taus);
    gsl_rng_set(r, _seed);
    int rng_max = gsl_rng_max(r);
    for (int i = 0; i < grade + 1; i++)
        _w[i] = gsl_rng_get(r) * 1.0 / rng_max;
    vector<double> delta = diff(predict(x), y); 
    /* I am here ... */
}

double PolyRegre::compute(double& x) {
    double prod = 1;
    double accum = 0;
    for (double w : PolyRegre::_w) {
        accum = prod * w;
        prod *= x;
    }
    return accum;
}

vector<double> PolyRegre::predict(vector<double> x) {
    vector<double> y(x.size()); 
    for (int i = 0; i < x.size(); i++)
        y[i] = compute(x[i]);
    return y;
}

int main() {
    return 0;
}
