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

void astreePrint(AST *node, int level) {
    int i;
    if (!node) return;
    for (int i = 0; i < level; ++i) {
        fprintf(stderr, " ");
    }
    
    switch (node->type) {
        case AST_SYMBOL: fprintf(stderr, "%s",node->symbol->text); break;
        case AST_ADD: astreePrint(node->son[0], level +1);fprintf(stderr, " + ");astreePrint(node->son[1], level +1); break;
        case AST_MUL: astreePrint(node->son[0], level +1);fprintf(stderr, " * ");astreePrint(node->son[1], level +1); break;
        case AST_NOT: fprintf(stderr, " ~ ");astreePrint(node->son[0], level +1);break;
        case AST_DIF: astreePrint(node->son[0], level +1); fprintf(stderr, " != ");astreePrint(node->son[1], level +1);break;
        case AST_EQ: astreePrint(node->son[0], level +1); fprintf(stderr, " == ");astreePrint(node->son[1], level +1);break;
        case AST_GE: astreePrint(node->son[0], level +1); fprintf(stderr, " >= ");astreePrint(node->son[1], level +1);break;
        case AST_LE: astreePrint(node->son[0], level +1); fprintf(stderr, " <= ");astreePrint(node->son[1], level +1);break;
        case AST_OR:astreePrint(node->son[0], level +1); fprintf(stderr, " v ");astreePrint(node->son[1], level +1);break;
        case AST_AND:astreePrint(node->son[0], level +1); fprintf(stderr, " . ");astreePrint(node->son[1], level +1);break;
        case AST_GENE:astreePrint(node->son[0], level +1); fprintf(stderr, " > ");astreePrint(node->son[1], level +1);break;
        case AST_LENE:astreePrint(node->son[0], level +1); fprintf(stderr, " < ");astreePrint(node->son[1], level +1);break;
        case AST_MIN:astreePrint(node->son[0], level +1); fprintf(stderr, " - ");astreePrint(node->son[1], level +1);break;
        case AST_DIV: astreePrint(node->son[0], level +1); fprintf(stderr, " / ");astreePrint(node->son[1], level +1);break;
        case AST_FUNC:fprintf(stderr, " %s ",node->symbol->text);fprintf(stderr, "(");astreePrint(node->son[0], level +1) ;fprintf(stderr, ")");   break;
        case AST_CMDINIT: astreePrint(node->son[0], level +1);astreePrint(node->son[1], level +1);break;
        case AST_CMDLIST: fprintf(stderr, ";");astreePrint(node->son[0], level +1);astreePrint(node->son[1], level +1);break;
        case AST_BODY: fprintf(stderr, "{");astreePrint(node->son[0], level +1);fprintf(stderr, "}");break;
        case AST_DEFVEC: astreePrint(node->son[0], level +1);fprintf(stderr, " %s ",node->symbol->text);fprintf(stderr, "["); astreePrint(node->son[1], level +1);fprintf(stderr, "]");astreePrint(node->son[2], level +1);fprintf(stderr, ";");break;
        case AST_SEQLITI: fprintf(stderr, ":");astreePrint(node->son[0], level +1);break;
        case AST_DEC: astreePrint(node->son[0], level +1);astreePrint(node->son[1], level +1); break;
        case AST_SEQLIT: astreePrint(node->son[0], level +1);astreePrint(node->son[1], level +1); break;
        case AST_DEF: astreePrint(node->son[0], level +1);fprintf(stderr, " %s ",node->symbol->text);fprintf(stderr, "="); astreePrint(node->son[1], level +1);fprintf(stderr, ";");break;
        case AST_FUNDEC: astreePrint(node->son[0], level +1);fprintf(stderr, " %s ",node->symbol->text);fprintf(stderr, "("); astreePrint(node->son[1], level +1);fprintf(stderr, ")");
        astreePrint(node->son[2], level +1);break;
        case AST_FUNDPARMSI:astreePrint(node->son[0], level +1);astreePrint(node->son[1], level +1); break;
        case AST_FUNDPARMS:fprintf(stderr, ",");astreePrint(node->son[0], level +1);astreePrint(node->son[1], level +1); break;
        case AST_PARAMETER:astreePrint(node->son[0], level +1);fprintf(stderr, " %s ",node->symbol->text); break;
        case AST_VARASS:fprintf(stderr, " %s ",node->symbol->text);fprintf(stderr, " = ");astreePrint(node->son[0], level +1);break;
        case AST_ARRAYASS:fprintf(stderr, " %s ",node->symbol->text);fprintf(stderr, "[");astreePrint(node->son[0], level +1);fprintf(stderr, "]");fprintf(stderr, " = ");astreePrint(node->son[1], level +1);break;
        case AST_READ: fprintf(stderr, " read ");fprintf(stderr, " %s ",node->symbol->text); break;
        case AST_PRINT:fprintf(stderr, " print ");astreePrint(node->son[0], level +1); break;
        case AST_PRINTARRAY:astreePrint(node->son[0], level +1);astreePrint(node->son[1], level +1); break;
        case AST_RETURN:fprintf(stderr, " return ");astreePrint(node->son[0], level +1);break;
        case AST_FUNCPARF:astreePrint(node->son[0], level +1);fprintf(stderr, " , ");astreePrint(node->son[1], level +1);break;
        case AST_IF:fprintf(stderr, " if ( ");astreePrint(node->son[0], level +1);fprintf(stderr, " ) ");fprintf(stderr, " then ");astreePrint(node->son[1], level +1);break;
        case AST_IFELSE:fprintf(stderr, " if ( ");astreePrint(node->son[0], level +1);fprintf(stderr, " ) ");
        fprintf(stderr, " then ");astreePrint(node->son[1], level +1);
        fprintf(stderr, " else ");astreePrint(node->son[2], level +1);break;
        case AST_FOR:fprintf(stderr, " for ( ");astreePrint(node->son[0], level +1);fprintf(stderr, " : ");astreePrint(node->son[0], level +1);
        fprintf(stderr, " , ");astreePrint(node->son[1], level +1);
        fprintf(stderr, " , ");astreePrint(node->son[2], level +1);
        fprintf(stderr, " )");astreePrint(node->son[3], level +1);break;
        case AST_WHILE:fprintf(stderr, " while ( ");astreePrint(node->son[0], level +1);fprintf(stderr, " ) ");
        astreePrint(node->son[1], level +1);
        break;
        case AST_BREAK:fprintf(stderr, " break ");break;
        case AST_TINT: fprintf(stderr, " int ");break;
        case AST_TBYTE: fprintf(stderr, " byte ");break;
        case AST_TLONG: fprintf(stderr, " long ");break;
        case AST_TFLOAT: fprintf(stderr, " float ");break;
        case AST_TBOOL: fprintf(stderr, " bool ");break;
        case AST_VECREAD:fprintf(stderr, " %s ",node->symbol->text);fprintf(stderr, "[");astreePrint(node->son[0], level +1) ;fprintf(stderr, "]"); break;
        default:break;
    }

   // for (int i = 0; i < MAX_SONS; ++i) {
   //     astreePrint(node->son[i], level +1);
   // }
}

