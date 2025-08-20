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

/*
 * \brief Binary heap implemented using `std::vector`.
 */
template<typename T, typename F = std::greater<T>>
class BinaryHeap {
public:
    /**
     * Constructs an empty AVL tree.
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
    std::vector<T> m_data;
};

#include "heap.ipp"

#endif // LY_HEAP_HPP
