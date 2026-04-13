#ifndef MEMORY_SUBTRACT_COMMAND_H
#define MEMORY_SUBTRACT_COMMAND_H

#include "calculator_facade.h"
#include "i_command.h"

class MemorySubtractCommand final : public ICommand {
public:
    MemorySubtractCommand(CalculatorFacade* receiver, double value)
        : receiver(receiver), value(value) {}

    void execute() override {
        receiver->memorySubtract(value);
    }

    void undo() override {
        receiver->memoryAdd(value);;
    }

private:
    CalculatorFacade* receiver;
    double value;
};

#endif // MEMORY_SUBTRACT_COMMAND_H
