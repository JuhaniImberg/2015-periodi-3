#include "tila.h"

struct Node *identifier_parser(struct Parser *parser,
                               struct Token *token) {
    return IdentifierNode_new(token, parser->gc);
}

struct Node *assign_parser(struct Parser *parser,
                           struct Node *left,
                           struct Token *token) {
    ASSERT(left->type != N_IDENTIFIER, "Left token must be an identifier");
    struct Node *right = Parser_parse_node(parser, 0);
    return AssignNode_new(left, token, right, parser->gc);
}

struct Node *number_parser(struct Parser *parser,
                           struct Token *token) {
    char *content = Token_content(token, parser->src);
    long long value;
    sscanf(content, "%lld", &value);
    return NumberNode_new(token, value, parser->gc);
}

struct Node *string_parser(struct Parser *parser,
                           struct Token *token) {
    return StringNode_new(token, parser->gc);
}

struct Node *argument_parser(struct Parser *parser,
                             struct Token *token) {
    struct Vector *vector = Vector_new();
    while(!Parser_match(parser, T_RPAREN)) {
        do {
            Vector_push(vector, Parser_parse_node(parser, 0));
        } while(Parser_match(parser, T_COMMA));
    }
    return ArgumentNode_new(vector, token, parser->gc);
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
    return FunctionNode_new(body, left, token, parser->gc);
}

struct Node *call_parser(struct Parser *parser,
                         struct Node *left,
                         struct Token *token) {
    struct Vector *vector = Vector_new();
    while(!Parser_match(parser, T_RPAREN)) {
        do {
            Vector_push(vector, Parser_parse_node(parser, 0));
        } while(Parser_match(parser, T_COMMA));
    }
    return CallNode_new(left, token, vector, parser->gc);
}

struct Node *list_parser(struct Parser *parser,
                         struct Token *token) {
    struct Vector *vector = Vector_new();
    while(!Parser_match(parser, T_RBRACKET)) {
        do {
            struct Node *node = Parser_parse_node(parser, 0);
            if(node != NULL) {
                Vector_push(vector, node);
            }
        } while(Parser_match(parser, T_COMMA));
    }
    return ListNode_new(vector, token, parser->gc);
}

struct Node *infix_operator_parser(struct Parser *parser,
                                   struct Node *left,
                                   struct Token *token) {
    int prec = *(int *)Map_get(parser->precedences,
                               &token->type->id,
                               sizeof(enum TokenTypeEnum));
    struct Node *right = Parser_parse_node(parser, prec);
    return InfixOperatorNode_new(left, token, right, parser->gc);
}

struct Node *list_access_parser(struct Parser *parser,
                                struct Node *left,
                                struct Token *token) {
    struct Node *pos = Parser_parse_node(parser, 0);
    Parser_require(parser, T_RBRACKET);
    return ListAccessNode_new(left, token, pos, parser->gc);
}

struct Node *conditional_parser(struct Parser *parser,
                                struct Node *condition,
                                struct Token *token) {
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

    struct Node *next = NULL;

    while(Parser_match(parser, T_EOL) || Parser_match(parser, T_INDENT)) {

    }

    if(Parser_match(parser, T_NOTCOND)) {
        struct Vector *else_body = Vector_new();
        node = Parser_parse_node(parser, 0);
        if(node != NULL) {
            Vector_push(else_body, node);
        } else {
            our_indent = Parser_increase_indentation(parser);
            while(Parser_has_indentation(parser, our_indent)) {
                node = Parser_parse_node(parser, 0);
                if(node != NULL) {
                    Vector_push(else_body, node);
                }
            }
            Parser_decrease_indentation(parser);
        }
        next = ConditionalNode_new(NumberNode_new(NULL, 1, parser->gc),
                                   token, else_body, NULL, parser->gc);
    }

    return ConditionalNode_new(condition, token, body, next, parser->gc);
}
