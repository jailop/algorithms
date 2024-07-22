#include <iostream>
#include "linalg.h"

using namespace std;

void Vector::read(ifstream& ifs) {
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
    m.read(ifs);
    m.data_ = nullptr;

}

ostream& operator<<(ostream& os, Vector& m) {
    for (int i = 0; i < m.size(); i++) {
        cout << m(i);
        cout << (i < m.size() - 1 ? ' ' : '\n');
    }
    return os;
}
