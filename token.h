#ifndef TOKEN_H
#define TOKEN_H

#include <memory>
#include <vector>
#include <string>

enum class TokenType { //
    Number,
    UnaryOperator,
    BinaryOperator,
};

enum class Associativity { //
    Left,
    Right
};

class Token
{
public:
    virtual ~Token() = default;

    virtual TokenType type() const = 0;

    virtual int getPrecedence() const {
        return 0;
    }

    virtual Associativity getAssociativity() const {
        return Associativity::Left;
    }

};

#endif // TOKEN_H
