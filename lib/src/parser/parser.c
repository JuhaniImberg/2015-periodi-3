#include "tila.h"
#include "parser/subparsers.h"

struct Parser *Parser_new(struct Vector *tokens) {
    struct Parser *parser = (struct Parser *)malloc(sizeof(struct Parser));
    parser->tokens = tokens;
    parser->pos = 0;
    parser->indent_pos = 0;
    parser->last_nl = false;
    parser->prefix = Map_new();
    parser->prefix->copy_value = false;
    parser->infix = Map_new();
    parser->infix->copy_value = false;
    parser->precedences = Map_new();

    Parser_add_prefix(parser, T_IDENTIFIER, identifier_parser);
    Parser_add_prefix(parser, T_NUMBER, number_parser);
    Parser_add_prefix(parser, T_LPAREN, argument_parser);
    Parser_add_prefix(parser, T_STRING, string_parser);
    Parser_add_prefix(parser, T_LBRACKET, list_parser);

    Parser_add_infix(parser, T_SET, assign_parser);
    Parser_add_infix(parser, T_FN, function_parser);
    Parser_add_infix(parser, T_LPAREN, call_parser);
    Parser_add_infix(parser, T_LBRACKET, list_access_parser);
    Parser_add_infix(parser, T_COND, conditional_parser);

    Parser_add_infix(parser, T_ADD, infix_operator_parser);
    Parser_add_infix(parser, T_SUB, infix_operator_parser);
    Parser_add_infix(parser, T_MUL, infix_operator_parser);
    Parser_add_infix(parser, T_DIV, infix_operator_parser);
    Parser_add_infix(parser, T_MOD, infix_operator_parser);
    Parser_add_infix(parser, T_EQ, infix_operator_parser);
    Parser_add_infix(parser, T_NOTEQ, infix_operator_parser);
    Parser_add_infix(parser, T_GT, infix_operator_parser);
    Parser_add_infix(parser, T_LT, infix_operator_parser);
    Parser_add_infix(parser, T_GTOE, infix_operator_parser);
    Parser_add_infix(parser, T_LTOE, infix_operator_parser);
    Parser_add_infix(parser, T_OR, infix_operator_parser);
    Parser_add_infix(parser, T_AND, infix_operator_parser);

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
    Parser_add_precedence(parser, T_MOD, 7);
    Parser_add_precedence(parser, T_LBRACKET, 10);
    Parser_add_precedence(parser, T_LPAREN, 10);
    Parser_add_precedence(parser, T_COND, 1);

    return parser;
}

void Parser_add_precedence(struct Parser *parser, enum TokenTypeEnum i, int v) {
    Map_put(parser->precedences, &i, sizeof(enum TokenTypeEnum),
            &v, sizeof(int));
}

void Parser_add_prefix(struct Parser *parser, enum TokenTypeEnum type,
                       PrefixParser prefix) {
    Map_put(parser->prefix, &type, sizeof(enum TokenTypeEnum),
            prefix, sizeof(prefix));
}

void Parser_add_infix(struct Parser *parser, enum TokenTypeEnum type,
                      InfixParser infix) {
    Map_put(parser->infix, &type, sizeof(enum TokenTypeEnum),
            infix, sizeof(infix));
}

PrefixParser Parser_get_prefix(struct Parser *parser, enum TokenTypeEnum type) {
    return (PrefixParser)Map_get(parser->prefix, &type,
                                 sizeof(enum TokenTypeEnum));
}


InfixParser Parser_get_infix(struct Parser *parser, enum TokenTypeEnum type) {
    return (InfixParser)Map_get(parser->infix, &type,
                                sizeof(enum TokenTypeEnum));
}

int Parser_increase_indentation(struct Parser *parser) {
    parser->indent_pos += 2;
    return parser->indent_pos;
}

void Parser_decrease_indentation(struct Parser *parser) {
    ASSERT(parser->indent_pos < 2, "Can't decrease indentation more");
    parser->indent_pos -= 2;
}

bool Parser_has_indentation(struct Parser *parser, unsigned int pos) {
    struct Token *token = Parser_current(parser);
    if(token->type->id == T_EOL) {
        parser->last_nl = true;
        Parser_consume(parser);
    }
    token = Parser_current(parser);
    if(token == NULL) {
        return false;
    }
    if(token->type->id == T_INDENT && Token_length(token) >= pos) {
        return true;
    }
    return false;
}

struct Node *Parser_parse_node(struct Parser *parser, int precedence) {
    struct Token *token = Parser_consume(parser);

    if(parser->last_nl && token->type->id == T_INDENT) {
        ASSERT(Token_length(token) != parser->indent_pos,
               "Incorrect indentation");
        token = Parser_consume(parser);
        parser->last_nl = false;
    }

    if(token == NULL || token->type->id == T_EOL) {
        parser->last_nl = true;
        return NULL;
    }

    PrefixParser prefix = Parser_get_prefix(parser, token->type->id);
    ASSERT(prefix == NULL, "Unexpected token %d:%d",
           token->line, token->column)

    struct Node *left = prefix(parser, token);
    while(precedence < Parser_precedence(parser)) {
        token = Parser_consume(parser);

        InfixParser infix = Parser_get_infix(parser, token->type->id);
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
    return Vector_get(parser->tokens, parser->pos++);
}

bool Parser_done(struct Parser *parser) {
    return parser->pos >= Vector_size(parser->tokens);
}

int Parser_precedence(struct Parser *parser) {
    struct Token *token = Parser_current(parser);
    if(token == NULL) {
        return -1;
    }
    void *val = Map_get(parser->precedences, &token->type->id,
                        sizeof(enum TokenTypeEnum));
    if(val == NULL) {
        return false;
    }
    return *(int *)val;
}

void Parser_delete(struct Parser *parser) {
    Map_delete(parser->prefix);
    Map_delete(parser->infix);
    Map_delete(parser->precedences);
    free(parser);
}
