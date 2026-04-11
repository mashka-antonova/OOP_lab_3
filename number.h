#ifndef NUMBER_H
#define NUMBER_H

#include "token.h"

class Number : public Token
{
public:
    explicit Number(double num);

    TokenType type() const override;
    std::unique_ptr<Token> clone() const override;
    std::string toString() const override;

private:
    double value;
};

#endif // NUMBER_H
