#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <istream>
#include "token.hpp"
#include "number.hpp"
#include "keyword.hpp"

namespace lexer {
    std::istream& operator>>(std::istream& is, Token& token) {
        
    }
}

#endif // LEXER_HPP