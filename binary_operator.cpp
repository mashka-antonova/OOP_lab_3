#include "binary_operator.h"

BinaryOperator::BinaryOperator(char name, int precedence, Associativity associativity)
    : name(name), precedence(precedence), associativity(associativity) {}

TokenType BinaryOperator::type() const {
    return TokenType::BinaryOperator;
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
