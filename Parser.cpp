#include "Parser.h"
#include <memory>

using std::unique_ptr;
using std::string;

node_t Parser::parse(const string &s) {
    lexer = Lexer(s);
    node_t root = S();
    if (lexer.get_cur_tok() == END) {
        return root;
    }
    parser_error();
}

node_t Parser::S() {
    node_t root(new Node("S"));
    switch (lexer.get_cur_tok()) {
        case LEFT_BRACKET:
        case SYMBOL: {
            root->append_child(F());
            root->append_child(S_());
            break;
        }
        default: {
            parser_error();
        }
    }
    return root;
}

node_t Parser::S_() {
    node_t root(new Node("S'"));
    switch (lexer.get_cur_tok()) {
        case CHOICE: {
            root->append_child(term_symbol("|"));
            root->append_child(F());
            root->append_child(S_());
            break;
        }
        case RIGHT_BRACKET:
        case END: {
            root->append_child(eps_symbol());
            break;
        }
        default: {
            parser_error();
        }
    }
    return root;
}

node_t Parser::F() {
    node_t root(new Node("F"));
    switch (lexer.get_cur_tok()) {
        case LEFT_BRACKET:
        case SYMBOL: {
            root->append_child(K());
            root->append_child(F_());
            break;
        }
        default: {
            parser_error();
        }
    }
    return root;
}

node_t Parser::F_() {
    node_t root(new Node("F'"));
    switch (lexer.get_cur_tok()) {
        case LEFT_BRACKET:
        case SYMBOL: {
            root->append_child(K());
            root->append_child(F_());
            break;
        }
        case CHOICE:
        case RIGHT_BRACKET:
        case END: {
            root->append_child(eps_symbol());
            break;
        }
        default: {
            parser_error();
        }
    }
    return root;
}

node_t Parser::K() {
    node_t root(new Node("K"));
    switch (lexer.get_cur_tok()) {
        case LEFT_BRACKET:
        case SYMBOL: {
            root->append_child(T());
            root->append_child(K_());
            break;
        }
        default: {
            parser_error();
        }
    }
    return root;
}

node_t Parser::K_() {
    node_t root(new Node("K'"));
    switch (lexer.get_cur_tok()) {
        case KLEENE_STAR: {
            root->append_child(term_symbol("*"));
            break;
        }
        case LEFT_BRACKET:
        case RIGHT_BRACKET:
        case SYMBOL:
        case CHOICE:
        case END: {
            root->append_child(eps_symbol());
            break;
        }
        default: {
            parser_error();
        }
    }
    return root;
}

node_t Parser::T() {
    node_t root(new Node("T"));
    switch (lexer.get_cur_tok()) {
        case LEFT_BRACKET: {
            root->append_child(term_symbol("("));
            root->append_child(S());
            root->append_child(term_symbol(")"));
            break;
        }
        case SYMBOL: {
            root->append_child(term_symbol(string(1, lexer.get_cur_char())));
            break;
        }
        default: {
            parser_error();
        }
    }
    return root;
}

node_t Parser::term_symbol(string const & s) {
    node_t node(new Node(s));
    lexer.next_token();
    return node;
}

node_t Parser::eps_symbol() {
    return node_t(new Node(""));
}

void Parser::parser_error() {
    Token expected_tok = lexer.get_cur_tok();
    int pos = lexer.get_cur_pos();
    char buf[50];
    std::string tok_descr;
    switch (expected_tok) {
        case SYMBOL:
            tok_descr = "\'symbol\'";
            break;
        case END:
            tok_descr = "\'end of string\'";
            break;
        default:
            tok_descr = string("\'") + string(1, expected_tok) + "\'";
    }
    sprintf(buf, "Unexpected token: %s at position: %d", tok_descr.c_str(), pos);
    throw parser_exception(buf);
}

parser_exception::parser_exception(const string & s) : message(s) {}
