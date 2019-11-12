//
// Created by I861082 on 06/11/2019.
//

#include "tacs.h"
static int call_count = 0;
TAC* makeBinOp(int type, TAC* code0, TAC* code1);
TAC* makeIfThen(int type, TAC* code0, TAC* code1);
TAC* makeWhile(TAC *condition, TAC *body);
TAC* makeIfThenElse(TAC *condition, TAC *if_true, TAC *if_false);

TAC* tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2) {
    TAC* newtac;
    newtac = (TAC*) calloc(1, sizeof(TAC));
    newtac->type = type;
    newtac->res = res;
    newtac->op1 = op1;
    newtac->op2 = op2;
    newtac->prev = 0;
    newtac->next = 0;
    return newtac;
}

void tacPrintSingle( TAC *tac) {
    if (!tac) return;
    if (tac->type == TAC_SYMBOL) return;
    fprintf(stderr, "TAC(");
    switch (tac->type) {
        case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); break;
        case TAC_ADD: fprintf(stderr, "TAC_ADD"); break;
        case TAC_SUB: fprintf(stderr, "TAC_SUB"); break;
        case TAC_MUL: fprintf(stderr, "TAC_MUL"); break;
        case TAC_DIV: fprintf(stderr, "TAC_DIV"); break;
        case TAC_MOVE: fprintf(stderr, "TAC_MOVE"); break;
        case TAC_AND: fprintf(stderr, "TAC_AND"); break;
        case TAC_OR: fprintf(stderr, "TAC_OR"); break;
        case TAC_NOT: fprintf(stderr, "TAC_NOT"); break;
        case TAC_LABEL: fprintf(stderr, "TAC_LABEL"); break;
        case TAC_LE: fprintf(stderr, "TAC_LE"); break;
        case TAC_GE: fprintf(stderr, "TAC_GE"); break;
        case TAC_EQ: fprintf(stderr, "TAC_EQ"); break;
        case TAC_DIF: fprintf(stderr, "TAC_DIF"); break;
        case TAC_PRINT: fprintf(stderr, "TAC_PRINT"); break;
        case TAC_ASSIGN: fprintf(stderr, "TAC_ASSIGN"); break;
        case TAC_BEGIN_FUNC: fprintf(stderr, "TAC_BEGIN_FUNC"); break;
        case TAC_END_FUNC: fprintf(stderr, "TAC_END_FUNC"); break;
        case TAC_INDEX_TEMP:fprintf(stderr, "TAC_INDEX_TEMP"); break;
        case TAC_ARRAY_INDEX: fprintf(stderr, "TAC_VEC_READ"); break;
        case TAC_RET: fprintf(stderr, "TAC_RET"); break;
        case TAC_READ: fprintf(stderr, "TAC_READ"); break;
        case TAC_JUMP: fprintf(stderr, "TAC_JUMP"); break;
        case TAC_IFZ: fprintf(stderr, "TAC_IFZ"); break;
        case TAC_WHILE: fprintf(stderr, "TAC_WHILE"); break;
        case TAC_PUSH_ARG:fprintf(stderr, "TAC_PUSH_ARG"); break;
        case TAC_CALL:fprintf(stderr, "TAC_CALL"); break;
        case TAC_TEMP_FUNCTION:fprintf(stderr, "TAC_TEMP_FUNCTION"); break;
        //TODO: finish print cases
        default: fprintf(stderr, "UNKNOWN - type %i", tac->type); break;
    }
    if (tac->res) fprintf(stderr, ",%s", tac->res->text);
            else fprintf(stderr, ",0");
    if (tac->op1) fprintf(stderr, ",%s", tac->op1->text);
            else fprintf(stderr, ",0");
    if (tac->op2) fprintf(stderr, ",%s", tac->op2->text);
            else fprintf(stderr, ",0");
    fprintf(stderr, ");\n");
}

void tacPrintBackwards(TAC *tac) {
    for (;tac; tac = tac->prev) {
        tacPrintSingle(tac);
    }
}

TAC* tacJoin(TAC *l1, TAC *l2) {
    TAC* tac;
    if(!l1) return l2;
    if(!l2) return l1;
    for ( tac = l2; tac->prev; tac = tac->prev)
        ;
    tac->prev = l1;
    return l2;
}

