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

unsigned int Token_length(struct Token *token) {
    return token->end - token->start;
}

void Token_print(struct Token *token, const char *src) {
    printf("|%4d:%-4d| %-15s | %.*s\n",
           token->line,
           token->column,
           token->type->name,
           token->type->id == T_EOL ? 2 : token->end - token->start,
           token->type->id == T_EOL ? "\\n" : src + token->start);
}

int Token_indent_length(struct Token *token) {
    if(token->type->id != T_INDENT) {
        return -1;
    }
    return token->end - token->start;
}

void Token_delete(struct Token *token) {
    free(token);
}
