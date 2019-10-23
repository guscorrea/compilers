#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "semantic.h"

void initMe(void);
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
    } else {
        fprintf(stderr, "Error opening file %s!\n", argv[2]);
        exit(2);
    }
 
    yyparse();
    hashPrint();

    if(getSemanticErrors() > 0)
        exit(4);

    fprintf(stderr, "Finished!\n");
    exit(0);
}
