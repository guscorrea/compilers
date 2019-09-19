//
// Created by I861082 on 19/09/2019.
//

#include "astree.h"
#include <stdio.h>
#include <stdlib.h>

AST *astreeCreate(int type, HASH_NODE* symbol, AST *son0, AST *son1, AST *son2, AST *son3) {
    AST* newnode = 0;

    newnode = (AST*) calloc(1, sizeof(AST));
    newnode->type = type;
    newnode->symbol = symbol;
    newnode->son[0] = son0;
    newnode->son[1] = son1;
    newnode->son[2] = son2;
    newnode->son[3] = son3;
    return newnode;
}

void astreePrint(AST *node, int level) {
    int i;
    if (!node) return;
    for (int i = 0; i < level; ++i) {
        fprintf(stderr, " ");
    }
    fprintf(stderr, "AST(");
    switch (node->type) {
        case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL,"); break;
        case AST_ADD: fprintf(stderr, "AST_ADD,"); break;
        case AST_MUL: fprintf(stderr, "AST_MUL,"); break;
        default: break;
    }

    for (int i = 0; i < MAX_SONS; ++i) {
        astreePrint(node->son[i], level +1);
    }
}

