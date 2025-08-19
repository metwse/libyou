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
            size_t code = m_map.at(c);
            
            // Calculate the actual bit length of the code
            size_t bit_length = 1;
            if (code > 0) {
                bit_length = 0;
                size_t temp = code;
                while (temp > 0) {
                    bit_length++;
                    temp >>= 1;
                }
            }

            if (bit_length + len > cap) {
                auto new_cap = (bit_length / 8) + len + !!(bit_length % 8) + 1;

                if (cap == 0)
                    arr = (byte *) malloc(new_cap);
                else
                    arr = (byte *) realloc(arr, new_cap);

                for (size_t i = cap / 8; i < new_cap; i++)
                    arr[i] = byte(0);

                cap = new_cap * 8;
            }

            // Write bits from MSB to LSB correctly
            for (int i = bit_length - 1; i >= 0; i--) {
                int bit = (code >> i) & 1;
                size_t byte_index = len / 8;
                size_t bit_index = len % 8;
                
                if (bit) {
                    arr[byte_index] |= (byte)(1 << bit_index);
                }
                
                len++;
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
