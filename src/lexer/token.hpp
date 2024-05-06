// define lexer token

#ifndef LEXER_TOKEN_HPP
#define LEXER_TOKEN_HPP

#include <iostream>
#include <optional>
#include <variant>
#include "utils.hpp"
#include "identify.hpp"
#include "string_literals.hpp"
#include "type.hpp"
#include "keyword.hpp"
#include "number.hpp"

namespace lexer {

class DynamicToken {
public:
    using dynamic_type = std::variant<Integer, Real, StringLiteral, Identify>;
    DynamicToken() = delete;
    DynamicToken(std::ifstream& is)
    : value {
        [&] () {
        if (auto integer = Integer::parse(is); integer.has_value()) {
            return dynamic_type(integer.value());
        } else if (auto real = Real::parse(is); real.has_value()) {
            return dynamic_type(real.value());
        } else if (auto str = StringLiteral::parse(is); str.has_value()) {
            return dynamic_type(str.value());
        } else if (auto identify = Identify::parse(is); identify.has_value()) {
            return dynamic_type(identify.value());
        } else {
            throw utils::UnexpectedToken();
        }
        } ()
    } {}

    friend std::ostream& operator<<(std::ostream& os, const DynamicToken& token) {
        std::visit([&](auto&& value) {
            os << value;
        }, token.value);
        return os;
    }

    TokenType type() const {
        return std::visit(utils::overloaded {
            // string literal
            [](Integer) { return TokenType::NUMBER; },
            [](Real) { return TokenType::NUMBER; },
            [](StringLiteral) { return TokenType::LITERAL; },
            [](Identify) { return TokenType::IDENTIFIER; }
        }, this->value);
    }

    TokenTag tag() const {
        return std::visit(utils::overloaded {
            // string literal
            [](Integer) { return TokenTag::LITERAL; },
            [](Real) { return TokenTag::LITERAL; },
            [](StringLiteral) { return TokenTag::LITERAL; },
            [](Identify) { return TokenTag::IDENTIFIER; }
        }, this->value);
    }

private:
    dynamic_type value;
};

class Token {
    using token_t = std::variant<StaticToken, DynamicToken>;
public:
    Token(std::ifstream& is)
    : inner {
        [&] () {
            // utils::clean_whitespace(is);
            // parse all static tokens then dynamic tokens
            for (const auto& token : KEYWORDS) {
                if (token.parse(is)) {
                    return token_t {token};
                }
            }
            return token_t {DynamicToken(is)};
        } ()
    } {}

    friend std::ostream& operator<<(std::ostream& os, const Token& token) {
        if (!token.inner.has_value()) {
            throw utils::EmptyToken();
        }
        std::visit([&](auto&& value) {
            os << value;
        }, token.inner.value());
        return os;
    }

    TokenType type() const {
        if (!this->inner.has_value()) {
            throw utils::EmptyToken();
        }
        return std::visit([](auto&& token){
            return token.type();
        }, this->inner.value());
    }

    TokenTag tag() const {
        if (!this->inner.has_value()) {
            throw utils::EmptyToken();
        }
        return std::visit([](auto&& token){
            return token.tag();
        }, this->inner.value());
    }
private:
    std::optional<token_t> inner = std::nullopt;
};

} // namespace lexer

#endif // TOKEN