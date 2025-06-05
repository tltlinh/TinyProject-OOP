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
    double& operator()(int i);
    const double& operator()(int i) const;//const ver
    double& operator[](int i);
    const double& operator[](int i) const;   //const ver
    
    // Unary operators
    Vector operator+() const;
    Vector operator-() const;
    
    // Binary operators
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;
    double operator*(const Vector& other) const; // Dot product
    
    double Norm() const;
};
// Non-member vi neu la member func thi the object need to be on the left side
Vector operator*(double scalar, const Vector& vec);

#endif 