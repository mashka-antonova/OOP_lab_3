#ifndef UNARY_OPERATOR_FACTORY_H
#define UNARY_OPERATOR_FACTORY_H

#include "token_factory.h"

class UnaryOperatorFactory: public TokenFactory
{
public:
    UnaryOperatorFactory(int precedence, Associativity associativity);
    std::unique_ptr<Token> create(const std::string& lexeme) override;

private:
    int precedence;
    Associativity associativity;
};

#endif // UNARY_OPERATOR_FACTORY_H
