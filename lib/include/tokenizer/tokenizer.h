#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "tila.h"

struct Tokenizer {
    char *source;
    struct Vector *tokens;
    struct TTMatcher *matcher;
    unsigned int pos, line, column;
    bool in_string, in_comment;
};

struct Tokenizer *Tokenizer_new(char *source);
void Tokenizer_tokenize(struct Tokenizer *tokenizer);
void Tokenizer_delete(struct Tokenizer *tokenizer);

#endif
