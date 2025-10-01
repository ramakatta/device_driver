#include <pthread.h>
#include <stdio.h>

void *work(void *parg)
{
  int *val=(int*)parg;
  printf("worker tid=%d\n", *val);
  *val=100;
  //return (void*)25;
}

int main (){
pthread_t handle;
int data = 0;
void *retptr;

  pthread_create(&handle, NULL, work, &data);    
  //pthread_join(handle, (void**) &retptr);
//  printf("final = %d retptr = %d\n", data, retptr);

  return 0;
}


