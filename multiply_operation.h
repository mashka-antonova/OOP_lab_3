#ifndef MULTIPLY_OPERATION_H
#define MULTIPLY_OPERATION_H

#include "i_binary_operation.h"

class MultiplyOperation final : public IBinaryOperation {

    double binaryExecute(double leftValue, double rightValue) const override {
        return leftValue * rightValue;
    }

};

#endif // MULTIPLY_OPERATION_H
