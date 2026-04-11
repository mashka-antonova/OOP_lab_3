#ifndef ADD_OPERATION_H
#define ADD_OPERATION_H

#include "i_binary_operation.h"

class AddOperation final : public IBinaryOperation {

    double binaryExecute(double leftValue, double rightValue) const override {
        return leftValue + rightValue;
    }

};

#endif // ADD_OPERATION_H
