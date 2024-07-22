#include "linalg.h"

Vector Vector::operator+(double value) {
    Vector m(*this);
    m.operateScalar(value, SUM);
    return m;
}

Vector Vector::operator-(double value) {
    Vector m(*this);
    m.operateScalar(value, DIFF);
    return m;
}

Vector Vector::operator*(double value) {
    Vector m(*this);
    m.operateScalar(value, PROD);
    return m;
}

Vector Vector::operator/(double value) {
    Vector m(*this);
    m.operateScalar(value, DIV);
    return m;
}

Vector& Vector::operator+=(double value) {
    operateScalar(value, SUM);
    return *this;
}

Vector& Vector::operator-=(double value) {
    operateScalar(value, DIFF);
    return *this;
}

Vector& Vector::operator*=(double value) {
    operateScalar(value, PROD);
    return *this;
}

Vector& Vector::operator/=(double value) {
    operateScalar(value, DIV);
    return *this;
}

Vector Vector::operator+(Vector &m) {
    Vector n(*this);
    n.operateBlock(m, SUM);
    return n;
}

Vector Vector::operator-(Vector &m) {
    Vector n(*this);
    n.operateBlock(m, DIFF);
    return n;
}

Vector& Vector::operator+=(Vector &m) {
    operateBlock(m, SUM);
    return *this;
}

Vector& Vector::operator-=(Vector &m) {
    operateBlock(m, DIFF);
    return *this;
}

Vector::Vector() : Block() {
    coltype_ = true;
}

Vector::Vector(int size) : Block(size) {
    coltype_ = true;
}

Vector::Vector(const Vector& m) : Block(m) {
    coltype_ = m.coltype_;
}

Vector::Vector(std::initializer_list<double> list) 
    : Vector(list.size()) {
    *this = list;
}

Vector& Vector::operator=(Vector m) {
    if (this == &m)
        return *this;
    coltype_ = m.coltype_;
    assign(m);
    return *this;
}

Vector& Vector::operator=(std::initializer_list<double> list) {
    int size_new = list.size();
    if (size_ != size_new) {
        if (data_ != nullptr)
            delete[] data_;
        data_ = new double[size_new];
    }
    size_ = size_new;
    int i = 0;
    for (double value : list)
        data_[i++] = value;
    return *this;
}

bool Vector::operator==(Vector x) {
    if (coltype_ != x.coltype_)
        return false;
    return isEqual(x);
}

bool Vector::operator!=(Vector m) {
    return !(*this == m);
}

const double& Vector::operator()(int index) const {
    return data_[index];
}

double& Vector::operator()(int index) {
    return data_[index];
}

void Vector::write(std::ofstream& ofs) {
    Matrix m;
    if (coltype_) {
        m.cols_ = 1;
        m.rows_ = this->size_;
    }
    else {
        m.rows_ = 1;
        m.cols_ = this->size_;
    }
    m.size_ = this->size_;
    m.data_ = this->data_;
    m.write(ofs);
    m.data_ = nullptr;

}

Vector Vector::t() {
    Vector x(*this);
    x.coltype_ = !(this->coltype_);
    return x;
}


double Vector::operator*(Vector& x) {
    double sum = 0;
    for (int i = 0; i < size_; i++)
        sum += data_[i] * x.data_[i];
    return sum;
}
