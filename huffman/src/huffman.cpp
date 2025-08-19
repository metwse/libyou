#include <huffman.hpp>
#include "node.hpp"

#include <map>
#include <cstddef>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;


Huffman::Huffman(std::string str)
    : Huffman::Huffman(Huffman::frequency_list(str))
{}

Huffman::Huffman(FrequecyList list) {
    size_t size = list.size();
    auto nodes = new Huffman::Node *[size];

    for (size_t i = 0; i < size; i++) {
        nodes[i] = new Node();
        nodes[i]->c = list[i].second;
        nodes[i]->freq = list[i].first;
    }

    while (size > 1) {
        auto parent = new Node();
        parent->right = nodes[size - 1];
        parent->left = nodes[size - 2];
        parent->freq = nodes[size - 1]->freq + nodes[size - 2]->freq;
        nodes[size - 2] = parent;

        for (size_t i = size - 1; i > 1; i--)
            if (*nodes[i] > *nodes[i - 1])
                swap(nodes[i], nodes[i - 1]);

        size--;
    }

    for (size_t i = 1; i < size; i++)
        delete nodes[i];

    m_root = nodes[0];
    m_root->into_map(m_map, 0);

    delete[] nodes;
}

Huffman::~Huffman() {
    if (m_root)
        delete m_root;
}

Huffman::FrequecyList Huffman::frequency_list(string str) {
    map<char, size_t> freq_list;

    for (char c : str)
        freq_list[c]++;

    FrequecyList list;
    list.reserve(freq_list.size());

    for (auto it = freq_list.begin(); it != freq_list.end(); it++)
        list.push_back(pair<size_t, char>(it->second, it->first));

    sort(list.begin(),
         list.end(),
         [] (pair<size_t, char>a, pair<size_t, char>b) {
            return (a.first > b.first) || \
                (a.first == b.first && a.second > b.second);
         });

    return list;
}

ostream &operator<<(ostream &os, const Huffman &huffman) {
    huffman.m_root->print(os, "");
    return os;
}
