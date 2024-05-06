#include <ios>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "lexer/lexer.hpp"
#include "utils.hpp"

int main()
{
    auto is = std::ifstream("../test.src");
    // // print the file
    // std::cout << "File content: " << std::endl;
    // std::cout << is.rdbuf() << std::endl;
    is.exceptions(is.failbit | is.badbit | is.eofbit);
    int i = 0;
    
    while(is) {
        try {
            utils::clean_whitespace(is);
            auto result = lexer::lex(is);
            // print using format (TokenType, TokenValue)
            // each output takes 10 spaces
            std::stringstream ss;
            ss << '(' << result.type() << ", " << result << ')';
            std::cout << std::setw(16) << std::left << ss.str();
            ++i;
            if (i % 5 == 0) {
                std::cout << std::endl;
            }
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