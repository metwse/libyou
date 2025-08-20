#include <heap.hpp>

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <functional>


int main() {
    srand(time(0));

    for (int _fuzz1 = 0; _fuzz1 < 16; _fuzz1++) {
        auto heap = BinaryHeap<int>();

        auto arr = std::vector<int>();

        for (int _fuzz2 = 0; _fuzz2 < 128; _fuzz2++) {
            int r = rand() % 1024;
            arr.push_back(r);
            heap.insert(r);
        }

        std::sort(arr.begin(), arr.end(), std::greater<int>());

        for (int i = 0; i < 128; i++) {
            assert(arr[i] == heap.pop());
        }
    }
}
