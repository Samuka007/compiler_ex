#pragma once

#include <string>
#include <optional>
#include <fstream>
#include "../utils.hpp"

namespace lexer {
class Identify {
    public:
    Identify() = delete;
    Identify(std::string&& lexeme)
        : lexeme(std::move(lexeme)) {}

    friend std::ostream& operator<<(std::ostream& os, const Identify& identify) {
        os << identify.lexeme;
        return os;
    }

    static std::optional<Identify> parse(std::ifstream& is) {
        std::string lexeme;
        char c;

        // the same rule as c++ identifier
        // the first character must be a letter or an underscore
        if (!is.get(c)) {
            throw utils::UnexpectedEOF();
        }
        if (!std::isalpha(c) && c != '_') {
            is.unget();
            return std::nullopt;
        }
        lexeme.push_back(c);
        while (true) {
            if (!is.get(c)) {
                throw utils::UnexpectedEOF();
            }
            if (!std::isalnum(c) && c != '_') {
                is.unget();
                break;
            }
            lexeme.push_back(c);
        }
        return Identify(std::move(lexeme));
    }

    private:
    std::string lexeme;
};
}