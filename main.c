#include <stdio.h>

int main(int argc, char** argv)
{
    int tok;
    initMe();
    yyparse();
    hashPrint();
}
