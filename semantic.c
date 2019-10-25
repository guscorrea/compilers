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


/*
*
*
*
* FUNCÕES DO SOR
*
*
*
*/

void checkAndSetTypes(AST*node) {
    int i;
    if (!node) return;

    //take all declaration nodes
    if(node->type == AST_DEF || node->type == AST_FUNDEC ||node->type == AST_DEFVEC){
        if(node->symbol && node->symbol->type != SYMBOL_IDENTIFIER) {
                fprintf(stderr, "Semantic ERROR: Symbol %s already declared. \n", node->symbol->text);
                semanticError++;
        }

            //set the correct type (nature)
            if(node->type == AST_DEF)
                node->symbol->type = SYMBOL_SCALAR;
            if(node->type == AST_FUNDEC)
                node->symbol->type = SYMBOL_FUNCTION;
            if(node->type == AST_DEFVEC)
                node->symbol->type = SYMBOL_VECTOR;

            //set also the datatype from declaration
            if(node->son[0]->type == AST_TINT)
                node->symbol->datatype = DATATYPE_INT;
            if(node->son[0]->type == AST_TFLOAT )
                node->symbol->datatype = DATATYPE_FLOAT;
            if(node->son[0]->type==AST_TLONG)
                node->symbol->datatype = DATATYPE_LONG;
            if(node->son[0]->type==AST_TBOOL)
                node->symbol->datatype = DATATYPE_BOOL;
            if(node->son[0]->type==AST_TBYTE)
                node->symbol->datatype = DATATYPE_BYTE;
        }

    for (int i = 0; i < MAX_SONS; ++i) {
        checkAndSetTypes(node->son[i]);
    }
}

void checkOperands(AST* node){
        if(!node)
            return;
    switch(node->type) {
        case AST_SYMBOL:
            if((node->symbol->type == SYMBOL_FUNCTION|| node->symbol->type == SYMBOL_VECTOR)){
                error();
            } break;
        case AST_VECREAD:
            if(node->symbol->type != SYMBOL_VECTOR){
                error();
            }
            if(isBoolean(node->son[0])){//indice é boleano erro
                error();
            }
            break;
        case AST_VARASS:
            if((node->symbol->type == SYMBOL_FUNCTION|| node->symbol->type == SYMBOL_VECTOR)){
                error();
            }
            if (isARITMETHICS(node->son[0])){//checa se da o tipo correto no caso aritimetico
                if(node->symbol->datatype==DATATYPE_BOOL){
                    error();
                }
            }
            if (isBoolean(node->son[0])){//checa se da o tipo correto no caso booleano
                if(node->symbol->datatype==DATATYPE_INT||
                   node->symbol->datatype==DATATYPE_FLOAT||
                   node->symbol->datatype==DATATYPE_LONG||
                   node->symbol->datatype==DATATYPE_BYTE){
                       fprintf(stderr,
                            "Semantic ERROR: Operands not compatible.\n");
                    error();
                }
            }
            break;
        case AST_ARRAYASS:
            if((node->symbol->type == SYMBOL_FUNCTION|| node->symbol->type == SYMBOL_VECTOR)){
                error();
            }
            if(isBoolean(node->son[0])){//indice é boleano erro
                error();
            }
            if (isARITMETHICS(node->son[1])){//checa se da o tipo correto no caso aritimetico
                if(node->symbol->datatype==DATATYPE_BOOL){
                    
                    error();
                }
            }
            if (isBoolean(node->son[1])){//checa se da o tipo correto no caso booleano
                if(node->symbol->datatype==DATATYPE_INT||
                   node->symbol->datatype==DATATYPE_FLOAT||
                   node->symbol->datatype==DATATYPE_LONG||
                   node->symbol->datatype==DATATYPE_BYTE){
                    error();
                }
            }
            break;
        case AST_ADD:
            for(int i=0;i<2;i++){
                if(isBoolean(node->son[i])){
                    error();
                }
            }
            break;
        case AST_MIN:
            for(int i=0;i<2;i++){
                if(isBoolean(node->son[i])){
                    error();
                }
            }
            break;
        case AST_MUL:
            for(int i=0;i<2;i++){
                if(isBoolean(node->son[i])){
                    error();
                }
            }
            break;
        case AST_DIV: // deixei quieto para deixar o exemplo do sor ,depois muda
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
        case AST_LENE://comeca booleanas
            for(int i=0;i<2;i++){
                if(isARITMETHICS(node->son[i])){
                    error();
                }
            }
            break;
        case AST_GENE:
            for(int i=0;i<2;i++){
                if(isARITMETHICS(node->son[i])){
                    error();
                }
            }
            break;
        case AST_AND:
            for(int i=0;i<2;i++){
                if(isARITMETHICS(node->son[i])){
                    error();
                }
            }
            break;
        case AST_OR:
            for(int i=0;i<2;i++){
                if(isARITMETHICS(node->son[i])){
                    error();
                }
            }
            break;
        case AST_LE:
            for(int i=0;i<2;i++){
                if(isARITMETHICS(node->son[i])){
                    error();
                }
            }
            break;
        case AST_GE:
            for(int i=0;i<2;i++){
                if(isARITMETHICS(node->son[i])){
                    error();
                }
            }
            break;
        case AST_EQ:
            for(int i=0;i<2;i++){
                if(isARITMETHICS(node->son[i])){
                    error();
                }
            }
            break;
        case AST_DIF:
            for(int i=0;i<2;i++){
                if(isARITMETHICS(node->son[i])){
                    error();
                }
            }
            break;
        case AST_NOT:
            if(isARITMETHICS(node->son[0])){
                error();
            }
            break;
        case AST_FUNC:
            break;
    }

    for(int i = 0; i < MAX_SONS; i++)
        checkOperands(node->son[i]);
}

