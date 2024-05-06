#pragma once

#include <iostream>

namespace lexer {

enum class TokenType {
    IDENTIFIER, LITERAL, KEYWORD, SYMBOL, NUMBER
};

enum class TokenTag {
    // Single-character tokens
    // + - * / % \ < > = 
    // ! ; , . [ ] ( ) { }
    PLUS, MINUS, STAR, SLASH, MODULO, BACKSLASH,
    LESS, GREATER, ASSIGN,
    BANG, SEMICOLON, COMMA, DOT, LEFT_BRACKET, RIGHT_BRACKET,
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,

    // Keywords
    // multi ch
    // != == && || >= <= 
    NOT_EQUAL, EQUAL, AND, OR, GREATER_EQUAL, LESS_EQUAL,
    // void int double bool string
    VOID, INT, DOUBLE, BOOL, STRING,
    // class extends for while break if else return static new NewArray Print ReadInteger ReadLine
    CLASS, EXTENDS, FOR, WHILE, BREAK, IF, ELSE, RETURN, STATIC, 
    NEW, NEW_ARRAY, PRINT, READ_INTEGER, READ_LINE,
    // true false null this
    TRUE, FALSE, NULL_, THIS, A_MINUS,

    INDEX, TEMP,

    // End of file
    END_OF_FILE,
};

// make token type formatable
inline std::ostream& operator<<(std::ostream& os, const TokenType& type) {
    switch (type) {
        case TokenType::IDENTIFIER:
            os << "ID";
            break;
        case TokenType::LITERAL:
            os << "LIT";
            break;
        case TokenType::KEYWORD:
            os << "KEY";
            break;
        case TokenType::SYMBOL:
            os << "SYM";
            break;
        case TokenType::NUMBER:
            os << "NUM";
            break;
    }
    return os;
}

}