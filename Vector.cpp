#include "Vector.hpp"
#include <cmath>
#include <stdexcept>
#include <iostream>
using namespace std;

Vector::Vector(int size) {
    mSize=size; 
    if (size <= 0) cout << "vector size must be positive\n";
    mData = new double[size];
    for (int i = 0; i < size; i++)
        mData[i] = 0.0;
}

Vector::Vector(const Vector& V) {
    mSize=V.mSize;
    mData = new double[mSize];
    for (int i = 0; i < mSize; i++) 
        mData[i] = V.mData[i];
}

Vector::~Vector() {
    delete[] mData;
}

int Vector::GetSize() const {return mSize; }

Vector& Vector::operator=(const Vector& V) {
    if (this != &V) {
        if (mSize != V.mSize) {
            delete[] mData;
            mSize = V.mSize;
            mData = new double[mSize];
        }
        for (int i = 0; i < mSize; i++) 
            mData[i] = V.mData[i];
    }
    return *this;
}


double& Vector::operator()(int i) {
    if (i < 1 || i > mSize) cout <<"Vector index out of range";
    return mData[i-1];
}

const double& Vector::operator()(int i) const {
    if (i < 1 || i > mSize) cout <<"Vector index out of range";
    return mData[i-1];
}

double& Vector::operator[](int i) {
    if (i < 0 || i >= mSize) cout <<"Vector index out of range";
    return mData[i];
}

const double& Vector::operator[](int i) const {
    if (i < 0 || i >= mSize) cout <<"Vector index out of range";
    return mData[i];
}

Vector Vector::operator+() const {
    return *this;
}

Vector Vector::operator-() const {
    Vector tam(mSize);
    for (int i = 0; i < mSize; i++) tam.mData[i] = -mData[i];
    return tam;
}

Vector Vector::operator+(const Vector& V) const {
    if (mSize != V.mSize) cout <<"Vector sizes must match for addition";
    Vector tam(mSize);
    for (int i = 0; i < mSize; i++) 
        tam.mData[i] = mData[i] + V.mData[i];
    return tam;
}

Vector Vector::operator-(const Vector& V) const {
    if (mSize != V.mSize) cout <<"Vector sizes must match for subtraction";
    Vector tam(mSize);
    for (int i = 0; i < mSize; i++) 
        tam.mData[i] = mData[i] - V.mData[i];
    return tam;
}

Vector Vector::operator*(double scalar) const {
    Vector tam(mSize);
    for (int i = 0; i < mSize; i++) 
        tam.mData[i] = mData[i] * scalar;
    return tam;
}

double Vector::operator*(const Vector& V) const {
    if (mSize != V.mSize) cout <<"Vector sizes must match for dot product";
    double tam = 0.0;
    for (int i = 0; i < mSize; i++) 
        tam += mData[i] * V.mData[i];
    return tam;
}

Vector operator*(double scalar, const Vector& vec) {
    return vec * scalar;
}