#ifndef CALCULATOR_FACADE_H
#define CALCULATOR_FACADE_H

#include <string>
#include <memory>

#include "tokenizer.h"
#include "shunting_yard.h"
#include "evaluator.h"

class CalculatorFacade
{
public:
    CalculatorFacade();
    double calculate(const std::string& expression);
private:
    std::unique_ptr<Tokenizer> tokenizer;
    std::unique_ptr<ShuntingYard> shuntingYard;
    std::unique_ptr<Evaluator> evaluator;
};

#endif // CALCULATOR_FACADE_H
