#include "mystr.h"
extern char str1[30],str2[30];
void mystrcpy(char *str3)
{
#if 1
    int i=0;
    while(str1[i]!='\0')
    {
     *str3=str1[i++];
     str3++;
    }
    *str3='\0';
#endif
}
    
