#include "PosSymLinSystem.hpp"
#include <cmath>
#include <stdexcept>

PosSymLinSystem::PosSymLinSystem(const Matrix& A, const Vector& b) : LinearSystem(A, b) {
    
    if (!IsSymmetric()) {
        throw std::invalid_argument("Matrix must be symmetric for PosSymLinSystem");
    }
}

Vector PosSymLinSystem::Solve() const{
    const Matrix& A = *mpA;
    const Vector& b = *mpb;
    Vector x(mSize); // initial guess = 0
    Vector r = b - A * x;
    Vector p = r;
    double rs_old = r * r;

    const double tol_sq = 1e-10 * 1e-10;
    const int max_iter = std::max(100, mSize * 10);

    for (int i = 0; i < max_iter; ++i) {
        Vector Ap = A * p;
        double alpha = rs_old / (p * Ap);

        x = x + alpha * p;
        r = r- alpha * Ap;

        double rs_new = r * r;
        if (rs_new < tol_sq) {
            break;
        }

        double beta = rs_new / rs_old;
        p = r + beta * p;
        rs_old = rs_new;
    }

    return x;
}
bool PosSymLinSystem::IsSymmetric() const {
    const double tolerance = 1e-10;
    for (int i = 1; i <= mSize; ++i) {
        for (int j = 1; j <= mSize; ++j) {
            if (abs((*mpA)(i,j) - (*mpA)(j,i)) > tolerance) {
                return false;
            }
        }
    }
    return true;
}