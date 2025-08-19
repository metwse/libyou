#ifndef LY_HUFFMAN_NODE
#define LY_HUFFMAN_NODE

#include <huffman.hpp>

#include <map>
#include <ostream>
#include <cstddef>

using namespace std;


/**
 * Internal Huffman tree Node.
 */
class Huffman::Node {
private:
    friend Huffman;
    friend ostream &operator<<(ostream &os, const Huffman &);

    Node() = default;

    ~Node();

    size_t height() const;

    bool operator>(Node &other) const;

    void print(ostream &os, string) const;
    void into_map(map<char, size_t> &, size_t) const;

    Node *left { nullptr };
    Node *right { nullptr };

    char c { '\0' };
    size_t freq { 0 };
};


#endif
