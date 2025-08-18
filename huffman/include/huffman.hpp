/**
 * \file
 * \brief Huffman library public header.
 *
 * Huffman is a library for constructing Huffman-coded binary trees.
 */

#ifndef LY_HUFFMAN_HPP
#define LY_HUFFMAN_HPP

#include <cstddef>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

/**
 * A binary tree wrapper class.
 */
class Huffman {
public:
    /**
     * Prints Huffman tree in a human readable format.
     */
    friend std::ostream &operator<<(std::ostream &os, const Huffman &);

    /**
     * List of characters with their total occurance count.
     */
    typedef std::vector<std::pair<std::size_t, char>> FrequecyList;

    /**
     * Constructs a Huffman-coded binary tree from `std::string`.
     */
    Huffman(std::string);

    /**
     * Huffman binary tree from frequecy list.
     *
     * Provided list should have been ordered.
     */
    Huffman(FrequecyList);

    /**
     * Utility function for converting a string to \ref FrequecyList.
     */
    static FrequecyList frequecy_list(std::string);

    ~Huffman();

private:
    class Node;

    friend std::ostream &operator<<(std::ostream &os, const Huffman::Node &);

    Node *m_root { nullptr };
};


#endif
