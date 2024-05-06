#pragma once

#include <fstream>
#include "token.hpp"

namespace lexer {
    inline Token lex(std::ifstream& is) {
        return Token(is);
    }
}
