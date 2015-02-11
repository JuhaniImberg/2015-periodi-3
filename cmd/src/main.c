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

        // Parser parses the tokens into a tree
        struct Parser *parser = Parser_new(ti->tokens, source);
        // Environment describes the environment where the program is run,
        // the current context and so on
        struct Environment *env = Environment_new(source);

        struct Vector *nodes = Vector_new();

        // While there are things to parse
        while(!Parser_done(parser)) {
            struct Node *node = Parser_parse_node(parser, 0);
            if(node != NULL) {
                // Call the repr function of each node that we got
                node->repr(node, env);
                printf("\n");
                if(node->get_value != NULL) {
                    struct Node *res = node->get_value(node, env);
                    if(res != NULL) {
                        res->repr(res, env);
                    } else {
                        printf("null");
                    }
                    printf("\n");
                }
                Vector_push(nodes, node);
            }
        }
        Vector_each(nodes, Node_delete_void_pointer);

        Parser_delete(parser);
        Environment_delete(env);
        Tokenizer_delete(ti);
    }
    return 0;
}
