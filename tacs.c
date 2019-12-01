//
// Created by I861082 on 06/11/2019.
//

#include "tacs.h"
#include <string.h>

int temps[10000]={0};
static int call_count = 0;
TAC* makeBinOp(int type, TAC* code0, TAC* code1);
TAC* makeIfThen(int type, TAC* code0, TAC* code1);
TAC* makeWhile(TAC *condition, TAC *body);
TAC* makeFor(HASH_NODE* symbol, TAC* begin, TAC* condition, TAC* increment, TAC* body);
TAC* makeIfThenElse(TAC *condition, TAC *if_true, TAC *if_false);
int OpCalculation(TAC* tac);
void symbolScalarCase(TAC* tac, FILE* fout);

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
        case TAC_FOR:fprintf(stderr, "TAC_FOR"); break;
        case TAC_BREAK:fprintf(stderr, "TAC_BREAK"); break;
        case TAC_DEFVAR:fprintf(stderr, "TAC_DEFVAR"); break;
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
            case AST_FOR: return makeFor(ast->symbol, code[0], code[2], code[1], code[3]); break;
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
            case AST_BREAK: return tacCreate(TAC_BREAK, 0, 0, 0); break;
            case AST_DEF: return tacCreate(TAC_DEFVAR, ast->symbol, code[1]?code[1]->res:0, 0);break;
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

