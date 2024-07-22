#include <cstdlib>
#include <cstring>
#include "linalg.h"

Block::Block() : size_(0), data_(nullptr) {}

Block::Block(int size) : Block() {
    size_ = size;
    data_ = new double[size_];
}

Block::Block(const Block& b) : Block(b.size_) {
    memcpy(data_, b.data_, sizeof(double) * size_);
}

Block::~Block() {
    if (data_)
        delete[] data_;
}

void Block::setAll(double value) {
    for (int i = 0; i < size_; i++)
        data_[i] = value;
}

bool Block::isEqual(Block& m) {
    if (size_ != m.size_)
        return false;
    else if (memcmp(data_, m.data_, size_ * sizeof(double)) != 0)
        return false;
    return true;
}

void Block::assign(Block& b) {
    if (size_ != b.size_) {
        if (data_)
            delete[] data_;
        size_ = b.size_;
        data_ = new double[size_];
    }
    memcpy(data_, b.data_, size_ * TYPE_SIZE);
}

void Block::operateScalar(double value, int op) {
    for (int i = 0; i < size_; i++)
        switch (op) {
            case SUM:
                data_[i] += value;
                break;
            case DIFF:
                data_[i] -= value;
                break;
            case PROD:
                data_[i] *= value;
                break;
            case DIV:
                data_[i] /= value;
                break;
        }
}

void Block::operateBlock(Block& b, int op) {
    for (int i = 0; i < size_; i++)
        switch (op) {
            case SUM:
                data_[i] += b.data_[i];
                break;
            case DIFF:
                data_[i] -= b.data_[i];
                break;
            case PROD:
                data_[i] *= b.data_[i];
                break;
            case DIV:
                data_[i] /= b.data_[i];
                break;
        }
}
