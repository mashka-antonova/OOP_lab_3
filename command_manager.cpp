#include "command_manager.h"

CommandManager::CommandManager() {}

void CommandManager::execute(std::unique_ptr<ICommand> cmd) {
    cmd->execute();
    undoStack.push(std::move(cmd));
    while (!redoStack.empty())
        redoStack.pop();
}

void CommandManager::undo() {
    if (canUndo()) {
        std::unique_ptr<ICommand> cmd = std::move(undoStack.top());
        undoStack.pop();
        cmd->undo();
        redoStack.push(std::move(cmd));
    }
}

void CommandManager::redo() {
    if (canRedo()) {
        std::unique_ptr<ICommand> cmd = std::move(redoStack.top());
        redoStack.pop();
        cmd->execute();
        undoStack.push(std::move(cmd));
    }
}

bool CommandManager::canUndo() const {
    return !undoStack.empty();
}

bool CommandManager::canRedo() const {
    return !redoStack.empty();
}
