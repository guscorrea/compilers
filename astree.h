//
// Created by I861082 on 19/09/2019.
//

#ifndef ETAPA1_ASTREE_H
#define ETAPA1_ASTREE_H

#include <stdio.h>
#include "hash.h"

#define MAX_SONS 4
#define AST_SYMBOL 1
#define AST_ADD 2
#define AST_MUL 3

typedef struct astree_node {
    int type;
    HASH_NODE *symbol;
    struct astree_node *son[MAX_SONS];
} AST;

AST *astreeCreate(int type, HASH_NODE* symbol, AST *son0, AST *son1, AST *son2, AST *son3);
void astreePrint(AST *son0, int level);
#endif //ETAPA1_ASTREE_H
