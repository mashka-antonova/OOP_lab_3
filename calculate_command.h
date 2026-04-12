#ifndef CALCULATE_COMMAND_H
#define CALCULATE_COMMAND_H

#include "i_command.h"
#include "calculator_facade.h"

class CalculateCommand final : public ICommand {
public:
    CalculateCommand(CalculatorFacade* receiver, std::string expression);

    void execute() override;
    void undo() override;

private:
    CalculatorFacade* receiver;
    std::string expression;
    std::string prevExpression;
    double result;
    double prevResult;
};

#endif // CALCULATE_COMMAND_H
