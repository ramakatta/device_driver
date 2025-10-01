#include<stdio.h>
#include "mystr.h"
#define MAIN
char str1[30],str2[30];
int main()
{
    int len;
    char str3[30];
    printf("Enter 2 strings\n");
    scanf("%s%s",str1,str2);
    len=mystrlen(str1);
    printf("Length of str1:%d\n",len);
    len=mystrlen(str2);
    printf("Length of strng2:%d\n",len);
#if 1
    mystrcpy(str3);
    printf("Copy of str3:%s\n",str3);
    if(mystrcmp()==0)
        printf("Strings are equal\n");
    else
      printf("Strings are not equal\n");
    //mystrrev(str1);
    mystrrev();
    printf("Reverse:%s %s\n",str1,str2);
#endif
    return 0;
}
