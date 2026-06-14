
#include<stddef.h>
#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
typedef struct PodTag
{
   char c;
   long long d;
   int i;
} PodType;
 
int main()
{
   printf("offset:%d\n", OFFSETOF(PodType, d));
   printf("int:%d\n",sizeof(int));
   return 0;
}
