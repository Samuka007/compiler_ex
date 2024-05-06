// token for integer

#ifndef LEXER_NUMBER_HPP
#define LEXER_NUMBER_HPP

#include <iostream>
#include <optional>
#include <fstream>

namespace lexer {
    class Integer {
    public:
        Integer(long value)
            : value(value) {}

    friend std::ostream& operator<<(std::ostream& os, const Integer& integer) {
        os << integer.value;
        return os;
    }

    static std::optional<Integer> parse(std::ifstream& is) {
        auto pos = is.tellg();
        long value;
        try {
            is.exceptions(is.failbit);
            is >> value;
            return Integer(value);
        }
        catch (const std::ios_base::failure& e) {
            is.clear();
            is.seekg(pos);
            return std::nullopt;
        }
    }

    private:
        long value;
    };

    class Real {
    public:
        Real(double value)
            : value(value) {}

    friend std::ostream& operator<<(std::ostream& os, const Real& real) {
        os << real.value;
        return os;
    }

    static std::optional<Real> parse(std::ifstream& is) {
        auto pos = is.tellg();
        double value;
        try {
            is.exceptions(is.failbit);
            is >> value;
            return Real(value);
        }
        catch (const std::ios_base::failure& e) {
            is.clear();
            is.seekg(pos);
            return std::nullopt;
        }
    }

    private:
        double value;
    };
}

#endif // LEXER_NUMBER_HPP