#pragma once
#include <string>
#include <regex>
#include <unordered_set>

enum Token {
    LEFT_BRACKET, RIGHT_BRACKET,
    CHOICE, KLEENE_STAR,
    SYMBOL,
    END$
};

class Lexer {
public:
    Lexer() = default;
    explicit Lexer(const std::string & s);

    void next_token();
    Token get_cur_tok();
    size_t get_cur_pos();
    std::string get_cur_tok_text();
private:
    static const int tokens_num = 5;
    std::regex token_regexps[tokens_num];
    std::unordered_set<char> skip_symbols;

    Token cur_tok;
    std:: string cur_tok_text;
    size_t cur_pos;
    std::string s;
};

class lexer_exception : public std::exception {
    std::string message;
public:
    explicit lexer_exception(const std::string &);
    virtual const char* what() const noexcept override;
};
