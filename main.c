#include <stdio.h>
#include <stdlib.h>

void initMe(void);
void hashPrint(void);
int yyparse(void);
void setOutPutFile(FILE *outputFile);
extern FILE* yyin;

int main(int argc, char** argv)
{
    int tok;
    FILE *outputFile;
    initMe();

    if(argc < 3){
        fprintf(stderr, "One of the file name argument is missing!\n");
        exit(1);
    }

    yyin = fopen(argv[1], "r");
    if(yyin == 0){
        fprintf(stderr, "Error opening file %s!\n", argv[1]);
        exit(2);
    }

    if(outputFile = fopen(argv[2], "w")) {
        setOutPutFile(outputFile);
    }
 
    yyparse();
    //hashPrint();
    exit(0);
}
