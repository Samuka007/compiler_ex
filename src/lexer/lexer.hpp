#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <istream>
#include <variant>
#include <vector>
#include "token.hpp"
#include "number.hpp"
#include "keyword.hpp"

namespace lexer {
    Token lex(std::istream& is);
}

#endif // LEXER_HPP