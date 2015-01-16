#include "tila.h"

void TokenType_initall() {
    struct TokenType type;
    size_t len = 0;
    char *tmp = NULL;
    int s = 0;
    for(unsigned int i = 0; i < sizeof(token_types) / sizeof(token_types[0]); i++) {
        type = token_types[i];
        if(type.regex) {
            break;
        }
        len = strlen(type.match);
        tmp = (char *)calloc(len + 3, sizeof(char));
        tmp[0] = '^';
        strncpy(tmp + 1, type.match, len);
        tmp[len + 1] = '$';
        s = regcomp(type.regex, tmp, REG_EXTENDED);
        ERROR(s, "Regex compile failed");
        free(tmp);
    }
}

void TokenType_match(struct Token *token, char *src) {

    struct TokenType type;
    char tmp = src[token->end];
    src[token->end] = '\0';
    for(unsigned int i = 0; i < sizeof(token_types) / sizeof(token_types[0]); i++) {
        type = token_types[i];
        if(regexec(type.regex, src + token->start, 0, NULL, 0) == 0) {
            token->type = &type;
            break;
        }
    }
    src[token->end] = tmp;
}
