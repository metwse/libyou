#include <huffman.hpp>
#include "node.hpp"

#include <cstdlib>
#include <bitset>
#include <cstddef>
#include <map>
#include <cstdint>
#include <string>

using namespace std;


template<typename T>
static inline uint_fast8_t msb(T num) {
    if (num == 0)
        return 0;
    uint_fast8_t msb = 1;

    while (num /= 2)
        msb++;

    return msb;
}

template<typename T, typename U>
static inline T pow(T num, U pow) {
    if (pow == 0)
        return 1;
    if (pow == 1)
        return num;

    T new_num = num;
    while (--pow)
        new_num *= num;
    return new_num;
}


Huffman::ByteArray Huffman::encode(string &str) const {
    byte *arr = nullptr;
    size_t len = 0;
    size_t cap = 0;

    for (char c : str) {
        if (m_map.count(c) == 1) {
            size_t b = m_map.at(c);
            auto mb = msb(b);

            if (mb + len > cap) {
                auto new_cap = (mb / 8) + len + !!(mb % 8);

                if (cap == 0)
                    arr = (byte *) malloc(new_cap);
                else
                    arr = (byte *) realloc(arr, new_cap);

                for (size_t i = cap / 8; i < new_cap; i++)
                    arr[i] = byte(0);

                cap = new_cap * 8;
            }

            if (b == 0)
                len += 1;

            size_t reversed_b = 0;
            for (auto i = 0; i < mb; i++) {
                reversed_b |= (!!(b & (1 << i))) << (mb - i - 1);
            }

            b = reversed_b;

            while (mb) {
                size_t shift = len % 8;
                size_t write = 8 - shift;
                size_t mask = pow(2, write) - 1;
                size_t push = b & mask;

                size_t written;
                if (mb < write) {
                    written = mb;
                    mb = 0;
                } else {
                    written = write;
                    mb -= write;
                }

                b >>= write;

                arr[len / 8] |= (byte) push << shift;

                len += written;
            }
        }
    }

    return {
        .arr = arr,
        .len = len,
    };
}

string Huffman::decode(Huffman::ByteArray &arr) const {
    string str = "";
    auto current = m_root;

    for (size_t i = 0; i < arr.len; i++) {
        if (size_t(arr.arr[i / 8]) & pow(2, i % 8))
            current = current->right;
        else
            current = current->left;
        if (current->c) {
            str.push_back(current->c);
            current = m_root;
        }
    }

    return str;
}

ostream &operator<<(ostream &os, const Huffman::ByteArray &arr) {
    os << arr.len << ": ";
    for (ssize_t i = arr.len / 8 + !!(arr.len % 8) - 1; i >= 0; i--)
        os << bitset<8>((int) arr.arr[i]) << " ";
    os << endl;

    return os;
}

Huffman::ByteArray::~ByteArray() {
    free(arr);
}
