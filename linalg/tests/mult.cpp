#include <linalg.hpp>

#include <cassert>


int main() {
    assert((
        Matrix<3, 2>({
            { 1, 4 },
            { 2, 5 },
            { 3, 6 }
        }) * Matrix<2, 2>({
            { 1, 6 },
            { 3, 7 }
        }) == Matrix<3, 2>({
            { 13, 34 },
            { 17, 47 },
            { 21, 60 },
        })
    ));

    auto a = Matrix<3, 2>({
        { 1, 0 },
        { 2, 4 },
        { 2, 1 },
    });

    auto b = Matrix<2, 3>({
        { 3, 3, 0 },
        { 1, 2, 1 },
    });

    auto a1b1 = a.col(0) * b.row(0);
    auto a2b2 = a.col(1) * b.row(1);

    auto c = Matrix<3, 2>({
        { 1, 0 },
        { 2, 4 },
        { 2, 1 },
    }) * Matrix<2, 3>({
        { 3, 3, 0 },
        { 1, 2, 1 },
    });

    assert((
        c == Matrix<3, 3>({
            { 3, 3, 0 },
            { 10, 14, 4 },
            { 7, 8, 1 },
        })
    ));

    assert((c == a1b1 + a2b2));
    assert((
        Matrix<1, 2>({ { 2, 1 }, }) - Matrix<1, 2>({ { 1,  3 }, }) ==
        Matrix<1, 2>({ { 1, -2 }, })
    ));

    assert((dot(c.col(0), c.col(1)) == 205));

    assert(((c.col(0).transpose() * c.col(1)).elem(0, 0) == 205));
}
