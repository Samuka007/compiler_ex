// define lexer token

#ifndef LEXER_TOKEN_HPP
#define LEXER_TOKEN_HPP

// #include <string>
// #include <string_view>
#include <array>
#include <iostream>
// #include <string>
#include <string_view>
#include <variant>
#include "identify.hpp"
#include "type.hpp"
#include "keyword.hpp"
#include "number.hpp"

namespace lexer {

// A token object can output using the << operator`
template <typename T>
concept TokenObject = requires(T t) {
    { std::cout << t };
};

using token_t = std::variant<Keyword, OneWord, Integer, Real, Identify>;

class Token {
public:
    // Token(TokenType type, token_t value)
    //     : type(type), value(value) {}
    Token(TokenType type, char value)
        : type(type), value(OneWord(value)) {}

    Token(TokenType type, std::string_view value)
        : type(type), value(Keyword(value)) {}
    
    Token(Integer&& value)
        : type(TokenType::INT), value(value) {}
    
    Token(Real&& value)
        : type(TokenType::DOUBLE), value(value) {}

    Token(Identify&& value)
        : type(TokenType::IDENTIFIER), value(value) {}

    TokenType type;
    token_t value;

    friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

// helper type for the visitor #4
template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

} // namespace lexer

namespace lexer {
    namespace keywords {
        const Token NE(TokenType::NOT_EQUAL, "!=");
        const Token EQ(TokenType::EQUAL, "==");
        const Token AND(TokenType::AND, "&&");
        const Token OR(TokenType::OR, "||");
        const Token GE(TokenType::GREATER_EQUAL, ">=");
        const Token LE(TokenType::LESS_EQUAL, "<=");

        const Token VOID(TokenType::VOID, "void");
        const Token INT(TokenType::INT, "int");
        const Token DOUBLE(TokenType::DOUBLE, "double");
        const Token BOOL(TokenType::BOOL, "bool");
        const Token STRING(TokenType::STRING, "string");

        const Token CLASS(TokenType::CLASS, "class");
        const Token EXTENDS(TokenType::EXTENDS, "extends");
        const Token FOR(TokenType::FOR, "for");
        const Token WHILE(TokenType::WHILE, "while");
        const Token BREAK(TokenType::BREAK, "break");
        const Token IF(TokenType::IF, "if");
        const Token ELSE(TokenType::ELSE, "else");
        const Token RETURN(TokenType::RETURN, "return");
        const Token STATIC(TokenType::STATIC, "static");

        const Token NEW(TokenType::NEW, "new");
        const Token NEW_ARRAY(TokenType::NEW_ARRAY, "NewArray");
        const Token PRINT(TokenType::PRINT, "print");
        const Token READ_INTEGER(TokenType::READ_INTEGER, "ReadInteger");
        const Token READ_LINE(TokenType::READ_LINE, "ReadLine");
        
        const Token FALSE(TokenType::FALSE, "false");
        const Token TRUE(TokenType::TRUE, "true");
        const Token NULL_(TokenType::NULL_, "null");
        const Token THIS(TokenType::THIS, "this");
        const Token A_MINUS(TokenType::A_MINUS, "minus");
        const Token INDEX(TokenType::INDEX, "index");

        // One Character Tokens
        const Token SEMICOLON(TokenType::SEMICOLON, ';');
        const Token COMMA(TokenType::COMMA, ',');
        const Token DOT(TokenType::DOT, '.');
        const Token L_PAREN(TokenType::LEFT_PAREN, '(');
        const Token R_PAREN(TokenType::RIGHT_PAREN, ')');
        const Token L_SQUARE(TokenType::LEFT_BRACKET, '[');
        const Token R_SQUARE(TokenType::RIGHT_BRACKET, ']');
        const Token L_BRACE(TokenType::LEFT_BRACE, '{');
        const Token R_BRACE(TokenType::RIGHT_BRACE, '}');
        const Token PLUS(TokenType::PLUS, '+');
        const Token MINUS(TokenType::MINUS, '-');
        const Token STAR(TokenType::STAR, '*');
        const Token DIVIDE(TokenType::SLASH, '/');
        const Token MODULO(TokenType::MODULO, '%');
        const Token LESS(TokenType::LESS, '<');
        const Token GREATER(TokenType::GREATER, '>');
        const Token BANG(TokenType::BANG, '!');
        const Token ASSIGN(TokenType::ASSIGN, '=');
    } // namespace keywords

    const auto KEYWORDS = std::array {
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
} // namespace lexer

#endif // TOKEN