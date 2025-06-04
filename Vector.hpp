#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector {
private:
    int mSize;
    double* mData;

public:
    // Constructors and destructor
    Vector(int size);
    Vector(const Vector& other);
    ~Vector();

    // Size accessor
    int GetSize() const;

    // Operator overloading
    Vector& operator=(const Vector& other);
    const double& operator()(int i) const;   // 1-based indexing const version
    const double& operator[](int i) const;   // 0-based indexing const version
    
    // Unary operators
    Vector operator+() const;
    Vector operator-() const;
    
    // Binary operators
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;
    double operator*(const Vector& other) const; // Dot product
    
    // Other operations
    double Norm() const;
};

// Non-member operator for scalar multiplication (scalar * vector)
Vector operator*(double scalar, const Vector& vec);

#endif // VECTOR_HPP