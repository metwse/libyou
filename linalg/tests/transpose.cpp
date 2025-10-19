#include <linalg.hpp>

#include <cassert>


int main() {
    assert((
        Matrix<3, 2>({
            { 1, 4 },
            { 2, 5 },
            { 3, 6 },
        }) == Matrix<2, 3>({
            { 1, 2, 3 },
            { 4, 5, 6 },
        }).transpose()
    ));

    assert((
        Matrix<4, 1>({
            { 1 },
            { 2 },
            { 3 },
            { 4 },
        }) == Matrix<1, 4>({
            { 1, 2, 3, 4 },
        }).transpose()
    ));
}
