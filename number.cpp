#include "number.h"

Number::Number(double num)
    : value(num) {}

TokenType Number::type() const {
    return TokenType::Number;
}

double Number::getValue() const {
    return value;
}
