#include "mystr.h"
extern char str1[30],str2[30];
int mystrcmp()
{
    int i=0,flag=0;

    while(str1[i]!='\0' || str2[i]!='\0')
    {
        if(str1[i]!=str2[i])
        {
            flag=1;
            break;
        }
        i++;
    }
    if(flag==0)
        return 0;
    else
        return 1;
}
    
