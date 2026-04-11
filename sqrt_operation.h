#ifndef SQRT_OPERATION_H
#define SQRT_OPERATION_H

#include "i_unary_operation.h"
#include <cmath>

class SqrtOperation final : IUnaryOperation {
    double unaryExecute(double arg) const override {
        return arg < 0 ? throw std::domain_error("Square root of a negative number")
                       : std::sqrt(arg);
    }
};

#endif // SQRT_OPERATION_H
