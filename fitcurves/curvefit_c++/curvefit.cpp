#include <iostream>
#include <armadillo>

int main(int argc, char **argv)
{
    // Loading data
    arma::mat A;
    A.load("data.txt");
    // Generating training and test datasets
    int n = A.n_rows;
    arma::uvec p = arma::randperm(n);
    int train_size = int(n * 0.8);
    int test_size  = n = train_size;
    arma::uvec train_index = p.head(train_size);
    arma::uvec test_index  = p.tail(test_size);
    arma::mat train = A(train_index);
    arma::mat test = A(test_index);
    arma::vec x_train = train.col(0);
    arma::vec y_train = train.col(1);
    arma::vec x_test = test.col(0);
    arma::vec y_test = test.col(1);
    for (int i = 1; i < 10; i++) {
        arma::vec p = arma::polyfit(x_train, y_train, i);
        p.save("coef_" + std::to_string(i) + ".txt", arma::raw_ascii);
    }
}
