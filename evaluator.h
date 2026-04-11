#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "token.h"
#include "operation_factory.h"

#include <vector>
#include <memory>
#include <stack>
#include <map>
#include <functional>

class Evaluator
{
public:
    Evaluator();
    double evaluate(const std::vector<std::unique_ptr<Token>>& rpn);

private:
    OperationFactory operationFactory;
    std::stack<double> values;
    std::map<TokenType, std::function<void(const Token&)>> dispatch;

    void initDispatch();
    void resetState();

    void handleNumber(const Token& token);
    void handleUnaryOperator(const Token& token);
    void handleBinaryOperator(const Token& token);

    void applyOperation(const std::string& name, int arity);

    std::vector<double> popArgs(int count);
    double popOne();
    double takeResult();
};

#endif // EVALUATOR_H
