//
// Created by I861082 on 21/10/2019.
//

#ifndef ETAPA1_SEMANTIC_H
#define ETAPA1_SEMANTIC_H

#include "astree.h"

void checkAndSetTypes(AST*node);
void checkUndeclared(void);
int getSemanticErrors(void);
int hashCheckUndeclared(void);
void checkOperands(AST* node);
void SearchReturn(AST* node);
void error();
int isBoolean(AST* node);
int isARITMETHICS(AST* node);
void CheckReturn(AST* node ,int type);

#endif //ETAPA1_SEMANTIC_H
