#include "tila.h"

struct Node *StringNode_new(struct Token *token, struct GC *gc) {
    ASSERT(token->type->id != T_STRING, "Token is not a string");
    struct Node *node = Node_new(gc, token, N_STRING);
    node->repr = StringNode_repr;
    node->get_value = StringNode_get_value;
    return node;
}

void StringNode_repr(struct Node *node, struct Environment *env) {
    char *content = Token_content(node->start, env->src);
    printf("%s", content);
}

void StringNode_get_value(struct Node *node,
                          struct Environment *env) {
    GC_push(node->gc, NULL);
    char *content = Token_content(node->start, env->src);
    size_t len = strlen(content);
    size_t start = 0;
    for(size_t i = 1; i < len - 1; i++) {
        char c = content[i];
        if(c != '{') {
            putchar(c);
        } else {
            i++;
            start = i;
            while(i < len - 1) {
                c = content[i];
                if(c == '}') {
                    content[i] = '\0';
                    struct Node *sub = Environment_get(env, content + start);
                    if(sub == NULL) {
                        printf("NULL");
                    } else {
                        sub->repr(sub, env);
                    }
                    content[i] = c;
                    break;
                }
                i++;
            }
        }
    }
    putchar('\n');
}
