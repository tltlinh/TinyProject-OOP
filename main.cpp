#include <iostream>
#include "Matrix.hpp"
#include "Vector.hpp"
#include "LinearSystem.hpp"
using namespace std;
int main() {
    // Test Matrix creation and assignment
    Matrix A(2, 2);
    A(1, 1) = 3; A(1, 2) = 2;
    A(2, 1) = 1; A(2, 2) = 2;

    cout << "Matrix A:" << endl;
    for (int i = 1; i <= 2; ++i) {
        for (int j = 1; j <= 2; ++j) {
            cout << A(i, j) << " ";
        }
        cout << endl;
    }

    // Test Vector creation and assignment
    Vector b(2);
    b(1) = 5;
    b(2) = 3;

    cout << "Vector b:" << endl;
    for (int i = 1; i <= 2; ++i) {
        cout << b(i) << " ";
    }
    cout << endl;

    // Test LinearSystem solve (assuming SolveWithTikhonov or similar exists)
    LinearSystem system(A, b);
    Vector x = system.SolveWithTikhonov(A, b);

    cout << "Solution x:" << endl;
    for (int i = 1; i <= 2; ++i) {
        cout << x(i) << " ";
    }
    cout << endl;

    // Test Matrix operations
    Matrix B = A;
    Matrix C = A + B;
    cout << "Matrix C = A + B:" << endl;
    for (int i = 1; i <= 2; ++i) {
        for (int j = 1; j <= 2; ++j) {
            cout << C(i, j) << " ";
        }
        cout << endl;
    }

    // Test determinant and inverse
    double det = A.Determinant();
    cout << "Determinant of A: " << det << endl;
    if (det != 0) {
        Matrix invA = A.Inverse();
        cout << "Inverse of A:" << endl;
        for (int i = 1; i <= 2; ++i) {
            for (int j = 1; j <= 2; ++j) {
                cout << invA(i, j) << " ";
            }
            cout << endl;
        }
    }

    // Test LinearSystem solve (Gaussian elimination)
 
    Vector x_gauss = system.Solve();

    cout << "Solution x (Gaussian elimination):" << endl;
    for (int i = 1; i <= 2; ++i) {
        cout << x_gauss(i) << " ";
    }
    cout << endl;

    // Test LinearSystem solve with Tikhonov regularization
    Vector x_tikh = system.SolveWithTikhonov(A, b);

    cout << "Solution x (Tikhonov regularization):" << endl;
    for (int i = 1; i <= 2; ++i) {
        cout << x_tikh(i) << " ";
    }
    cout << endl;
    Matrix I(3,3);
    I.Identity(3);
    cout << "Identity matrix 3x3:" << endl;
    for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
        cout << I(i, j) << " ";
    }
    cout << endl;
}
    return 0;
}