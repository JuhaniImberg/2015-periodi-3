#include "tila.h"

#include <getopt.h>

int tokens_flag = 0;
int nodes_flag = 0;
int returns_flag = 0;

int print_help() {
    fprintf(stderr, "usage: tila [--tokens] [--nodes] [--returns] FILES\n");
    fprintf(stderr, "  --tokens   Print the tokens in the program\n");
    fprintf(stderr, "  --nodes    Print the nodes in the program\n");
    fprintf(stderr, "  --returns  Print the returns of the executed nodes\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {

    static struct option long_options[] = {
        {"tokens", no_argument, &tokens_flag, 1},
        {"nodes", no_argument, &nodes_flag, 1},
        {"returns", no_argument, &returns_flag, 1},
        {0, 0, 0, 0}
    };
    int c;
    int option_index = 1;
    while(1) {
        c = getopt_long(argc, argv, "::", long_options, NULL);
        if(c == -1) {
            break;
        }
        switch(c) {
        case 0:
            option_index++;
            break;
        case '?':
            print_help();
            break;
        default:
            abort();
        }
   }

    // Lets fail if we don't get an argument
    ASSERT(option_index == argc, "%s takes the source code file as an argument", argv[0]);
    // Iterate over the rest of the arguments (0 is program name)
    for(int i = option_index; i < argc; i++) {
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

        if(tokens_flag) {
            // Lets print a nice table of the tokens
            printf("\nFile: %s\n", filename);
            printf("| %-8s| %-15s | %s\n", "pos", "type", "value");
            printf("|---------|-----------------|-------\n");
            for(unsigned int i = 0; i < len; i++) {
                Token_print((struct Token *)Vector_get(ti->tokens, i), source);
            }
        }

        struct GC *gc = GC_new();

        // Parser parses the tokens into a tree
        struct Parser *parser = Parser_new(ti->tokens, gc, source);
        // Environment describes the environment where the program is run,
        // the current context and so on
        struct Environment *env = Environment_new(gc, source);

        // While there are things to parse
        while(!Parser_done(parser)) {
            gc->enabled = false;
            struct Node *node = Parser_parse_node(parser, 0);
            if(node != NULL) {
                // Call the repr function of each node that we got
                if(nodes_flag) {
                    node->repr(node, env);
                    printf("\n");
                }
                if(node->get_value != NULL) {
                    // gc->enabled = true;
                    node->get_value(node, env);
                    struct Node *res = GC_pop(gc);
                    if(returns_flag) {
                        if(res != NULL) {
                            res->repr(res, env);
                        } else {
                            printf("null");
                        }
                        printf("\n");
                    }
                }
            }
        }

        Parser_delete(parser);
        Environment_delete(env);
        Tokenizer_delete(ti);
        GC_delete(gc);
    }
    return 0;
}
