/**
 * \file
 * \brief Sorting algorithms
 *
 * Sorting algorithm implementations.
 */

#pragma once
#ifndef LY_SORT_HPP
#define LY_SORT_HPP

#include <cstddef>


template<typename It>
void quicksort(It first, It last);

template<typename It, typename Cmp>
void quicksort(It first, It last, Cmp cmp);

template<typename It>
void mergesort(It first, It last);

template<typename It, typename Cmp>
void mergesort(It first, It last, Cmp cmp);

template<typename It, typename ToBitset>
void radixsort(It first, It last, ToBitset convert, std::size_t);

#include "sort.ipp"

#endif
