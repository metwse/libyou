#include <heap.hpp>

#include <cassert>


#define assert_parent(a, b) \
    assert(BinaryHeap<int>::parent_of(a) == b);

#define assert_left(a, b) \
    assert(BinaryHeap<int>::left_of(a) == b);

#define assert_right(a, b) \
    assert(BinaryHeap<int>::right_of(a) == b);


int main() {
    assert_parent(1, 0);
    assert_parent(2, 0);
    assert_parent(3, 1);
    assert_parent(4, 1);
    assert_parent(5, 2);
    assert_parent(6, 2);
    assert_parent(7, 3);
    assert_parent(8, 3);
    assert_parent(9, 4);
    assert_parent(10, 4);
    assert_parent(11, 5);
    assert_parent(12, 5);
    assert_parent(13, 6);
    assert_parent(14, 6);

    assert_right(0, 2);
    assert_right(1, 4);
    assert_right(2, 6);
    assert_right(4, 10);
    assert_right(6, 14);

    assert_left(0, 1);
    assert_left(1, 3);
    assert_left(2, 5);
    assert_left(4, 9);
    assert_left(6, 13);
}
