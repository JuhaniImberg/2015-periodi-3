#include "tila.h"

struct Tokenizer *Tokenizer_new(char *source) {
    struct Tokenizer *ti = (struct Tokenizer *)malloc(sizeof(struct Tokenizer));
    size_t len = strlen(source);
    ti->source = (char *)malloc(len * sizeof(char));
    memcpy(ti->source, source, len);
    ti->tokens = Vector_new();
    TokenType_initall();
    return ti;
}

void Tokenizer_tokenize() {

}

void Tokenizer_delete(struct Tokenizer *ti) {
    free(ti->source);
    Vector_delete(ti->tokens);
    free(ti);
}
