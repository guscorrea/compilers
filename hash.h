//
// Created by I861082 on 21/08/2019.
//

#ifndef ETAPA1_HASH_H
#define ETAPA1_HASH_H

#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 997

#define SYMBOL_IDENTIFIER 1
#define SYMBOL_LITINT 2
#define SYMBOL_LITREAL 3
#define SYMBOL_SCALAR 4
#define SYMBOL_VECTOR 5
#define SYMBOL_FUNCTION 6

#define DATATYPE_INT 1
#define DATATYPE_LONG 2
#define DATATYPE_FLOAT 3
#define DATATYPE_BOOL 4

typedef struct hash_node {

    int type;
    int datatype;
    char *text;
    struct hash_node * next;

} HASH_NODE;

void hashInit(void);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
int hashAddress(char *text);
void hashPrint(void);
HASH_NODE *hashFind(char *text);
int hashCheckUndeclared(void);

#endif //ETAPA1_HASH_H
