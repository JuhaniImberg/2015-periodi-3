#include "tila.h"

int main(int argc, char **argv) {
    if(argc < 2) {
        ERROR(1, "%s needs more arguments than %d", argv[0], argc);
    }
    for(int i = 1; i < argc; i++) {
        char *filename = argv[i];
        int fd = open(filename, O_RDONLY);
        ERROR(fd < 0, "couldn't open \"%s\" for reading", filename);
        int flen = lseek(fd, 0, SEEK_END);
        ERROR(flen < 0, "couldn't seek \"%s\"", filename);
        char *source = mmap(0, flen, PROT_READ, MAP_PRIVATE, fd, 0);
        struct Tokenizer *ti = Tokenizer_new(source);
        Tokenizer_tokenize(ti);
        unsigned int len = Vector_size(ti->tokens);

        printf("\n%s\n%.*s\n\n", filename,
               (int)strlen(filename), "======================================");
        printf("| %-8s| %-15s | %s\n", "pos", "type", "value");
        printf("|---------|-----------------|-------\n");
        for(unsigned int i = 0; i < len; i++) {
            Token_print((struct Token *)Vector_get(ti->tokens, i), source);
        }
        Tokenizer_delete(ti);
    }
    return 0;
}
