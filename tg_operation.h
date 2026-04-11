#ifndef TG_OPERATION_H
#define TG_OPERATION_H

#include "i_unary_operation.h"
#include <cmath>

class TgOperation : public IUnaryOperation {
    double unaryExecute(double arg) const override {
        return std::cos(arg) == 0.0 ? throw std::domain_error("Tangent is undefined at this point")
                                    : std::tan(arg);
    }
};

#endif // TG_OPERATION_H
