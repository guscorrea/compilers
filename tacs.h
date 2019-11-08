//
// Created by I861082 on 06/11/2019.
//

#ifndef ETAPA1_TACS_H
#define ETAPA1_TACS_H

#include "hash.h"
#include "astree.h"

#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_MUL 4
#define TAC_DIV 5
#define TAC_MOVE 6
#define TAC_IF 7
#define TAC_LABEL 8
#define TAC_AND 9
#define TAC_OR 10
#define TAC_NOT 11
#define TAC_LE 12
#define TAC_GE 13
#define TAC_EQ 14
#define TAC_DIF 15


typedef struct tac_node {
    int type;
    HASH_NODE *res;
    HASH_NODE *op1;
    HASH_NODE *op2;
    struct tac_node *prev;
    struct tac_node *next;
} TAC;

TAC* tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2);
void tacPrintSingle( TAC *tac);
void tacPrintBackwards(TAC *tac);
TAC* tacJoin(TAC *l1, TAC *l2);
TAC* generateCode (AST *ast);

#endif //ETAPA1_TACS_H