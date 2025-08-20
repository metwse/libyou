#include <avl.hpp>

#include <cassert>
#include <type_traits>


int main() {
    {
        auto root = AvlTree<int>::Node(0);

        root.set_left(0);
        root.left->set_left(0);
        root.set_right(0);
        root.right->set_left(0);

        assert(root.height() == 3);
        assert(root.right->height() == 2);
    }

    {
        auto root = new AvlTree<int>::Node(1);
        root->set_left(0);
        root->set_right(2);

        root = root->right_rotate();
        assert(root->data == 0);
        assert(root->right->data == 1);
        assert(root->right->right->data == 2);

        root = root->left_rotate();
        root = root->left_rotate();
        assert(root->data == 2);
        assert(root->left->data == 1);
        assert(root->left->left->data == 0);

        delete root;
    }

    {
        auto root = new AvlTree<int>::Node(1);
        root->set_left(0);

        root = root->right_rotate();
        assert(root->data == 0);
        assert(root->right->data == 1);
        assert(!root->right->right);
        assert(!root->left);

        root = root->left_rotate();
        assert(root->data == 1);
        assert(root->left->data == 0);
        assert(!root->left->left);
        assert(!root->right);

        delete root;
    }

    {
        auto root = new AvlTree<int>::Node(1);

        root->set_left(2);
        root->set_right(5);
        root->left->set_right(4);
        root->left->set_left(3);
        root->left->right->set_left(6);

        root->left->right->right_rotate();
        root->left->left_rotate();
        root = root->right_rotate();

        assert(root->data == 6);
        assert(root->left->data == 2);
        assert(root->right->left->data == 4);
        assert(root->left->left->data == 3);
        assert(root->right->data == 1);
        assert(root->right->right->data == 5);

        delete root;
    }
}
