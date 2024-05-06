#pragma once

#include <exception>
#include <string_view>
#include <iostream>

namespace lexer::utils {
    // helper type for the visitor #4
    template<class... Ts>
    struct overloaded : Ts... { using Ts::operator()...; };
    // explicit deduction guide (not needed as of C++20)
    template<class... Ts>
    overloaded(Ts...) -> overloaded<Ts...>;

    inline void clean_whitespace(std::istream& is) {
        char c;
        while (is.get(c) && std::isspace(c)) {
            continue;
        }
        is.unget();
    }

    class CompilerException : public std::exception {
    public:
        CompilerException(std::string_view message)
            : message(message) {}

        const char* what() const noexcept override {
            return message.data();
        }
    private:
        std::string_view message;
    };

    // unexpected token
    class UnexpectedToken : public CompilerException {
    public:
        UnexpectedToken()
            : CompilerException("Unexpected token") {}
    };

    // output empty token
    class EmptyToken : public CompilerException {
    public:
        EmptyToken()
            : CompilerException("Empty token") {}
    };
}