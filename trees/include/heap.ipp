#pragma once
#ifndef LY_HEAP_IPP
#define LY_HEAP_IPP

#include "heap.hpp"

#include <utility>

template<typename T, typename F>
void BinaryHeap<T, F>::heapify(std::size_t i) {
    size_t largest_i;
    T *largest { nullptr };

    auto ri = right_of(i);
    auto li = left_of(i);


    if (ri < m_data.size() && !F()(m_data[i], m_data[ri])) {
        largest = &m_data[ri];
        largest_i = ri;
    }
    if (li < m_data.size() && !F()(m_data[i], m_data[li])) {
        if (!largest || (largest && !F()(m_data[ri], m_data[li]))) {
            largest = &m_data[li];
            largest_i = li;
        }
    }

    if (largest) {
        std::swap(*largest, m_data[i]);
        heapify(largest_i);
    }
}

template<typename T, typename F>
T BinaryHeap<T, F>::pop() {
    T elem = m_data[0];

    if (m_data.size() > 0) {
        std::swap(m_data[0], m_data[m_data.size() - 1]);
        m_data.pop_back();

        heapify(0);
    } else {
        m_data.pop_back();
    }

    return elem;
}

template<typename T, typename F>
void BinaryHeap<T, F>::insert(T elem) {
    m_data.push_back(elem);

    size_t i = m_data.size() - 1;

    while (i && !F()(m_data[parent_of(i)], m_data[i])) {
        std::swap(m_data[i], m_data[parent_of(i)]);

        i = parent_of(i);
    }
}

#endif // LY_HEAP_IPP
