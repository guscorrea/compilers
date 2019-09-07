//
// Created by I861082 on 21/08/2019.
//

#ifndef ETAPA1_HASH_H
#define ETAPA1_HASH_H

#endif //ETAPA1_HASH_H

#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 997

typedef struct hash_node {

    int type;
    char *text;
    struct hash_node * next;

} HASH_NODE;

void hashInit(void);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text);
int hashAddress(char *text);
void hashPrint(void);