/*
 *
 *
 *
 * FUNCÕES DO SOR
 *
 *
 *
 */

int isARITMETHICS(AST* node){
    if (node->type == AST_AND ||
                    node->type == AST_LENE ||
                    node->type == AST_GENE||
                    node->type == AST_OR ||
                    node->type == AST_LE ||
                    node->type == AST_GE ||
                    node->type == AST_EQ ||
                    node->type == AST_DIF ||
                    node->type == AST_NOT ){
                        return 0;
                    }
  if(node->type == AST_ADD || //EXEMPLO É ARITIMETICO
                    node->type == AST_DIF ||
                    node->type == AST_MUL ||
                    node->type == AST_DIV ||

                    (node->type == AST_SYMBOL &&
                     node->symbol->type == SYMBOL_SCALAR||
                     node->symbol->type == SYMBOL_FUNCTION||
                     node->symbol->type == SYMBOL_VECTOR  &&
                     node->symbol->datatype == DATATYPE_FLOAT||
                     node->symbol->datatype == DATATYPE_INT||
                     node->symbol->datatype == DATATYPE_LONG) ||
                    (node->type == AST_SYMBOL &&
                     (node->symbol->type == SYMBOL_LITINT ||
                      node->symbol->type == SYMBOL_LITREAL))){
                          return 1;
                      }
    else{
        return 0;
    }
}
int isBoolean(AST* node){
    if(!node){
        return 0;
    }
    if(node->type == AST_ADD || //EXEMPLO É ARITIMETICO
                    node->type == AST_DIF ||
                    node->type == AST_MUL ||
                    node->type == AST_DIV ){
        return 0;
    }
    if (node->type == AST_AND ||
                    node->type == AST_LENE ||
                    node->type == AST_GENE||
                    node->type == AST_OR ||
                    node->type == AST_LE ||
                    node->type == AST_GE ||
                    node->type == AST_EQ ||
                    node->type == AST_DIF ||
                    node->type == AST_NOT ||
                    (node->type == AST_SYMBOL &&
                    node->symbol->type == SYMBOL_SCALAR||
                     node->symbol->type == SYMBOL_FUNCTION||
                     node->symbol->type == SYMBOL_VECTOR &&
                     node->symbol->datatype == DATATYPE_BOOL) ||

                    (node->type == AST_SYMBOL &&
                     (node->symbol->type == SYMBOL_LITBOOL ))){
                         return 1; 
                     }
    else{
        return 0;
    }
}
void error(){
    fprintf(stderr,
                            "Semantic ERROR: Operands not compatible.\n");
                    semanticError++;
}


