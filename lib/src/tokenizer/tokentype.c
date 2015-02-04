#include "tila.h"

struct TTMatcher *TTMatcher_new() {
    struct TokenType old;
    struct TokenType *new;
    struct TTMatcher *tt = (struct TTMatcher *)malloc(sizeof(struct TTMatcher));
    tt->types = Vector_new();

    size_t len = 0;
    char *tmp = NULL;
    int s = 0;

    for(unsigned int i = 0; i < sizeof(token_types_raw) / sizeof(token_types_raw[0]); i++) {
        old = token_types_raw[i];
        new = (struct TokenType *)malloc(sizeof(struct TokenType));
        new->id = old.id;
        new->name = old.name;
        new->match = old.match;
        new->regex = (regex_t *)malloc(sizeof(regex_t));

        len = strlen(old.match);
        tmp = (char *)calloc(len + 3, sizeof(char));
        tmp[0] = '^';
        strncpy(tmp + 1, old.match, len);
        tmp[len + 1] = '$';

        s = regcomp(new->regex, tmp, REG_EXTENDED);
        ASSERT(s, "Regex compile failed");

        free(tmp);
        Vector_push(tt->types, (void *)new);
    }
    return tt;
}

void TTMatcher_match(struct TTMatcher *tt, struct Token *token, char *src) {
    struct TokenType *type;
    unsigned int len = Vector_size(tt->types);
    char tmp = src[token->end];
    src[token->end] = '\0';
    for(unsigned int i = 0; i < len; i++) {
        type = Vector_get(tt->types, i);
        //DEBUG("%s %d", type->name, type->regex == NULL);
        if(regexec(type->regex, src + token->start, 0, NULL, 0) == 0) {
            token->type = type;
            break;
        }
    }
    src[token->end] = tmp;
}

void TTMatcher_delete(struct TTMatcher *tt) {
    unsigned int len = Vector_size(tt->types);
    struct TokenType *type;
    for(unsigned int i = 0; i < len; i++) {
        type = Vector_get(tt->types, i);
        regfree(type->regex);
        free(type->regex);
        free(type);
    }
    Vector_delete(tt->types);
    free(tt);
}
