#ifndef SIN_OPERATION_H
#define SIN_OPERATION_H

#include "i_unary_operation.h"
#include <cmath>

class SinOperation final : public IUnaryOperation {
    double unaryExecute(double arg) const override {
        double radians = arg * (std::numbers::pi / 180.0);
        return std::sin(radians);
    }
};

#endif // SIN_OPERATION_H
