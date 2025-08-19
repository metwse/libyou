/**
 * \file
 * \brief Huffman library public header.
 *
 * Huffman is a library for constructing Huffman-coded binary trees.
 */

#ifndef LY_HUFFMAN_HPP
#define LY_HUFFMAN_HPP

#include <cstddef>
#include <map>
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
     * List of characters with their total occurance count.
     */
    typedef std::vector<std::pair<std::size_t, char>> FrequecyList;

    /**
     * Array of bytes.
     */
    struct ByteArray {
        ~ByteArray();

        std::byte *arr;
        std::size_t len;
    };

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

    ~Huffman();

    /**
     * Encodes given string.
     */
    ByteArray encode(std::string &) const;

    /**
     * Decodes given \ref ByteArray into string.
     */
    std::string decode(ByteArray &) const;

    /**
     * Utility function for converting a string to \ref FrequecyList.
     */
    static FrequecyList frequecy_list(std::string);

    /**
     * Prints Huffman tree in a human readable format.
     */
    friend std::ostream &operator<<(std::ostream &os, const Huffman &);


private:
    class Node;

    friend std::ostream &operator<<(std::ostream &os, const Huffman::Node &);

    Node *m_root { nullptr };
    std::map<char, size_t> m_map;
};

std::ostream &operator<<(std::ostream &os, const Huffman::ByteArray &arr);

#endif
