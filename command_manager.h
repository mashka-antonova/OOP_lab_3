#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#include <memory>
#include <stack>

#include "i_command.h"

class CommandManager final{
public:
    CommandManager();

    void execute(std::unique_ptr<ICommand> cmd);
    void undo();
    void redo();

    bool canUndo() const;
    bool canRedo() const;

private:
    std::stack<std::unique_ptr<ICommand>> undoStack;
    std::stack<std::unique_ptr<ICommand>> redoStack;
};

#endif // COMMAND_MANAGER_H
