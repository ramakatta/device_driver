#include<stdio.h>
int main()
{
    int x=5;
    int *p;
    const char *name="rama";
    printf("\nX address:0x%x",&x);
    printf("\nname address:0x%x",&name);
    p=malloc(sizeof(int)*4);
    if(p!=NULL)
     printf("\np address:0x%x\n",p);
    return 0;
}
