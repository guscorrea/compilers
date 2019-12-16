#include "assembly_utils.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

int emptyIndex = 0;
TEMP_LIST temps[1000];

void addTemp(char* text, int counter){
    temps[emptyIndex].text = (char*)malloc(strlen(text)*sizeof(char)+1);
    strcpy(temps[emptyIndex].text, text);
    temps[emptyIndex].counter = counter;
    emptyIndex++;
}

void printBoolAndString(FILE* fout){
        fprintf(fout, "\t.section\t.rodata\n"
                      "LC0:\t.string \"%%d\"\n"
                      "LC1:\t.string \"%%f\"\n"
                      "LC2:\t.string \" %%c\"\n"
                      "TRUE:\t.string \"TRUE\"\n"
                      "FALSE:\t.string \"FALSE\"\n"
                      "_TRUE:\t.long 1\n"
                      "_FALSE:\t.long 0\n");
}


char* getVarName(char* text, const char* varName){
    int counter = findTempCounter(text);
    char* varFullName = (char*)malloc(sizeof(varName) + sizeof(counter));
    strcpy(varFullName, varName);
    char num[10];
    sprintf(num, "%d", counter);
    strcat(varFullName, num);
    return varFullName;
}

int findTempCounter(char* text){
    for(int i = 0; i < index; i++){
        if(strcmp(text, temps[i].text) == 0)
            return temps[i].counter;
    }
    return 0;
}



