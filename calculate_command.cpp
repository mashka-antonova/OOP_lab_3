#include "calculate_command.h"

CalculateCommand::CalculateCommand(CalculatorFacade* receiver, const std::string& expr, double result)
    : receiver(receiver), expression(expr), result(result), prevResult(0.0) {}

void CalculateCommand::execute() {
    prevExpression = receiver->getCurrentExpression();
    prevResult = receiver->getCurrentResult();

    receiver->setCurrentExpression(expression);
    receiver->setCurrentResult(result);
}

void CalculateCommand::undo() {
    receiver->setCurrentExpression(prevExpression);
    receiver->setCurrentResult(prevResult);
}
