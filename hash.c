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

void generateGlobals(FILE* fout){
    static int counter = 0;
    printBoolAndString(fout);
    for(int i = 0; i < HASH_SIZE; i++){
        for(HASH_NODE* node = Table[i]; node; node = node->next){
            if(node){
                switch (node->type){
                    case SYMBOL_LITSTRING: {
                        addTemp(node->text, counter);
                        fprintf(fout, "\t.section\t.rodata\n"
                                      "%s%d:\t.string\t%s\n", STRING_TEMP, counter, node->text);
                        counter++;
                    }
                    break;
                    case SYMBOL_LITINT: {
                        fprintf(fout, "\t.section\t.rodata\n"
                                      "_%s:\t.long\t%s\n", node->text, node->text);
                    }
                    break;
                    case SYMBOL_LITCHAR: {
                        addTemp(node->text, counter);
                        fprintf(fout, "\t.section\t.rodata\n"
                                      "%s%d:\t.long\t%d\n", STRING_TEMP, counter, (int)(node->text[1]));
                        counter++;
                    }
                    break;
                    case SYMBOL_TEMP: {
                        fprintf(fout, "\t.data\n"
                                      "_%s:\t.long\t 0\n", node->text);
                    }
                    break;
                    default:
                        break;
                }
            }
        }
    }
}
