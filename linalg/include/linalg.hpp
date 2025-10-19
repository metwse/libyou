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
     * Formats and prints the matrix.
     */
    template<int a, int b, typename U>
    friend std::ostream &operator<<(std::ostream &, const Matrix<a, b, U> &);

    /**
     * Calculates the whole matrix multiplication.
     */
    template<int a, int b, int c, typename U>
    friend Matrix<a, c, U> operator*(const Matrix<a, b, U> &,
                                     const Matrix<b, c, U> &);

protected:
    /**
     * Underlying 2D array.
     */
    std::array<std::array<T, n>, m> arr;
};

#include "linalg.ipp"

#endif
