#ifndef UNARY_OPERATOR_H
#define UNARY_OPERATOR_H

#include "token.h"

class UnaryOperator final: public Token
{
public:
    UnaryOperator(const std::string& name, int precedence, Associativity associativity);

    TokenType type() const override;
    std::unique_ptr<Token> clone() const override;
    std::string toString() const override;

    const std::string& getName() const;
    int getPrecedence() const;
    Associativity getAssociativity() const;

    bool isOpenParen() const;
    bool isCloseParen() const;
    bool isFunction() const;

private:
    std::string name;
    int precedence;
    Associativity associativity;
};

#endif // UNARY_OPERATOR_H
