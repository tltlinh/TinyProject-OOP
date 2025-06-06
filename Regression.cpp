
#include "Regression.hpp"
#include "LinearSystemB.hpp"
#include <iostream>
#include <cmath>
using namespace std;

LinearRegression::LinearRegression()
    : x(1),  // Initialize with empty matrix
      trained(false) {}



void LinearRegression::train(const Matrix& A, const Vector& b) {
    Matrix A_copy = A; 
    Vector b_copy = b;
    LinearSystemB sys(A_copy, b_copy);
    x = sys.SolveWithTikhonov(A_copy, b_copy);
    trained = true;
}

Vector LinearRegression::predict(const Matrix& A) const {
    if (!trained) {
        cout << "Model is not trained.\n";
        return Vector(1);
    }
    return A*x;
}

double LinearRegression::rmse(const Vector& predictions, const Vector& targets) const {
    double sum = 0.0;
    int n = predictions.GetSize();
    for (int i = 0; i < n; i++) {
        double diff = predictions(i+1) - targets(i+1);
        sum += diff * diff;
    }
    return sqrt(sum/n);
}


// Output: Displays model coefficients
void LinearRegression::printWeights() const {
    if (!trained) {
        cout << "Model is not trained.\n";
        return;
    }
    cout << "Weights:\n";
    for (int i = 0; i < x.GetSize(); i++)
        cout << "w" << i << ": " << x(i+1) << "\n";
}
