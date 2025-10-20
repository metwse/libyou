#pragma once
#include <utility>
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
void Matrix<m, n, T>::swap_rows(int a, int b) {
    std::swap(arr[a], arr[b]);
}

template<int m, int n, typename T>
void Matrix<m, n, T>::multiply_row(int a, T k) {
    for (int i = 0; i < n; i++)
        arr[a][i] *= k;
}

template<int m, int n, typename T>
void Matrix<m, n, T>::multiply_row_and_add_to(int a, T k, int b) {
    for (int i = 0; i < n; i++)
        arr[b][i] += arr[a][i] * k;
}

template<int m, int n, typename T>
inline Matrix<m, 1, T> Matrix<m, n, T>::col(int j) const {
    auto col = Matrix<m, 1, T>();

    for (int k = 0; k < m; k++)
        col.arr[k][0] = arr[k][j];

    return col;
}

template<int m, int n, typename T>
inline Matrix<1, n, T> Matrix<m, n, T>::row(int i) const {
    auto row = Matrix<1, n, T>();

    for (int k = 0; k < n; k++)
        row.arr[0][k] = arr[i][k];

    return row;
}

template<int m, int n, typename T>
inline Matrix<n, m, T> Matrix<m, n, T>::transpose() const {
    auto transposition = Matrix<n, m, T>();

    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
            transposition.arr[i][j] = arr[j][i];

    return transposition;
}

template<int m, int n, typename T>
template<typename U>
inline Matrix<m, n, U> Matrix<m, n, T>::cast() const {
    auto cast = Matrix<m, n, U>();

    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
            cast.arr[i][j] = static_cast<U>(arr[i][j]);

    return cast;
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
inline Matrix<m, p, T> Matrix<m, n, T>::operator*(
    const Matrix<n, p, T> &rhs
) const {
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
inline Matrix<m, n, T> Matrix<m, n, T>::operator+(
    const Matrix<m, n, T> &rhs
) const {
    auto result = Matrix<m, n, T>();

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            result.arr[i][j] = arr[i][j] + rhs.arr[i][j];

    return result;
}

template<int m, int n, typename T>
inline Matrix<m, n, T> Matrix<m, n, T>::operator-(
    const Matrix<m, n, T> &rhs
) const {
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

template<int n, typename T>
T dot(const Matrix<n, 1, T> &a, const Matrix<n, 1, T> &b) {
    T dot = 0;

    for (int k = 0; k < n; k++)
        dot += a.arr[k][0] * b.arr[k][0];

    return dot;
}

#endif
