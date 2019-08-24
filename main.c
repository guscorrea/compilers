#include <stdio.h>
#include "hash/hash.h"
extern int yylex();
extern int lc;
extern int running;

int main(void)
{ 
  hashInit();
  int tok;
  while(running){
  tok=yylex();
  if(!running){
    break;
  }
  fprintf(stderr,"Found keyword %i\n",tok);
  }
  printf("The line number is: %d\n",lc);
  return 0;
}
int isRunning(void){
  return !running;
}
int getLineNumber(void){
  return lc+1;
}
