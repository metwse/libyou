#include <linalg.hpp>
#include <iostream>

using std::cout, std::endl;

int main() {
    cout << Matrix<4, 4>::identity() << ", " << Matrix<4, 4>::zeros() << endl;
}
