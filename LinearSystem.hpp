#ifndef LINEAR_SYSTEM_HPP
#define LINEAR_SYSTEM_HPP

#include "Matrix.hpp"
#include "Vector.hpp"

class LinearSystem {
protected:
    int mSize;       // Kích thước hệ phương trình
    Matrix* mpA;     // Ma trận hệ số (vuông)
    Vector* mpb;     // Vector vế phải
    
    // Ngăn chặn sao chép
    LinearSystem(const LinearSystem& other) = delete;
    LinearSystem& operator=(const LinearSystem& other) = delete;
    
public:
    // Constructor
    LinearSystem(const Matrix& A, const Vector& b);
    
    // Destructor
    ~LinearSystem();
    
    // Phương thức giải hệ
    Vector virtual Solve() const;
    

};

#endif // LINEAR_SYSTEM_HPP