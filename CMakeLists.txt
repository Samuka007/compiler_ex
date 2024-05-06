cmake_minimum_required(VERSION 3.10)
project(Compiler)

# std=c++20
set(CMAKE_CXX_STANDARD 20)

# Add the executable target for test_lexer.cpp
add_executable(test_lexer src/test_lexer.cpp)

# Add any additional dependencies or compile options here
