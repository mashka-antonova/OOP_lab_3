#ifndef I_COMMAND_H
#define I_COMMAND_H

class ICommand {
public:
    virtual ~ICommand() = default;

    virtual void execute() = 0;
    virtual void undo() = 0;
};

#endif // I_COMMAND_H
