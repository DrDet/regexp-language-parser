#include <iostream>
#include <memory>
#include "gtest/gtest.h"
#include "Parser.h"

using namespace std;

void lexing(const string &s) {
    Lexer lexer(s);
    while (lexer.get_cur_tok() != END) {
        lexer.next_token();
    }
}

node_t parse(const string &s) {
    Parser parser;
    return parser.parse(s);
}

int LIMIT = 10;

string get_random_regexp(char name = 'S', int cnt = 0) {
    static const string alpha = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    int r = rand() % 2;
    string res;
    switch(name) {
        case 'S': {
            if (r % 2) {
                return get_random_regexp('S', cnt) + "|" + get_random_regexp('F', cnt);
            } else {
                return get_random_regexp('F', cnt);
            }
        }
        case 'F': {
            if (r % 2) {
                return get_random_regexp('F', cnt) + get_random_regexp('K', cnt);
            } else {
                return get_random_regexp('K', cnt);
            }
        }
        case 'K': {
            if (r % 2) {
                return get_random_regexp('T', cnt) + "*";
            } else {
                return get_random_regexp('T', cnt);
            }
        }
        case 'T': {
            if (r % 2 && cnt < LIMIT) {
                return "(" + get_random_regexp('S', cnt + 1) + ')';
            } else {
                return string(1, alpha[rand() % alpha.length()]);
            }
        }
    }
}

TEST(lexer, lexer_alpha_Test) {
    EXPECT_NO_THROW(lexing("1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM()|*"));
}

TEST(lexer, lexer_ignoring_spaces_Test) {
    EXPECT_NO_THROW(
            lexing("\n123 4567890qw     \t\t\t\n\n\n\ner tyuiopasdfghjklzxc vbn\tmQ  WERTYUIOPASD\t \t\t   FGHJKLZXCVBNM       \n\n\n"));
}

TEST(lexer, lexer_invalid_symbols_Test) {
    EXPECT_THROW(lexing("."), lexer_exception);
    EXPECT_THROW(lexing(","), lexer_exception);
    EXPECT_THROW(lexing("!"), lexer_exception);
    EXPECT_THROW(lexing("_"), lexer_exception);
    EXPECT_THROW(lexing("\\"), lexer_exception);
    EXPECT_THROW(lexing("/"), lexer_exception);
    EXPECT_THROW(lexing("@"), lexer_exception);
    EXPECT_THROW(lexing("#"), lexer_exception);
    EXPECT_THROW(lexing("`"), lexer_exception);
    EXPECT_THROW(lexing("~"), lexer_exception);
}

TEST(parser, parser_simple_Test) {
    //a
    EXPECT_EQ("SFKTaK'F'S'", parse("a")->to_string());
}

TEST(parser, parser_choice_Test) {
    //a|b
    EXPECT_EQ("SFKTaK'F'S'|FKTbK'F'S'", parse("a|b")->to_string());
}

TEST(parser, parser_concat_Test) {
    //ab
    EXPECT_EQ("SFKTaK'F'KTbK'F'S'", parse("ab")->to_string());
}

TEST(parser, parser_kleene_Test) {
    //a*
    EXPECT_EQ("SFKTaK'*F'S'", parse("a*")->to_string());
}

TEST(parser, parser_complex_Test)
{
    EXPECT_NO_THROW(parse("((abc*b|a)*ab(aa|b*)b)*"));
    EXPECT_NO_THROW(parse("((AbC)*|dd)*"));
    EXPECT_NO_THROW(parse("((abc*b|a)*ab(aa|b*)b((abc*b|a)*ab(aa|b*)b))*"));
}

TEST(parser, parser_failures_Test)
{
    EXPECT_THROW(parse(""), parser_exception);
    EXPECT_THROW(parse("()"), parser_exception);
    EXPECT_THROW(parse("(a))"), parser_exception);
    EXPECT_THROW(parse("a||b"), parser_exception);
    EXPECT_THROW(parse("a**"), parser_exception);
    EXPECT_THROW(parse("a*|b*("), parser_exception);
    EXPECT_THROW(parse("a|(vd))"), parser_exception);
    EXPECT_THROW(parse(")a"), parser_exception);

}

TEST(parser, parser_random_Test)
{
    constexpr int TESTS_CNT = 200;
    for (int i = 0; i < TESTS_CNT; ++i) {
        LIMIT = rand() % 10 + 1;
        EXPECT_NO_THROW(parse(get_random_regexp()));
    }
}
