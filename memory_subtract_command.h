#ifndef MEMORY_SUBTRACT_COMMAND_H
#define MEMORY_SUBTRACT_COMMAND_H

#include "calculator_facade.h"
#include "i_command.h"

class MemorySubtractCommand final : public ICommand {
public:
    MemorySubtractCommand(CalculatorFacade* receiver, double value)
        : receiver(receiver), value(value), previousMemory(0.0) {}

    void execute() override {
        previousMemory = receiver->memoryRecall();
        receiver->memorySubtract(value);
    }

    void undo() override {
        receiver->memoryClear();
        receiver->memoryAdd(previousMemory);
    }

private:
    CalculatorFacade* receiver;
    double value;
    double previousMemory;
};

#endif // MEMORY_SUBTRACT_COMMAND_H
