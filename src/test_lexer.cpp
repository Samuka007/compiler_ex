#include <iostream>
#include <fstream>
#include "lexer/lexer.hpp"

int main()
{
    std::ifstream is("C:\\Users\\Administrator\\Workspace\\Compiler\\compiler_ex\\src\\test.src");
    while(is) {
        auto result = lexer::lex(is);
        std::cout << result << std::endl;
    }
}