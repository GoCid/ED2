#include <stdio.h>
#include<stdlib.h>

void main(void)
{ char x='a',y;
  int  *c=NULL;
  void *apr=NULL;
  
  apr=&x;
  y=*((char *)apr) ;
  y=y+1;
  printf("El caracter fue %c \n",y);
  c=malloc(sizeof(int));
  *c=5;
  (*c)++;
  apr=c;
  printf("El nuevo valor de c es %d \n",*((int *)apr));
  system("pause");
}
