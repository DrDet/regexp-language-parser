cmake_minimum_required(VERSION 3.10)
project(regexp-language-parser)

set(CMAKE_CXX_STANDARD 11)

add_executable(regexp-language-parser main.cpp Lexer.cpp Lexer.h Parser.cpp Parser.h Tree.cpp Tree.h)
