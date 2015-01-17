#ifndef TOKEN_H
#define TOKEN_H

#include "tila.h"

struct Token {
    unsigned int start, end, line, column;
    struct TokenType *type;
};

struct Token *Token_new(unsigned int start, unsigned int end,
                        unsigned int line, unsigned int column);
unsigned int Token_length(struct Token *token);
int Token_indent_length(struct Token *token);
void Token_print(struct Token *token, const char *src);
void Token_delete(struct Token *token);


#endif
