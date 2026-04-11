#ifndef TOKEN_CREATOR_H
#define TOKEN_CREATOR_H

#include "token_factory.h"
#include <map>

class TokenCreator {

public:
    explicit TokenCreator(std::map<std::string, TokenFactory*> factories)
        : factories(std::move(factories)) {}

    bool isOperator(const std::string& lexeme) const;

    std::unique_ptr<Token> createToken(const std::string& type, const std::string& lexeme) const;

private:
    std::map<std::string, TokenFactory*> factories;
};

#endif // TOKEN_CREATOR_H
