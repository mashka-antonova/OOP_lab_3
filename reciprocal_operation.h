#ifndef RECIPROCAL_OPERATION_H
#define RECIPROCAL_OPERATION_H

#include "i_unary_operation.h"

class ReciprocalOperation final : public IUnaryOperation {
    double unaryExecute(double arg) const override {
        return arg == 0.0 ? throw std::domain_error("Division by zero")
                          : 1.0 / arg;
    }
};

#endif // RECIPROCAL_OPERATION_H
