#ifndef TOKENTYPE_H
#define TOKENTYPE_H

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
    T_NONE
};

struct TokenType {
    enum TokenTypeEnum id;
    const char *name;
    regex_t* regex;
};

#endif
