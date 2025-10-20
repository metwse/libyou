#include <linalg.hpp>

#include <cassert>


int main() {
    auto a = Matrix<3, 2>({
        { 1, 4 },
        { 2, 5 },
        { 3, 6 },
    });
    a.multiply_row(0, 2);
    a.multiply_row_and_add_to(0, 2, 2);
    a.swap_rows(0, 1);

    assert((
        a == Matrix<3, 2>({
            { 2, 5 },
            { 2, 8 },
            { 7, 22 },
        })
    ));
}
