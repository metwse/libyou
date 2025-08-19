#include <huffman.hpp>
#include "node.hpp"

#include <cstddef>
#include <ostream>


Huffman::Node::~Node() {
    if (left)
        delete left;
    if (right)
        delete right;
}

size_t Huffman::Node::height() const {
    size_t l = 0, r = 0;
    if (left)
        l = left->height();
    if (right)
        r = right->height();

    return 1 + max(r, l);
}

bool Huffman::Node::operator>(Huffman::Node &other) const  {
    if (freq > other.freq) {
        return true;
    } else if (freq == other.freq) {
        if (height() > other.height())
            return true;
        else if (height() == other.height())
            return c > other.c;
    }
    return false;
}

void Huffman::Node::print(ostream &os, string str) const {
    if (left)
        left->print(os, str + "0");
    if (right)
        right->print(os, str + "1");

    if (c)
        os << str << ": " << c << endl;
}

void Huffman::Node::into_map(map<char, size_t> &map, size_t parent) const {
    if (left)
        left->into_map(map, parent << 1);
    if (right)
        right->into_map(map, (parent << 1) | 1);

    if (c)
        map[c] = parent;
}
