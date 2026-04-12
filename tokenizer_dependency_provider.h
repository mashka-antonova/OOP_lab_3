#ifndef TOKENIZER_DEPENDENCY_PROVIDER_H
#define TOKENIZER_DEPENDENCY_PROVIDER_H

#include "token_creator.h"

class TokenizerDependencyProvider
{
public:
    TokenizerDependencyProvider();
    std::unique_ptr<TokenCreator> createTokenCreator();

private:
    std::vector<std::unique_ptr<TokenFactory>> factoryStorage;
    std::map<std::string, TokenFactory*> factoryMap;

    template<typename T, typename... Args>
    void registerFactory(const std::string& lexeme, Args&&... args);
};

#endif // TOKENIZER_DEPENDENCY_PROVIDER_H
