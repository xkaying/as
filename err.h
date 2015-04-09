#ifndef ERR_H
#define ERR_H

#include "token.h"

void printLexerError(char *text,Token *token);
//void printParserError(SourceLocation *location,char *text,AstNode *node);

#endif // ERR_H
