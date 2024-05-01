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
#include "type.hpp"
#include "keyword.hpp"
#include "number.hpp"

namespace lexer {

// A token object can output using the << operator`
template <typename T>
concept TokenObject = requires(T t) {
    { std::cout << t };
};

using token_t = std::variant<Keyword, Integer, Real>;

class Token {
public:
    // Token(TokenType type, token_t value)
    //     : type(type), value(value) {}
    Token(TokenType type, std::string_view value)
        : type(type), value(Keyword(value)) {}
    
    Token(TokenType type, long value)
        : type(type), value(Integer(value)) {}
    
    Token(TokenType type, double value)
        : type(type), value(Real(value)) {}

    TokenType type;
    token_t value;
};

// helper type for the visitor #4
template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

template <TokenObject T>
std::ostream& operator<<(std::ostream& os, const Token& token) {
    std::visit(overloaded {
        [&os](auto arg) { os << arg; },
        [&os](Real arg) { os << std::fixed << arg; },
        // [&os](const std::string& arg) { os << std::quoted(arg) << ' '; },
        // [&os](const std::string_view& arg) { os << std::quoted(arg) << ' '; } // Add the string_view overload
    }, token.value);
}

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
    } // namespace keywords

    const auto KEYWORDS = std::array {
        keywords::NE, keywords::EQ, keywords::AND, keywords::OR, keywords::GE, keywords::LE,
        keywords::VOID, keywords::INT, keywords::DOUBLE, keywords::BOOL, keywords::STRING,
        keywords::CLASS, keywords::EXTENDS, keywords::FOR, keywords::WHILE, keywords::BREAK,
        keywords::IF, keywords::ELSE, keywords::RETURN, keywords::STATIC,
        keywords::NEW, keywords::NEW_ARRAY, keywords::PRINT, keywords::READ_INTEGER, keywords::READ_LINE,
        keywords::FALSE, keywords::TRUE, keywords::NULL_, keywords::THIS, keywords::A_MINUS,
        keywords::INDEX
    };
} // namespace lexer

#endif // TOKEN