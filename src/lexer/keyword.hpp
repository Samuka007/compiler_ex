/**
* Static tokens
*/

#pragma once

#include <string_view>
#include <optional>
#include <iostream>
#include <fstream>
#include <variant>
#include <array>
#include "type.hpp"
#include "../utils.hpp"

namespace lexer {
    template<typename T>
    concept IsStaticToken = requires(T t, std::ifstream& is) {
        { std::cout << t };
        { t.parse(is) } -> std::same_as<bool>;
    };

    class OneWord {
    public:
        constexpr OneWord(char c)
            : c(c) {}

        bool parse(std::ifstream& is) const {
            char c;
            is.get(c);
            if (c == this->c) {
                return true;
            }
            is.unget();
            return false;
        }

        friend std::ostream& operator<<(std::ostream& os, const OneWord& keyword) {
            os << keyword.c;
            return os;
        }
    private:
        char c;
    };

    class Symbol {
    public:
        constexpr Symbol(std::string_view symbol)
            : symbol(symbol) {}

        bool parse(std::ifstream& is) const {
            char c;
            for (auto ch {symbol.begin()}; ch != symbol.end(); ++ch) {
                is.get(c);
                if (c != *ch) {
                    if (ch == symbol.begin()) {
                        // putback the charactors
                        is.putback(c);
                        return false;
                    }
                    // putback the charactors
                    is.putback(c);
                    while(ch != symbol.begin()) {
                        --ch;
                        is.putback(*ch);
                    }
                    return false;
                }
            }
            return true;
        }

        friend std::ostream& operator<<(std::ostream& os, const Symbol& keyword) {
            os << keyword.symbol;
            return os;
        }
    private:
        std::string_view symbol;
    };

    class Keyword {
    public:
        constexpr Keyword(std::string_view lexeme)
            : lexeme(lexeme) {}

        friend std::ostream& operator<<(std::ostream& os, const Keyword& keyword) {
            os << keyword.lexeme;
            return os;
        }

        bool parse(std::ifstream& is) const {
            char c;
            for (auto ch {lexeme.begin()}; ch != lexeme.end(); ++ch) {
                is.get(c);
                if (c != *ch) {
                    if (ch == lexeme.begin()) {
                        // putback the charactors
                        is.putback(c);
                        return false;
                    }
                    // putback the charactors
                    is.putback(c);
                    while(ch != lexeme.begin()) {
                        --ch;
                        is.putback(*ch);
                    }
                    return false;
                }
            }

            // check if the next character is not a letter or a number
            if (is && !std::isalnum(is.peek())) {
                return true;
            }
            return false;
        }
    private:
        std::string_view lexeme;
    };
    template <IsStaticToken... T>
    class StaticToken_t {
    public:
        constexpr StaticToken_t(TokenTag t, const char keyword)
            : m_tag(t), inner(keyword) {}

        constexpr StaticToken_t(TokenTag t, std::string_view keyword)
            : m_tag(t), inner(Keyword(keyword)) {}

        constexpr StaticToken_t(TokenTag t, Symbol symbol)
            : m_tag(t), inner(symbol) {}

        std::optional<StaticToken_t<T...>> parse(std::ifstream& is) const {
            return std::visit([&](auto&& keyword) -> std::optional<StaticToken_t<T...>> {
                if (keyword.parse(is)) {
                    return *this;
                }
                return std::nullopt;
            }, this->inner);
        }

        friend std::ostream& operator<<(std::ostream& os, const StaticToken_t<T...>& token) {
            std::visit([&](auto&& keyword) {
                os << keyword;
            }, token.inner);
            return os;
        }

        inline TokenType type() const {
            return std::visit(utils::overloaded {
                [](Keyword) { return TokenType::KEYWORD; },
                [](Symbol) { return TokenType::SYMBOL; },
                [](OneWord) { return TokenType::SYMBOL; }
            }, this->inner);
        }

        inline TokenTag tag() const {
            return this->m_tag;
        }
    private:
        TokenTag m_tag;
        std::variant<T...> inner;
    };

    using StaticToken = StaticToken_t<Keyword, OneWord, Symbol>;
    namespace keywords {
        constexpr StaticToken NE(TokenTag::NOT_EQUAL, Symbol("!="));
        constexpr StaticToken EQ(TokenTag::EQUAL, Symbol("=="));
        constexpr StaticToken AND(TokenTag::AND, Symbol("&&"));
        constexpr StaticToken OR(TokenTag::OR, Symbol("||"));
        constexpr StaticToken GE(TokenTag::GREATER_EQUAL, Symbol(">="));
        constexpr StaticToken LE(TokenTag::LESS_EQUAL, Symbol("<="));

        constexpr StaticToken VOID(TokenTag::VOID, "void");
        constexpr StaticToken INT(TokenTag::INT, "int");
        constexpr StaticToken DOUBLE(TokenTag::DOUBLE, "double");
        constexpr StaticToken BOOL(TokenTag::BOOL, "bool");
        constexpr StaticToken STRING(TokenTag::STRING, "string");

