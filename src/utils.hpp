#pragma once

// helper type for the visitor #4
template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

#include <exception>
#include <string_view>

namespace utils {
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
}