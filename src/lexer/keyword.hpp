// words

#ifndef LEXER_KEYWORD_HPP
#define LEXER_KEYWORD_HPP

#include <string_view>
// #include <string>
#include <optional>
#include <iostream>
#include "type.hpp"

namespace lexer {
    class OneWord {
    public:
        OneWord(char c)
            : c(c) {}

        friend std::ostream& operator<<(std::ostream& os, const OneWord& oneWord) {
            os << oneWord.c;
            return os;
        }

        std::optional<OneWord> parse(std::istream& is) {
            char c;
            if (is.get(c) && c == this->c) {
                return *this;
            }
            return std::nullopt;
        }
    private:
        char c;
    };

    class Keyword {
    public:
        Keyword(std::string_view lexeme)
            : lexeme(lexeme) {}

        friend std::ostream& operator<<(std::ostream& os, const Keyword& keyword) {
            os << keyword.lexeme;
            return os;
        }

        std::optional<Keyword> parse(std::istream& is) {
            // using dfa to check if the following word is keyword same as this.lexeme
            // first, clean the leading whitespaces
            char c;
            while (std::isspace(c = is.get())) {
                continue;
            }
            
            // then check if the first character is the same as the first character of the keyword
            auto it = lexeme.begin();
            if (c != *it) {
                return std::nullopt;
            }

            // then check the rest of the characters
            while (it != lexeme.end()) {
                if (c != *it) {
                    return std::nullopt;
                }
                c = is.get();
                ++it;
            }

            // check end, if the next character is not a letter, then the keyword is found
            if (!std::isalpha(is.peek())) {
                return *this;
            }
            return std::nullopt;
        }
    private:
        std::string_view lexeme;
    };

}

#endif // LEXER_KEYWORD_HPP