#include "token_creator.h"
#include <stdexcept>


bool TokenCreator::isOperator(const std::string& lexeme) const {
    return factories.count(lexeme) > 0 && lexeme != "number";
}

std::unique_ptr<Token> TokenCreator::createToken(const std::string& type, const std::string& lexeme) const {
    auto it = factories.find(type);
    if (it == factories.end())
        throw std::invalid_argument("Unknown token type: " + type);
    return it->second->create(lexeme);
}
