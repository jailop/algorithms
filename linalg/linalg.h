#ifndef _LINALG_H
#define _LINALG_H 1

#include <fstream>

#define GET(a, i, j) ((a).data_[(i) * ((a).cols_) + (j)])

const int TYPE_SIZE = sizeof(double);

enum {
    SUM = 1,
    DIFF,
    PROD,
    DIV
};

class Block {
    public:
        Block();
        Block(int size);
        Block(const Block& b);
        ~Block();
        int size() { return size_; }
        double* data() { return data_; }
        void operateScalar(double value, int op);
        void operateBlock(Block& b, int op);
        void assign(Block& b);
        void setAll(double value);
        bool isEqual(Block& m);
    protected:
        int size_;
        double* data_;
};

class Vector;

class Matrix : public Block {
    public:
        Matrix();
        Matrix(const Matrix& m);
        Matrix(int rows, int cols);
        Matrix(std::initializer_list<std::initializer_list<double>> list);
        Matrix(const char *filename);
        Matrix& operator=(Matrix m);
        Matrix& operator=(std::initializer_list<std::initializer_list<double>> list);
        Matrix operator+(double value);
        Matrix operator-(double value);
        Matrix operator*(double value);
        Matrix operator/(double value);
        Matrix& operator+=(double value);
        Matrix& operator-=(double value);
        Matrix& operator*=(double value);
        Matrix& operator/=(double value);
        bool operator==(Matrix m);
        bool operator!=(Matrix m);
        Matrix operator+(Matrix &m);
        Matrix& operator+=(Matrix &m);
        Matrix operator-(Matrix &m);
        Matrix& operator-=(Matrix &m);
        Matrix operator*(Matrix &m);
        Matrix t();
        const double& operator()(int row, int col) const;
        double& operator()(int row, int col);
        void read(std::ifstream& ifs);
        void write(std::ofstream& ofs);
        void writetxt(std::ofstream& ofs);
        void fread(const char *filename);
        void fwrite(const char *filename);
        int rows() { return rows_; }
        int cols() { return cols_; }
        friend std::ostream& operator<<(std::ostream& os, Matrix& m);
    private:
        int rows_;
        int cols_;
        friend class Vector;
};

class Vector : public Block {
    public:
        Vector();
        Vector(const Vector& m);
        Vector(int size_);
        Vector(std::initializer_list<double> list);
        Vector(const char *filename);
        Vector& operator=(Vector m);
        Vector& operator=(std::initializer_list<double> list);
        Vector& operator=(double value);
        Vector operator+(double value);
        Vector operator-(double value);
        Vector operator*(double value);
        Vector operator/(double value);
        Vector& operator+=(double value);
        Vector& operator-=(double value);
        Vector& operator*=(double value);
        Vector& operator/=(double value);
        bool operator==(Vector m);
        bool operator!=(Vector m);
        Vector operator+(Vector &m);
        Vector& operator+=(Vector &m);
        Vector operator-(Vector &m);
        Vector& operator-=(Vector &m);
        double operator*(Vector &m);
        Vector t();
        const double& operator()(int index) const;
        double& operator()(int index);
        void read(std::ifstream& ifs);
        void write(std::ofstream& ofs);
        void fread(const char *filename);
        void fwrite(const char *filename);
        friend std::ostream& operator<<(std::ostream& os, Vector& m);
    private:
        bool coltype_;
};

#endif // _LINALG_H
