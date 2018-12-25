#include "Lexer.h"
#include <cctype>
#include <stdexcept>

using std::string;

inline bool starts_with(std::string const & s, std::string const & start) {
    if (s.length() < start.length()) {
        return false;
    }
    return s.substr(0, start.length()) == start;
}

Lexer::Lexer(const string & s) : s(s), cur_pos(0) {
    skip_symbols = {' ', '\t', '\n', '\r'};
    token_regexps[LEFT_BRACKET] = std::regex("\\(");
    token_regexps[RIGHT_BRACKET] = std::regex("\\)");
    token_regexps[CHOICE] = std::regex("\\|");
    token_regexps[KLEENE_STAR] = std::regex("\\*");
    token_regexps[SYMBOL] = std::regex("\\w");
    next_token();
}

void Lexer::next_token() {
    while (true) {
        if (cur_pos >= s.length()) {
            cur_tok = END$;
            return;
        }
        std::sregex_token_iterator no_match;
        for (int i = 0; i < tokens_num; ++i) {
            std::sregex_token_iterator it(s.begin() + cur_pos, s.end(), token_regexps[i]);
            if (it != no_match && starts_with(s.substr(cur_pos), it->str())) {
                cur_tok = static_cast<Token>(i);
                cur_tok_text = it->str();
                cur_pos += it->str().length();
                return;
            }
        }
        if (skip_symbols.find(s[cur_pos]) != skip_symbols.end()) {
            char skip = s[cur_pos];
            while (cur_pos < s.length() && s[cur_pos] == skip) {
                cur_pos++;
            }
        } else {
            char buf[50];
            sprintf(buf, "Unexpected symbol: '%c' at position: %zu", s[cur_pos], cur_pos);
            throw lexer_exception(buf);
        }
    }
}

Token Lexer::get_cur_tok() {
    return cur_tok;
}

size_t Lexer::get_cur_pos() {
    return cur_pos;
}

std::string Lexer::get_cur_tok_text() {
    return cur_tok_text;
}

lexer_exception::lexer_exception(const std::string & s) : message(s) {}

const char *lexer_exception::what() const noexcept {
    return message.c_str();
}
