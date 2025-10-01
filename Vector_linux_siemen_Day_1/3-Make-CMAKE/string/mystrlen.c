#include "mystr.h"
extern char str1[30],str2[30];
int mystrlen(char *str)
{
    int i=0;
    while(*str!='\0')
    {
        i++;
        str++;
    }
    return i;
  } 
