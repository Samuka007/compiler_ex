// token for integer
#pragma once

#include <iostream>
#include <iomanip>
#include <optional>
#include <fstream>
#include <bitset>

namespace lexer {
    enum class NumberBase {
        DECIMAL,
        HEXADECIMAL,
        OCTAL,
        BINARY
    };
    class Integer {
    public:
        Integer(long value, NumberBase base)
            : value(value), base(base) {}

    friend std::ostream& operator<<(std::ostream& os, const Integer& integer) {
        // output the value in different base
        switch (integer.base) {
            case NumberBase::DECIMAL:
                os << integer.value;
                break;
            case NumberBase::HEXADECIMAL:
                os << "0x" << std::hex << integer.value;
                break;
            case NumberBase::OCTAL:
                os << "0o" << std::oct << integer.value;
                break;
            case NumberBase::BINARY:
                os << "0b" << std::bitset<sizeof(long) * 8>(integer.value);
                break;
        }
        return os;
    }

    static std::optional<Integer> parse(std::ifstream& is) {
        auto pos = is.tellg();
        long value;
        try {
            is.exceptions(is.failbit);
            if (is.peek() == '0') {
                is.get();
                if (is.peek() == 'x' || is.peek() == 'X') {
                    is.get();
                    is >> std::hex >> value;
                    return Integer(value, NumberBase::HEXADECIMAL);
                }
                else if (is.peek() == 'b' || is.peek() == 'B') {
                    is.get();
                    is >> std::hex >> value;
                    return Integer(value, NumberBase::BINARY);
                }
                else if (is.peek() == 'o' || is.peek() == 'O') {
                    is >> std::oct >> value;
                    return Integer(value, NumberBase::OCTAL);
                }
                is.unget();
            }
            is >> value;
            if (is.peek() == '.') {
                is.unget();
                is.clear();
                is.seekg(pos);
                return std::nullopt;
            }
            return Integer(value, NumberBase::DECIMAL);
        }
        catch (const std::ios_base::failure& e) {
            is.clear();
            is.seekg(pos);
            return std::nullopt;
        }
    }

    private:
        long value;
        NumberBase base;
    };

    class Real {
    public:
        Real(double value)
            : value(value) {}

    friend std::ostream& operator<<(std::ostream& os, const Real& real) {
        os << std::fixed << std::setprecision(3) << real.value;
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
