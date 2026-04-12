#include "calculate_command.h"

CalculateCommand::CalculateCommand(CalculatorFacade* receiver, std::string expression)
    : receiver(receiver), expression(std::move(expression)), result(0.0), prevResult(0.0) {}

void CalculateCommand::execute() {
    prevExpression = receiver->getCurrentExpression();
    prevResult = receiver->getCurrentResult();
    result = receiver->calculate(expression);
    receiver->setCurrentExpression(expression);
    receiver->setCurrentResult(result);
}

void CalculateCommand::undo() {
    receiver->setCurrentExpression(prevExpression);
    receiver->setCurrentResult(prevResult);
}

