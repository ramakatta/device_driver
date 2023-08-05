#include<stdio.h>
int global_uninit;
int global_init = 10;
static int st_global_uninit;
static int st_global_init = 10;
extern int ext_uinit;
extern int ext_init=99;
int func()
{
    printf("Hellow world\n");
}
static int func2()
{
    printf("Hellow world\n");
}
static inline int func3()
{
    printf("Hellow world static inline\n");
}
int main()
{
    int x,y,z=20;
    char *name = "rama";
    printf("Iocal addresses:%x %x %x\n",&x,&y,&z);
    printf("Global addresses:%x %x %x\n",&global_uninit,&global_init,&st_global_uninit);
    printf("func address%u\n",func);
    printf("%d ",get_count());
    printf("%d ",get_count());
    printf("%d ",get_count());
    printf("%d ",get_count());
    func3();
}
int get_count()
{
    static int k = 20;
    //char *p = NULL;
    k++;
    //*p =20;
    return k;
}
