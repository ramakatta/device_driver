
#include<stddef.h>
#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
typedef struct PodTag
{
   int i;
   double d;
   char c;
} PodType;
 
int main()
{
   printf("offset:%d\n", OFFSETOF(PodType, d));
   return 0;
}
