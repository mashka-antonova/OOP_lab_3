#ifndef TOKENIZER_DEPENDENCY_PROVIDER_H
#define TOKENIZER_DEPENDENCY_PROVIDER_H

#include "token_creator.h"

class TokenizerDependencyProvider
{
public:
    TokenizerDependencyProvider();
    std::unique_ptr<TokenCreator> createTokenCreator();

private:
    std::map<std::string, std::shared_ptr<TokenFactory>> factoryMap;

    template<typename T, typename... Args>
    void registerFactory(const std::string& lexeme, Args&&... args);
};

#endif // TOKENIZER_DEPENDENCY_PROVIDER_H
