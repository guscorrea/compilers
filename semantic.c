//
// Created by I861082 on 21/10/2019.
//
#include "semantic.h"

int semanticError = 0;

void checkUndeclared(void){
    semanticError += hashCheckUndeclared();
}

int getSemanticErrors(void){
    return semanticError;
}

void checkAndSetTypes(AST*node) {
    int i;
    if (!node) return;

    //take all declaration nodes
    if(node->type == AST_VARASS
            || node->type == AST_FUNDEC)
    {
        if(node->symbol) {
            if(node->symbol->type != SYMBOL_IDENTIFIER) {
                fprintf(stderr, "Semantic ERROR: Symbol %s already declared. \n", node->symbol->text);
                semanticError++;
            }

            //set the correct type (nature)
            if(node->type == AST_VARASS)
                node->symbol->type = SYMBOL_SCALAR;
            if(node->type == AST_FUNDEC)
                node->symbol->type = SYMBOL_FUNCTION;

            //set also the datatype from declaration
            if(node->son[0]->type == AST_TINT)
                node->symbol->datatype = DATATYPE_INT;
            if(node->son[0]->type == AST_TFLOAT )
                node->symbol->datatype = DATATYPE_FLOAT;
        }
    }

    if(node->type == AST_FUNDEC) {
        if(node->symbol->type != SYMBOL_IDENTIFIER) {
            fprintf(stderr, "Semantic ERROR: Symbol %s already declared. \n", node->symbol->text);
        }
        node->symbol->type = SYMBOL_FUNCTION;
        if(node->son[0]->type == AST_TINT)
            node->symbol->datatype = DATATYPE_INT;
        if(node->son[0]->type == AST_TFLOAT )
            node->symbol->datatype = DATATYPE_FLOAT;
    }

    for (int i = 0; i < MAX_SONS; ++i) {
        checkAndSetTypes(node->son[i]);
    }
}

void checkOperands(AST* node){
    switch(node->type) {
        case AST_ADD:
        case AST_DIF:
        case AST_MUL:
        case AST_DIV: // check correctness of the two operands
            for (int i = 0; i < 2; i++) {
                if (node->son[i]->type == AST_ADD ||
                    node->son[i]->type == AST_DIF ||
                    node->son[i]->type == AST_MUL ||
                    node->son[i]->type == AST_DIV ||

                    (node->son[i]->type == AST_SYMBOL &&
                     node->son[i]->symbol->type == SYMBOL_SCALAR &&
                     node->son[i]->symbol->datatype != DATATYPE_BOOL) ||

                    (node->son[i]->type == AST_SYMBOL &&
                     (node->son[i]->symbol->type == SYMBOL_LITINT ||
                      node->son[i]->symbol->type == SYMBOL_LITREAL)));
                else {
                    fprintf(stderr,
                            "Semantic ERROR: Operands not compatible.\n");
                    semanticError++;
                }
            }
            break;
    }

    for(int i = 0; i < MAX_SONS; i++)
        checkOperands(node->son[i]);
}


