#include "Matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <algorithm>
using namespace std;
Matrix::Matrix(int numRows, int numCols) {
    mNumRows=numRows; 
    mNumCols=numCols; 
    if (numRows <= 0 || numCols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }

    mData = new double*[mNumRows];
    
    for (int i = 0; i < mNumRows; i++) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; j++) 
            mData[i][j] = 0.0;
    }
}

// Copy constructor
Matrix::Matrix(const Matrix& other) {
    mNumRows=other.mNumRows; 
    mNumCols=other.mNumCols; 
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; i++) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] = other.mData[i][j];
        }
    }
}

// Destructor
Matrix::~Matrix() {
    // Giải phóng bộ nhớ từng hàng trước
    for (int i = 0; i < mNumRows; i++) {
        delete[] mData[i];
    }
    // Giải phóng mảng con trỏ hàng
    delete[] mData;
}

// Phiên bản không const - cho phép đọc và ghi
double& Matrix::operator()(int row, int col) {
    if (row < 1 || row > mNumRows || col < 1 || col > mNumCols) {
        throw std::out_of_range("Matrix indices out of range");
    }
    return mData[row-1][col-1];  // Chuyển từ 1-based sang 0-based
}

// Phiên bản const - chỉ cho phép đọc
const double& Matrix::operator()(int row, int col) const {
    if (row < 1 || row > mNumRows || col < 1 || col > mNumCols) {
        throw std::out_of_range("Matrix indices out of range");
    }
    return mData[row-1][col-1];  // Chuyển từ 1-based sang 0-based
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {  
        // Nếu khác kích thước
        if (mNumRows != other.mNumRows || mNumCols != other.mNumCols) {
            // Giải phóng bộ nhớ cũ
            for (int i = 0; i < mNumRows; i++) {
                delete[] mData[i];
            }
            delete[] mData;
            
            // Cập nhật kích thước mới
            mNumRows = other.mNumRows;
            mNumCols = other.mNumCols;
            
            // Cấp phát mới
            mData = new double*[mNumRows];
            for (int i = 0; i < mNumRows; i++) {
                mData[i] = new double[mNumCols];
            }
        }
        
        // Copy dữ liệu
        for (int i = 0; i < mNumRows; i++) {
            for (int j = 0; j < mNumCols; j++) {
                mData[i][j] = other.mData[i][j];
            }
        }
    }
    return *this;
}

Matrix Matrix::operator+() const { 
    return *this; 
}

Matrix Matrix::operator-() const {
    Matrix tam(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            tam.mData[i][j] = -mData[i][j];
        }
    }
    return tam;
}

Matrix Matrix::operator+(const Matrix& other) const {
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = mData[i][j] + other.mData[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator-(const Matrix& other) const {
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    
    Matrix tam(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            tam.mData[i][j] = mData[i][j] - other.mData[i][j];
        }
    }
    return tam;
}
Matrix Matrix::operator*(double scalar) const {
    Matrix tam(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            tam.mData[i][j] = mData[i][j] * scalar;
        }
    }
    return tam;
}


Matrix operator*(double scalar, const Matrix& mat) {
    return mat * scalar;  // Reuse the member function
}
 

Matrix Matrix::operator*(const Matrix& other) const {
    assert(mNumCols == other.mNumRows);
    
    Matrix result(mNumRows, other.mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < other.mNumCols; j++) {
            for (int k = 0; k < mNumCols; k++) {
                result.mData[i][j] += mData[i][k] * other.mData[k][j];
            }
        }
    }
    return result;
}

Vector Matrix::operator*(const Vector& vec) const {
    assert(mNumCols == vec.GetSize());
    Vector result(mNumRows);
    for (int i = 0; i < mNumRows; i++) {
        double sum = 0.0;
        for (int j = 0; j < mNumCols; j++) {
            sum += mData[i][j] * vec(j+1);  // Using 1-based indexing for Vector
        }
        result(i+1) = sum;
    }
    return result;
}

