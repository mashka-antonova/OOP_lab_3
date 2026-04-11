#ifndef I_OPERATION_H
#define I_OPERATION_H

#include <vector>

class IOperation {
    public:
        virtual ~IOperation() = default;
        virtual double execute(const std::vector<double>& args) const  = 0;
};


#endif // I_OPERATION_H
