#include<stdio.h>
int main()
{
  int a[5]={134,1,23,5,45},n=5,i,first,second;
  first=second=-1;
  int *p=NULL;
  *p=20;
  for(i=0;i<5;i++)
  {
     if(a[i]>first)
     {
     second=first;
     first=a[i];
     }
     else if(a[i]>second && a[i]!=first)
        second=a[i];

  }
  printf("first:%d seond:%d\n",first,second);
 }
