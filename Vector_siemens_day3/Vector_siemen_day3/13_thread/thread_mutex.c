#include<stdio.h>
#include<pthread.h>
int cnt;
pthread_t th;
pthread_t th2;
void *myfunc(void *arg);
void *myfunc2(void *arg);
pthread_mutex_t mlock;
int main()
{
  char ch;
  int exitstat;
  void *retptr;
  pthread_create(&th,NULL,myfunc,(void*)1);
  pthread_create(&th2,NULL,myfunc2,(void*)1);
  pthread_join(th,&retptr);
  pthread_join(th2,&retptr);
}

void *myfunc(void *arg)
{
  pthread_mutex_lock(&mlock);
  cnt++;
  printf("Thread1:%d\n",cnt);
  cnt = cnt *2;
  pthread_mutex_unlock(&mlock);
}
void *myfunc2(void *arg)
{
  pthread_mutex_lock(&mlock);
  cnt--;
  printf("Thread2:%d\n",cnt);
  cnt = cnt *4;
  pthread_mutex_unlock(&mlock);
}


    
