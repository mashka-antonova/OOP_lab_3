#ifndef OPERATION_FACTORY_H
#define OPERATION_FACTORY_H

#include <map>
#include <string>
#include <memory>
#include <functional>
#include "i_operation.h"

class OperationFactory final {
public:
    OperationFactory();
    std::unique_ptr<IOperation> create(const std::string& name) const;
private:
    void initCreators();
    std::map<std::string, std::function<std::unique_ptr<IOperation>()>> creators;
};

#endif // OPERATION_FACTORY_H
