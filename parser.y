%{

#include <stdio.h>
#include <stdlib.h>
#include "lex.yy.h"
#include "hash.h"
#include "astree.h"
#include "semantic.h"
int yyerror(char *msg);
int getLineNumber(void);

FILE *outputFile = NULL;

%}

%union
{
    HASH_NODE *symbol;
    AST *ast;
}

%token<symbol> TK_IDENTIFIER
%token<symbol>  LIT_TRUE 
%token<symbol>   LIT_FALSE 
%token<symbol>   LIT_FLOAT 
%token<symbol>   LIT_INTEGER  
%token<symbol>   LIT_CHAR 
%token<symbol> LIT_STRING

%token KW_BYTE
%token KW_INT
%token KW_LONG
%token KW_FLOAT
%token KW_BOOL

%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_FOR
%token KW_READ
%token KW_PRINT
%token KW_RETURN
%token KW_BREAK

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF

%token TOKEN_ERROR

%type<ast> exp
%type<ast> decl
%type<ast> programa
%type<ast> defvet 
%type<ast> atrivet
%type<ast> seqlit
%type<ast> def
%type<ast> tipo
%type<ast> lit
%type<ast> fundec
%type<ast> parlist
%type<ast> resto
%type<ast> par
%type<ast> body
%type<ast> ibody
%type<ast> rest
%type<ast> cmd
%type<ast> print
%type<ast> expprint
%type<ast> litexp
%type<ast> return
%type<ast> funcpar
%type<ast> if
%type<ast> ifelse
%type<ast> while
%type<ast> for
%type<ast> break
%type<ast> litint

%left '+' '-'
%left '*' '/'
%left OPERATOR_LE OPERATOR _GE
%left OPERATOR_EQ OPERATOR_DIF
%left '<' '>'
%left '.' 'v'
%left '~'


%%
main: programa {astreePrint($1,0,outputFile); astreePrint($1,0,stderr); checkAndSetTypes($1); checkUndeclared();checkOperands($1); fprintf(stderr, "%d semantic errors.\n", getSemanticErrors()); }
;
programa: decl programa {$$ = astreeCreate(AST_DEC,0,$1,$2,0,0);}
| {$$ = 0;}
;
decl: defvet
| def
| fundec
;
defvet: tipo TK_IDENTIFIER '[' litint ']' atrivet ';' {$$ = astreeCreate(AST_DEFVEC,$2,$1,$4,$6,0);}
  ;
