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
#define TAC_LABEL 8
#define TAC_AND 9
#define TAC_OR 10
#define TAC_NOT 11
#define TAC_LE 12
#define TAC_GE 13
#define TAC_EQ 14
#define TAC_DIF 15
#define TAC_PRINT 16
#define TAC_ASSIGN 17
#define TAC_BEGIN_FUNC 18
#define TAC_END_FUNC 19
#define TAC_INDEX_TEMP 20
#define TAC_ARRAY_INDEX 21
#define TAC_RET 22
#define TAC_READ 23
#define TAC_IFZ 24
#define TAC_JUMP 25
#define TAC_WHILE 26
#define TAC_TEMP_FUNCTION 27
#define TAC_CALL 28
#define TAC_PUSH_ARG 29
#define TAC_FOR 30
#define TAC_BREAK 31
typedef struct tac_node {
    int type;
    int callId;
    HASH_NODE *res;
    HASH_NODE *op1;
    HASH_NODE *op2;
    struct tac_node *prev;
    struct tac_node *next;
} TAC;
TAC *TAC_make_push_arg(TAC *arg, AST *func_name, int callId);
TAC *TAC_make_func_call(AST *func_name, TAC *args, int callId);
TAC *TAC_make_return(TAC *expression);
TAC *TAC_make_ary_index(AST *id, TAC *index);
TAC *TAC_make_func_declaration(AST *node, TAC *func_params, TAC *func_body);
TAC* TAC_make_assign(TAC *expression2 , TAC *expression,AST *node);
TAC* TAC_make_print(TAC *expression);
TAC* tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2);
void tacPrintSingle( TAC *tac);
void tacPrintBackwards(TAC *tac);
TAC* tacJoin(TAC *l1, TAC *l2);
TAC* generateCode (AST *ast,AST *FUNC);

#endif //ETAPA1_TACS_H
