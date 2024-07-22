#include "linalg.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE matrix
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(MatrixConstructor)
{
    Matrix a;
    BOOST_CHECK_EQUAL(a.rows(), 0);
    BOOST_CHECK_EQUAL(a.cols(), 0);
    BOOST_CHECK(a.data() == nullptr);
    
    Matrix b(3, 4);
    BOOST_CHECK_EQUAL(b.rows(), 3);
    BOOST_CHECK_EQUAL(b.cols(), 4);
    BOOST_CHECK(b.data() != nullptr);
}

BOOST_AUTO_TEST_CASE(ValueAssignment)
{
    Matrix a(3, 3);
    a(0, 0) = 1;
    BOOST_CHECK_EQUAL(*a.data(), 1);
}

BOOST_AUTO_TEST_CASE(MatrixComparison) 
{
    Matrix a({{1, 2}, {3, 4}});
    Matrix b = {{1, 2}, {3, 4}};
    BOOST_CHECK(a == b);
    b(0, 0) = 0;
    BOOST_CHECK(a != b);
}

BOOST_AUTO_TEST_CASE(MatrixInitialization)
{
    Matrix a({{1, 2}, {3, 4}});
    BOOST_CHECK_EQUAL(a(1, 1), 4);
    Matrix b = {{1, 2}, {3, 4}};
    BOOST_CHECK_EQUAL(b(1, 0), 3);
    Matrix c;
    c = {{1, 2}, {3, 4}};
    BOOST_CHECK_EQUAL(c(0, 1), 2);
    Matrix d;
    d = c;
    BOOST_CHECK_EQUAL(d(0, 0), 1);
    Matrix e = d;
    BOOST_CHECK_EQUAL(e(1, 1), 4);
    e(0, 0) = 10;
    BOOST_CHECK_EQUAL(e(0, 0), 10);
}

BOOST_AUTO_TEST_CASE(MatrixFilesOps)
{
    Matrix a({{1, 2}, {3, 4}});
    a.fwrite("test.dat");
    Matrix b;
    b.fread("test.dat");
    // BOOST_CHECK(a == b);
    Matrix c("test.dat");
    // BOOST_CHECK(a == c);
}

BOOST_AUTO_TEST_CASE(MatrixTranspose)
{
    Matrix a({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix b = a.t();
    Matrix c = b.t();
    BOOST_CHECK(a == c);
}

BOOST_AUTO_TEST_CASE(MatrixScalarArithmetics)
{
    Matrix a({{1, 2}, {3, 4}});
    Matrix b = a + 1.0;
    BOOST_CHECK_EQUAL(b(0, 0), 2);
    b = a - 1.0;
    BOOST_CHECK_EQUAL(b(0, 1), 1);
    b = a * 2;
    BOOST_CHECK_EQUAL(b(1, 0), 6);
    b = a / 2;
    BOOST_CHECK_EQUAL(b(1, 1), 2);
    a += 2;
    BOOST_CHECK_EQUAL(a(0, 0), 3);
    a -= 3;
    BOOST_CHECK_EQUAL(a(0, 1), 1);
    a *= 2;
    BOOST_CHECK_EQUAL(a(1, 0), 4);
    a /= 2;
    BOOST_CHECK_EQUAL(a(1, 1), 3);
}

BOOST_AUTO_TEST_CASE(MatrixMatrixArithmetics)
{
    Matrix a{{1, 2}, {-1, 4}};
    Matrix b{{2, 2}, {1, -1}};
    Matrix c = a + b;
    BOOST_CHECK(c == Matrix({{3, 4}, {0, 3}}));
    c = a - b;
    BOOST_CHECK(c == Matrix({{-1, 0}, {-2, 5}}));
    a += b;
    BOOST_CHECK(a == Matrix({{3, 4}, {0, 3}}));
    a -= b;
    BOOST_CHECK(a == Matrix({{1, 2}, {-1, 4}}));
}

BOOST_AUTO_TEST_CASE(MatrixProduct)
{
    Matrix a{{1, 2}, {-1, 4}};
    Matrix b{{2, 2, -1}, {1, -1, 2}};
    Matrix c = a * b;
    BOOST_CHECK(c == Matrix({{4, 0, 3}, {2, -6, 9}}));
}

BOOST_AUTO_TEST_CASE(VectorConstructor)
{
    Vector a;
    BOOST_CHECK_EQUAL(a.size(), 0);
    BOOST_CHECK(a.data() == nullptr);
    
    Vector b(3);
    BOOST_CHECK_EQUAL(b.size(), 3);
    BOOST_CHECK(b.data() != nullptr);
}

BOOST_AUTO_TEST_CASE(VectorValueAssignment)
{
    Vector a(3);
    a(0) = 1;
    BOOST_CHECK_EQUAL(*a.data(), 1);
}

BOOST_AUTO_TEST_CASE(VectorComparison) 
{
    Vector a({1, 2, 3, 4});
    Vector b = {1, 2, 3, 4};
    BOOST_CHECK(a == b);
    b(0) = 0;
    BOOST_CHECK(a != b);
}

BOOST_AUTO_TEST_CASE(VectorInitialization)
{
    Vector a({1, 2, 3, 4});
    BOOST_CHECK_EQUAL(a(3), 4);
    Vector b = {1, 2, 3, 4};
    BOOST_CHECK_EQUAL(b(2), 3);
    Vector c;
    c = {1, 2, 3, 4};
    BOOST_CHECK_EQUAL(c(1), 2);
    Vector d;
    d = b;
    BOOST_CHECK_EQUAL(d(0), 1);
    Vector e = d;
    BOOST_CHECK_EQUAL(e(3), 4);
    e(0) = 10;
    BOOST_CHECK_EQUAL(e(0), 10);
}

BOOST_AUTO_TEST_CASE(VectorTranspose)
{
    Vector a({1, 2, 3});
    Vector b = a.t();
    Vector c = b.t();
    BOOST_CHECK(a == c);
}

BOOST_AUTO_TEST_CASE(VectorScalarArithmetics)
{
    Vector a({1, 2, 3, 4});
    Vector b = a + 1.0;
    BOOST_CHECK_EQUAL(b(0), 2);
    b = a - 1;
    BOOST_CHECK_EQUAL(b(1), 1);
    b = a * 2;
    BOOST_CHECK_EQUAL(b(2), 6);
    b = a / 2;
    BOOST_CHECK_EQUAL(b(3), 2);
    a += 2;
    BOOST_CHECK_EQUAL(a(0), 3);
    a -= 3;
    BOOST_CHECK_EQUAL(a(1), 1);
    a *= 2;
    BOOST_CHECK_EQUAL(a(2), 4);
    a /= 2;
    BOOST_CHECK_EQUAL(a(3), 3);
}

BOOST_AUTO_TEST_CASE(VectorVectorArithmetics)
{
    Vector a{1, 2, -1, 4};
    Vector b{2, 2, 1, -1};
    Vector c = a + b;
    BOOST_CHECK(c == Vector({3, 4, 0, 3}));
    c = a - b;
    BOOST_CHECK(c == Vector({-1, 0, -2, 5}));
    a += b;
    BOOST_CHECK(a == Vector({3, 4, 0, 3}));
    a -= b;
    BOOST_CHECK(a == Vector({1, 2, -1, 4}));
}

BOOST_AUTO_TEST_CASE(VectorProduct)
{
    Vector a{1, 2, -1, 4};
    Vector b{2, 2, -1, 2};
    double c = a * b;
    BOOST_CHECK(c == 15);
}

