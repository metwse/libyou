#include <huffman.hpp>

#include <cassert>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;


int main() {
    srand(time(0));

    for (size_t _fuzz = 0; _fuzz < 128; _fuzz++) {
        string str = "";
        str.reserve(1024);

        for (size_t i = 0; i < 1024; i++)
            str.push_back(rand() % ('~' - ' ') + ' ');

        auto huffman = Huffman(str);

        auto encoded = huffman.encode(str);

        assert(huffman.decode(encoded) == str);
    }
}
