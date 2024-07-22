#include <iostream>
#include "linalg.h"

void Matrix::read(std::ifstream& ifs) {
    ifs.read(reinterpret_cast<char *>(&rows_), sizeof(int));
    ifs.read(reinterpret_cast<char *>(&cols_), sizeof(int));
    int size__new = rows_ * cols_;
    if (size_ != size__new) {
        if (data_ != nullptr)
            free(data_);
        data_ = static_cast<double*>(malloc(sizeof(double) * size__new));
    }
    size_ = size__new;
    ifs.read(reinterpret_cast<char *>(data_), size_ * sizeof(double));
}

void Matrix::fread(const char *filename) {
    std::ifstream ifs(filename, std::ios::binary);
    read(ifs);
    ifs.close();
}

void Matrix::fwrite(const char *filename) {
    std::ofstream ofs(filename, std::ios::out);
    writetxt(ofs);
    ofs.close();
}

void Matrix::write(std::ofstream& ofs) {
    ofs.write(reinterpret_cast<char *>(&rows_), sizeof(int));
    ofs.write(reinterpret_cast<char *>(&cols_), sizeof(int));
    ofs.write(reinterpret_cast<char *>(data_), size_ * sizeof(double));
}

void Matrix::writetxt(std::ofstream& ofs) {
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++) {
            ofs << GET(*this, i, j);
            ofs << (j < cols_ - 1 ? ' ' : '\n');
        }
}

std::ostream& operator<<(std::ostream& os, Matrix& m) {
    for (int i = 0; i < m.rows(); i++) {
        for (int j = 0; j < m.cols(); j++) {
            std::cout << m(i, j);
            if (j < m.cols() - 1)
                std::cout << ' ';
        }
        std::cout << std::endl;
    }
    return os;
}
