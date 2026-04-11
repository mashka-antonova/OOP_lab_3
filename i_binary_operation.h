#ifndef I_BINARY_OPERATION_H
#define I_BINARY_OPERATION_H

#include "i_operation.h"
#include <stdexcept>

class IBinaryOperation : public IOperation
{
public:

    double execute(const std::vector<double>& args) const final{
        return args.size() == 2 ? binaryExecute(args[0], args[1])
                                : throw std::invalid_argument("Binary operation expects 2 arguments");
}
protected:
    virtual double binaryExecute(double leftValue, double rightValue) const = 0;
};

#endif // I_BINARY_OPERATION_H
