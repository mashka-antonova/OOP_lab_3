#ifndef TOKEN_FACTORY_H
#define TOKEN_FACTORY_H

#include "token.h"

class TokenFactory
{
public:
    virtual ~TokenFactory() = default;

    virtual std::unique_ptr<Token> create(const std::string& lexeme) = 0;
};

#endif // TOKEN_FACTORY_H
