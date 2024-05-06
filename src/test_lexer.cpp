#include <ios>
#include <iostream>
#include <fstream>
#include "lexer/lexer.hpp"
#include "utils.hpp"

int main()
{
    auto is = std::ifstream("../test.src");
    // // print the file
    // std::cout << "File content: " << std::endl;
    // std::cout << is.rdbuf() << std::endl;
    is.exceptions(is.failbit | is.badbit | is.eofbit);
    
    while(is) {
        try {
            utils::clean_whitespace(is);
            auto result = lexer::lex(is);
            // print using format (TokenType, TokenValue)
            std::cout << "(" << result.type() << ", " << result << "), ";
        }
        catch (const std::ios_base::failure& e)
        {
            // if eof, break the loop
            if (is.eof()) {
                break;
            }
            std::cout << "Caught an ios_base::failure.\n"
                      << "Explanatory string: " << e.what() << '\n'
                      << "Error code: " << e.code() << '\n';
        }
    }
}