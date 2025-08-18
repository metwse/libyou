#include <huffman.hpp>

#include <cassert>
#include <string>

using namespace std;


int main() {
    auto freq_list = Huffman::frequecy_list("abcddddeeff");

    assert(freq_list[0].first == 4 && freq_list[0].second == 'd');
    assert(freq_list[1].first == 2 && freq_list[1].second == 'f');
    assert(freq_list[2].first == 2 && freq_list[2].second == 'e');
    assert(freq_list[3].first == 1 && freq_list[3].second == 'c');
    assert(freq_list[4].first == 1 && freq_list[4].second == 'b');
    assert(freq_list[5].first == 1 && freq_list[5].second == 'a');

    auto huffman = Huffman("aaaaaaaaaacccddddeeeeeeeeeeeeeeeggiiiikkmmmnnnnnn"
                           "oooooooorrrrrrrsssssttttttttttttuuuuu");

    freq_list = Huffman::FrequecyList();
    freq_list.push_back(pair<size_t, char>(45, 'f'));
    freq_list.push_back(pair<size_t, char>(16, 'e'));
    freq_list.push_back(pair<size_t, char>(13, 'd'));
    freq_list.push_back(pair<size_t, char>(12, 'c'));
    freq_list.push_back(pair<size_t, char>(9, 'b'));
    freq_list.push_back(pair<size_t, char>(5, 'a'));
    auto other_huffman = Huffman(freq_list);
}