TAC* generateCode (AST *ast,AST *FUNC) {
    int i;
    TAC *code[MAX_SONS];

    if(!ast) return 0;
    if(ast->type ==AST_FUNC){
            call_count++;
        }
    for (int i = 0; i < MAX_SONS; ++i)
        if(ast->type ==AST_FUNC){
            code[i] = generateCode(ast->son[i],ast);
        }
        else{
            code[i] = generateCode(ast->son[i],FUNC);
        }

        switch (ast->type) {
            case AST_SYMBOL: return tacCreate(TAC_SYMBOL, ast->symbol, 0, 0); break;
            case AST_VARASS: return tacJoin(code[0], tacCreate(TAC_MOVE, ast->symbol, code[0]?code[0]->res:0,0)); break;
            case AST_ADD: return makeBinOp(TAC_ADD, code[0], code[1]); break;
            case AST_MIN: return makeBinOp(TAC_SUB, code[0], code[1]); break;
            case AST_MUL: return makeBinOp(TAC_MUL, code[0], code[1]); break;
            case AST_DIV: return makeBinOp(TAC_DIV, code[0], code[1]); break;
            case AST_LE: return makeBinOp(TAC_LE, code[0], code[1]); break;
            case AST_GE: return makeBinOp(TAC_GE, code[0], code[1]); break;
            case AST_AND: return makeBinOp(TAC_AND, code[0], code[1]); break;
            case AST_OR: return makeBinOp(TAC_OR, code[0], code[1]); break;
            case AST_NOT: return tacJoin(code[0], tacCreate(TAC_NOT, makeTemp(), code[0]?code[0]->res:0,0));
            case AST_EQ: return makeBinOp(TAC_EQ, code[0], code[1]); break;
            case AST_DIF: return makeBinOp(TAC_DIF, code[0], code[1]); break;
            case AST_IF: return makeIfThen(TAC_IFZ, code[0], code[1]);  break;
            case AST_WHILE: return makeWhile(code[0], code[1]); break;
            case AST_IFELSE: return makeIfThenElse(code[0], code[1], code[2]);
            case AST_ARRAYASS: return TAC_make_assign(code[0],code[1], ast);break;
            case AST_VECREAD: return TAC_make_ary_index(ast, code[0]);break;
            case AST_RETURN: return TAC_make_return(code[0]);
            case AST_READ: return  tacCreate(TAC_READ, ast->symbol, NULL, NULL);
            //case AST_FOR: return makeFor(ast->symbol, code[0], code[1], code[3]);
            //case AST_DEFVEC: return
            case AST_PRINT: return code[0];break;
            case AST_PRINTARRAY: if(code[1]==NULL){ return TAC_make_print(code[0]); } else { return tacJoin(TAC_make_print(code[0]), code[1]); } break;
            case AST_SEQLITI: return code[0];break;
            case AST_SEQLIT: if(code[1]==NULL){ return code[0]; } else { return tacJoin(code[0], code[1]); } break;
            case AST_FUNDEC: return TAC_make_func_declaration(ast, code[1], code[2]);break;
            case AST_FUNC: return TAC_make_func_call(ast, code[0],call_count);break;
            case AST_FUNDPARMSI: if(code[1]==NULL){ return code[0]; } else { return tacJoin(code[0], code[1]); } break;
            case AST_FUNDPARMS: if(code[1]==NULL){ return code[0]; } else { return tacJoin(code[0], code[1]); } break;
            case AST_PARAMETER: return tacCreate(TAC_SYMBOL, ast->symbol, 0, 0); break;
            case AST_FUNCPARF: return tacJoin(code[1], TAC_make_push_arg(code[0],FUNC, call_count)); break;
            case AST_ARG: return TAC_make_push_arg(code[0], FUNC, call_count);break;
            //TODO: finish the operations*/
            default: return tacJoin(tacJoin(tacJoin(code[0], code[1]), code[2]), code[3]); break;
        }
        return 0;
}

TAC* makeBinOp(int type, TAC* code0, TAC* code1) {
    TAC *list = 0;
    TAC *novatac = 0;
    novatac = tacCreate(type, makeTemp(), code0?code0->res:0, code1?code1->res:0);
    list = tacJoin(code0, code1);
    novatac->prev = list;
    return novatac;
}

TAC *TAC_make_return(TAC *expression) {
    TAC *return_tac = tacCreate(TAC_RET, expression->res, NULL, NULL);
    return tacJoin(expression, return_tac);
}


TAC *TAC_make_func_declaration(AST *node, TAC *func_params, TAC *func_body) {
    TAC *begin_func_tac = tacCreate(TAC_BEGIN_FUNC, node->symbol, NULL, NULL);
    TAC *end_func_tac = tacCreate(TAC_END_FUNC, node->symbol, NULL, NULL);

    return tacJoin(tacJoin(tacJoin(begin_func_tac, func_params), func_body), end_func_tac);
}

TAC* TAC_make_print(TAC *expression) {
    TAC *print_tac = tacCreate(TAC_PRINT, expression->res, NULL, NULL);
    return tacJoin(expression, print_tac);
}

