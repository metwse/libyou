#pragma once
#ifndef LY_AVL_IPP
#define LY_AVL_IPP

#include "avl.hpp"

#include <algorithm>

template<typename T, typename F>
AvlTree<T, F>::~AvlTree<T, F>() {
    delete m_root;
}

template<typename T, typename F>
void AvlTree<T, F>::insert(T elem) {
    if (!m_root) {
        m_root = new Node(elem);
    } else {
        Node *parent = nullptr;
        Node **target = &m_root;

        do {
            parent = *target;
        } while (*(target = F()(elem, (*target)->data) ?
               &(*target)->right : &(*target)->left));

        *target = new Node(elem);
        (*target)->parent = parent;

        balance_up(parent);
    }
}

template<typename T, typename F>
bool AvlTree<T, F>::contains(const T &elem) {
    if (!m_root)
        return false;

    Node *current = m_root;

    do {
        if (elem == current->data)
            return true;
    } while ((current = F()(elem, current->data) ?
              current->right : current->left));

    return false;
}

template<typename T, typename F>
bool AvlTree<T, F>::remove(const T &elem) {
    if (!m_root)
        return false;

    Node *current = m_root;
    bool found = false;

    while (current) {
        if (elem == current->data) {
            found = true;
            break;
        }

        current = F()(elem, current->data) ? current->right : current->left;
    }

    if (!found)
        return false;

    auto parent_subtree = current->parent_subtree();
    if (!parent_subtree)
        parent_subtree = &m_root;

    Node *replace = nullptr;

    if (current->left)
        replace = extract_extreme(current->left, &Node::right);
    else if (current->right)
        replace = extract_extreme(current->right, &Node::left);

    Node *hold_parent = nullptr;

    *parent_subtree = replace;
    if (replace) {
        if (replace->parent)
            hold_parent = replace->parent->parent;

        replace->parent = current->parent;
        replace->left = current->left;
        replace->right = current->right;

        if (replace->right)
            replace->right->parent = replace;
        if (replace->left)
            replace->left->parent = replace;
    }

    balance_up(hold_parent ? hold_parent : current->parent);

    operator delete(current);
    return true;
}

template<typename T, typename F>
void AvlTree<T, F>::balance_up(Node *node) {
    while (node) {
        Node *hold_parent = node->parent;
        Node *new_root = node->balance();
        if (new_root && !hold_parent)
            m_root = new_root;
        node = hold_parent;
    }
}

template<typename T, typename F>
typename AvlTree<T, F>::Node *AvlTree<T, F>::extract_extreme(Node *node,
                                                             Node *Node::*child) {
    Node *Node::*other = child == &Node::left ? &Node::right : &Node::left;

    while (node->*child)
        node = node->*child;

    auto parent_subtree = node->parent_subtree();
    if (!parent_subtree)
        parent_subtree = &m_root;

    *parent_subtree = node->*other;
    if (node->*other)
        (node->*other)->parent = node->parent;

    return node;
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
    auto hold_parent_subtree = parent_subtree();
    auto hold_right = right;
    auto hold_left = right->left;

    parent = right;
    right->parent = hold_parent;
    right->left = this;
    right = hold_left;

    if (hold_left)
        hold_left->parent = this;

    if (is_root) {
        return hold_right;
    } else {
        *hold_parent_subtree = hold_right;
        return nullptr;
    }
}

template<typename T, typename F>
typename AvlTree<T, F>::Node *AvlTree<T, F>::Node::right_rotate() {
    bool is_root = !parent;
    auto hold_parent = parent;
    auto hold_parent_subtree = parent_subtree();
    auto hold_left = left;
    auto hold_right = left->right;

    parent = left;
    left->parent = hold_parent;
    left->right = this;
    left = hold_right;

    if (hold_right)
        hold_right->parent = this;

    if (is_root) {
        return hold_left;
    } else {
        *hold_parent_subtree = hold_left;
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
typename AvlTree<T, F>::Node **AvlTree<T, F>::Node::parent_subtree() {
    if (parent == nullptr)
        return nullptr;

    return (parent->right == this) ? &parent->right : &parent->left;
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
            Node *hold = left->left_rotate();
            if (hold && !hold->parent)
                return hold;
            return right_rotate();
        }
    }

    if (right && balance_factor < -1) {
        if ((right->right ? right->right->height() : 0) >=
            (right->left ? right->left->height() : 0)) {
            return left_rotate();
        } else {
            Node *hold = right->right_rotate();
            if (hold && !hold->parent)
                return hold;
            return left_rotate();
        }
    }

    return nullptr;
}

template<typename T, typename F>
void AvlTree<T, F>::Node::set_left(T elem) {
    if (left) {
        left->data = elem;
    } else {
        left = new Node(elem);
        left->parent = this;
    }
}

template<typename T, typename F>
void AvlTree<T, F>::Node::set_right(T elem) {
    if (right) {
        right->data = elem;
    } else {
        right = new Node(elem);
        right->parent = this;
    }
}

#endif // LY_AVL_IPP
