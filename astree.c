//
// Created by I861082 on 19/09/2019.
//

#include "astree.h"
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

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

void astreePrint(AST *node, int level, FILE *outputFile) {
    int i;
    if (!node) return;
    for (int i = 0; i < level; ++i) {
        fprintf(outputFile, " ");
    }
    
    switch (node->type) {
        case AST_SYMBOL: fprintf(outputFile, "%s",node->symbol->text); break;
        case AST_ADD: astreePrint(node->son[0], level+1, outputFile);fprintf(outputFile, " + ");astreePrint(node->son[1], level+1, outputFile); break;
        case AST_MUL: astreePrint(node->son[0], level+1, outputFile);fprintf(outputFile, " * ");astreePrint(node->son[1], level+1, outputFile); break;
        case AST_NOT: fprintf(outputFile, " ~ ");astreePrint(node->son[0], level+1, outputFile);break;
        case AST_DIF: astreePrint(node->son[0], level+1, outputFile); fprintf(outputFile, " != ");astreePrint(node->son[1], level+1, outputFile);break;
        case AST_EQ: astreePrint(node->son[0], level+1, outputFile); fprintf(outputFile, " == ");astreePrint(node->son[1], level+1, outputFile);break;
        case AST_GE: astreePrint(node->son[0], level+1, outputFile); fprintf(outputFile, " >= ");astreePrint(node->son[1], level+1, outputFile);break;
        case AST_LE: astreePrint(node->son[0], level+1, outputFile); fprintf(outputFile, " <= ");astreePrint(node->son[1], level+1, outputFile);break;
        case AST_OR:astreePrint(node->son[0], level+1, outputFile); fprintf(outputFile, " v ");astreePrint(node->son[1], level+1, outputFile);break;
        case AST_AND:astreePrint(node->son[0], level+1, outputFile); fprintf(outputFile, " . ");astreePrint(node->son[1], level+1, outputFile);break;
        case AST_GENE:astreePrint(node->son[0], level+1, outputFile); fprintf(outputFile, " > ");astreePrint(node->son[1], level+1, outputFile);break;
        case AST_LENE:astreePrint(node->son[0], level+1, outputFile); fprintf(outputFile, " < ");astreePrint(node->son[1], level+1, outputFile);break;
        case AST_MIN:astreePrint(node->son[0], level+1, outputFile); fprintf(outputFile, " - ");astreePrint(node->son[1], level+1, outputFile);break;
        case AST_DIV: astreePrint(node->son[0], level+1, outputFile); fprintf(outputFile, " / ");astreePrint(node->son[1], level+1, outputFile);break;
        case AST_FUNC:fprintf(outputFile, " %s ",node->symbol->text);fprintf(outputFile, "(");astreePrint(node->son[0], level+1, outputFile) ;fprintf(outputFile, ")");   break;
        case AST_CMDINIT: astreePrint(node->son[0], level+1, outputFile);astreePrint(node->son[1], level+1, outputFile);break;
        case AST_CMDLIST: fprintf(outputFile, ";");astreePrint(node->son[0], level+1, outputFile);astreePrint(node->son[1], level+1, outputFile);break;
        case AST_BODY: fprintf(outputFile, "{");astreePrint(node->son[0], level+1, outputFile);fprintf(outputFile, "}");break;
        case AST_DEFVEC: astreePrint(node->son[0], level+1, outputFile);fprintf(outputFile, " %s ",node->symbol->text);fprintf(outputFile, "["); astreePrint(node->son[1], level+1, outputFile);fprintf(outputFile, "]");astreePrint(node->son[2], level+1, outputFile);fprintf(outputFile, ";");break;
        case AST_SEQLITI: fprintf(outputFile, ":");astreePrint(node->son[0], level+1, outputFile);break;
        case AST_DEC: astreePrint(node->son[0], level+1, outputFile);astreePrint(node->son[1], level+1, outputFile); break;
        case AST_SEQLIT: astreePrint(node->son[0], level+1, outputFile);astreePrint(node->son[1], level+1, outputFile); break;
        case AST_DEF: astreePrint(node->son[0], level+1, outputFile);fprintf(outputFile, " %s ",node->symbol->text);fprintf(outputFile, "="); astreePrint(node->son[1], level+1, outputFile);fprintf(outputFile, ";");break;
        case AST_FUNDEC: astreePrint(node->son[0], level+1, outputFile);fprintf(outputFile, " %s ",node->symbol->text);fprintf(outputFile, "("); astreePrint(node->son[1], level+1, outputFile);fprintf(outputFile, ")");
        astreePrint(node->son[2], level+1, outputFile);break;
        case AST_FUNDPARMSI:astreePrint(node->son[0], level+1, outputFile);astreePrint(node->son[1], level+1, outputFile); break;
        case AST_FUNDPARMS:fprintf(outputFile, ",");astreePrint(node->son[0], level+1, outputFile);astreePrint(node->son[1], level+1, outputFile); break;
        case AST_PARAMETER:astreePrint(node->son[0], level+1, outputFile);fprintf(outputFile, " %s ",node->symbol->text); break;
        case AST_VARASS:fprintf(outputFile, " %s ",node->symbol->text);fprintf(outputFile, " = ");astreePrint(node->son[0], level+1, outputFile);break;
        case AST_ARRAYASS:fprintf(outputFile, " %s ",node->symbol->text);fprintf(outputFile, "[");astreePrint(node->son[0], level+1, outputFile);fprintf(outputFile, "]");fprintf(outputFile, " = ");astreePrint(node->son[1], level+1, outputFile);break;
        case AST_READ: fprintf(outputFile, " read ");fprintf(outputFile, " %s ",node->symbol->text); break;
        case AST_PRINT:fprintf(outputFile, " print ");astreePrint(node->son[0], level+1, outputFile); break;
        case AST_PRINTARRAY:astreePrint(node->son[0], level+1, outputFile);astreePrint(node->son[1], level+1, outputFile); break;
        case AST_RETURN:fprintf(outputFile, " return ");astreePrint(node->son[0], level+1, outputFile);break;
        case AST_FUNCPARF:astreePrint(node->son[0], level+1, outputFile);fprintf(outputFile, " , ");astreePrint(node->son[1], level+1, outputFile);break;
        case AST_IF:fprintf(outputFile, " if ( ");astreePrint(node->son[0], level+1, outputFile);fprintf(outputFile, " ) ");fprintf(outputFile, " then ");astreePrint(node->son[1], level+1, outputFile);break;
        case AST_IFELSE:fprintf(outputFile, " if ( ");astreePrint(node->son[0], level+1, outputFile);fprintf(outputFile, " ) ");
        fprintf(outputFile, " then ");astreePrint(node->son[1], level+1, outputFile);
        fprintf(outputFile, " else ");astreePrint(node->son[2], level+1, outputFile);break;
        case AST_FOR:fprintf(outputFile, " for ( ");astreePrint(node->son[0], level+1, outputFile);fprintf(outputFile, " : ");astreePrint(node->son[0], level+1, outputFile);
        fprintf(outputFile, " , ");astreePrint(node->son[1], level+1, outputFile);
        fprintf(outputFile, " , ");astreePrint(node->son[2], level+1, outputFile);
        fprintf(outputFile, " )");astreePrint(node->son[3], level+1, outputFile);break;
        case AST_WHILE:fprintf(outputFile, " while ( ");astreePrint(node->son[0], level+1, outputFile);fprintf(outputFile, " ) ");
        astreePrint(node->son[1], level+1, outputFile);
        break;
        case AST_BREAK:fprintf(outputFile, " break ");break;
        case AST_TINT: fprintf(outputFile, " int ");break;
        case AST_TBYTE: fprintf(outputFile, " byte ");break;
        case AST_TLONG: fprintf(outputFile, " long ");break;
        case AST_TFLOAT: fprintf(outputFile, " float ");break;
        case AST_TBOOL: fprintf(outputFile, " bool ");break;
        case AST_VECREAD:fprintf(outputFile, " %s ",node->symbol->text);fprintf(outputFile, "[");astreePrint(node->son[0], level+1, outputFile) ;fprintf(outputFile, "]"); break;
        default:break;
    }

   // for (int i = 0; i < MAX_SONS; ++i) {
   //     astreePrint(node->son[i], level+1, outputFile);
   // }
}

