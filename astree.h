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
#define AST_NOT 4
#define AST_DIF 5
#define AST_EQ 6
#define AST_GE 7
#define AST_LE 8
#define AST_OR 9
#define AST_AND 10
#define AST_GENE 11
#define AST_LENE 12
#define AST_MIN 13
#define AST_DIV 46
#define AST_FUNC 14
#define AST_QUOTA 15
#define AST_CMDINIT 16
#define AST_CMDLIST 17
#define AST_BODY 18
#define AST_DEC 19
#define AST_DEFVEC 20
#define AST_SEQLITI 21
#define AST_SEQLIT 22
#define AST_DEF 23
#define AST_FUNDEC 24
#define AST_FUNDPARMSI 25
#define AST_PARAMETER 26
#define AST_VARASS 27//VARIABLE ASSIGN  
#define AST_ARRAYASS 28//ARRAY ASSIGN
#define AST_READ 29 
#define AST_PRINT 30
#define AST_PRINTARRAY 31
#define AST_RETURN 32
#define AST_FUNCPARF 33
#define AST_FUNCPAR 34
#define AST_IF 35
#define AST_IFELSE 36
#define AST_FOR 37
#define AST_WHILE 38
#define AST_BREAK 39
#define AST_TINT 40
#define AST_TBYTE 41
#define AST_TLONG 42
#define AST_TFLOAT 43
#define AST_TBOOL 44
#define AST_FUNDPARMS 45
#define AST_VECREAD 100


typedef struct astree_node {
    int type;
    HASH_NODE *symbol;
    struct astree_node *son[MAX_SONS];
} AST;

AST *astreeCreate(int type, HASH_NODE* symbol, AST *son0, AST *son1, AST *son2, AST *son3);
void astreePrint(AST *son0, int level, FILE *outputFile);
#endif //ETAPA1_ASTREE_H
