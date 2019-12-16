#ifndef COMP_LITSTR_H
#define COMP_LITSTR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hash.h"

#define STRING_TEMP "STRING"
#define CHAR_TEMP "CHAR"
#define LOGIC_LABEL "LogicLabel"

typedef struct temp_list{
        int counter;
        char* text;
} TEMP_LIST;

int findTempCounter(char* text);
void addTemp(char* text, int counter);
void printBoolAndString(FILE* fout);
char* getVarName(char* text, const char* varName);

#endif // COMP_LITSTR_H
