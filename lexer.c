#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "err.h"

/*****************************
    digit 0-9
    letter a-z|A-Z|_
    letterOrdigit digit|letter
    identify  letter letterOrdigit*
    number 0 | [1-9] digit*
    operator +|-|*|/|%

    key  var | print

**************************/

Lexer *createLexer()
{
    Lexer *lexer;
    lexer=(Lexer*)calloc(sizeof(Lexer),1);
    return lexer;
}

Lexer *initLexer(Lexer *lexer,char *buffer,int size)
{
    assert(lexer);
    lexer->buffer=buffer;
    lexer->size=size;
    lexer->pos=0;
    resetLocation(&(lexer->location));
    return lexer;
}

Token *readToken(Lexer *self)
{
    assert(self);
    if(!readChar(self)){
        //表示读取结束
        return 0;
    }
    moveLocation(&(self->location));
    if(isSkip(self->ch)){        
        return readToken(self);
    }
    if(isNewLine(self->ch)){
        enterLocation(&(self->location));
        return readToken(self);
    }
    if(isLetter(self->ch)){
        return readIdentify(self);
    }
    if(isDigit(self->ch)){
        return readNumber(self);
    }
    return readOptToken(self);
}

int readChar(Lexer *self)
{
    if(self->pos>=self->size){
        return 0;
    }
    self->ch=self->buffer[self->pos++];
    return 1;
}

Token *readIdentify(Lexer *self)
{
    Token *token;
    token=createToken();
    char *buffer=malloc(sizeof(char)*128);
    int len=0;
    buffer[len]=self->ch;
    len++;
    initToken(token,TK_IDENTIFY,&(self->location),0);
    while(readChar(self)){
        if(isLetterOrDigit(self->ch)){
            moveLocation(&(self->location));
            buffer[len]=self->ch;
            len++;
        }else{
            self->pos--;
            buffer[len]='\0';
            token->text=buffer;
            return checkKeyToken(token);
        }
    }
    buffer[len]='\0';
    token->text=buffer;
    return checkKeyToken(token);
}

Token *readNumber(Lexer *self)
{
    Token *token;
    token=createToken();
    char *buffer=malloc(sizeof(char)*128);
    int len=0;
    buffer[len]=self->ch;
    len++;
    initToken(token,TK_NUMBER,&(self->location),0);

    int unknow;
    unknow=0;
    while(readChar(self)){
        if(isDigit(self->ch)){
            if(buffer[0]=='0'){
                unknow=1;
            }
            moveLocation(&(self->location));
            buffer[len]=self->ch;
            len++;
        }else if(isLetter(self->ch)){
            unknow=1;
            moveLocation(&(self->location));
            buffer[len]=self->ch;
            len++;
        }else{
            buffer[len]='\0';
            token->text=buffer;
            if(unknow>0){
                //出错提示
                printLexerError("非法的标识符。\n",token);
                exit(1);
            }
            self->pos--;

            return token;
        }
    }
    if(unknow>0){
        //出错提示
    }
    buffer[len]='\0';
    token->text=buffer;
    if(unknow>0){
        //出错提示
        printLexerError("非法的标识符 ",token);
        exit(1);
    }
    return token;
}

Token *readOptToken(Lexer *self)
{
    TokenType type;
    Token *token;
    token=createToken();
    initToken(token,type,&(self->location),0);

    switch (self->ch){
    case '+':
        {
            type = TKOPT_ADD;
            break;
        }
    case '-':
        {
            type = TKOPT_SUB;
            break;
        }
    case '*':
        {
            type = TKOPT_MUL;
            break;
        }
    case '/':
        {
            type = TKOPT_DIV;
            break;
        }
    case '%':
        {
            type = TKOPT_MOD;
            break;
        }
    case '=':{
            type=TKOPT_ASSIGN;
            break;
        }
    default:
        {
            token->type=TK_IDENTIFY;
            char buff[32];
            buff[0]=self->ch;
            buff[1]='\0';
            token->text=buff;
            printLexerError("未知的字符 ",token);
            exit(1);
        }
    }
    token->type=type;
    return token;
}


inline int isDigit(char c)
{
    return '0' <= c && c <= '9';
}

inline int isDigitOct(char c) {
    return '0' <= c && c <= '7';
}

inline int isDigitHex(char c)
{
    return isDigit(c) || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F');
}

inline int isLetter(char c)
{
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_';
}

inline int isLetterOrDigit(char c)
{
    return isLetter(c) || isDigit(c);
}

inline int isSkip(char c)
{
    if( c == '\t' || c == '\v' || c == ' ') {
        return 1;
    }
    return 0;
}

inline int isNewLine(char c)
{
    if(c=='\n'){
        return 1;
    }
    return 0;
}
