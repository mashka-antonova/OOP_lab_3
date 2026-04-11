#ifndef COS_OPERATION_H
#define COS_OPERATION_H

#include "i_unary_operation.h"
#include <cmath>

class CosOperation : public IUnaryOperation {
    double unaryExecute(double arg) const override {
        return std::cos(arg);
    }
};

#endif // COS_OPERATION_H
