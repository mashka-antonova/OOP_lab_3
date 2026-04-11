#ifndef NUMBER_FACTORY_H
#define NUMBER_FACTORY_H

#include "token_factory.h"

class NumberFactory : public TokenFactory
{
public:
    std::unique_ptr<Token> create(const std::string& lexeme) override;
};

#endif // NUMBER_FACTORY_H
