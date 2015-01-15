#include "tila.h"

struct Token *Token_new(unsigned int start, unsigned int end,
                        unsigned int line, unsigned int column) {
    struct Token *token = (struct Token *) malloc(sizeof(struct Token));
    token->start = start;
    token->end = end;
    token->line = line;
    token->column = column;
    token->type = NULL;
    return token;
}

void Token_print(struct Token *token, const char src) {
    //printf("%4d:%-4d %15s %.*s\n", token->line, token->column, token->type);
}

void Token_delete(struct Token *token) {
    free(token);
}
