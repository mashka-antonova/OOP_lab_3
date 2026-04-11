#ifndef UNARY_MINUS_OPERATION_H
#define UNARY_MINUS_OPERATION_H

#include "i_unary_operation.h"

class UnaryMinusOperation final : public IUnaryOperation {
    double unaryExecute(double arg) const override {
        return -arg;
    }
};

#endif // UNARY_MINUS_OPERATION_H
