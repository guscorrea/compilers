//
// Created by I861082 on 21/08/2019.
//

#include <string.h>
#include "hash.h"

HASH_NODE*Table[HASH_SIZE];

void hashInit(void) {

    int i;
    for (int i = 0; i < HASH_SIZE; ++i) {
        Table[i] = 0;
    }
}

int hashAddress(char *text) {
    int address = 1;
    int i;
    for (int i = 0; i < strlen(text); ++i) {
        address = (address * text[i]) % HASH_SIZE + 1;
    }

    return address-1;
}

HASH_NODE *hashFind(char *text) {
    HASH_NODE *node;
    int adress = hashAddress(text);
    for (node = Table[adress]; node; node = node->next)
        if (!strcmp(text, node->text))
            return node;
    return 0;
}

HASH_NODE *hashInsert(char *text, int type) {
    HASH_NODE *newnode;
    if ((newnode = hashFind(text)) != 0)
        return newnode;
    int address = hashAddress(text);
    newnode = (HASH_NODE*) calloc(1, sizeof(HASH_NODE));
    newnode-> type = type;
    newnode->text = (char*) calloc(strlen(text)+1, sizeof(char));
    strcpy(newnode->text, text);
    newnode->next = Table[address];
    for(int i=0;i<200;i++){
      newnode->datatypefunction[i] =0;   
    }
    Table[address] = newnode;
    return newnode;
}

void hashPrint(void){
    int index;
    HASH_NODE* currentNode;
    for(index = 0; index < HASH_SIZE; index++)
        for(currentNode = Table[index]; currentNode; currentNode = currentNode->next)
            printf("Hash <%d, %s> \t Addr: %p \n", index, currentNode->text, currentNode);
}

int hashCheckUndeclared(void){
    HASH_NODE* node;
    int errors = 0;

    for(int i = 0; i < HASH_SIZE; ++i){
        for(node = Table[i]; node; node = node->next){
            if(node->type == SYMBOL_IDENTIFIER){
                fprintf(stderr, "Semantic ERROR: Symbol %s undeclared.\n", node->text);
                errors++;
            }
        }
    }

    return errors;
}

HASH_NODE * makeTemp(void) {
    static int serialNumber = 0;
    static char name[100];

    sprintf(name, "Temp%d", serialNumber++);
    return hashInsert(name, SYMBOL_TEMP);
}

HASH_NODE * makeLabel(void) {
    static int serialNumber = 0;
    static char name[100];

    sprintf(name, "Label%d", serialNumber++);
    return hashInsert(name, SYMBOL_LABEL);
}

void generateASMGlobalVariablesFromLitValues(FILE* fout){
    static int stringCounter = 0;

    fprintf(fout, "\t.section\t.rodata\n"
                  "LC0:\t.string \"%%d\"\n"
                  "LC1:\t.string \"%%f\"\n"
                  "LC2:\t.string \" %%c\"\n"
                  "TRUE:\t.string \"TRUE\"\n"
                  "FALSE:\t.string \"FALSE\"\n"
                  "_TRUE:\t.long 1\n"
                  "_FALSE:\t.long 0\n");

    for(int i = 0; i < HASH_SIZE; i++){
        for(HASH_NODE* node = Table[i]; node; node = node->next){
            if(node){
                if(node->type == SYMBOL_LITSTRING){
                    addMatch(node->text, stringCounter);
                    fprintf(fout, "\t.section\t.rodata\n"
                                  "%s%d:\t.string\t%s\n", LITSTR_VAR_NAME, stringCounter, node->text);
                    stringCounter++;
                }
                else if(node->type == SYMBOL_LITINT){
                    fprintf(fout, "\t.section\t.rodata\n"
                                  "_%s:\t.long\t%s\n", node->text, node->text);
                }
                else if(node->type == SYMBOL_LITCHAR){
                    addMatch(node->text, stringCounter);
                    fprintf(fout, "\t.section\t.rodata\n"
                                  "%s%d:\t.long\t%d\n", LITCHAR_VAR_NAME, stringCounter, (int)(node->text[1]));
                    stringCounter++;
                }
                else if(node->type == SYMBOL_TEMP){
                    fprintf(fout, "\t.data\n"
                                  "_%s:\t.long\t 0\n", node->text);
                }
            }
        }
    }
}
