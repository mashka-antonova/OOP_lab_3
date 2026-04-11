#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token.h"
#include "token_creator.h"
#include <string>
#include <vector>
#include <functional>
#include <map>

enum class CharType {
    Whitespace,
    Digit,
    Dot,
    Alpha,
    Operator,
    OpenParen,
    CloseParen,
    Unknown
};

class Tokenizer
{
public:
    explicit Tokenizer(std::unique_ptr<TokenCreator> creator);
    std::vector<std::unique_ptr<Token>> tokenize(const std::string& expression) const;

private:
    using TokenList = std::vector<std::unique_ptr<Token>>;
    using Handler = std::function<void(const std::string&, size_t&, TokenList&)>;

    std::unique_ptr<TokenCreator>  creator;
    std::map<CharType, Handler> dispatch;
    std::map<char, CharType> specialCharMap;

    void initSpecialCharMap();
    void initDispatchTable();

    CharType classify(char ch) const;

    void handleWhiteSpace(const std::string& expr, size_t& pos, TokenList& tokens) const;
    void handleNumber(const std::string& expr, size_t& pos, TokenList& tokens) const;
    void handleWord(const std::string& expr, size_t& pos, TokenList& tokens) const;
    void handleOperator(const std::string& expr, size_t& pos, TokenList& tokens) const;
    void handleOpenParen(const std::string& expr, size_t& pos, TokenList& tokens) const;
    void handleCloseParen(const std::string& expr, size_t& pos, TokenList& tokens) const;
    void handleUnknown(const std::string& expr, size_t& pos, TokenList& tokens) const;

    bool isUnaryContext(const TokenList& tokens) const;
    std::string buildUnaryName(char ch) const;
};

#endif // TOKENIZER_H