double Matrix::Determinant() const {
    // Kiểm tra ma trận vuông
    assert(mNumRows == mNumCols && "Matrix must be square to compute determinant");

    //ma trận 1x1
    if (mNumRows == 1) {
        return mData[0][0];
    }
    
    //ma trận 2x2
    if (mNumRows == 2) {
        return mData[0][0] * mData[1][1] - mData[0][1] * mData[1][0];
    }
    
    //sử dụng khai triển Laplace
    double det = 0.0;
    int sign = 1;
    
    for (int col = 0; col < mNumCols; ++col) {
        // Tạo ma trận con bỏ hàng 0 và cột hiện tại
        Matrix subMatrix(mNumRows - 1, mNumCols - 1);
        
        for (int i = 1; i < mNumRows; i++) {
            int subCol = 0;
            for (int j = 0; j < mNumCols; j++) {
                if (j == col) continue;
                subMatrix(i-1, subCol++) = mData[i][j];
            }
        }
        
        det += sign * mData[0][col] * subMatrix.Determinant();
        sign = -sign;  
    }
    
    return det;
}

Matrix Matrix::Inverse() const {
    // Kiểm tra ma trận vuông
    if (mNumRows != mNumCols) {
        throw std::runtime_error("Matrix must be square to compute inverse");
    }
    
    int n = mNumRows;
    Matrix result(n, n);
    Matrix temp(*this); // Tạo bản sao để thao tác
    
    // Khởi tạo ma trận đơn vị
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result(i+1, j+1) = (i == j) ? 1.0 : 0.0;
        }
    }
    
    // Phương pháp Gauss-Jordan Elimination
    for (int col = 0; col < n; ++col) {
        // Tìm pivot có giá trị tuyệt đối lớn nhất
        int max_row = col;
        double max_val = abs(temp(col+1, col+1));
        
        for (int row = col + 1; row < n; ++row) {
            if (abs(temp(row+1, col+1)) > max_val) {
                max_val = abs(temp(row+1, col+1));
                max_row = row;
            }
        }
        
        // Kiểm tra ma trận suy biến
        if (max_val < 1e-10) {
            throw std::runtime_error("Matrix is singular (non-invertible)");
        }
        
        // Đổi hàng nếu cần
        if (max_row != col) {
            for (int j = 0; j < n; j++) {
                swap(temp(col+1, j+1), temp(max_row+1, j+1));
                swap(result(col+1, j+1), result(max_row+1, j+1));
            }
        }
        /* std::swap(temp.mData[col], temp.mData[max_row]);
        std::swap(result.mData[col], result.mData[max_row]); */
        
        // Chuẩn hóa hàng pivot
        double pivot = temp(col+1, col+1);
        for (int j = 0; j < n; ++j) {
            temp(col+1, j+1) /= pivot;
            result(col+1, j+1) /= pivot;
        }
        
        // Khử các hàng khác
        for (int row = 0; row < n; ++row) {
            if (row != col && abs(temp(row+1, col+1)) > 1e-10) {
                double factor = temp(row+1, col+1);
                for (int j = 0; j < n; ++j) {
                    temp(row+1, j+1) -= factor * temp(col+1, j+1);
                    result(row+1, j+1) -= factor * result(col+1, j+1);
                }
            }
        }
    }
    
    return result;
}
Matrix Matrix::Transpose() const {
    Matrix transposed(mNumCols, mNumRows);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            transposed(j+1, i+1) = mData[i][j];
        }
    }
    return transposed;
}
Matrix Matrix::PseudoInverse() const {
    Matrix At = Transpose();

    if (mNumRows >= mNumCols) { 
        // A+ = (A^T A)^-1 A^T
        Matrix AtA = At * (*this);
        Matrix AtA_inverse = AtA.Inverse();
        return AtA_inverse * At;
    } else {
        // A+ = A^T (A A^T)^-1
        Matrix AAt = (*this) * At;
        Matrix AAt_inverse = AAt.Inverse();
        return At * AAt_inverse;
    }
}

Matrix Matrix::Identity(int size) { //still need size because we 
    Matrix I(size, size); 
    for (int i = 0; i < size; ++i) {
        I(i+1, i+1) = 1.0;
    }
    return I;
}
