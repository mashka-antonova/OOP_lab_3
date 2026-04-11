#include "operation_factory.h"
#include "add_operation.h"
#include "subtract_operation.h"
#include "multiply_operation.h"
#include "devide_operation.h"
#include "sin_operation.h"
#include "cos_operation.h"
#include "tg_operation.h"
#include "ctg_operation.h"
#include "sqrt_operation.h"
#include "reciprocal_operation.h"
#include "unary_minus_operation.h"
#include "unary_plus_operation.h"

//лучше чтобы объекты операций каждый раз заново создавались или один раз и потом переиспользовались

OperationFactory::OperationFactory() {
    initCreators();
}

void OperationFactory::initCreators() {
    creators["+"] = []{ return std::make_unique<AddOperation>(); };
    creators["-"] = []{ return std::make_unique<SubtractOperation>(); };
    creators["*"] = []{ return std::make_unique<MultiplyOperation>(); };
    creators["/"] = []{ return std::make_unique<DevideOperation>(); };

    creators["unary+"] = []{ return std::make_unique<UnaryPlusOperation>(); };
    creators["unary-"] = []{ return std::make_unique<UnaryMinusOperation>(); };
    creators["sin"] = []{ return std::make_unique<SinOperation>(); };
    creators["cos"] = []{ return std::make_unique<CosOperation>(); };
    creators["tg"]  = []{ return std::make_unique<TgOperation>(); };
    creators["ctg"] = []{ return std::make_unique<CtgOperation>(); };
    creators["sqrt"] = []{ return std::make_unique<SqrtOperation>(); };
    creators["1/x"]  = []{ return std::make_unique<ReciprocalOperation>(); };
}

std::unique_ptr<IOperation> OperationFactory::create(const std::string& name) const {
    return creators.at(name)();
}
