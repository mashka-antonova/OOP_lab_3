#include "unary_operator.h"

UnaryOperator::UnaryOperator(const std::string& name, int precedence, Associativity associativity)
    : name(name), precedence(precedence), associativity(associativity)
{}

TokenType UnaryOperator::type() const {
    return TokenType::UnaryOperator;
}

std::unique_ptr<Token> UnaryOperator::clone() const {
    return std::make_unique<UnaryOperator>(name, precedence, associativity);
}

std::string UnaryOperator::toString() const {
    return getName();
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

bool UnaryOperator::isFunction() const {
    return name == "sin"  || name == "cos"
           || name == "tg"   || name == "ctg"
           || name == "sqrt" || name == "1/x";
}
