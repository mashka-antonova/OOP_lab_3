#include "tokenizer.h"
#include "unary_operator.h"
#include "tokenizer_error.h"

Tokenizer::Tokenizer(std::unique_ptr<TokenCreator> creator)
    : creator(std::move(creator)) {
    initSpecialCharMap();
    initDispatchTable();
}

void Tokenizer::initSpecialCharMap() {
    specialCharMap['('] = CharType::OpenParen;
    specialCharMap[')'] = CharType::CloseParen;
    specialCharMap['+'] = CharType::Operator;
    specialCharMap['-'] = CharType::Operator;
    specialCharMap['*'] = CharType::Operator;
    specialCharMap['/'] = CharType::Operator;
    specialCharMap['.'] = CharType::Dot;
}

void Tokenizer::initDispatchTable() {

    dispatch[CharType::Whitespace] = [this](const std::string& expr, size_t& pos, TokenList& tokens) {
        handleWhiteSpace(expr, pos, tokens);
    };

    dispatch[CharType::Digit] = [this](const std::string& expr, size_t& pos, TokenList& tokens) {
        handleNumber(expr, pos, tokens);
    };

    dispatch[CharType::Dot] = [this](const std::string& expr, size_t& pos, TokenList& tokens) {
        handleNumber(expr, pos, tokens);
    };

    dispatch[CharType::Alpha] = [this](const std::string& expr, size_t& pos, TokenList& tokens) {
        handleWord(expr, pos, tokens);
    };

    dispatch[CharType::Operator] = [this](const std::string& expr, size_t& pos, TokenList& tokens) {
        handleOperator(expr, pos, tokens);
    };

    dispatch[CharType::OpenParen] = [this](const std::string& expr, size_t& pos, TokenList& tokens) {
        handleOpenParen(expr, pos, tokens);
    };

    dispatch[CharType::CloseParen] = [this](const std::string& expr, size_t& pos, TokenList& tokens) {
        handleCloseParen(expr, pos, tokens);
    };

    dispatch[CharType::Unknown] = [this](const std::string& expr, size_t& pos, TokenList& tokens) {
        handleUnknown(expr, pos, tokens);
    };
}

std::vector<std::unique_ptr<Token>> Tokenizer::tokenize(const std::string& expression) const {
    TokenList tokens;
    size_t pos = 0;

    while (pos < expression.size()) {
        CharType category = classify(expression[pos]);
        dispatch.at(category)(expression, pos, tokens);
    }

    if (tokens.empty())
        throw TokenizerError("Empty expression");

    return tokens;
}

CharType Tokenizer::classify(char c) const {
    CharType result = CharType::Unknown;
    if (std::isspace(c))
        result = CharType::Whitespace;
    if (std::isdigit(c))
        result = CharType::Digit;
    if (std::isalpha(c))
        result = CharType::Alpha;
    auto it = specialCharMap.find(c);
    if (it != specialCharMap.end())
        result = it->second;

    return result;
}

void Tokenizer::handleWhiteSpace(const std::string& expr, size_t& pos, TokenList& tokens) const {
    ++pos;
}

void Tokenizer::handleNumber(const std::string& expr, size_t& pos, TokenList& tokens) const {
    size_t start = pos;
    bool hasDot = false;

    while (pos < expr.size()) {
        CharType category = classify(expr[pos]);
        bool isDigit = (category == CharType::Digit);
        bool isDot = (category == CharType::Dot) && !hasDot;

        bool shouldContinue = isDigit || isDot;
        hasDot = hasDot || isDot;

        if (!shouldContinue)
            break;

        ++pos;
    }

    std::string numStr = expr.substr(start, pos - start);

    if (numStr == ".")
        throw TokenizerError("Invalid number: alone point");

    tokens.push_back(creator->createToken("number", numStr));
}

void Tokenizer::handleWord(const std::string& expr, size_t& pos, TokenList& tokens) const {
    size_t start = pos;

    while (pos < expr.size() && std::isalpha((expr[pos])))
        ++pos;

    std::string word = expr.substr(start, pos - start);

    bool isKnown = creator->isOperator(word);
    if (!isKnown)
        throw TokenizerError("Unknown function: '" + word + "'");

    tokens.push_back(creator->createToken(word, word));
}

void Tokenizer::handleOperator(const std::string& expr, size_t& pos, TokenList& tokens) const {
    char ch = expr[pos];
    bool canBeUnary = (ch == '-' || ch == '+');
    bool unaryContext = canBeUnary && isUnaryContext(tokens);

    std::string lexeme = unaryContext
                             ? buildUnaryName(ch)
                             : std::string(1, ch);

    tokens.push_back(creator->createToken(lexeme, lexeme));
    ++pos;
}

void Tokenizer::handleOpenParen(const std::string& expr, size_t& pos, TokenList& tokens) const {
    tokens.push_back(creator->createToken("(", "("));
    ++pos;
}

void Tokenizer::handleCloseParen(const std::string& expr, size_t& pos, TokenList& tokens) const {
    tokens.push_back(creator->createToken(")", ")"));
    ++pos;
}

void Tokenizer::handleUnknown(const std::string& expr, size_t& pos, TokenList& tokens) const {
    throw TokenizerError( std::string("Unexpected char: '") + expr[pos] + "'");
}

bool Tokenizer::isUnaryContext(const TokenList& tokens) const {
    bool result = true;
    if (!tokens.empty()) {
        const Token* last = tokens.back().get();
        TokenType lastType = last->type();

        bool afterBinary = (lastType == TokenType::BinaryOperator);
        bool afterNumber = (lastType == TokenType::Number);
        bool afterNonClosingUnary = false;

        if (lastType == TokenType::UnaryOperator) {
            const UnaryOperator* unary = static_cast<const UnaryOperator*>(last);
            afterNonClosingUnary = !unary->isCloseParen();
        }

        result = afterBinary || afterNonClosingUnary;

        if (afterNumber)
            result = false;
    }
    return result;
}

std::string Tokenizer::buildUnaryName(char ch) const {
    return std::string("unary") + ch;
}
