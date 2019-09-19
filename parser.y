%{

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
int yyerror(char *msg);
int getLineNumber(void);
%}

%union
{
    HASH_NODE *symbol;
}

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

programa: defvet programa | def programa | fundec programa | 
    ;

defvet: tipo TK_IDENTIFIER '[' LIT_INTEGER ']' atrivet ';'
  ;
atrivet: ':' seqlit |
;
seqlit: lit seqlit |  
;
def: tipo TK_IDENTIFIER '=' lit ';'
        ;
tipo: KW_INT | KW_BYTE | KW_LONG | KW_FLOAT | KW_BOOL 
;
lit:  LIT_INTEGER  | LIT_FLOAT | LIT_CHAR | LIT_TRUE | LIT_FALSE
;
fundec: tipo TK_IDENTIFIER '(' parlist ')' body
    ;
parlist: par resto
|
;
resto: ',' par resto
|
;
par: tipo TK_IDENTIFIER
;

body: '{' ibody '}'
;

ibody: cmd rest
;

rest: ';' cmd rest
|
;

cmd: TK_IDENTIFIER '=' exp | TK_IDENTIFIER '[' exp ']' '=' exp | KW_READ TK_IDENTIFIER | print 
| return | body | if | ifelse | while | break | for |
;
print: KW_PRINT expprint
;
expprint: LIT_STRING expprint | exp expprint | exp | LIT_STRING
;
return: KW_RETURN exp
;
exp:  exp '+' exp
      	| exp '-' exp
      	| exp '*' exp
      	| exp '/' exp
      	| exp '<' exp
      	| exp '>' exp
      	| exp '.' exp
      	| exp 'v' exp
      	| exp OPERATOR_LE exp
      	| exp OPERATOR_GE exp
      	| exp OPERATOR_EQ exp
      	| exp OPERATOR_DIF exp
      	| '~' exp
      	| TK_IDENTIFIER
      	|  TK_IDENTIFIER '[' exp ']'
      	| LIT_TRUE
      	| LIT_FALSE
      	| LIT_FLOAT
        | LIT_INTEGER
        | LIT_CHAR
        | TK_IDENTIFIER '(' funcpar ')'
      	| '(' exp ')'
        ;
funcpar: exp ',' funcpar | exp | 
;
if: KW_IF '(' exp  ')' KW_THEN cmd
;
ifelse: KW_IF '(' exp ')' KW_THEN cmd KW_ELSE cmd 
;
while: KW_WHILE '(' exp ')' cmd 
;
for: KW_FOR '(' TK_IDENTIFIER ':' exp ',' exp ',' exp ')' cmd
;
break: KW_BREAK
;
%%

int yyerror(char *msg) {
fprintf(stderr, "Deu erro de sintaxe na linha %d!\n",getLineNumber());
exit(3);
}