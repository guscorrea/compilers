%{

#include <stdio.h>
#include <stdlib.h>
%}

%token KW_BYTE       256
%token KW_INT        257
%token KW_LONG       258
%token KW_FLOAT      259
%token KW_BOOL       260

%token KW_IF         261
%token KW_THEN       262
%token KW_ELSE       263
%token KW_WHILE      264
%token KW_FOR        265
%token KW_READ       266
%token KW_PRINT      267
%token KW_RETURN     268
%token KW_BREAK      269

%token OPERATOR_LE   270
%token OPERATOR_GE   271
%token OPERATOR_EQ   272
%token OPERATOR_DIF  273

%token TK_IDENTIFIER 280

%token LIT_INTEGER   281
%token LIT_FLOAT     282
%token LIT_TRUE      283
%token LIT_FALSE     284
%token LIT_CHAR      285
%token LIT_STRING    286

%token TOKEN_ERROR   290



%%

programa: programa def
    |
    ;


def: KW_INT TK_IDENTIFIER '=' LIT_INTEGER
        ;

decl: vardec | fundec
    ;

vardec: KW_INT TK_IDENTIFIER ';' LIT_INTEGER
    ;

fundec: KW_INT TK_IDENTIFIER '(' ')' body
    ;

body: cmd body
    |
    ;

cmd: TK_IDENTIFIER '=' LIT_FLOAT
;


%%

int yyerror(char *msg) {
fprintf(stderr, "Deu erro de sintaxe!\n");
exit(3);
}