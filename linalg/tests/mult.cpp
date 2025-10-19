#include <linalg.hpp>

#include <iostream>

using std::cout, std::endl;


int main() {
    auto a = Matrix<3, 2>({
        { 1, 4 },
        { 2, 5 },
        { 3, 6 }
    });

    auto b = Matrix<2, 1>({
        { 1 },
        { 2 }
    });

    cout << a * b << endl;
}