TAC* makeFor(HASH_NODE* symbol, TAC* begin, TAC* increment, TAC* condition, TAC* body){
    HASH_NODE* startLabel = makeLabel();
    HASH_NODE* endLabel = makeLabel();
    TAC* tacBegin = tacCreate(TAC_LABEL, startLabel, 0, 0);
    TAC* tacEnd = tacCreate(TAC_LABEL, endLabel, 0, 0);

    TAC *goto_end_if_zero = tacCreate(TAC_IFZ, endLabel, makeTemp(),0);
    TAC* goto_begin = tacCreate(TAC_JUMP, startLabel, 0, 0);

    TAC* moveInitial = tacCreate(TAC_MOVE, symbol, begin?begin->res:0, 0);

    TAC* tacCompare;
    if( atoi(increment->res->text) >= 0 ) {
        tacCompare = tacCreate(TAC_LE, makeTemp(), symbol, condition?condition->res:0);
    } else {
        tacCompare = tacCreate(TAC_GE, makeTemp(), symbol, condition?condition->res:0);
    }

    TAC* tacIncrement = tacCreate(TAC_ADD, makeTemp(), symbol, increment?increment->res:0);
    TAC* moveIncrement = tacCreate(TAC_MOVE, symbol, tacIncrement?tacIncrement->res:0, 0);

    return tacJoin(tacBegin,
                   tacJoin(moveInitial,
                       tacJoin(condition,
                               tacJoin(goto_end_if_zero,
                                       tacJoin(body,
                                               tacJoin(tacIncrement,
                                                   tacJoin(moveIncrement,
                                                       tacJoin(tacCompare,
                                                           tacJoin(goto_begin, tacEnd)))))))));

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

void generateASM(TAC* tac, FILE* fout) {
    int temp1, temp2, tempres;
    static int funclabel = 0;

    if (!tac)return;
    
    if(!(tac->prev)){
        fprintf(fout,".LC0:\n"
	                 ".string\t\"%%i\"\n"
	                 ".text\n");
    }
    if (tac->prev){
        generateASM(tac->prev, fout);
    }

    switch (tac->type) {
        case TAC_MOVE:
            if(tac->op1->type == SYMBOL_LITINT) {
                fprintf(fout, "## TAC_MOVE ##\n"
                              "\tmovl\t$%s, %s(%%rip)\n",
                        tac->op1->text,
                        tac->res->text);
            } else {
                fprintf(fout, "## TAC_MOVE ##\n"
                              "\tmovl\t%s(%%rip), %%eax\n"
                              "\tmovl\t%%eax, %s(%%rip)\n",
                        tac->op1->text,
                        tac->res->text);
            }
            break;
        case TAC_DIV:
        case TAC_SUB:
        case TAC_ADD:
        case TAC_MUL:
        case TAC_DIF:
        case TAC_AND:
        case TAC_EQ:
        case TAC_GE:
        case TAC_LE:
        case TAC_OR:
            OpCalculation(tac);
            break;
        case TAC_NOT:
            tempres = TempInt(tac->res->text);
            if(tac->op1->text[0]=='T' && tac->op1->text[4]==':' ){
                temp1 = temps[TempInt(tac->op1->text)];
            }
            else{
            if(!strcmp(tac->op1->text,"TRUE")){
                temp1=1;
            }
            else if(!strcmp(tac->op1->text,"FALSE")){
                 temp1=0;
            }
            else{
            temp1 = atoi(tac->op1->text);
            }
            temps[tempres]= !temp1;
        }
        break;
        case TAC_PRINT:
        if(tac->res->text[0]=='T'&&tac->res->text[4]==':'){
            fprintf(fout,"## TAC_PRINT ##\n"
                         "movl\t$%d,\t%%esi\n"
	                     "leaq\t.LC0(%%rip),\t%%rdi\n"
                         "movl\t$0,\t%%eax\n"
	                     "call\tprintf@PLT\n",temps[TempInt(tac->res->text)]); break;
        }
         switch(tac->res->type){
       case SYMBOL_LITINT: 
         fprintf(fout,"## TAC_PRINT LIT INT ##\n"
                      "movl\t$%s,\t%%esi\n"
	                  "leaq\t.LC0(%%rip),\t%%rdi\n"
	                  "movl\t$0,\t%%eax\n"
	                  "call\tprintf@PLT\n",tac->res->text); break;
        case SYMBOL_LITBOOL: {
            int boolValue = 0;
            if (strcmp(tac->res->text, "TRUE") == 0)
                boolValue = 1;
            fprintf(fout, "## TAC_PRINT LITBOOL ##\n"
                          "movl\t$%d,\t%%esi\n"
                          "leaq\t.LC0(%%rip),\t%%rdi\n"
                          "movl\t$0,\t%%eax\n"
                          "call\tprintf@PLT\n",
                    boolValue);
        }
            break;
        case SYMBOL_SCALAR:
            symbolScalarCase(tac, fout);
            break;
        }
        break;
        case TAC_LABEL:
            fprintf(fout, "## TAC_LABEL ##\n"
                          ".%s:\n",
                    tac->res->text);
            break;
        case TAC_JUMP:
            fprintf(fout, "## TAC_JUMP ##\n"
                          "\tjmp\t.%s\n",
                    tac->res->text);
            break;
        case TAC_RET:
            fprintf(fout, "## TAC_RETURN ##\n"
                          "\tmovl\t%s(%%rip), %%eax\n", tac->res->text);
            break;
        case TAC_BREAK:
            if (tac->res != 0) {
                fprintf(fout, "## TAC_BREAK ##\n"
                              "\tjmp\t.%s\n", tac->res->text);
            }
            break;
        case TAC_BEGIN_FUNC: fprintf(fout, "\n## TAC_BEGIN_FUNC ##\n"
                                         "\t.globl\t%s\n"
                                         "\t.type\t%s, @function\n"
                                         "%s:\n"
                                         ".LFB%d:\n"
                                         "\tpushq\t%%rbp\n"
                                         "\tmovq\t%%rsp, %%rbp\n", tac->res->text,
                                     tac->res->text,
                                     tac->res->text,
                                     funclabel);
            break;
        case TAC_END_FUNC: fprintf(fout, "## TAC_END_FUNC ##\n"
                                         "\tmovl\t$%d, %%eax\n"
                                       "\tpopq\t%%rbp\n"
                                       "\tret\n"
                                       ".LFE%d:\n"
                                       "\t.size\t%s, .-%s\n", 0, funclabel, tac->res->text,
                                   tac->res->text);
        funclabel++;
            break;
        case TAC_DEFVAR:{
            HASH_NODE* hash = hashFind(tac->res->text);
            switch(hash->datatype){
                case DATATYPE_INT:
                    fprintf(fout, ".globl\t%s\n"
	                              ".align\t8\n"
	                              ".type\t%s,\t@object\n"
	                              ".size\t%s,\t8\n"
                                  "%s:\n"
                                  "\t.quad\t%s\n",
                            tac->res->text,tac->res->text,tac->res->text,tac->res->text,tac->op1->text);
                break;
                case DATATYPE_LONG:
                break;
                case DATATYPE_BOOL:{
                 int value = 0;
                    if(strcmp(tac->op1->text, "TRUE") == 0)
                        value = 1;
                fprintf(fout, ".globl\t%s\n"
	                          ".align\t8\n"
	                          ".type\t%s,\t@object\n"
	                          ".size\t%s,\t8\n"
                              "i:\n"
	                          "\t.quad\t%d\n",
                        tac->res->text,tac->res->text,tac->res->text,value);
                }
                break;
                case DATATYPE_BYTE:
                break;
                case DATATYPE_FLOAT:
                break;
                default:
                break;
            }
        }
        break;
        case TAC_READ: fprintf(fout, "## TAC_READ ##\n"
                                       "\tmovl\t%s(%%rip), %%eax\n"
                                       "\tmovl\t%%eax, %%edi\n"
                                       "\tmovl\t$%d, %%eax\n"
                                       "\tcall\tread@PLT\n"
                                       "\tmovl\t$%d, %%eax\n", tac->res->text, 0, 0); //revisar
        default:
            break;
    }
}

void symbolScalarCase(TAC* tac, FILE* fout) {
    HASH_NODE *var = hashFind(tac->res->text);
    switch (var->datatype) {
        case DATATYPE_INT:
            fprintf(fout, "## TAC_PRINT DATATYPE INT ## ##\n"
                          "\tmovl\t%s(%%rip),\t%%eax\n"
                          "\tmovl\t%%eax,\t%%esi\n"
                          "\tleaq\t.LC0(%%rip),\t%%rdi\n"
                          "\tmovl\t$0,\t%%eax\n"
                          "\tcall\tprintf@PLT\n", tac->res->text);
            break;
        case DATATYPE_BOOL:
            fprintf(fout, "## TAC_PRINT DATATYPE BOOL ## ##\n"
                          "\tmovl\t%s(%%rip),\t%%eax\n"
                          "\tmovl\t%%eax,\t%%esi\n"
                          "\tleaq\t.LC0(%%rip),\t%%rdi\n"
                          "\tmovl\t$0,\t%%eax\n"
                          "\tcall\tprintf@PLT\n", tac->res->text);
            break;
    }
}
int TempInt(char * temp){
   char  token[sizeof(temp)];
   strncpy(token,temp,sizeof(temp));
   char * token2 = strtok(token, " ");
   token2 = strtok(NULL, " ");
   return atoi(token2);
}
int OpCalculation(TAC* tac){
    int temp1;
    int temp2;
    int tempres;
    tempres = TempInt(tac->res->text);
    if(tac->op1->text[0]=='T' && tac->op1->text[4]==':' ){
         printf("passou");
         temp1 = temps[TempInt(tac->op1->text)];
        }
    else{
         if(!strcmp(tac->op1->text,"TRUE")){
            temp1=1;
         }
         else if(!strcmp(tac->op1->text,"FALSE")){
             temp1=0;
         }
         else{
         temp1 = atoi(tac->op1->text);
         }
        }
    if(tac->op2->text[0]=='T' && tac->op2->text[4]==':' ){
        printf("passou");
        temp2 = temps[TempInt(tac->op2->text)];
            }
    else{
        if(!strcmp(tac->op2->text,"TRUE")){
            temp2=1;
         }
         else if(!strcmp(tac->op2->text,"FALSE")){
             temp2=0;
         }
         else{
        temp2 = atoi(tac->op2->text);
         }
        }
    switch(tac->type){
                case TAC_ADD:
                    temps[tempres]= temp1+ temp2; break;
                case TAC_DIF:
                    temps[tempres]= temp1!= temp2; break;
                case TAC_DIV:
                    temps[tempres]= temp1/ temp2; break;
                case TAC_MUL:
                    temps[tempres]= temp1* temp2; break;
                case TAC_AND:
                    temps[tempres]= temp1&& temp2;
                    printf("%d,",temps[tempres]); break;
                case TAC_EQ:
                    temps[tempres]= temp1 == temp2;
                    printf("%d,",temps[tempres]); break;
                case TAC_GE:
                    temps[tempres]= temp1>= temp2; break;
                case TAC_LE:
                    temps[tempres]= temp1<= temp2; break;
                case TAC_OR:
                    temps[tempres]= temp1|| temp2; 
                    printf("%d,",temps[tempres]); break;
                case TAC_SUB:
                    temps[tempres]= temp1- temp2; break;
    }
}

