#include "tila.h"

struct Node *identifier_parser(struct Parser *parser __attribute__((unused)),
                               struct Token *token) {
    return IdentifierNode_new(token);
}

struct Node *assign_parser(struct Parser *parser,
                           struct Node *left,
                           struct Token *token) {
    ASSERT(left->type != N_IDENTIFIER, "Left token must be an identifier");
    struct Node *right = Parser_parse_node(parser, 0);
    return AssignNode_new(left, token, right);
}

struct Node *number_parser(struct Parser *parser __attribute__((unused)),
                           struct Token *token) {
    return NumberNode_new(token);
}

struct Node *argument_parser(struct Parser *parser,
                             struct Token *token) {
    struct Vector *vector = Vector_new();
    while(!Parser_match(parser, T_RPAREN)) {
        do {
            Vector_push(vector, Parser_parse_node(parser, 0));
        } while(Parser_match(parser, T_COMMA));
    }
    return ArgumentNode_new(vector, token);
}

struct Node *function_parser(struct Parser *parser,
                             struct Node *left,
                             struct Token *token) {
    ASSERT(left->type != N_ARGUMENT, "Left needs to be a list of arguments");
    struct Vector *body = Vector_new();
    unsigned int our_indent = Parser_increase_indentation(parser);
    struct Node *node = Parser_parse_node(parser, 0);
    if(node != NULL) {
        Vector_push(body, node);
    } else {
        while(Parser_has_indentation(parser, our_indent)) {
            node = Parser_parse_node(parser, 0);
            if(node != NULL) {
                Vector_push(body, node);
            }
        }
    }
    Parser_decrease_indentation(parser);
    return FunctionNode_new(body, left, token);
}
