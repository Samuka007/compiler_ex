#pragma once

#include <string>
#include <optional>
#include <fstream>

namespace lexer {
    class StringLiteral {
    public:
        StringLiteral() = delete;
        StringLiteral(std::string&& lexeme)
            : lexeme(std::move(lexeme)) {}

        friend std::ostream& operator<<(std::ostream& os, const StringLiteral& string_literal) {
            os << string_literal.lexeme;
            return os;
        }

        static std::optional<StringLiteral> parse(std::ifstream& is) {
            std::string lexeme;
            char c;

            // the first character must be a double quote
            is.get(c);
            if (c != '"') {
                is.unget();
                return std::nullopt;
            }
            while (true) {
                is.get(c);
                if (c == '"') {
                    return StringLiteral(std::move(lexeme));
                }
                lexeme.push_back(c);
            }

        }

    private:
        std::string lexeme;
    };
}