#ifndef BINARY_OPERATOR_H
#define BINARY_OPERATOR_H

#include "token.h"

class BinaryOperator final : public Token
{
public:
    BinaryOperator(char name, int precedence, Associativity associativity);

    TokenType type() const override;
    std::unique_ptr<Token> clone() const override;
    std::string toString() const override;

    char getName() const;
    int getPrecedence() const;
    Associativity getAssociativity() const;

private:
    char name;
    int precedence;
    Associativity associativity;
};

#endif // BINARY_OPERATOR_H
