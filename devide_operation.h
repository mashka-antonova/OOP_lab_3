#ifndef DEVIDE_OPERATION_H
#define DEVIDE_OPERATION_H

#include "i_binary_operation.h"

class DevideOperation final : public IBinaryOperation {

    double binaryExecute(double leftValue, double rightValue) const override {
        return rightValue == 0 ? throw std::domain_error("Division by zero")
                               : leftValue / rightValue;
    }

};

#endif // DEVIDE_OPERATION_H
