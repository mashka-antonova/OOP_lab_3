#ifndef MEMORY_ADD_COMMAND_H
#define MEMORY_ADD_COMMAND_H

#include "calculator_facade.h"
#include "i_command.h"

class MemoryAddCommand final : public ICommand {
public:
    MemoryAddCommand(CalculatorFacade* receiver, double value)
        : receiver(receiver), value(value), previousMemory(0.0) {}

    void execute() override {
        previousMemory = receiver->memoryRecall();
        receiver->memoryAdd(value);
    }

    void undo() override {
        receiver->memorySubtract(value);
    }

private:
    CalculatorFacade* receiver;
    double value;
    double previousMemory;
};

#endif // MEMORY_ADD_COMMAND_H
