#ifndef CTG_OPERATION_H
#define CTG_OPERATION_H

#include "i_unary_operation.h"
#include <cmath>

class CtgOperation final : public IUnaryOperation {
    double unaryExecute(double arg) const override {
        double radians = arg * (std::numbers::pi / 180.0);
        return std::sin(radians) == 0.0 ? throw std::domain_error("Ctangent is undefined at this point")
                                    : 1.0 / std::tan(radians);
    }
};

#endif // CTG_OPERATION_H
