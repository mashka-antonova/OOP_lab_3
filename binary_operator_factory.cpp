#include "binary_operator_factory.h"
#include "binary_operator.h"

BinaryOperatorFactory::BinaryOperatorFactory(int prec, Associativity assoc)
    : precedence(prec), associativity(assoc) {}

std::unique_ptr<Token> BinaryOperatorFactory::create(const std::string& lexeme) {
    return std::make_unique<BinaryOperator>(lexeme[0], precedence, associativity);
}
