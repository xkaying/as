#include "err.h"
#include <stdio.h>
#include "token.h"
#include <assert.h>

void printLexerError(char *text,Token *token)
{
    assert(text);
    assert(token);
    printf("%s ",text);
    printToken(token);
}
