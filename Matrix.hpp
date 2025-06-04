#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Vector.hpp"

class Matrix {
private:
    int mNumRows;    // Số hàng của ma trận
    int mNumCols;    // Số cột của ma trận
    double** mData;  // Con trỏ tới dữ liệu ma trận

public:
    // Constructors và destructor
    Matrix(int numRows, int numCols);          // Constructor với kích thước
    Matrix(const Matrix& other);               // Copy constructor
    Matrix& operator=(const Matrix& other); 
    ~Matrix();                                 // Destructor

    // Phương thức truy cập thông tin
    int GetNumRows() const { return mNumRows; }
    int GetNumCols() const { return mNumCols; }
    double GetData(int r, int c) const { return mData[r][c]; }


    // Toán tử truy cập phần tử (1-based indexing)
    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

    
    Matrix operator+() const;
    Matrix operator-() const;

    // Binary operators
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
  
    Vector operator*(const Vector& vec) const;

    double Determinant() const;
    Matrix Inverse() const;
    Matrix Transpose() const;
    Matrix PseudoInverse() const;
    static Matrix Identity(int size);


};

#endif // MATRIX_HPP