TAC* TAC_make_assign(TAC *expression2 , TAC *expression,AST *node) {
    TAC *symbol = tacCreate(TAC_SYMBOL, node->symbol , 0, 0);
    TAC *assign_tac = tacCreate(TAC_ASSIGN, node->symbol,expression2->res, expression->res);
    return tacJoin(tacJoin(tacJoin(symbol, expression2), expression), assign_tac);
}
/*
TAC *TAC_make_ary_assign(TAC *identifier, TAC *index, TAC *expression) {
    TAC *ary_assign_tac = tacCreate(TAC_ARRAY_ASSIGN, identifier->res,
                                     index->res, expression->res);
    return tacJoin(tacJoin(tacJoin(identifier, index), expression), ary_assign_tac);
}

*/
TAC *TAC_make_ary_index(AST *id, TAC *index) {
    TAC *temp_tac = tacCreate(TAC_INDEX_TEMP, makeTemp(), NULL, NULL);
    TAC *identifier = tacCreate(TAC_SYMBOL, id->symbol , 0, 0);
    TAC *ary_index_tac = tacCreate(TAC_ARRAY_INDEX, temp_tac->res,
                                    id->symbol, index->res);
    return tacJoin(tacJoin(tacJoin(temp_tac, identifier), index), ary_index_tac);
}
TAC* makeIfThen(int type, TAC* code0, TAC* code1){
    HASH_NODE *label = 0;
    TAC* tacif = 0;
    TAC* taclabel = 0;

    label = makeLabel();
    tacif = tacCreate(TAC_IFZ, label, code0?code0->res:0,0);
    taclabel = tacCreate(TAC_LABEL, label, 0, 0);

    return tacJoin(tacJoin(tacJoin(code0, tacif), code1), taclabel);
}

TAC* makeIfThenElse(TAC *condition, TAC *if_true, TAC *if_false) {
    HASH_NODE *elseLabel = makeLabel();
    HASH_NODE *endLabel = makeLabel();
    TAC *jz_tac = tacCreate(TAC_IFZ, elseLabel, condition?condition->res:0, 0);
    TAC *else_tac = tacCreate(TAC_LABEL, elseLabel, 0, 0);
    TAC *jmp_tac = tacCreate(TAC_JUMP, endLabel, 0, 0);
    TAC *end_tac = tacCreate(TAC_LABEL, endLabel, 0, 0);

    return tacJoin(condition, tacJoin(jz_tac, tacJoin(if_true, tacJoin(jmp_tac, tacJoin(else_tac, tacJoin(if_false, end_tac))))));
}

TAC* makeWhile(TAC *condition, TAC *body) {
    HASH_NODE *startNode = makeLabel();
    HASH_NODE *endNode = makeLabel();
    TAC *beginLabel = tacCreate(TAC_LABEL, startNode, 0, 0);
    TAC *endLabel = tacCreate(TAC_LABEL, endNode, 0, 0);
    TAC *goto_end_if_zero = tacCreate(TAC_IFZ, endNode, condition?condition->res:0,0);
    TAC *goto_begin = tacCreate(TAC_JUMP, startNode, 0, 0);
    return tacJoin(beginLabel, tacJoin(condition, tacJoin(goto_end_if_zero, tacJoin(body, tacJoin(goto_begin, endLabel)))));
}

TAC* makeFor(HASH_NODE* symbol, TAC* code0, TAC* code1, TAC* code2, TAC* code3){
    HASH_NODE* startLabel = makeLabel();
    HASH_NODE* endLabel = makeLabel();
    TAC* tacBegin = tacCreate(TAC_LABEL, startLabel, 0, 0);
    TAC* tacEnd = tacCreate(TAC_LABEL, endLabel, 0, 0);

    TAC* goto_end_if_zero = tacCreate(TAC_IFZ, endLabel, symbol, 0);
    TAC* goto_begin = tacCreate(TAC_JUMP, startLabel, 0, 0);

    TAC* moveInitial = tacCreate(TAC_MOVE, symbol, code0?code0->res:0, 0);
    TAC* tacIncrement = tacCreate(TAC_ADD, symbol, code2?code2->res:0, 0);
    TAC* moveIncrement = tacCreate(TAC_MOVE, symbol, tacIncrement?tacIncrement->res:0, 0);
    TAC* tacSymbol = tacCreate(TAC_SYMBOL, symbol, 0, 0);
    TAC* tacCompare = makeBinOp(TAC_DIF, tacSymbol, code1);
    return 0;

    }

TAC *TAC_make_func_call(AST *func_name, TAC *args, int callId) {
    TAC *temp_tac = tacCreate(TAC_TEMP_FUNCTION, makeTemp(), NULL, NULL);
    TAC *func_call = tacCreate(TAC_CALL, temp_tac->res, func_name->symbol, NULL);
    func_call->callId = callId;
    fprintf(stderr, "%i",callId);
    return tacJoin(tacJoin(temp_tac, args), func_call);
}
TAC *TAC_make_push_arg(TAC *arg, AST *func_name, int callId) {
    TAC *push_arg = tacCreate(TAC_PUSH_ARG, arg->res, func_name->symbol, NULL);
    push_arg->callId = callId;
     fprintf(stderr, " ARG:%i /n",callId);
    return tacJoin(arg, push_arg);
}





