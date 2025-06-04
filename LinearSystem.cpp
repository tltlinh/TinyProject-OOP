#include "LinearSystem.hpp"
#include <stdexcept>
#include <cmath>
#include <algorithm>
using namespace std;

LinearSystem::LinearSystem(const Matrix& A, const Vector& b){
    if (A.GetNumRows() != A.GetNumCols()) {
        throw std::invalid_argument("Matrix A must be square");
    }
    if (A.GetNumRows() != b.GetSize()) {
        throw std::invalid_argument("Matrix and vector dimensions must agree");
    }
    mSize = A.GetNumRows();
    mpA = new Matrix(A);
    mpb = new Vector(b);
}
LinearSystem::~LinearSystem(){
    delete mpA;
    delete mpb;
}
Vector LinearSystem::Solve() const  {
    Matrix A(*mpA);  // Tạo bản sao để thao tác
    Vector b(*mpb);
    Vector x(mSize);

    for (int k = 0; k < mSize; ++k) {
        // Tìm pivot hàng
        int max_row = k;
        double max_val = abs(A(k+1, k+1));
        
        for (int i = k+1; i < mSize; ++i) {
            if (abs(A(i+1, k+1)) > max_val) {
                max_val = abs(A(i+1, k+1));
                max_row = i;
            }
        }
        
        // Kiểm tra hệ suy biến
        /* if (max_val < 1e-12) {
            throw runtime_error("Matrix is singular or nearly singular");
        } */
        
        // Đổi hàng nếu cần
        if (max_row != k) {
            for (int j = k; j < mSize; ++j) {
                swap(A(k+1, j+1), A(max_row+1, j+1));
            }
            swap(b(k+1), b(max_row+1));
        }
        
        // Chuẩn hóa hàng pivot
        double pivot = A(k+1, k+1);
        for (int j = k; j < mSize; ++j) {
            A(k+1, j+1) /= pivot;
        }
        b(k+1) /= pivot;
        
        // Khử các hàng dưới
        for (int i = k+1; i < mSize; ++i) {
            double factor = A(i+1, k+1);
            for (int j = k; j < mSize; ++j) {
                A(i+1, j+1) -= factor * A(k+1, j+1);
            }
            b(i+1) -= factor * b(k+1);
        }
    }
    
    // back sub
    for (int i = mSize-1; i >= 0; --i) {
        x(i+1) = b(i+1);
        for (int j = i+1; j < mSize; ++j) {
            x(i+1) -= A(i+1, j+1) * x(j+1);
        }
    }
    return x;
}

Vector LinearSystem::SolveWithTikhonov( Matrix& A,  Vector& b) {
    //check 
    Matrix A_t = A.Transpose();
    int n = A.GetNumCols();
    float lambda=0.01;
    if (A.GetNumRows() >= A.GetNumCols()) {
        // over-determined (A^T A + λI)^-1 A^T b
        Matrix ATA = A_t * A;
        Matrix lambda_ver = ATA + A.Identity(n) * lambda;
        return lambda_ver.Inverse() * A_t * b;
    } else {
        // under-determined A^T (A A^T + λI)^-1 b
        Matrix AAT = A * A_t;
        int m = A.GetNumRows();
        Matrix lambda_ver = AAT + A.Identity(n) * lambda;
        return A_t * lambda_ver.Inverse() * b;
    }
}