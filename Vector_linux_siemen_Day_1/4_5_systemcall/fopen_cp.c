#include<stdio.h>
int main(int argc,char *argv[])
{
  FILE *fp1,*fp2;
  char ch;
  printf("argc:%d\n",argc);
  fp1 = fopen(argv[1],"r");
  if(fp1==NULL)
  {
    printf("File not exist\n");
    exit(1);
  }
  fp2= fopen(argv[2],"w");
  while(1)
  {
    ch = fgetc(fp1);
    if(ch==EOF)
    break;
    fputc(ch,fp2);
  }
  fclose(fp1);
  fclose(fp2);
}  
