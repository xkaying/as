#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "token.h"

Token *createToken()
{
    Token *token;
    token=(Token*)calloc(sizeof(Token),1);
    return token;
}

Token *initToken(Token *token,TokenType type,SourceLocation *location,char *text)
{
    assert(token);
    assert(location);
    token->type=type;
    token->text=text;
    token->location.line=location->line;
    token->location.column=location->column;
    return token;
}

Token *checkKeyToken(Token *token)
{
    assert(token);
    if(token->type==TK_IDENTIFY){
        if(strcmp(token->text,"var")==0){
            token->type=TKKEY_VAR;
            free(token->text);
            token->text=0;
        }else if(strcmp(token->text,"print")==0){
            token->type=TKKEY_PRINT;
            free(token->text);
            token->text=0;
        }
    }
    return token;
}

void printToken(Token *token)
{
    assert(token);
    switch(token->type){
        case TK_IDENTIFY:{
            printf("TK_IDENTIFY line:%d column:%d %s\n",token->location.line,token->location.column,token->text);
            break;
        }
        case TK_NUMBER:{
            printf("TK_NUMBER: line:%d column:%d %s\n",token->location.line,token->location.column,token->text);
            break;
        }
        case TKOPT_ADD:{
            printf("TKOPT_ADD: line:%d column:%d\n",token->location.line,token->location.column);
            break;
        }
        case TKOPT_SUB:{
            printf("TKOPT_SUB: line:%d column:%d\n",token->location.line,token->location.column);
            break;
        }
        case TKOPT_MUL:{
            printf("TKOPT_MUL: line:%d column:%d\n",token->location.line,token->location.column);
            break;
        }
        case TKOPT_DIV:{
            printf("TKOPT_DIV: line:%d column:%d\n",token->location.line,token->location.column);
            break;
        }
        case TKOPT_MOD:{
            printf("TKOPT_MOD: line:%d column:%d\n",token->location.line,token->location.column);
            break;
        }
        case TKOPT_ASSIGN:{
            printf("TKOPT_ASSIGN: line:%d column:%d\n",token->location.line,token->location.column);
            break;
        }
        case TKKEY_PRINT:{
            printf("TKKEY_PRINT: line:%d column:%d\n",token->location.line,token->location.column);
            break;
        }
        case TKKEY_VAR:{
            printf("TKKEY_VAR: line:%d column:%d\n",token->location.line,token->location.column);
            break;
        }

        default:{
            printf("TK_NONE: line:%d column:%d\n",token->location.line,token->location.column);
        }
    }
}
