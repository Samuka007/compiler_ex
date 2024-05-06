#pragma once

#include <fstream>
#include "type.hpp"
#include "token.hpp"

namespace lexer {
    inline Token lex(std::ifstream& is) {
        auto tmp = Token(is);
        if (tmp.tag() == TokenTag::SEMICOLON) {
            auto a = 1;
        }
        if (tmp.tag() == TokenTag::COMMENT_A) {
            while (is) {
                char c;
                is.get(c);
                if (c == '\n') {
                    break;
                }
            }
            utils::clean_whitespace(is);
            return lex(is);
        }
        if (tmp.tag() == TokenTag::COMMENT_B_1) {
            while (is) {
                char c;
                is.get(c);
                if (c == '*') {
                    is.get(c);
                    if (c == '/') {
                        break;
                    }
                }
            }
            utils::clean_whitespace(is);
            return lex(is);
        }
        return tmp;
    }
}
