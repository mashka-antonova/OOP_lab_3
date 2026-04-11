#ifndef TOKEN_H
#define TOKEN_H

#include <memory>
#include <vector>
#include <string>

enum class TokenType {
    Number,
    UnaryOperator,
    BinaryOperator,
};

enum class Associativity {
    Left,
    Right
};

class Token
{
public:
    virtual ~Token() = default;

    virtual TokenType type() const = 0;
    virtual std::unique_ptr<Token> clone() const = 0;
    virtual std::string toString() const = 0;

    virtual int getPrecedence() const {
        return 0;
    }

    virtual Associativity getAssociativity() const {
        return Associativity::Left;
    }

    static std::vector<std::unique_ptr<Token>> cloneList(const std::vector<std::unique_ptr<Token>>& source); //возможно потом вынести выше(memento)
};

#endif // TOKEN_H
