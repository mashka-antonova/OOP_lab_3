#include "shunting_yard.h"

#include "unary_operator.h"
#include <stdexcept>

ShuntingYard::ShuntingYard() {
    initDispatch();
}

void ShuntingYard::initDispatch() {
    dispatch[TokenType::Number] = [this](std::unique_ptr<Token> t) {handleNumber(std::move(t));};
    dispatch[TokenType::BinaryOperator] = [this](std::unique_ptr<Token> t) {handleBinaryOperator(std::move(t));};
    dispatch[TokenType::UnaryOperator] = [this](std::unique_ptr<Token> t) {handleUnaryOperator(std::move(t));};
}

void ShuntingYard::resetState() {
    output.clear();
    while (!operators.empty())
        operators.pop();
}

void ShuntingYard::flushRemainingOperators() {
    while (!operators.empty()) {
        if (isTopOpenParen())
            throw std::runtime_error("ShuntingYard: mismatched open parenthesis");
        output.push_back(std::move(operators.top()));
        operators.pop();
    }
}

std::vector<std::unique_ptr<Token>> ShuntingYard::convertToRPN(std::vector<std::unique_ptr<Token>> lexemes) {
    resetState();
    for (auto& token : lexemes)
        dispatch.at(token->type())(std::move(token));
    flushRemainingOperators();
    return std::move(output);
}

void ShuntingYard::handleNumber(std::unique_ptr<Token> token) {
    output.push_back(std::move(token));
}

void ShuntingYard::handleBinaryOperator(std::unique_ptr<Token> token) {
    popOperatorsByPrecedence(*token);
    pushToOperators(std::move(token));
}

void ShuntingYard::handleUnaryOperator(std::unique_ptr<Token> token) {
    const UnaryOperator* op = static_cast<const UnaryOperator*>(token.get());
    op->isCloseParen() ? handleCloseParen()
                       : pushToOperators(std::move(token));
}

void ShuntingYard::handleCloseParen() {
    popUntilOpenParen();
    popFunctionsAboveOpenParen();
}

void ShuntingYard::pushToOperators(std::unique_ptr<Token> token) {
    operators.push(std::move(token));
}

void ShuntingYard::popOperatorsByPrecedence(const Token& current) {
    while (shouldPopForBinary(current)) {
        output.push_back(std::move(operators.top()));
        operators.pop();
    }
}

void ShuntingYard::popUntilOpenParen() {
    while (!operators.empty() && !isTopOpenParen()) {
        output.push_back(std::move(operators.top()));
        operators.pop();
    }
    if (operators.empty())
        throw std::runtime_error("ShuntingYard: mismatched close parenthesis");
    operators.pop();
}

void ShuntingYard::popFunctionsAboveOpenParen() {
    while (topIsNonParenUnary()) {
        output.push_back(std::move(operators.top()));
        operators.pop();
    }
}

bool ShuntingYard::shouldPopForBinary(const Token& current) const {
    return !operators.empty() && !isTopOpenParen() && (operators.top()->getPrecedence() > current.getPrecedence()
            || (operators.top()->getPrecedence() == current.getPrecedence() && current.getAssociativity() == Associativity::Left));
}

bool ShuntingYard::isTopOpenParen() const {
    return !operators.empty() &&
           operators.top()->type() == TokenType::UnaryOperator &&
           static_cast<const UnaryOperator&>(*operators.top()).isOpenParen();
}

bool ShuntingYard::topIsNonParenUnary() const {
    return !operators.empty()
           && operators.top()->type() == TokenType::UnaryOperator
           && !static_cast<const UnaryOperator&>(*operators.top()).isOpenParen()
           && !static_cast<const UnaryOperator&>(*operators.top()).isCloseParen();
}

