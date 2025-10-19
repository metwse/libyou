/**
 * \file
 * \brief Linear algebra implementations.
 *
 * Implementations of standard linear algebra algorithms for 2-dimensional
 * array.
 */

#pragma once
#ifndef LY_LINALG_HPP
#define LY_LINALG_HPP

#include <initializer_list>
#include <ostream>
#include <array>

/**
 * \brief 2D array, a.k.a matrix.
 */
template<int m, int n, typename T = int>
class Matrix {
public:
    /**
     * Constructs an uninitialized matrix.
     */
    Matrix() = default;

    /**
     * Constructs a matrix from given 1D array.
     */
    template<typename... U>
    constexpr Matrix(U... input) : arr { input... } { }

    /**
     * Constructs a matrix from given 2D array.
     */
    constexpr Matrix(std::initializer_list<std::initializer_list<T>> input) {
        int i = 0, j = 0;
        for (const auto &row : input) {
            i = 0;
            for (const auto &elem : row)
                arr[j][i++] = elem;
            j++;
        }
    }

    /**
     * Creates a zero matrix.
     */
    constexpr static Matrix zeros();

    /**
     * Creates a identitiy matrix.
     */
    constexpr static Matrix identity();

    /**
     * Returns a clone of j th column of matrix.
     */
    Matrix<m, 1, T> col(int j) const;

    /**
     * Returns a clone of i th row of matrix.
     */
    Matrix<1, n, T> row(int i) const;

    /**
     * Element at (row, col)
     */
    T elem(int row, int col) const;

    /**
     * Transpose of the matrix.
     */
    Matrix<n, m, T> transpose() const;

    /**
     * Calculates the whole matrix multiplication.
     */
    template<int p>
    Matrix<m, p, T> operator*(const Matrix<n, p, T> &) const;

    /**
     * Matrix addition.
     */
    Matrix operator+(const Matrix &) const;

    /**
     * Matrix substraction.
     */
    Matrix operator-(const Matrix &) const;

    /**
     * Calculates the whole matrix multiplication.
     */
    bool operator==(const Matrix &) const;

    /**
     * Formats and prints the matrix.
     */
    template<int a, int b, typename U>
    friend std::ostream &operator<<(std::ostream &, const Matrix<a, b, U> &);

    template <int, int, typename> friend class Matrix;

    template<int a, typename U>
    friend U dot(const Matrix<a, 1, U> &, const Matrix<a, 1, U> &);

protected:
    /**
     * Underlying 2D array.
     */
    std::array<std::array<T, n>, m> arr;
};

template<int n, typename T>
T dot(const Matrix<n, 1, T> &a, const Matrix<n, 1, T> &b);

#include "linalg.ipp"

#endif
