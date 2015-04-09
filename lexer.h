#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include "location.h"

typedef struct _lexer{
        char *buffer;
        int size;
        int pos;
        char ch;
        SourceLocation location;
}Lexer;

Lexer *createLexer();
Lexer *initLexer(Lexer *lexer,char *buffer,int size);

Token *readToken(Lexer *lexer);
Token *readIdentify(Lexer *lexer);
Token *readNumber(Lexer *lexer);
Token *readOptToken(Lexer *lexer);
int readChar(Lexer *lexer);


int isDigit(char c);
int isDigitOct(char c);
int isDigitHex(char c);
int isLetter(char c);
int isLetterOrDigit(char c);
int isSkip(char c);
int isNewLine(char c);

#endif // LEXER_H
