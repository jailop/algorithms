#include "linalg.h"

Matrix::Matrix() : Block(), rows_(0), cols_(0) {
}

Matrix::Matrix(int rows, int cols) 
    : Block(rows * cols), rows_(rows), cols_(cols) {
}

Matrix::Matrix(const Matrix& m) 
    : Block(m), rows_(m.rows_), cols_(m.cols_) {
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> list) 
    : Matrix() {
    *this = list;
}

Matrix::Matrix(const char *filename) : Block() {
    fread(filename);
}

Matrix& Matrix::operator=(Matrix m) {
    if (this == &m)
        return *this;
    rows_ = m.rows_;
    cols_ = m.cols_;
    assign(m);
    return *this;
}


Matrix& Matrix::operator=(std::initializer_list<std::initializer_list<double>> list) {
    rows_ = list.size();
    cols_ = list.begin()->size();
    int size_new = rows_ * cols_;
    if (size_ != size_new) {
        if (data_ != nullptr)
            delete[] data_;
        data_ = new double[size_new];
    }
    size_ = size_new;
    int i = 0;
    for (std::initializer_list<double> row : list)
        for (double value : row)
            data_[i++] = value;
    return *this;
}

bool Matrix::operator==(Matrix m) {
    if (rows_ != m.rows_)
        return false;
    if (cols_ != m.cols_)
        return false;
    return isEqual(m);
}

bool Matrix::operator!=(Matrix m) {
    return !(*this == m);
}

const double& Matrix::operator()(int row, int col) const {
    return GET(*this, row, col);
}

double& Matrix::operator()(int row, int col) {
    return GET(*this, row, col);
}

Matrix Matrix::t() {
    Matrix m(*this);
    m.rows_ = cols_;
    m.cols_ = rows_;
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++) 
            GET(m, i, j) = GET(*this, j, i);
    return m;
}

Matrix Matrix::operator+(double value) {
    Matrix m(*this);
    m.operateScalar(value, SUM);
    return m;
}

Matrix Matrix::operator-(double value) {
    Matrix m(*this);
    m.operateScalar(value, DIFF);
    return m;
}

Matrix Matrix::operator*(double value) {
    Matrix m(*this);
    m.operateScalar(value, PROD);
    return m;
}

Matrix Matrix::operator/(double value) {
    Matrix m(*this);
    m.operateScalar(value, DIV);
    return m;
}

Matrix& Matrix::operator+=(double value) {
    operateScalar(value, SUM);
    return *this;
}

Matrix& Matrix::operator-=(double value) {
    operateScalar(value, DIFF);
    return *this;
}

Matrix& Matrix::operator*=(double value) {
    operateScalar(value, PROD);
    return *this;
}

Matrix& Matrix::operator/=(double value) {
    operateScalar(value, DIV);
    return *this;
}

Matrix Matrix::operator+(Matrix &m) {
    Matrix n(*this);
    n.operateBlock(m, SUM);
    return n;
}

Matrix Matrix::operator-(Matrix &m) {
    Matrix n(*this);
    n.operateBlock(m, DIFF);
    return n;
}

Matrix& Matrix::operator+=(Matrix &m) {
    operateBlock(m, SUM);
    return *this;
}

Matrix& Matrix::operator-=(Matrix &m) {
    operateBlock(m, DIFF);
    return *this;
}

Matrix Matrix::operator*(Matrix& m) {
    double sum;
    Matrix n(rows_, m.cols_);
    for (int i = 0; i < n.rows_; i++)
        for (int j = 0; j < n.cols_; j++) {
            sum = 0;
            for (int k = 0; k < cols_; k++)
                sum += GET(*this, i, k) * GET(m, k, j);
            GET(n, i, j) = sum;
        }
    return n;
}
