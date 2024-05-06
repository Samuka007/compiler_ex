#pragma once

#include <exception>
#include <string_view>
#include <iostream>

namespace utils {
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

    // unexpected end of file or broken stream
    class UnexpectedEOF : public CompilerException {
    public:
        UnexpectedEOF()
            : CompilerException("Unexpected end of file") {}
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

    class BadiStream : std::exception {
    public:
        BadiStream(std::istream& is)
            :  is{is} {}
        void what() {
            std::cerr << "Bad input stream" << std::endl;
            // print stream state and current position
            // std::cerr << "Stream state: " << is.rdstate() << std::endl;
            // convert stream state to human readable format
            if (is.rdstate() & std::ios::failbit) {
                std::cerr << "Fail bit is set" << std::endl;
            }
            if (is.rdstate() & std::ios::badbit) {
                std::cerr << "Bad bit is set" << std::endl;
            }
            if (is.rdstate() & std::ios::eofbit) {
                std::cerr << "EOF bit is set" << std::endl;
            }
            std::cerr << "Stream position: " << is.tellg() << std::endl;
        }
    private:
        std::istream& is;
    };
}