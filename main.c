#include <stdio.h>
extern int yylex();
extern int lc;
extern int running;

void initMe(void);
int getLineNumber(void);
int isRunning(void);

int main(void)
{
  initMe();
  int tok;
  while(running){
  tok=yylex();
  if(!running){
    break;
  }
  fprintf(stderr,"Found keyword %i\n",tok);
  }
  printf("The line number is: %d\n", getLineNumber());
  return 0;
}
