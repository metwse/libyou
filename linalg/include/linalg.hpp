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

#include <ostream>

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
     * Creates a zero matrix.
     */
    constexpr static Matrix zeros();

    /**
     * Creates a identitiy matrix.
     */
    constexpr static Matrix identity();

    template<int a, int b, typename U>
    friend std::ostream &operator<<(std::ostream &, const Matrix<a, b, U> &);

protected:
    T arr[m][n];
};

#include "linalg.ipp"

#endif
