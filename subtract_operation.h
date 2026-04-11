#ifndef SUBTRACT_OPERATION_H
#define SUBTRACT_OPERATION_H

#include "i_binary_operation.h"

class SubtractOperation final : public IBinaryOperation {

    double binaryExecute(double leftValue, double rightValue) const override {
        return leftValue - rightValue;
    }

};


#endif // SUBTRACT_OPERATION_H
