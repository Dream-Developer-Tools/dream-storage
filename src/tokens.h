#ifndef DSTORAGE_TOKENS_H
#define DSTORAGE_TOKENS_H

#include <map>
#include <string>

enum class Token {
    OBJECT_BEGIN, // {
    OBJECT_END, // }
    LIST_BEGIN, // [
    LIST_END, // ]
    IS, // =
    END_OF_LINE, // ,
    STRING_BEGIN, // " or '
    STRING_END, // " or '
    NUMBER_BEGIN, // |
    NUMBER_END, // |
    TRUE, // true
    FALSE, // false
};

const std::map<Token, std::string> tokenMap = {
        {Token::OBJECT_BEGIN, "{"},
        {Token::OBJECT_END,   "}"},
        {Token::LIST_BEGIN,   "["},
        {Token::LIST_END,     "]"},
        {Token::IS,           "="},
        {Token::END_OF_LINE,  ","},
        {Token::STRING_BEGIN, "\""},
        {Token::STRING_END,   "\""},
        {Token::NUMBER_BEGIN, "|"},
        {Token::NUMBER_END,   "|"},
        {Token::TRUE,         "true"},
        {Token::FALSE,        "false"},
};

#endif //DSTORAGE_TOKENS_H
