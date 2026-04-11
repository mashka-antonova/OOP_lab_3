#include "calculator_facade.h"

#include "tokenizer_provider.h"
#include <stdexcept>

CalculatorFacade::CalculatorFacade()
    : tokenizer(nullptr)
    , shuntingYard(std::make_unique<ShuntingYard>())
    , evaluator(std::make_unique<Evaluator>())
{
    TokenizerDependencyProvider provider;
    tokenizer = std::make_unique<Tokenizer>(provider.createTokenCreator());
}

double CalculatorFacade::calculate(const std::string& expression) {
    if (expression.empty())
        throw std::runtime_error("CalculatorFacade: expression is empty");

    std::vector<std::unique_ptr<Token>> lexemes = tokenizer->tokenize(expression);
    std::vector<std::unique_ptr<Token>> rpn = shuntingYard->convertToRPN(std::move(lexemes));
    return evaluator->evaluate(rpn);
}
