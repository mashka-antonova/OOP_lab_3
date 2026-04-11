#ifndef TOKENIZER_ERROR_H
#define TOKENIZER_ERROR_H

#include <stdexcept>
#include <string>

class TokenizerError : public std::runtime_error
{
public:
    TokenizerError(const std::string& message, size_t position)
        : std::runtime_error(message)
        , position(position) {}

    size_t getPosition() const {
        return position;
    }

private:
    size_t position;
};

#endif // TOKENIZER_ERROR_H

