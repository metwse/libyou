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
Matrix<m, 1, T> Matrix<m, n, T>::col(int j) {
    auto col = Matrix<m, 1, T>();

    for (int k = 0; k < m; k++)
        col.arr[k][0] = arr[k][j];

    return col;
}

template<int m, int n, typename T>
Matrix<1, n, T> Matrix<m, n, T>::row(int i) {
    auto row = Matrix<1, n, T>();

    for (int k = 0; k < n; k++)
        row.arr[0][k] = arr[i][k];

    return row;
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

template<int m, int n, typename T>
template<int p>
Matrix<m, p, T> Matrix<m, n, T>::operator*(const Matrix<n, p, T> &rhs) const {
    auto result = Matrix<m, p, T>();

    for (int i = 0; i < m; i++)
        for (int j = 0; j < p; j++) {
            auto cell = &result.arr[i][j];
            *cell = 0;

            for (int k = 0; k < n; k++)
                *cell += arr[i][k] * rhs.arr[k][j];
        }

    return result;
}

template<int m, int n, typename T>
Matrix<m, n, T> Matrix<m, n, T>::operator+(const Matrix<m, n, T> &rhs) const {
    auto result = Matrix<m, n, T>();

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            result.arr[i][j] = arr[i][j] + rhs.arr[i][j];

    return result;
}

template<int m, int n, typename T>
Matrix<m, n, T> Matrix<m, n, T>::operator-(const Matrix<m, n, T> &rhs) const {
    auto result = Matrix<m, n, T>();

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            result.arr[i][j] = arr[i][j] - rhs.arr[i][j];

    return result;
}

template<int m, int n, typename T>
bool Matrix<m, n, T>::operator==(const Matrix<m, n, T> &rhs) const {
    return arr == rhs.arr;
}

#endif
