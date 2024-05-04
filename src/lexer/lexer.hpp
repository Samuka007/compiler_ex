#pragma once

#include <fstream>
#include <istream>
#include <variant>
// #include <vector>
#include "token.hpp"
#include "number.hpp"
#include "keyword.hpp"

namespace lexer {
    Token lex(std::ifstream& is) {
        return Token(is);
    }
}
