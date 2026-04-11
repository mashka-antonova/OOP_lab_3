#ifndef I_UNARY_OPERATION_H
#define I_UNARY_OPERATION_H

#include "i_operation.h"
#include <stdexcept>

class IUnaryOperation: public IOperation
{
public:

    double execute(const std::vector<double>& args) const final{
        return args.size() == 1 ? unaryExecute(args.front())
                                : throw std::invalid_argument("Unary operation expects 1 argument");
}
protected:
    virtual double unaryExecute(double arg) const = 0;
};

#endif // I_UNARY_OPERATION_H
