#include <avl.hpp>

#include <cassert>
#include <cstdlib>
#include <ctime>


int main() {
    srand(time(0));

    for (int _fuzz1 = 0; _fuzz1 < 16; _fuzz1++) {
        auto avl = AvlTree<int>();

        for (int _fuzz2 = 0; _fuzz2 < 1024; _fuzz2++) {
            int val = rand();
            if (!avl.contains(val))
                avl.insert(val);

            if (avl.m_root->left && avl.m_root->right) {
                ssize_t balance_factor = ssize_t(avl.m_root->left->height()) -
                    ssize_t(avl.m_root->right->height());

                assert(-2 < balance_factor && balance_factor < 2);
            }
        }
    }
}
