#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "tila.h"

struct Tokenizer {
    char *source;
    struct Vector *tokens;
};

struct Tokenizer *Tokenizer_new(char *source);
void Tokenizer_tokenize();
void Tokenizer_delete(struct Tokenizer *tokenizer);

#endif
