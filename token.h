#ifndef TOKEN_H
#define TOKEN_H

#include "location.h"

typedef enum tokentype{
    TK_NONE,
    TK_IDENTIFY,
    TK_NUMBER,
    TKOPT_ADD,
    TKOPT_SUB,
    TKOPT_MUL,
    TKOPT_DIV,
    TKOPT_MOD,
    TKOPT_ASSIGN,
    TKKEY_VAR,
    TKKEY_PRINT,
}TokenType;

typedef struct _token{
    TokenType type;
    char *text;
    SourceLocation location;
}Token;

Token *createToken();
Token *initToken(Token *token,TokenType type,SourceLocation *location,char *text);
Token *checkKeyToken(Token *token);
void printToken(Token *token);

#endif // TOKEN_H
