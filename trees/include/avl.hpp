/**
 * \file
 * \brief AVL Tree public header.
 *
 * AVL Tree implementaiton for libtrees.
 */

#pragma once
#ifndef LY_AVL_HPP
#define LY_AVL_HPP

#include <functional>

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

        /**
         * Returns the pointer to the parent's subtree where this node is
         * attached.
         *
         * Useful for re-linking the node during rotations or deletions,
         * since it allows updating the parent's child pointer directly.
         */
        Node **parent_subtree();

        /**
         * Balances subtrees of the node.
         *
         * \return The new root if root of the tree should be changed,
         *         `nullptr` otherwise.
         */
        Node *balance();

        size_t height();

        T data;
        Node *parent { nullptr };
        Node *left { nullptr };
        Node *right { nullptr };
    };

    /**
     * Balances tree starting from the parent of given node.
     */
    void balance_up(Node *);

    /**
     * Extracts the extreme (leftmost or rightmost) node from the subtree.
     * \param child Pointer-to-member specifying which child pointer to
     *        follow.
     *        - Use `&Node::left` to extract the leftmost node.
     *        - Use `&Node::right` to extract the rightmost node.
     *
     * \note The caller takes ownership of the returned node and is responsible
     *       for managing its lifetime.
     */
    Node *extract_extreme(Node *, Node *Node::*child);

    /// Root node of the AVL tree (nullptr if empty).
    Node *m_root { nullptr };
};

#include "avl.ipp"

#endif // LY_AVL_HPP
