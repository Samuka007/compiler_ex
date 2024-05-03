#include "lexer.hpp"

namespace lexer {
    Token lex(std::istream& is) {
        for (auto key : KEYWORDS) {
            
            auto is_static = std::visit(overloaded {
                [&](Keyword keyword) {
                    if (auto token = keyword.parse(is)) {
                        return true;
                    }
                    return false;
                },
                [&](OneWord oneWord) {
                    if (auto token = oneWord.parse(is)) {
                        return true;
                    }
                    return false;
                },
                [&](auto&& other) {
                    return false;
                }
            }, key.value);
            is.clear();
            if (is_static) {
                return key;
            }
        }

        if (auto token = Real::parse(is)) {
            return Token(std::move(token.value()));
        }
        is.clear();
        if (auto token = Integer::parse(is)) {
            return Token(std::move(token.value()));
        }
        is.clear();
        if (auto token = Identify::parse(is)) {
            return Token(std::move(token.value()));
        }
        throw std::runtime_error("Unknown token");
    }
}