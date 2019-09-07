%{
   
   #include "hash.c"
   #include "main.c"
   #include "y.tab.c"
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
"TRUE" {return LIT_TRUE;}
"FALSE" {return LIT_FALSE;}
{DIGIT}+"."{DIGIT}+ {return LIT_FLOAT;}
{DIGIT}+"." {return LIT_FLOAT;}
"."{DIGIT}+ {return LIT_FLOAT;}
","|";"|":"|"("|")"|"["|"]"|"{"|"}"|"+"|"-"|"*"|"/"|"<"|">"|"="|"v"|"."|"~"|"&"|"$"|"#" {return yytext[0];}
"'"."'" {return LIT_CHAR;}
[A-Za-z_][A-Za-z_0-9]* {hashInsert(yytext); return TK_IDENTIFIER;}
"<=" {return OPERATOR_LE;}
">=" {return OPERATOR_GE;}
"==" {return OPERATOR_EQ;}
"!=" {return OPERATOR_DIF;}
{DIGIT}+ {return LIT_INTEGER ;}
"//".*
"###"            { BEGIN(C_COMMENT); }
<C_COMMENT>"###" { BEGIN(INITIAL); }
<C_COMMENT>.    { }
<C_COMMENT>\n    { lc++;}

["]            { BEGIN(STRING); }
<STRING>["] { BEGIN(INITIAL);return LIT_STRING; }
<STRING>.    { }
<STRING>\n    { lc++;}
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




