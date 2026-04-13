#ifndef COS_OPERATION_H
#define COS_OPERATION_H

#include "i_unary_operation.h"
#include <cmath>

class CosOperation : public IUnaryOperation {
    double unaryExecute(double arg) const override {
        double radians = arg * (std::numbers::pi / 180.0);
        return std::cos(radians);
    }
};

#endif // COS_OPERATION_H
