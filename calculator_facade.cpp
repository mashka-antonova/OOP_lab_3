#include "calculator_facade.h"

#include "tokenizer_provider.h"

#include <stdexcept>

CalculatorFacade::CalculatorFacade()
    : tokenizer(nullptr)
    , shuntingYard()
    , evaluator()
    , memory()

{
    TokenizerDependencyProvider provider;
    tokenizer = std::make_unique<Tokenizer>(provider.createTokenCreator());
}

double CalculatorFacade::calculate(const std::string& expression) {
    if (expression.empty())
        throw std::runtime_error("CalculatorFacade: expression is empty");

    std::vector<std::unique_ptr<Token>> lexemes = tokenizer->tokenize(expression);
    std::vector<std::unique_ptr<Token>> rpn = shuntingYard.convertToRPN(std::move(lexemes));
    return evaluator.evaluate(rpn);
}

void CalculatorFacade::memoryAdd(double value) {
    memory.add(value);
}

void CalculatorFacade::memorySubtract(double value) {
    memory.subtract(value);
}

void CalculatorFacade::memoryClear() {
    memory.clear();
}

double CalculatorFacade::memoryRecall() const {
    return memory.get();
}

const std::string& CalculatorFacade::getCurrentExpression() const {
    return currentExpression;
}

void CalculatorFacade::setCurrentExpression(const std::string& expression) {
    currentExpression = expression;
}

double CalculatorFacade::getCurrentResult() const {
    return currentResult;
}

void CalculatorFacade::setCurrentResult(double value) {
    currentResult = value;
}

void CalculatorFacade::runCommand(std::unique_ptr<ICommand> cmd) {
    commandManager.execute(std::move(cmd));
}

void CalculatorFacade::undo() {
    commandManager.undo();
}

void CalculatorFacade::redo() {
    commandManager.redo();
}

bool CalculatorFacade::canUndo() const {
    return commandManager.canUndo();
}

bool CalculatorFacade::canRedo() const {
    return commandManager.canRedo();
}
