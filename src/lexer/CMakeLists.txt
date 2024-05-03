# limit cmake version
cmake_minimum_required(VERSION 3.10)
add_library(lexer STATIC
    lexer.cpp
    lexer.h
    token.cpp
    token.h
)
# library requires c++20
target_compile_features(lexer PUBLIC cxx_std_20)