// define lexer token

#ifndef LEXER_TOKEN_HPP
#define LEXER_TOKEN_HPP

// #include <string>
// #include <string_view>
#include <array>
#include <iostream>
// #include <string>
#include <optional>
#include <string_view>
#include <variant>
#include "../utils.hpp"
#include "identify.hpp"
#include "type.hpp"
#include "keyword.hpp"
#include "number.hpp"

namespace lexer {

// template <typename T>
// concept IsDynamicToken = requires(T t, std::ifstream& is) {
//     { T::parse(is) } -> std::same_as<std::optional<T>>;
// };

class DynamicToken {
public:
    using dynamic_type = std::variant<Integer, Real, Identify>;
    DynamicToken() = delete;
    DynamicToken(std::ifstream& is)
    : value {
        [&] () {
        if (auto real = Real::parse(is); real.has_value()) {
            return dynamic_type(real.value());
        } else if (auto integer = Integer::parse(is); integer.has_value()) {
            return dynamic_type(integer.value());
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

private:
    dynamic_type value;
};

class Token {
    using token_t = std::variant<StaticToken, DynamicToken>;
public:
    Token(std::ifstream& is)
    : inner {
        [&] () {
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


private:
    std::optional<token_t> inner = std::nullopt;
};

} // namespace lexer

#endif // TOKEN