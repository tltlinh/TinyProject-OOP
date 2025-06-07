#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Vector.hpp"

class Matrix {
private:
    int mNumRows;    
    int mNumCols;    
    double** mData; 

public:
    Matrix(int numRows, int numCols);          
    Matrix(const Matrix& other); // Copy constructor
    Matrix& operator=(const Matrix& other); 
    ~Matrix(); // Destructor

    int GetNumRows() const { return mNumRows; }
    int GetNumCols() const { return mNumCols; }

    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

    
    Matrix operator+() const; //duong
    Matrix operator-() const; //am

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Vector operator*(const Vector& vec) const;

    double Determinant() const;
    Matrix Inverse() const;
    Matrix Transpose() const;
    Matrix PseudoInverse() const;
    Matrix Identity(int size);


};

#endif // MATRIX_HPP