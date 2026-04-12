#ifndef UNARY_OPERATOR_H
#define UNARY_OPERATOR_H

#include "token.h"

class UnaryOperator final: public Token
{
public:
    UnaryOperator(const std::string& name, int precedence, Associativity associativity);

    TokenType type() const override;

    const std::string& getName() const;
    int getPrecedence() const override;
    Associativity getAssociativity() const override;

    bool isOpenParen() const;
    bool isCloseParen() const;

private:
    std::string name;
    int precedence;
    Associativity associativity;
};

#endif // UNARY_OPERATOR_H
