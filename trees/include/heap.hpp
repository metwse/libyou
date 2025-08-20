/**
 * \file
 * \brief Binary heap public header.
 *
 * Binary tree implementaiton for libtrees.
 */

#pragma once
#ifndef LY_HEAP_HPP
#define LY_HEAP_HPP

#include <functional>
#include <vector>
#include <cstddef>

/**
 * \brief Binary heap implemented using `std::vector`.
 */
template<typename T, typename F = std::greater<T>>
class BinaryHeap {
public:
    /**
     * Constructs an empty binary heap.
     */
    BinaryHeap() = default;

    ~BinaryHeap() = default;

    /**
     * Pops the first element of queue.
     */
    T pop();

    /**
     * Inserts given element to the queue.
     */
    void insert(T);

#ifdef LY_DEBUG
public:
#else
private:
#endif
    void heapify(std::size_t);

    static inline std::size_t parent_of(std::size_t i) {
        return (i + 1) / 2 - 1;
    };

    static inline std::size_t left_of(std::size_t i) {
        return (i + 1) * 2 - 1;
    };

    static inline std::size_t right_of(std::size_t i) {
        return (i + 1) * 2;
    };

    std::vector<T> m_data;
};

#include "heap.ipp"

#endif // LY_HEAP_HPP
