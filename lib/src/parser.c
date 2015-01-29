#include "tila.h"
#include "subparsers.h"

struct Parser *Parser_new(struct Vector *tokens) {
    struct Parser *parser = (struct Parser *)malloc(sizeof(struct Parser));
    parser->tokens = tokens;
    parser->pos = 0;
    parser->prefix = Map_new();
    parser->infix = Map_new();
    parser->precedences = Map_new();
    Map_set_operations(parser->prefix, number_hash, number_equals);
    Map_set_operations(parser->infix, number_hash, number_equals);
    Map_set_operations(parser->precedences, number_hash, number_equals);

    Parser_add_prefix(parser, T_IDENTIFIER, identifier_parser);
    Parser_add_prefix(parser, T_NUMBER, number_parser);

    Parser_add_infix(parser, T_SET, assign_parser);

    Parser_add_precedence(parser, T_SET, 1);
    Parser_add_precedence(parser, T_FN, 1);
    Parser_add_precedence(parser, T_OR, 2);
    Parser_add_precedence(parser, T_AND, 3);
    Parser_add_precedence(parser, T_EQ, 4);
    Parser_add_precedence(parser, T_NOTEQ, 4);
    Parser_add_precedence(parser, T_GT, 5);
    Parser_add_precedence(parser, T_LT, 5);
    Parser_add_precedence(parser, T_GTOE, 5);
    Parser_add_precedence(parser, T_LTOE, 5);
    Parser_add_precedence(parser, T_ADD, 6);
    Parser_add_precedence(parser, T_SUB, 6);
    Parser_add_precedence(parser, T_DIV, 7);
    Parser_add_precedence(parser, T_MUL, 7);
    Parser_add_precedence(parser, T_LBRACKET, 10);
    Parser_add_precedence(parser, T_LPAREN, 10);

    return parser;
}

void Parser_add_precedence(struct Parser *parser, enum TokenTypeEnum i, int v) {
    Map_put(parser->precedences, &i, &v);
}

void Parser_add_prefix(struct Parser *parser, enum TokenTypeEnum type,
                       PrefixParser prefix) {
    Map_put(parser->prefix, &type, prefix);
}

void Parser_add_infix(struct Parser *parser, enum TokenTypeEnum type,
                      InfixParser infix) {
    Map_put(parser->infix, &type, infix);
}

struct Node *Parser_parse_node(struct Parser *parser, int precedence) {
    struct Token *token = Parser_consume(parser);

    if(token->type->id == T_EOL) {
        return NULL;
    }

    PrefixParser prefix = (PrefixParser)Map_get(parser->prefix,
                                                &token->type->id);
    ASSERT(prefix == NULL, "Unexpected token %d:%d",
           token->line, token->column)

    struct Node *left = prefix(parser, token);
    while(precedence < Parser_precedence(parser)) {
        token = Parser_consume(parser);

        InfixParser infix = (InfixParser)Map_get(parser->infix,
                                                 &token->type->id);
        ASSERT(infix == NULL, "Unexpected token %d:%d",
               token->line, token->column)

        left = infix(parser, left, token);
    }
    return left;
}

bool Parser_is_next(struct Parser *parser, enum TokenTypeEnum id) {
    return Parser_current(parser)->type->id == id;
}

bool Parser_match(struct Parser *parser, enum TokenTypeEnum id) {
    if(!Parser_is_next(parser, id)) {
        return false;
    }
    Parser_consume(parser);
    return true;
}

struct Token *Parser_require(struct Parser *parser, enum TokenTypeEnum id) {
    struct Token *token = Vector_get(parser->tokens, parser->pos);
    if(token->type->id != id) {
        ASSERT(1, "Unexpected token met while parsing, %d:%d",
              token->line, token->column);
    }
    return Parser_consume(parser);
}

struct Token *Parser_current(struct Parser *parser) {
    return Vector_get(parser->tokens, parser->pos);
}

struct Token *Parser_consume(struct Parser *parser) {
    if(Vector_size(parser->tokens) >= parser->pos -1) {
        ASSERT(1, "This is a dirty way to get out");
    }
    return Vector_get(parser->tokens, parser->pos++);
}

int Parser_precedence(struct Parser *parser) {
    struct Token *token = Parser_current(parser);
    void *val = Map_get(parser->precedences, &token->type->id);
    if(val == NULL) {
        return false;
    }
    return *(int *)val;
}

void Parser_delete(struct Parser *parser) {
    Map_delete(parser->prefix);
    Map_delete(parser->infix);
    free(parser);
}
