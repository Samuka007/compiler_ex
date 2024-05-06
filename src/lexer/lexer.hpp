#pragma once

#include <fstream>
#include <iostream>
#include "type.hpp"
#include "token.hpp"

namespace lexer {
    Token lex(std::ifstream& is) {
        utils::clean_whitespace(is);
        try{
        auto tmp = Token(is);
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
        } catch (utils::UnexpectedToken& e) {
            std::cerr << "ERROR: unknow symbol: \"" << static_cast<char>(is.get()) << "\"" << std::endl;
            return lex(is);
        }
    }
}
