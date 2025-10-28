#pragma once
#ifndef LY_SORT_IPP
#define LY_SORT_IPP

#include "sort.hpp"

#include <cstddef>
#include <functional>


template<typename It, typename Cmp>
void quicksort(It first, It last, Cmp cmp) {}

template<typename It>
void quicksort(It first, It last) {
    quicksort(first, last, std::less<It>());
}

template<typename It, typename Cmp>
void mergesort(It first, It last, Cmp cmp) {}

template<typename It>
void mergesort(It first, It last) {
    mergesort(first, last, std::less<It>());
}

template<typename It, typename ToBitset>
void radixsort(It first, It last, ToBitset convert, std::size_t bucket_size) {}

#endif
