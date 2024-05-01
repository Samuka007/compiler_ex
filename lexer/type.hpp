#pragma once

namespace lexer {

// public class Tag {
// 	public final static int AND = 256, BASIC = 257, BREAK = 258, DO = 259,
// 			ELSE = 260, EQ = 261, FALSE = 262, GE = 263, ID = 264, IF = 265,
// 			INDEX = 266, LE = 267, MINUS = 268, NE = 269, NUM = 270, OR = 271,
// 			REAL = 272, TEMP = 273, TRUE = 274, WHILE = 275;
// }

enum class TokenType {
    // Single-character tokens
    // + - * / % \ < > = 
    // ! ; , . [ ] ( ) { }
    PLUS, MINUS, STAR, SLASH, MODULO, BACKSLASH,
    LESS_THAN, GREATER_THAN, EQUALS,
    BANG, SEMICOLON, COMMA, DOT, LEFT_BRACKET, RIGHT_BRACKET,
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,

    // Literals
    IDENTIFIER,

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

}