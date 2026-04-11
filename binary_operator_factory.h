#ifndef BINARY_OPERATOR_FACTORY_H
#define BINARY_OPERATOR_FACTORY_H

#include "token_factory.h"

class BinaryOperatorFactory : public TokenFactory
{
public:
    BinaryOperatorFactory(int precedence, Associativity associativity);
    std::unique_ptr<Token> create(const std::string& lexeme)  override;
private:
    int precedence;
    Associativity associativity;
};

#endif // BINARY_OPERATOR_FACTORY_H
