#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include "token.h"

#include <functional>
#include <map>
#include <memory>
#include <stack>
#include <vector>

class ShuntingYard
{
public:
    ShuntingYard();
    std::vector<std::unique_ptr<Token>> convertToRPN (std::vector<std::unique_ptr<Token>> infix);

private:
    std::vector<std::unique_ptr<Token>> output;
    std::stack<std::unique_ptr<Token>> operators;
    std::map<TokenType, std::function<void(std::unique_ptr<Token>)>> dispatch;

    void initDispatch();
    void resetState();
    void flushRemainingOperators();

    void handleNumber(std::unique_ptr<Token> token);
    void handleBinaryOperator(std::unique_ptr<Token> token);
    void handleUnaryOperator(std::unique_ptr<Token> token);
    void handleCloseParen();

    void pushToOperators(std::unique_ptr<Token> token);
    void popOperatorsByPrecedence(const Token& current);
    void popUntilOpenParen();
    void popFunctionsAboveOpenParen();

    bool shouldPopForBinary(const Token& current) const;
    bool isTopOpenParen() const;
    bool topIsNonParenUnary() const;

};

#endif // SHUNTING_YARD_H
