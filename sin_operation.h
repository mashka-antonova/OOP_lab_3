#ifndef SIN_OPERATION_H
#define SIN_OPERATION_H

#include "i_unary_operation.h"
#include <cmath>

class SinOperation final : public IUnaryOperation {
    double unaryExecute(double arg) const override {
        return std::sin(arg);
    }
};

#endif // SIN_OPERATION_H
