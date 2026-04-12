#ifndef TOKENIZER_ERROR_H
#define TOKENIZER_ERROR_H

#include <stdexcept>
#include <string>

class TokenizerError : public std::runtime_error
{
public:
    TokenizerError(const std::string& message)
        : std::runtime_error(message) {}

};

#endif // TOKENIZER_ERROR_H

