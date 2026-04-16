#include "calculator_facade.h"
#include "calculate_command.h"
#include "memory_add_command.h"
#include "memory_subtract_command.h"
#include "memory_clear_command.h"
#include "unary_operator.h"
#include <stdexcept>

CalculatorFacade::CalculatorFacade()
    : provider()
    , tokenCreator(provider.createTokenCreator())
    , shuntingYard()
    , evaluator()
    , memory()
    , commandManager()
    , state()
{}

void CalculatorFacade::addNumberToken(double value) {
    tokenQueue.push_back(tokenCreator->createToken("number", std::to_string(value)));
}

void CalculatorFacade::addOperatorToken(const std::string& op) {
    std::string currentOp = op;
    if (op == "-" || op == "+") {
        if (tokenQueue.empty() ||
            (tokenQueue.back()->type() == TokenType::BinaryOperator) ||
            (tokenQueue.back()->type() == TokenType::UnaryOperator &&
             static_cast<UnaryOperator*>(tokenQueue.back().get())->isOpenParen())) {
            currentOp = "unary" + op;
        }
    }

    tokenQueue.push_back(tokenCreator->createToken(currentOp, currentOp));
}

void CalculatorFacade::clearTokenQueue() {
    tokenQueue.clear();
}

void CalculatorFacade::removeLastToken() {
    if (!tokenQueue.empty()) {
        tokenQueue.pop_back();
    }
}

double CalculatorFacade::calculateQueue() {
    double result = state.getResult();
    if (!tokenQueue.empty()) {
        std::vector<std::unique_ptr<Token>> rpn = shuntingYard.convertToRPN(std::move(tokenQueue));
        tokenQueue.clear();
        result = evaluator.evaluate(rpn);
    }
    return result;
}

void CalculatorFacade::computeAndSave(const std::string& displayExpression, double calculatedResult) {
    std::unique_ptr<ICommand> cmd = std::make_unique<CalculateCommand>(this, displayExpression, calculatedResult);
    runCommand(std::move(cmd));
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

void CalculatorFacade::addToMemory(double value) {
    runCommand(std::make_unique<MemoryAddCommand>(this, value));
}

void CalculatorFacade::subtractFromMemory(double value) {
    runCommand(std::make_unique<MemorySubtractCommand>(this, value));
}

void CalculatorFacade::clearMemory() {
    runCommand(std::make_unique<MemoryClearCommand>(this));
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
    return state.getExpression();
}

void CalculatorFacade::setCurrentExpression(const std::string& expression) {
    state.setExpression(expression);
}

double CalculatorFacade::getCurrentResult() const {
    return state.getResult();
}

void CalculatorFacade::setCurrentResult(double value) {
    state.setResult(value);
}


