/**
* Static tokens
*/

#pragma once

#include <exception>
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
            if (is.get(c) && c == this->c) {
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
                if (!is.get(c)) {
                    throw utils::UnexpectedEOF();
                }
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
        constexpr StaticToken_t(TokenType t, const char keyword)
            : m_type(t), inner(keyword) {}
        
        constexpr StaticToken_t(TokenType t, std::string_view keyword)
            : m_type(t), inner(keyword) {}

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
    private:
        TokenType m_type;
        std::variant<T...> inner;
    };

    using StaticToken = StaticToken_t<Keyword, OneWord>;
    namespace keywords {
        constexpr StaticToken NE(TokenType::NOT_EQUAL, "!=");
        constexpr StaticToken EQ(TokenType::EQUAL, "==");
        constexpr StaticToken AND(TokenType::AND, "&&");
        constexpr StaticToken OR(TokenType::OR, "||");
        constexpr StaticToken GE(TokenType::GREATER_EQUAL, ">=");
        constexpr StaticToken LE(TokenType::LESS_EQUAL, "<=");

        constexpr StaticToken VOID(TokenType::VOID, "void");
        constexpr StaticToken INT(TokenType::INT, "int");
        constexpr StaticToken DOUBLE(TokenType::DOUBLE, "double");
        constexpr StaticToken BOOL(TokenType::BOOL, "bool");
        constexpr StaticToken STRING(TokenType::STRING, "string");

        constexpr StaticToken CLASS(TokenType::CLASS, "class");
        constexpr StaticToken EXTENDS(TokenType::EXTENDS, "extends");
        constexpr StaticToken FOR(TokenType::FOR, "for");
        constexpr StaticToken WHILE(TokenType::WHILE, "while");
        constexpr StaticToken BREAK(TokenType::BREAK, "break");
        constexpr StaticToken IF(TokenType::IF, "if");
        constexpr StaticToken ELSE(TokenType::ELSE, "else");
        constexpr StaticToken RETURN(TokenType::RETURN, "return");
        constexpr StaticToken STATIC(TokenType::STATIC, "static");

        constexpr StaticToken NEW(TokenType::NEW, "new");
        constexpr StaticToken NEW_ARRAY(TokenType::NEW_ARRAY, "NewArray");
        constexpr StaticToken PRINT(TokenType::PRINT, "Print");
        constexpr StaticToken READ_INTEGER(TokenType::READ_INTEGER, "ReadInteger");
        constexpr StaticToken READ_LINE(TokenType::READ_LINE, "ReadLine");

        constexpr StaticToken FALSE(TokenType::FALSE, "false");
        constexpr StaticToken TRUE(TokenType::TRUE, "true");
        constexpr StaticToken NULL_(TokenType::NULL_, "null");
        constexpr StaticToken THIS(TokenType::THIS, "this");
        constexpr StaticToken A_MINUS(TokenType::A_MINUS, "minus");
        constexpr StaticToken INDEX(TokenType::INDEX, "index");

        // Onexpre Character Tokens
        constexpr StaticToken SEMICOLON(TokenType::SEMICOLON, ';');
        constexpr StaticToken COMMA(TokenType::COMMA, ',');
        constexpr StaticToken DOT(TokenType::DOT, '.');
        constexpr StaticToken L_PAREN(TokenType::LEFT_PAREN, '(');
        constexpr StaticToken R_PAREN(TokenType::RIGHT_PAREN, ')');
        constexpr StaticToken L_SQUARE(TokenType::LEFT_BRACKET, '[');
        constexpr StaticToken R_SQUARE(TokenType::RIGHT_BRACKET, ']');
        constexpr StaticToken L_BRACE(TokenType::LEFT_BRACE, '{');
        constexpr StaticToken R_BRACE(TokenType::RIGHT_BRACE, '}');
        constexpr StaticToken PLUS(TokenType::PLUS, '+');
        constexpr StaticToken MINUS(TokenType::MINUS, '-');
        constexpr StaticToken STAR(TokenType::STAR, '*');
        constexpr StaticToken DIVIDE(TokenType::SLASH, '/');
        constexpr StaticToken MODULO(TokenType::MODULO, '%');
        constexpr StaticToken LESS(TokenType::LESS, '<');
        constexpr StaticToken GREATER(TokenType::GREATER, '>');
        constexpr StaticToken BANG(TokenType::BANG, '!');
        constexpr StaticToken ASSIGN(TokenType::ASSIGN, '=');
    } // namespace keywords

    constexpr auto KEYWORDS = std::array {
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
