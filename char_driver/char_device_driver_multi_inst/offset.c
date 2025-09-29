#include <stdio.h>
  
#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
  
typedef struct PodTag
{
   int     i;
   int     j;
   char    c;
   char    cx;
} PodType;
  
int main()
{
   struct PodTag Podlocal;	
   printf("base addres:%x size:%d\n", &Podlocal.i,sizeof(Podlocal) );
   printf("%d %x",OFFSETOF(PodType, cx), &Podlocal.cx - OFFSETOF(PodType, cx) );
   getchar();
   return 0;
}
