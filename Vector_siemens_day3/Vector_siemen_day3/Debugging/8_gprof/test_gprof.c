//test_gprof.c
#include<stdio.h>

void func1(void);
void func2(void);
void func1(void)
{
    printf("\n Inside func1 \n");
    int i = 0;
}
void func2(void)
{
    printf("\n Inside func2 \n");
    int i = 0;

    for(;i<0xffffffaa;i++);
	    new_func1();
}
int main(void)
{
    printf("\n Inside main()\n");
    int i = 0;

    for(;i<0xffffff;i++);
    func1();
    func2();

    return 0;
}

