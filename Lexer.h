#pragma once
#include <string>

enum Token : char {
    LEFT_BRACKET = '(', RIGHT_BRACKET = ')',
    CHOICE = '|', KLEENE_STAR = '*',
    SYMBOL = 'c',
    END = '$'
};

class Lexer {
public:
    Lexer() = default;
    explicit Lexer(const std::string & s);

    void next_token();
    Token get_cur_tok();
    int get_cur_pos();
    char get_cur_char();
private:
    Token cur_tok;
    int cur_pos;
    std::string s;

    void skip_blanks();
};

class lexer_exception : public std::exception {
    std::string message;
public:
    explicit lexer_exception(const std::string &);
};