litint: LIT_INTEGER {$$=astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
;
atrivet: ':' seqlit {$$ = astreeCreate(AST_SEQLITI,0,$2,0,0,0);}
| {$$ = 0;}
;
seqlit: lit seqlit {$$ = astreeCreate(AST_SEQLIT,0,$1,$2,0,0);}
|  {$$ = 0;}
;
def: tipo TK_IDENTIFIER '=' lit ';' {$$ = astreeCreate(AST_DEF,$2,$1,$4,0,0);}
        ;
tipo: KW_INT {$$=astreeCreate(AST_TINT,0,0,0,0,0);}
 | KW_BYTE {$$=astreeCreate(AST_TBYTE,0,0,0,0,0);}
 | KW_LONG {$$=astreeCreate(AST_TLONG,0,0,0,0,0);}
 | KW_FLOAT {$$=astreeCreate(AST_TFLOAT,0,0,0,0,0);}
 | KW_BOOL {$$=astreeCreate(AST_TBOOL,0,0,0,0,0);}
;
lit:   LIT_TRUE  {$$=astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
      	| LIT_FALSE {$$=astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
      	| LIT_FLOAT {$$=astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
        | LIT_INTEGER  {$$=astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
        | LIT_CHAR {$$=astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
;
fundec: tipo TK_IDENTIFIER '(' parlist ')' body {PlaceFunctionParam($2,$4);$$ = astreeCreate(AST_FUNDEC,$2,$1,$4,$6,0);}
    ;
parlist: par  resto {$$ = astreeCreate(AST_FUNDPARMSI,0,$1,$2,0,0);}
| {$$ = 0;}
;
resto: ',' par resto {$$ = astreeCreate(AST_FUNDPARMS,0,$2,$3,0,0);}
| {$$ = 0;}
;
par: tipo TK_IDENTIFIER {$$ = astreeCreate(AST_PARAMETER,$2,$1,0,0,0);}
;

body: '{' ibody '}' {$$ = astreeCreate(AST_BODY,0,$2,0,0,0);}
;

ibody: cmd rest {$$ = astreeCreate(AST_CMDINIT,0,$1,$2,0,0);}
;

rest: ';' cmd rest {$$ = astreeCreate(AST_CMDLIST,0,$2,$3,0,0);}
|  {$$ = 0;}
;

cmd: TK_IDENTIFIER '=' exp {$$ = astreeCreate(AST_VARASS,$1,$3,0,0,0);}
| TK_IDENTIFIER '[' exp ']' '=' exp {$$ = astreeCreate(AST_ARRAYASS,$1,$3,$6,0,0);}
| KW_READ TK_IDENTIFIER {$$ = astreeCreate(AST_READ,$2,0,0,0,0);}
| print 
| return 
| body 
| if 
| ifelse 
| while 
| break 
| for 
| {$$ = 0;}
;
print: KW_PRINT expprint {$$ = astreeCreate(AST_PRINT,0,$2,0,0,0);}
;
expprint: litexp expprint {$$ = astreeCreate(AST_PRINTARRAY,0,$1,$2,0,0);}
| {$$ = 0;}
;
litexp: exp | LIT_STRING {$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
;
return: KW_RETURN exp {$$ = astreeCreate(AST_RETURN,0,$2,0,0,0);}
;
exp:  exp '+' exp {$$ = astreeCreate(AST_ADD ,0,$1,$3,0,0);}
      	| exp '-' exp {$$=astreeCreate(AST_MIN ,0,$1,$3,0,0);}
      	| exp '*' exp {$$=astreeCreate(AST_MUL ,0,$1,$3,0,0);}
      	| exp '/' exp {$$=astreeCreate(AST_DIV ,0,$1,$3,0,0);}
      	| exp '<' exp  {$$=astreeCreate(AST_LENE,0,$1,$3,0,0);}
      	| exp '>' exp {$$=astreeCreate(AST_GENE,0,$1,$3,0,0);}
      	| exp '.' exp {$$=astreeCreate(AST_AND,0,$1,$3,0,0);}
      	| exp 'v' exp {$$=astreeCreate(AST_OR,0,$1,$3,0,0);}
      	| exp OPERATOR_LE exp {$$=astreeCreate(AST_LE,0,$1,$3,0,0);}
      	| exp OPERATOR_GE exp {$$=astreeCreate(AST_GE,0,$1,$3,0,0);}
      	| exp OPERATOR_EQ exp {$$=astreeCreate(AST_EQ,0,$1,$3,0,0);}
      	| exp OPERATOR_DIF exp {$$=astreeCreate(AST_DIF,0,$1,$3,0,0);}
      	| '~' exp {$$=astreeCreate(AST_NOT,0, $2,0,0,0);}
      	| TK_IDENTIFIER {$$=astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
      	|  TK_IDENTIFIER '[' exp ']' {$$=astreeCreate(AST_VECREAD,$1,$3,0,0,0);}
      	| LIT_TRUE  {$$=astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
      	| LIT_FALSE {$$=astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
      	| LIT_FLOAT {$$=astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
        | LIT_INTEGER  {$$=astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
        | LIT_CHAR {$$=astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
        | TK_IDENTIFIER '(' funcpar ')' {$$=astreeCreate(AST_FUNC,$1,$3,0,0,0);}
      	| '(' exp ')'  {$$=astreeCreate(AST_PARENTHESIS,0,$2,0,0,0);}
        ;
funcpar: exp ',' funcpar  {$$=astreeCreate(AST_FUNCPARF,0,$1,$3,0,0);}
 | exp 
 | {$$ = 0;}
;
if: KW_IF '(' exp  ')' KW_THEN cmd {$$ = astreeCreate(AST_IF,0,$3,$6,0,0);}
;
ifelse: KW_IF '(' exp ')' KW_THEN cmd KW_ELSE cmd {$$ = astreeCreate(AST_IFELSE,0,$3,$6,$8,0);}
;
while: KW_WHILE '(' exp ')' cmd {$$ = astreeCreate(AST_WHILE,0,$3,$5,0,0);}
;
for: KW_FOR '(' TK_IDENTIFIER ':' exp ',' exp ',' exp ')' cmd {$$ = astreeCreate(AST_FOR,$3,$5,$7,$9,$11);}
;
break: KW_BREAK {$$ = astreeCreate(AST_BREAK,0,0,0,0,0);}
;
%%

void setOutPutFile(FILE *outputfile) {
outputFile = outputfile;
}

int yyerror(char *msg) {
fprintf(stderr, "Deu erro de sintaxe na linha %d!\n",getLineNumber());
exit(3);
}