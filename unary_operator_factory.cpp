#include "unary_operator_factory.h"
#include "unary_operator.h"

UnaryOperatorFactory::UnaryOperatorFactory(int precedence, Associativity associativity)
    : precedence(precedence), associativity(associativity) {}

std::unique_ptr<Token> UnaryOperatorFactory::create(const std::string& lexeme) {
    return std::make_unique<UnaryOperator>(lexeme, precedence, associativity);
}
