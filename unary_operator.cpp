#include "unary_operator.h"

UnaryOperator::UnaryOperator(const std::string& name, int precedence, Associativity associativity)
    : name(name), precedence(precedence), associativity(associativity)
{}

TokenType UnaryOperator::type() const {
    return TokenType::UnaryOperator;
}

const std::string& UnaryOperator::getName() const {
    return name;
}

int UnaryOperator::getPrecedence() const {
    return precedence;
}

Associativity UnaryOperator::getAssociativity() const {
    return associativity;
}

bool UnaryOperator::isOpenParen() const {
    return name == "(";
}

bool UnaryOperator::isCloseParen() const {
    return name == ")";
}
