#ifndef LINEAR_SYSTEM_B_HPP
#define LINEAR_SYSTEM_B_HPP

#include "Matrix.hpp"
#include "Vector.hpp"

class LinearSystemB {
protected:
    int mRows, mCols;      // Kích thước hệ phương trình
    Matrix* mpA;     // Ma trận hệ số 
    Vector* mpb;     // Vector vế phải
    
    // Ngăn chặn sao chép
    LinearSystemB(const LinearSystemB& other) = delete;
    LinearSystemB& operator=(const LinearSystemB& other) = delete;
    
public:
    // Constructor
    LinearSystemB(const Matrix& A, const Vector& b);
    
    // Destructor
    ~LinearSystemB();
    
    // Phương thức giải hệ
    Vector SolvewithMoore_Penrose(Matrix& A,  Vector& b) const;
    Vector SolveWithTikhonov( Matrix& A, Vector& b);

};

#endif // LINEAR_SYSTEM_B_HPP