#include "mystr.h"
#include<string.h>
void mystrrev(char *str1)
{
  int i,len,j;
  char temp;
 /*   char *p,*q,temp;
    p = str;
    q = p+strlen(str)-1;
    for(;p<q;p++,q--)
    {
      temp = *p;
      *p   = *q;
      *q   = temp;
    } */
    len = strlen(str1);
    for(i=0,j= len-1;i< len/2;i++,j--)
    {
        temp = str1[i];
        str1[i] = str1[j];
        str1[j] = temp;
    }

}


