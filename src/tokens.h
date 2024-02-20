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

#endif //DSTORAGE_TOKENS_H
