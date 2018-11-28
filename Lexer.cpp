#include "Lexer.h"
#include <cctype>
#include <stdexcept>

using std::string;

void Lexer::skip_blanks() {
    while (cur_pos < s.length() && std::isspace(s[cur_pos])) {
        ++cur_pos;
    }
}

Lexer::Lexer(const string & s) : s(s), cur_pos(-1) {
    next_token();
}

void Lexer::next_token() {
    ++cur_pos;
    skip_blanks();
    if (cur_pos >= s.length()) {
        cur_tok = END;
        return;
    }
    if (isalnum(s[cur_pos])) {
        cur_tok = SYMBOL;
        return;
    }
    switch (s[cur_pos]) {
        case '(':
            cur_tok = LEFT_BRACKET;
            return;
        case ')':
            cur_tok = RIGHT_BRACKET;
            return;
        case '|':
            cur_tok = CHOICE;
            return;
        case '*':
            cur_tok = KLEENE_STAR;
            return;
        default: {
            char buf[50];
            sprintf(buf, "Unexpected symbol: '%c' at position: %d", s[cur_pos], cur_pos);
            throw lexer_exception(buf);
        }
    }
}

Token Lexer::get_cur_tok() {
    return cur_tok;
}

int Lexer::get_cur_pos() {
    return cur_pos;
}

char Lexer::get_cur_char() {
    return s[cur_pos];
}

lexer_exception::lexer_exception(const std::string & s) : message(s) {}

const char *lexer_exception::what() const noexcept {
    return message.c_str();
}
