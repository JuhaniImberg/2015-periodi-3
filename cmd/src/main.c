#include "tila.h"

int main(int argc, char **argv) {
    // Lets fail if we don't get an argument
    ASSERT(argc < 2, "%s takes the source code file as an argument", argv[0]);
    // Iterate over the rest of the arguments (0 is program name)
    for(int i = 1; i < argc; i++) {
        char *filename = argv[i];
        // Open a file descriptor to the file
        int fd = open(filename, O_RDONLY);
        // fd is smaller than 0 if there was an error, the ASSERT macro will
        // take care of telling exactly what was the error (errno)
        ASSERT(fd < 0, "couldn't open \"%s\" for reading", filename);

        // The length of the file
        int flen = lseek(fd, 0, SEEK_END);
        ASSERT(flen < 0, "couldn't seek \"%s\"", filename);

        // *magic*, we map the files content to a memory position
        char *source = mmap(0, flen, PROT_READ, MAP_PRIVATE, fd, 0);

        // Tokenizer tokenizes some text
        struct Tokenizer *ti = Tokenizer_new(source);
        Tokenizer_tokenize(ti);

        // How many tokens did we encounter
        unsigned int len = Vector_size(ti->tokens);

        // Lets print a nice table of the tokens
        printf("\nFile: %s\n", filename);
        printf("| %-8s| %-15s | %s\n", "pos", "type", "value");
        printf("|---------|-----------------|-------\n");
        for(unsigned int i = 0; i < len; i++) {
            Token_print((struct Token *)Vector_get(ti->tokens, i), source);
        }
        Tokenizer_delete(ti);
    }
    return 0;
}
