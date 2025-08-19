#include <avl.hpp>

#include <cassert>
#include <cstdlib>
#include <ctime>


int main() {
    srand(time(0));
    auto avl = AvlTree<int>();

    for (int _fuzz = 0; _fuzz < 128; _fuzz++) {
        int val = rand();
        if (!avl.contains(val))
            avl.insert(val);
    }

    ssize_t balance_factor = ssize_t(avl.m_root->left->height()) -
               ssize_t(avl.m_root->right->height());
    assert(-2 < balance_factor && balance_factor < 2);
}
