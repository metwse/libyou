#pragma once
#ifndef LY_LINALG_IPP
#define LY_LINALG_IPP

#include "linalg.hpp"

#include <ostream>

using std::ostream;


template<int m, int n, typename T>
constexpr Matrix<m, n, T> Matrix<m, n, T>::identity() {
    static_assert(m == n, "Identity matrix must be square (m == n).");

    return []() {
        auto ident = Matrix<n, n, T>();

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                ident.arr[j][i] = i == j ? 1 : 0;

        return ident;
    } ();
}

template<int m, int n, typename T>
constexpr Matrix<m, n, T> Matrix<m, n, T>::zeros() {
    return []() {
        auto zeros = Matrix<n, n, T>();

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                zeros.arr[j][i] = 0;

        return zeros;
    } ();
}

template<int m, int n, typename T>
ostream &operator<<(ostream &os, const Matrix<m, n, T> &matrix) {
    os << "[\n";
    for (int j = 0; j < m; j++) {
        os << "      [ ";

        for (int i = 0; i < n; i++)
            os << matrix.arr[j][i] << (i == n - 1 ? " ]\n" : "\t");
    }
    os << "]";

    return os;
}

template<int a, int b, int c, typename U>
Matrix<a, c, U> operator*(const Matrix<a, b, U> &lhs,
                          const Matrix<b, c, U> &rhs) {
    auto result = Matrix<a, c, U>();

    for (int i = 0; i < a; i++)
        for (int j = 0; j < c; j++) {
            auto cell = &result.arr[i][j];
            *cell = 0;

            for (int k = 0; k < b; k++)
                *cell += lhs.arr[i][k] * rhs.arr[k][j];
        }

    return result;
}

#endif
