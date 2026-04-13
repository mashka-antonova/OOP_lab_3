#ifndef TG_OPERATION_H
#define TG_OPERATION_H

#include "i_unary_operation.h"
#include <cmath>

class TgOperation : public IUnaryOperation {
    double unaryExecute(double arg) const override {
        double radians = arg * (std::numbers::pi / 180.0);
        return std::cos(radians) == 0.0 ? throw std::domain_error("Tangent is undefined at this point")
                                    : std::tan(radians);
    }
};

#endif // TG_OPERATION_H
