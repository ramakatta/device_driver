#include<stdio.h>
#include<pthread.h>
int cnt;
pthread_t th;
void *myfunc(void *arg);
int main()
{
  char ch;
  int exitstat;
  void *retptr;
  int x=1;
  pthread_create(&th,NULL,myfunc,(void*)x);
  pthread_join(th,&retptr);
  printf("pointer returned:%d\n",retptr);
#if 0
/*  while(1)
  {
    ch=getchar();
    if(ch=='c')
      printf("%d\n",cnt);
    if(ch=='x')
      exit(2);
    if(ch=='r')
    {
       pthread_join(th,&retptr);
       printf("pointer returned:%d\n",retptr);
    }
  }*/
#endif
}

void *myfunc(void *arg)
{
  int sleeptime=(int)arg;
  printf("Thread:%d\n",sleeptime);
  while(1)
  {
    sleep(sleeptime);
    cnt++;
    if(cnt==10)
      return (void*)25;
  }
}



    
