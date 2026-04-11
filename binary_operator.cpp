#include "binary_operator.h"

BinaryOperator::BinaryOperator(char name, int precedence, Associativity associativity)
    : name(name), precedence(precedence), associativity(associativity) {}

TokenType BinaryOperator::type() const {
    return TokenType::BinaryOperator;
}

std::unique_ptr<Token> BinaryOperator::clone() const {
    return std::make_unique<BinaryOperator>(name, precedence, associativity);
}

std::string BinaryOperator::toString() const {
    return std::string(1, name);
}

char BinaryOperator::getName() const {
    return name;
}

int BinaryOperator::getPrecedence() const {
    return precedence;
}

Associativity BinaryOperator::getAssociativity() const {
    return associativity;
}
