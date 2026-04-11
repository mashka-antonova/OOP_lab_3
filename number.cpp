#include "number.h"

Number::Number(double num)
    : value(num) {}

TokenType Number::type() const {
    return TokenType::Number;
}

std::unique_ptr<Token> Number::clone() const {
    return std::make_unique<Number>(value);
}

std::string Number::toString() const {
    std::string str = std::to_string(value);
    size_t dot = str.find('.');
    if (dot != std::string::npos) {
        str.erase(str.find_last_not_of('0') + 1, std::string::npos);
        if (str.back() == '.') str.pop_back();
    }
    return str;
}

double Number::getValue() const {
    return value;
}
