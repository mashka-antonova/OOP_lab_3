#include "tokenizer_dependency_provider.h"
#include "binary_operator_factory.h"
#include "unary_operator_factory.h"
#include "number_factory.h"

TokenizerDependencyProvider::TokenizerDependencyProvider() {

    registerFactory<BinaryOperatorFactory>("+", 1, Associativity::Left);
    registerFactory<BinaryOperatorFactory>("-", 1, Associativity::Left);
    registerFactory<BinaryOperatorFactory>("*", 2, Associativity::Left);
    registerFactory<BinaryOperatorFactory>("/", 2, Associativity::Left);

    registerFactory<UnaryOperatorFactory>("unary+", 5, Associativity::Right);
    registerFactory<UnaryOperatorFactory>("unary-", 5, Associativity::Right);
    registerFactory<UnaryOperatorFactory>("sin", 5, Associativity::Right);
    registerFactory<UnaryOperatorFactory>("cos", 5, Associativity::Right);
    registerFactory<UnaryOperatorFactory>("(", 0, Associativity::Right);
    registerFactory<UnaryOperatorFactory>(")", 0, Associativity::Right);

    registerFactory<NumberFactory>("number");
}

template<typename T, typename... Args>
void TokenizerDependencyProvider::registerFactory(const std::string& lexeme, Args&&... args) {
    auto factory = std::make_unique<T>(std::forward<Args>(args)...);
    factoryMap[lexeme] = factory.get();
    factoryStorage.push_back(std::move(factory));
}

std::unique_ptr<TokenCreator> TokenizerDependencyProvider::createTokenCreator() {
    return std::make_unique<TokenCreator>(factoryMap);
}
