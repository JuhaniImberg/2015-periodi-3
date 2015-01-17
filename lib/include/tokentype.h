#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include "tila.h"
#include "token.h"

enum TokenTypeEnum {
    T_LPAREN,     // (
    T_RPAREN,     // )
    T_LBRACKET,   // [
    T_RBRACKET,   // ]
    T_FN,         // ->
    T_ADD,        // +
    T_SUB,        // -
    T_MUL,        // *
    T_DIV,        // /
    T_SET,        // =
    T_EQ,         // ==
    T_NOTEQ,      // !=
    T_GT,         // >
    T_LT,         // <
    T_GTOE,       // >=
    T_LTOE,       // <=
    T_NOT,        // !
    T_AND,        // &&
    T_OR,         // ||
    T_COND,       // ?
    T_NOTCOND,    // !?
    T_STRING,     // "content"
    T_IDENTIFIER, // name
    T_NUMBER,     // 3.14
    T_INDENT,     //
    T_EOL,        // \n
    T_NONE
};

struct TokenType {
    enum TokenTypeEnum id;
    const char *name;
    const char *match;
    regex_t* regex;
};

struct TTMatcher {
    struct Vector *types;
};

static const struct TokenType token_types_raw[] = {
    {T_LPAREN, "lparen", "\\(", NULL},
    {T_RPAREN, "rparen", "\\)", NULL},
    {T_LBRACKET, "lbracket", "\\[", NULL},
    {T_RBRACKET, "rbracket", "\\]", NULL},
    {T_FN, "fn", "\\->", NULL},
    {T_ADD, "add", "\\+", NULL},
    {T_SUB, "sub", "\\-", NULL},
    {T_MUL, "mul", "\\*", NULL},
    {T_DIV, "div", "\\/", NULL},
    {T_SET, "set", "=", NULL},
    {T_EQ, "eq", "==", NULL},
    {T_NOTEQ, "noteq", "\\!=", NULL},
    {T_GT, "gt", ">", NULL},
    {T_LT, "lt", "<", NULL},
    {T_GTOE, "gtoe", ">=", NULL},
    {T_LTOE, "ltoe", "<=", NULL},
    {T_NOT, "not", "\\!", NULL},
    {T_AND, "and", "\\&\\&", NULL},
    {T_OR, "or", "\\|\\|", NULL},
    {T_COND, "cond", "\\?", NULL},
    {T_NOTCOND, "notcond", "\\!\\?", NULL},
    {T_STRING, "string", "\".*\"", NULL},
    {T_IDENTIFIER, "identifier", "[A-Za-z_][A-Za-z0-9_]*", NULL},
    {T_NUMBER, "number", "[0-9]+", NULL},
    {T_INDENT, "indent", " +", NULL},
    {T_EOL, "eol", "\n", NULL}
};

struct TTMatcher *TTMatcher_new();
void TTMatcher_match(struct TTMatcher *tt, struct Token *token, char *src);
void TTMatcher_delete(struct TTMatcher *tt);

#endif
