#ifndef CALCULATOR_FACADE_H
#define CALCULATOR_FACADE_H

#include <string>
#include <memory>

#include "tokenizer.h"
#include "shunting_yard.h"
#include "evaluator.h"
#include "i_command.h"
#include "memory.h"
#include "command_manager.h"

class CalculatorFacade
{
public:
    CalculatorFacade();
    double calculate(const std::string& expression);

    void memoryAdd(double value);
    void memorySubtract(double value);
    void memoryClear();
    double memoryRecall() const;

    const std::string& getCurrentExpression() const;
    void setCurrentExpression(const std::string& expression);
    double getCurrentResult() const;
    void setCurrentResult(double value);

    void runCommand(std::unique_ptr<ICommand> cmd);
    void undo();
    void redo();

    bool canUndo() const;
    bool canRedo() const;

private:
    std::unique_ptr<Tokenizer> tokenizer;
    ShuntingYard shuntingYard;
    Evaluator evaluator;
    Memory memory;
    CommandManager commandManager;

    std::string currentExpression;
    double currentResult;
};

#endif // CALCULATOR_FACADE_H
