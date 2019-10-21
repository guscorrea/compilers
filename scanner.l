%{
   
   #include "hash.h"
   #include "astree.h"
   #include "y.tab.h"
   int lc=0;
   int running=1;
%}
%x C_COMMENT
%x STRING
DIGIT [0-9]
%%
"byte" {return KW_BYTE;}
"int" {return KW_INT;}
"long" {return KW_LONG;}
"float" {return KW_FLOAT;}
"bool" { return KW_BOOL;}
"if" { return KW_IF;}
"then" { return KW_THEN;}
"else" {return KW_ELSE ;}
"while" {return KW_WHILE;}
"for" {return KW_FOR;}
"read" {return KW_READ;}
"print" {return KW_PRINT;}
"return" {return KW_RETURN;}
"break" {return KW_BREAK;}
"TRUE" { yylval.symbol = hashInsert(yytext, 1);return LIT_TRUE;}
"FALSE" { yylval.symbol = hashInsert(yytext, 1);return LIT_FALSE;}
{DIGIT}+"."{DIGIT}+ {yylval.symbol = hashInsert(yytext, 1);return LIT_FLOAT;}
{DIGIT}+"." {yylval.symbol = hashInsert(yytext, 1);return LIT_FLOAT;}
"."{DIGIT}+ {yylval.symbol = hashInsert(yytext, 1);return LIT_FLOAT;}
","|";"|":"|"("|")"|"["|"]"|"{"|"}"|"+"|"-"|"*"|"/"|"<"|">"|"="|"v"|"."|"~"|"&"|"$"|"#" {return yytext[0];}
"'"."'" { yylval.symbol =   hashInsert(yytext, 1);return LIT_CHAR;}
\"(\\.|[^"])*\"	{  yylval.symbol =   hashInsert(yytext, 1); return LIT_STRING; }
[A-Za-z_][A-Za-z_0-9]* { yylval.symbol = hashInsert(yytext, 1);return TK_IDENTIFIER;}
"<=" {return OPERATOR_LE;}
">=" {return OPERATOR_GE;}
"==" {return OPERATOR_EQ;}
"!=" {return OPERATOR_DIF;}
{DIGIT}+ {yylval.symbol = hashInsert(yytext, 1);return LIT_INTEGER ;}
"//".*
"###"            { BEGIN(C_COMMENT); }
<C_COMMENT>"###" { BEGIN(INITIAL); }
<C_COMMENT>.    { }
<C_COMMENT>\n    { lc++;}
\n lc++;
[ \t\r]+ {}
. { return TOKEN_ERROR;}
%%
int yywrap(){
    running = 0;
    return 1;
}

void initMe(){
hashInit();
}

int isRunning(void){
  return running;
}
int getLineNumber(void){
  return lc+1;
}