        constexpr StaticToken CLASS(TokenTag::CLASS, "class");
        constexpr StaticToken EXTENDS(TokenTag::EXTENDS, "extends");
        constexpr StaticToken FOR(TokenTag::FOR, "for");
        constexpr StaticToken WHILE(TokenTag::WHILE, "while");
        constexpr StaticToken BREAK(TokenTag::BREAK, "break");
        constexpr StaticToken IF(TokenTag::IF, "if");
        constexpr StaticToken ELSE(TokenTag::ELSE, "else");
        constexpr StaticToken RETURN(TokenTag::RETURN, "return");
        constexpr StaticToken STATIC(TokenTag::STATIC, "static");

        constexpr StaticToken NEW(TokenTag::NEW, "new");
        constexpr StaticToken NEW_ARRAY(TokenTag::NEW_ARRAY, "NewArray");
        constexpr StaticToken PRINT(TokenTag::PRINT, "Print");
        constexpr StaticToken READ_INTEGER(TokenTag::READ_INTEGER, "ReadInteger");
        constexpr StaticToken READ_LINE(TokenTag::READ_LINE, "ReadLine");

        constexpr StaticToken FALSE(TokenTag::FALSE, "false");
        constexpr StaticToken TRUE(TokenTag::TRUE, "true");
        constexpr StaticToken NULL_(TokenTag::NULL_, "null");
        constexpr StaticToken THIS(TokenTag::THIS, "this");
        constexpr StaticToken A_MINUS(TokenTag::A_MINUS, "minus");
        constexpr StaticToken INDEX(TokenTag::INDEX, "index");

        constexpr StaticToken COMMENT_A(TokenTag::COMMENT_A, Symbol("//"));
        constexpr StaticToken COMMENT_B_START(TokenTag::COMMENT_B_1, Symbol("/*"));
        constexpr StaticToken COMMENT_B_END(TokenTag::COMMENT_B_2, Symbol("*/"));

        // Onexpre Character Tokens
        constexpr StaticToken SEMICOLON(TokenTag::SEMICOLON, ';');
        constexpr StaticToken COMMA(TokenTag::COMMA, ',');
        constexpr StaticToken DOT(TokenTag::DOT, '.');
        constexpr StaticToken L_PAREN(TokenTag::LEFT_PAREN, '(');
        constexpr StaticToken R_PAREN(TokenTag::RIGHT_PAREN, ')');
        constexpr StaticToken L_SQUARE(TokenTag::LEFT_BRACKET, '[');
        constexpr StaticToken R_SQUARE(TokenTag::RIGHT_BRACKET, ']');
        constexpr StaticToken L_BRACE(TokenTag::LEFT_BRACE, '{');
        constexpr StaticToken R_BRACE(TokenTag::RIGHT_BRACE, '}');
        constexpr StaticToken PLUS(TokenTag::PLUS, '+');
        constexpr StaticToken MINUS(TokenTag::MINUS, '-');
        constexpr StaticToken STAR(TokenTag::STAR, '*');
        constexpr StaticToken DIVIDE(TokenTag::SLASH, '/');
        constexpr StaticToken MODULO(TokenTag::MODULO, '%');
        constexpr StaticToken LESS(TokenTag::LESS, '<');
        constexpr StaticToken GREATER(TokenTag::GREATER, '>');
        constexpr StaticToken BANG(TokenTag::BANG, '!');
        constexpr StaticToken ASSIGN(TokenTag::ASSIGN, '=');
    } // namespace keywords

    constexpr auto KEYWORDS = std::array {
        keywords::COMMENT_A, keywords::COMMENT_B_START, keywords::COMMENT_B_END,
        keywords::NE, keywords::EQ, keywords::AND, keywords::OR, keywords::GE, keywords::LE,
        keywords::VOID, keywords::INT, keywords::DOUBLE, keywords::BOOL, keywords::STRING,
        keywords::CLASS, keywords::EXTENDS, keywords::FOR, keywords::WHILE, keywords::BREAK,
        keywords::IF, keywords::ELSE, keywords::RETURN, keywords::STATIC,
        keywords::NEW, keywords::NEW_ARRAY, keywords::PRINT, keywords::READ_INTEGER, keywords::READ_LINE,
        keywords::FALSE, keywords::TRUE, keywords::NULL_, keywords::THIS, keywords::A_MINUS,
        keywords::INDEX,

        keywords::SEMICOLON, keywords::COMMA, keywords::DOT, keywords::L_PAREN, keywords::R_PAREN,
        keywords::L_SQUARE, keywords::R_SQUARE, keywords::L_BRACE, keywords::R_BRACE,
        keywords::PLUS, keywords::MINUS, keywords::STAR, keywords::DIVIDE, keywords::MODULO,
        keywords::LESS, keywords::GREATER, keywords::BANG, keywords::ASSIGN
    };
}
