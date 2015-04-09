#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

#define AS_Version 0.0.1

void printUsage()
{
    printf("usage:as [-opinion] [filename]\n");
    printf("[opinion]\n");
    printf("\t-v 显示当前版本.\n");
    printf("\t-h 显示帮助信息.\n");
}

void printVersion()
{
    printf("as version 0.0.1");
    printf("\n");
}

void parserOpinion(char *buffer)
{
    if(buffer[0]=='-'){
        char *word=buffer+1;
        if(strcmp(word,"version")==0){
            printVersion();
            exit(0);
        }else if(strcmp(word,"help")==0){
            printUsage();
            exit(0);
        }
    }
    printf("未知的命令-%s\n",buffer);
    printUsage();
    exit(1);
}

void parserLexer(char *buffer,int size)
{
    Token *token;
    Lexer *lexer;
    lexer=createLexer();
    initLexer(lexer,buffer,size);
    token=readToken(lexer);
    while(token){
        printToken(token);
        token=readToken(lexer);
    }
}

int main(int argc,char *argv[])
{
    if(argc<2){
        printUsage();
        return 0;
    }
    char *buffer;
    buffer=argv[1];
    if(buffer[0]=='-'){
        parserOpinion(buffer+1);
    }
    //printf("%s\n",argv[1]);
    FILE *fl;
    fl=fopen(argv[1],"r");
    if(fl==0){
        printf("无法打开文件%s,请检查文件是否存在或者是否拥有足够的权限.",argv[1]);
        return 1;
    }
    long len;
    fseek(fl,0,SEEK_END);
    len=ftell(fl);
    buffer=(char*)malloc(len);
    fseek(fl,0,SEEK_SET);
    fread(buffer,sizeof(char),len,fl);
    parserLexer(buffer,len);
    free(buffer);
    return 0;
}


