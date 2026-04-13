#include "calculator_facade.h"

#include "tokenizer_dependency_provider.h"
#include "calculate_command.h"

#include "memory_add_command.h"
#include "memory_subtract_command.h"
#include "memory_clear_command.h"

#include <stdexcept>

CalculatorFacade::CalculatorFacade()
    : provider()
    , tokenizer(std::make_unique<Tokenizer>(provider.createTokenCreator()))
    , shuntingYard()
    , evaluator()
    , memory()
    , commandManager()
    , state()
{
}

/*=====================================================================
                    главный интрфейс вычислений
=====================================================================*/
void CalculatorFacade::compute(const std::string& expression) {
    std::unique_ptr<ICommand> cmd = std::make_unique<CalculateCommand>(this, expression);
    runCommand(std::move(cmd));
}

/*=====================================================================
                управление историей и командами
=====================================================================*/
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
/*=====================================================================
                        работа с памятью
=====================================================================*/
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

/*=====================================================================
                    управление состоянием экрана
=====================================================================*/
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

/*=====================================================================
                        логика вычислений
=====================================================================*/
double CalculatorFacade::calculate(const std::string& expression) {
    if (expression.empty())
        throw std::runtime_error("CalculatorFacade: expression is empty");

    std::vector<std::unique_ptr<Token>> lexemes = tokenizer->tokenize(expression);
    std::vector<std::unique_ptr<Token>> rpn = shuntingYard.convertToRPN(std::move(lexemes));
    return evaluator.evaluate(rpn);
}


