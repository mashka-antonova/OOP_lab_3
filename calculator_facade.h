#ifndef CALCULATOR_FACADE_H
#define CALCULATOR_FACADE_H

#include <string>
#include <memory>

#include "shunting_yard.h"
#include "evaluator.h"
#include "i_command.h"
#include "memory.h"
#include "command_manager.h"
#include "tokenizer_dependency_provider.h"
#include "calculator_state.h"

class CalculatorFacade
{
public:
    CalculatorFacade();
    void addNumberToken(double value);
    void addOperatorToken(const std::string& op);
    void clearTokenQueue();
    void removeLastToken();
    double calculateQueue();

    void computeAndSave(const std::string& displayExpression, double calculatedResult);

    void addToMemory(double value);
    void subtractFromMemory(double value);
    void clearMemory();
    double memoryRecall() const;

    void memoryAdd(double value);
    void memorySubtract(double value);
    void memoryClear();

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
    TokenizerDependencyProvider provider;
    std::unique_ptr<TokenCreator> tokenCreator;
    std::vector<std::unique_ptr<Token>> tokenQueue;
    ShuntingYard shuntingYard;
    Evaluator evaluator;
    Memory memory;
    CommandManager commandManager;
    CalculatorState state;

};

#endif // CALCULATOR_FACADE_H
