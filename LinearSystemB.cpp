#include "LinearSystemB.hpp"
#include "LinearSystem.hpp"
#include "Matrix.hpp"
#include <stdexcept>
#include <cmath>

LinearSystemB::LinearSystemB(const Matrix& A, const Vector& b) {
    if (A.GetNumRows() != b.GetSize()) {
        throw std::invalid_argument("Matrix and vector dimensions must agree");
    }
    mRows = A.GetNumRows();
    mCols = A.GetNumCols();
    mpA = new Matrix(A);
    mpb = new Vector(b);
}

LinearSystemB::~LinearSystemB() {
    delete mpA;
    delete mpb;
}

// Ordinary Least Squares: x = (A^T A)^(-1) A^T b
Vector LinearSystemB::SolvewithMoore_Penrose(Matrix& A,  Vector& b) const {
    Matrix At = A.Transpose();
    Matrix AtA = At * (*mpA);

    if (mRows >= mCols) { 
        // A+ = (A^T A)^-1 A^T
        Matrix AtA_inverse = AtA.Inverse();
        return AtA_inverse * At * (*mpb);
    } else {
        // A+ = A^T (A A^T)^-1
        Matrix AAt = (*mpA) * At;
        Matrix AAt_inverse = AAt.Inverse();
        return At * AAt_inverse * (*mpb);
    }
}

Vector LinearSystemB::SolveWithTikhonov(Matrix& A,  Vector& b) {
    Matrix A_t = A.Transpose();
    float lambda=0.01;
    if (A.GetNumRows() >= A.GetNumCols()) {
        // over-determined (A^T A + λI)^-1 A^T b
        Matrix ATA = A_t * A;
        int n = A.GetNumCols();
        Matrix lambda_ver = ATA + ATA.Identity(n) * lambda;
        return lambda_ver.Inverse() * A_t * b;
    } else {
        // under-determined A^T (A A^T + λI)^-1 b
        Matrix AAT = A * A_t;
        int m = A.GetNumCols();
        Matrix lambda_ver = AAT + AAT.Identity(m) * lambda;
        return A_t * lambda_ver.Inverse() * b;
    }
}