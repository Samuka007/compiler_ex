#include "token.hpp"

namespace lexer {
std::ostream& operator<<(std::ostream& os, const Token& token) {
    std::visit( overloaded {
        [&](Keyword keyword) {
            os << "( KEY, "<< keyword << ")";
        },
        [&](OneWord keyword) {
            os << "( KEY, "<< keyword << ")";
        },
        [&](Integer num) {
            os << "( NUM, "<< num << ")";
        },
        [&](Real num) {
            os << "( NUM, "<< num << ")";
        },
        [&](Identify identify) {
            os << "( ID, "<< identify << ")";
        }
    }, token.value);
    return os;
}
}