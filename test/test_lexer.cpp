#include <iostream>
#include "lexer/lexer.hpp"

int main()
{
    auto result = lexer::lex(std::cin);
    std::cout << result << std::endl;
}