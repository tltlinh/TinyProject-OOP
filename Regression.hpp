#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include "Matrix.hpp"

/*
 * Linear Regression model using Ordinary Least Squares (OLS)
 * Solves: weights = (X^T * X)^-1 * X^T * y
 */

class LinearRegression {
private:
    Vector x; // Model coefficients (including bias)
    bool trained;   // Training status flag


public:
    LinearRegression(); // Fixed: Initializes weights to 0x0 matrix
   
    // Trains model using input features X and target values y
    void train(const Matrix& A, const Vector& b);
   
    // Predicts target values for input features X
    Vector predict(const Matrix& A) const;
   
    // Computes Root Mean Squared Error
    double RMSE(const Vector& predictions, const Vector& targets) const;


    // Outputs model coefficients
    void GetxVector();
};

#endif