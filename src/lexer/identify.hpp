#pragma once

#include <string>
#include <string_view>
#include <optional>
#include <iostream>
#include "type.hpp"

namespace lexer {
class Identify {
    public:
    Identify(std::string lexeme)
        : lexeme(lexeme) {}

    friend std::ostream& operator<<(std::ostream& os, const Identify& identify) {
        os << identify.lexeme;
        return os;
    }

    static std::optional<Identify> parse(std::istream& is) {
        std::string lexeme;
        char c;
        // the same rule as c++ identifier
        while (std::isalnum(c = is.get()) || c == '_') {
            lexeme.push_back(c);
        }
        if (lexeme.empty()) {
            return std::nullopt;
        }
        return Identify(lexeme);
    }

    private:
    std::string lexeme;
};
}