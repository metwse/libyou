#include <linalg.hpp>

#include <cassert>
#include <sstream>

using std::stringstream;


int main() {
    std::stringstream buffer;
    buffer << Matrix<4, 4>::identity();

    assert((
        buffer.str() ==
       "[\n"
       "      [ 1\t0\t0\t0 ]\n"
       "      [ 0\t1\t0\t0 ]\n"
       "      [ 0\t0\t1\t0 ]\n"
       "      [ 0\t0\t0\t1 ]\n"
       "]"
    ));
}
