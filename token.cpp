#include "token.h"

std::vector<std::unique_ptr<Token>> Token::cloneList(const std::vector<std::unique_ptr<Token>>& source) {
    std::vector<std::unique_ptr<Token>> copy;
    copy.reserve(source.size());
    for (const auto& token : source) {
        copy.push_back(token->clone());
    }
    return copy;
}
