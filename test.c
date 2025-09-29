#include<stdio.h>

struct def
{
   int b;
};
struct abc
{
   int x;
   struct def *d;
};
struct abc ab;
struct abc *p=&ab;

int main()
{
    printf("sizeof:%d %x %x\n",sizeof(*ab.d), p->x,(*p).x);
}
