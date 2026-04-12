#ifndef MEMORY_CLEAR_COMMAND_H
#define MEMORY_CLEAR_COMMAND_H

#include "calculator_facade.h"
#include "i_command.h"

class MemoryClearCommand final : public ICommand {
public:
    explicit MemoryClearCommand(CalculatorFacade* receiver)
        : receiver(receiver), previousMemory(0.0) {}

    void execute() override {
        previousMemory = receiver->memoryRecall();
        receiver->memoryClear();
    }

    void undo() override {
        receiver->memoryAdd(previousMemory);
    }

private:
    CalculatorFacade* receiver;
    double previousMemory;
};

#endif // MEMORY_CLEAR_COMMAND_H
