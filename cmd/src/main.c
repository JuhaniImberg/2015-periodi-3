#include "tila.h"

char *src = "hello = 32 + 12";

int main() {
    struct Tokenizer *ti = Tokenizer_new(src);
    Tokenizer_tokenize(ti);
    unsigned int len = Vector_size(ti->tokens);
    for(unsigned int i = 0; i < len; i++) {
        Token_print((struct Token *)Vector_get(ti->tokens, i), src);
    }
    Tokenizer_delete(ti);
    return 0;
}
