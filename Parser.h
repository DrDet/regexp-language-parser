#pragma once

#include "Lexer.h"
#include "Tree.h"

class Parser {
public:
    Parser() = default;
    node_t parse(const std::string & s);
private:
    Lexer lexer;
    node_t S();
    node_t S_();
    node_t F();
    node_t F_();
    node_t K();
    node_t K_();
    node_t T();
    node_t term_symbol(std::string const & s);
    node_t eps_symbol();
    void parser_error();
};

class parser_exception : public std::exception {
    std::string message;
public:
    explicit parser_exception(const std::string &);
};
