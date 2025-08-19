/**
 * \file
 * \brief AVL Tree public header.
 *
 * AVL Tree implementaiton for libtrees.
 */

#pragma once
#ifndef LY_AVL_IPP
#define LY_AVL_IPP

#include "avl.hpp"

#include <functional>
#include <algorithm>


/**
 * \brief Self-balancing binary search tree (AVL Tree).
 *
 * The AvlTree class implements an AVL (Adelson-Velsky and Landis) tree,
 * which is a self-balancing binary search tree. For every node in the tree,
 * the height difference between the left and right subtrees is at most 1.
 */
template<typename T, typename F = std::greater<T>>
class AvlTree {
public:
    /**
     * Constructs an empty AVL tree.
     */
    AvlTree() = default;

    /**
     * Destructor.
     *
     * Recursively frees all nodes in the tree.
     */
    ~AvlTree();

    /**
     * Checks whether an element exists in the tree.
     */
    bool contains(const T &);

    /**
     * Removes an element from the tree.
     *
     * If the element does not exist, the function has no effect.
     *
     * \return true if the element was found and removed, false otherwise.
     */
    bool remove(const T &);

    /**
     * Inserts a new element into the tree.
     *
     * Balances the tree if necessary after insertion.
     */
    void insert(T);

#ifdef LY_DEBUG
public:
#else
private:
#endif
    /**
     * Internal node structure of the AVL tree.
     *
     * Each node stores an element, along with pointers to its left and right
     * children.
     */
    class Node {
#ifdef LY_DEBUG
    public:
#else
    private:
#endif
        Node() = default;

        Node(T data_)
            : data { data_ }
        {};

        ~Node();

        /**
         * Returns root node if root has been changed.
         */
        Node *left_rotate();

        /**
         * Returns root node if root has been changed.
         */
        Node *right_rotate();

        /**
         * Sets the left node, creates a node if left node not exists.
         */
        void set_left(T);

        /**
         * Sets the right node, creates a node if right node not exists.
         */
        void set_right(T);

        Node *balance();

        size_t height();

        T data;
        Node *parent { nullptr };
        Node *left { nullptr };
        Node *right { nullptr };
    };

    /// Root node of the AVL tree (nullptr if empty).
    Node *m_root { nullptr };
};


template<typename T, typename F>
AvlTree<T, F>::~AvlTree<T, F>() {
    delete m_root;
}

template<typename T, typename F>
void AvlTree<T, F>::insert(T data) {
    if (!m_root) {
        m_root = new Node(data);
    } else {
        Node *current = m_root;
        Node *parent;
        Node **target;

        while (current) {
            parent = current;

            if (F()(data, current->data))
                target = &current->right;
            else
                target = &current->left;

            current = *target;
        }

        *target = new Node(data);
        (*target)->parent = parent;

        Node *node = parent;
        while (node) {
            Node *new_root = node->balance();
            if (new_root && !new_root->parent)
                m_root = new_root;
            node = node->parent;
        }
    }
}

template<typename T, typename F>
bool AvlTree<T, F>::contains(const T &data) {
    if (!m_root)
        return false;

    Node *current = m_root;

    while (current) {
        if (data == current->data)
            return true;

        if (F()(data, current->data))
            current = current->right;
        else
            current = current->left;
    }

    return false;
}

template<typename T, typename F>
AvlTree<T, F>::Node::~Node() {
    if (left)
        delete left;
    if (right)
        delete right;
}

template<typename T, typename F>
typename AvlTree<T, F>::Node *AvlTree<T, F>::Node::left_rotate() {
    bool is_root = !parent;
    auto hold_parent = parent;
    auto hold_right = right;
    auto hold_left = right->left;

    parent = right;
    right->parent = hold_parent;
    right->left = this;
    right = hold_left;

    if (is_root) {
        return hold_right;
    } else {
        if (hold_parent->right == this)
            hold_parent->right = hold_right;
        if (hold_parent->left == this)
            hold_parent->left = hold_right;
        return nullptr;
    }
}

template<typename T, typename F>
typename AvlTree<T, F>::Node *AvlTree<T, F>::Node::right_rotate() {
    bool is_root = !parent;
    auto hold_parent = parent;
    auto hold_left = left;
    auto hold_right = left->right;

    parent = left;
    left->parent = hold_parent;
    left->right = this;
    left = hold_right;

    if (is_root) {
        return hold_left;
    } else {
        if (hold_parent->right == this)
            hold_parent->right = hold_left;
        if (hold_parent->left == this)
            hold_parent->left = hold_left;
        return nullptr;
    }
}

template<typename T, typename F>
size_t AvlTree<T, F>::Node::height() {
    size_t l = left ? left->height() : 0;
    size_t r = right ? right->height() : 0;

    return std::max(r, l) + 1;
}

template<typename T, typename F>
typename AvlTree<T, F>::Node *AvlTree<T, F>::Node::balance() {
    ssize_t balance_factor = ssize_t(left ? left->height() : 0) -
                             ssize_t(right ? right->height() : 0);

    if (left && balance_factor > 1) {
        if ((left->left ? left->left->height() : 0) >=
            (left->right ? left->right->height() : 0)) {
            return right_rotate();
        } else {
            Node *tmp = left->left_rotate();
            if (tmp && !tmp->parent) return tmp;

            return right_rotate();
        }
    }
    if (right && balance_factor < -1) {
        if ((right->right ? right->right->height() : 0) >=
            (right->left ? right->left->height() : 0)) {
            return left_rotate();
        } else {
            Node *tmp = right->right_rotate();
            if (tmp && !tmp->parent) return tmp;
            return left_rotate();
        }
    }

    return nullptr;
}

template<typename T, typename F>
void AvlTree<T, F>::Node::set_left(T data) {
    if (left) {
        left->data = data;
    } else {
        left = new Node(data);
        left->parent = this;
    }
}

template<typename T, typename F>
void AvlTree<T, F>::Node::set_right(T data) {
    if (right) {
        right->data = data;
    } else {
        right = new Node(data);
        right->parent = this;
    }
}

#endif // LY_AVL_IPP
