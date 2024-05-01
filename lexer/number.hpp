// token for integer

#ifndef LEXER_NUMBER_HPP
#define LEXER_NUMBER_HPP

#include <iostream>
#include <Optional>
#include <istream>

namespace lexer {

    class Integer {
    public:
        Integer(long value)
            : value(value) {}

    friend std::ostream& operator<<(std::ostream& os, const Integer& integer) {
        os << integer.value;
        return os;
    }

    static std::optional<Integer> parse(std::istream& is) {
        long value;
        is >> value;
        if (is) {
            return Integer(value);
        }
        return std::nullopt;
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

    static std::optional<Real> parse(std::istream& is) {
        double value;
        is >> value;
        if (is) {
            return Real(value);
        }
        return std::nullopt;
    }

    private:
        double value;
    };
}

#endif // LEXER_NUMBER_HPP