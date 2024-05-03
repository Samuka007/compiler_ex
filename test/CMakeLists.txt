# this is the test cmakelist of the project
# in this folder we will test the lexer
# lexer library is in the lexer folder
# The std version is above c++20
# now generate the cmake file

cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(../lexer lexer)
add_executable(lexer_test lexer_test.cpp)

target_link_libraries(lexer_test lexer)
