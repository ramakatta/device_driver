#include<stdio.h>
#include<fcntl.h>
#include<pthread.h>
#include<semaphore.h>

#define MAX_MSG_LEN 256

sem_t sem1;
char message1[MAX_MSG_LEN];
char message2[MAX_MSG_LEN];
sem_t sem2;

void *thrdfun1(void *arg);
void togglecase(char *buf);

int main()
{
 pthread_t thrd1;
 char msg1[]="Thread1";
 int res,num;

 res=sem_init(&sem1,0,0);
 res=sem_init(&sem2,0,0);
 res=pthread_create(&thrd1,NULL,thrdfun1,msg1);
 while(1)
 {
  printf("Enter message to convert case\n");
  fgets(message1,MAX_MSG_LEN,stdin);
  sem_post(&sem1);
 
  sem_wait(&sem2);
  printf("Resp message:%s",message2);
 }
}

void *thrdfun1(void *arg)
{
  char *buf=(char*)arg;
  printf("I am in %s\n",buf);
  while(1)
  {
    sem_wait(&sem1);
    togglecase(message1);
    sem_post(&sem2);
  }
}

void togglecase(char *buf)
{
  char *temp=buf;
  while(*buf!='\n')
  {
    if((*buf >= 65) &&(*buf <= 91))
     *buf=*buf+32;
    else
    if((*buf >= 97) &&(*buf <= 122))
      *buf=*buf-32;
    buf++;
  }
  strcpy(message2,temp);
}
    

