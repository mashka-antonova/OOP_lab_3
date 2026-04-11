#ifndef UNARY_PLUS_OPERATION_H
#define UNARY_PLUS_OPERATION_H

#include "i_unary_operation.h"

class UnaryPlusOperation final : public IUnaryOperation {
    double unaryExecute(double arg) const override {
        return +arg;
    }
};

#endif // UNARY_PLUS_OPERATION_H
