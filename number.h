#ifndef NUMBER_H
#define NUMBER_H

#include "token.h"

class Number : public Token
{
public:
    explicit Number(double num);

    TokenType type() const override;
    double getValue() const;

private:
    double value;
};

#endif // NUMBER_H
