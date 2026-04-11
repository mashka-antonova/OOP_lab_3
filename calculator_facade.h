#ifndef CALCULATOR_FACADE_H
#define CALCULATOR_FACADE_H

#include <string>
#include <memory>

#include "tokenizer.h"
#include "shunting_yard.h"
#include "evaluator.h"
#include "memory.h"

class CalculatorFacade
{
public:
    CalculatorFacade();
    double calculate(const std::string& expression);

    void memoryAdd(double value);
    void memorySubtract(double value);
    void memoryClear();
    double memoryRecall() const;
private:
    std::unique_ptr<Tokenizer> tokenizer;
    std::unique_ptr<ShuntingYard> shuntingYard;
    std::unique_ptr<Evaluator> evaluator;
    std::unique_ptr<Memory> memory;
};

#endif // CALCULATOR_FACADE_H
