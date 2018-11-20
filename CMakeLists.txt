cmake_minimum_required(VERSION 3.7)
project(regexp-language-parser)

set(CMAKE_CXX_STANDARD 11)
include_directories(${regexp-language-parser_SOURCE_DIR})

set(SOURCE_FILES Lexer.cpp Lexer.h Parser.cpp Parser.h Tree.cpp Tree.h)

add_executable(regexp-language-parser main.cpp ${SOURCE_FILES})
add_executable(regexp-language-parser-tests tests/tests.cpp ${SOURCE_FILES}
        gtest/gtest-all.cc
        gtest/gtest_main.cc
        gtest/gtest.h)

target_link_libraries(regexp-language-parser-tests -lpthread)
target_link_libraries(regexp-language-parser -lpthread)
