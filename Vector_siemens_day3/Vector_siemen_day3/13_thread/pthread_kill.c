#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>


void *threadfn1(void *p)
{
	while(1){
		printf("thread1\n");
		sleep(2);
	}
	return 0;
}

void *threadfn2(void *p)
{
	while(1){
		printf("thread2\n");
		sleep(2);
	}
	return 0;
}

void *threadfn3(void *p)
{
	while(1){
		printf("thread3\n");
		sleep(2);
	}
	return 0;
}


void handler(int signo, siginfo_t *info, void *extra) 
{
	int i;
	for(i=0;i<5;i++)
	{
		puts("signal");
		sleep(2);
	}
}

void set_sig_handler(void)
{
        struct sigaction action;


        action.sa_flags = SA_SIGINFO; 
        action.sa_sigaction = handler;

        if (sigaction(SIGINT, &action, NULL) == -1) { 
            perror("sigusr: sigaction");
            _exit(1);
        }

}

int main()
{
	pthread_t t1,t2,t3;
	set_sig_handler();
	pthread_create(&t1,NULL,threadfn1,NULL);
	pthread_create(&t2,NULL,threadfn2,NULL);
	pthread_create(&t3,NULL,threadfn3,NULL);
	sleep(3);
	pthread_kill(t1,SIGINT);
	sleep(15);
	pthread_kill(t2,SIGINT);
	pthread_kill(t3,SIGINT);
	pthread_exit(NULL);
	return 0;
}
