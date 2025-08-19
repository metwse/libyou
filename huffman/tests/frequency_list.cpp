#include <huffman.hpp>

#include <cassert>
#include <string>

using namespace std;


int main() {
    auto freq_list = Huffman::frequency_list("abcddddeeff");

    assert(freq_list[0].first == 4 && freq_list[0].second == 'd');
    assert(freq_list[1].first == 2 && freq_list[1].second == 'f');
    assert(freq_list[2].first == 2 && freq_list[2].second == 'e');
    assert(freq_list[3].first == 1 && freq_list[3].second == 'c');
    assert(freq_list[4].first == 1 && freq_list[4].second == 'b');
    assert(freq_list[5].first == 1 && freq_list[5].second == 'a');
}
