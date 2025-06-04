#ifndef POS_SYM_LIN_SYSTEM_HPP
#define POS_SYM_LIN_SYSTEM_HPP

#include "LinearSystem.hpp"

class PosSymLinSystem : public LinearSystem {
public:
    PosSymLinSystem(const Matrix& A, const Vector& b);
    Vector Solve() const override;
    
private:
    bool IsSymmetric() const;
};

#endif // POS_SYM_LIN_SYSTEM_HPP