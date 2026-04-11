#include "evaluator.h"

#include "number.h"
#include "unary_operator.h"
#include "binary_operator.h"

#include <string>
#include <stdexcept>

Evaluator::Evaluator() {
    initDispatch();
}

void Evaluator::initDispatch() {
    dispatch[TokenType::Number] = [this](const Token& t){handleNumber(t);};
    dispatch[TokenType::UnaryOperator] = [this](const Token& t){handleUnaryOperator(t);};
    dispatch[TokenType::BinaryOperator] = [this](const Token& t){handleBinaryOperator(t);};
}

void Evaluator::resetState() {
    while (!values.empty())
        values.pop();
}

double Evaluator::evaluate(const std::vector<std::unique_ptr<Token>>& rpn) {
    resetState();
    for (const auto& token : rpn)
        dispatch.at(token->type())(*token);
    return takeResult();
}

void Evaluator::handleNumber(const Token& token) {
    values.push(static_cast<const Number&>(token).getValue());
}

void Evaluator::handleUnaryOperator(const Token& token) {
    applyOperation(static_cast<const UnaryOperator&>(token).getName(), 1);
}

void Evaluator::handleBinaryOperator(const Token& token) {
    applyOperation(std::string(1, static_cast<const BinaryOperator&>(token).getName()), 2);
}

void Evaluator::applyOperation(const std::string& name, int arity) {
    std::vector<double> args = popArgs(arity);
    std::unique_ptr<IOperation> op = operationFactory.create(name);
    values.push(op->execute(args));
    //values.push(operationFactory.create(name)->execute(popArgs(arity))); хз как лучше
}

std::vector<double> Evaluator::popArgs(int count) {
    std::vector<double> args(count);
    for (int i = 0; i < count; ++i)
        args[count - 1 - i] = popOne();
    return args;
}

double Evaluator::popOne() {
    if (values.empty())
        throw std::runtime_error("Evaluator: not enough operands on the stack");

    double value = values.top();
    values.pop();
    return value;
}

double Evaluator::takeResult() {
    if (values.size() != 1)
        throw std::runtime_error("Evaluator: invalid RPN, stack must contain exactly one value");

    return values.top();
}
