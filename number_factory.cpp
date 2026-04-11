#include "number_factory.h"
#include "number.h"

std::unique_ptr<Token> NumberFactory::create(const std::string& lexeme) {
    return std::make_unique<Number>(std::stod(lexeme));
}
