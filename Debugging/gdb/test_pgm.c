/* Basic calculator program */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#define ADD_OPER	'a'
#define SUB_OPER	's'
#define MUL_OPER	'm'
#define DIV_OPER	'd'
#define REM_OPER	'r'


void *thrd_func(void *arg);
float add_func(int arg1, int arg2);
float sub_func(int arg1, int arg2);
float mul_func(int arg1, int arg2);
float div_func(int arg1, int arg2);
float rem_func(int arg1, int arg2);

void main()
{
	char oper,msg[30]="Have a great day!!!";
	int elem1,elem2;
	float res;
	pthread_t thrd;	
	char *non_ex=NULL;	

#ifdef USER_INPUT
	printf("\n****************************************************************************");
	printf("\nEnter the two numbers on which the below operations have to be performed");
	printf("\n****************************************************************************\n");
	scanf("%d%d",&elem1,&elem2);
	scanf("%c",&oper);	
	
	printf("\n****************************************************************************");
	printf("\nEnter the alphabet adjacent to the operation u wanna perform");
	printf("\n****************************************************************************\n");
	printf("A---->Addition\n");
	printf("S---->Subtraction\n");
	printf("M---->Multiplication\n");
	printf("D---->Division\n");
	printf("R---->Remainder\n");
	scanf("%c",&oper);	
#else
	elem1 = 11;
	elem2 = 7;
	oper = ADD_OPER;
#endif //USER_INPUT
	

	switch(oper)
	{
		case 'a':
		case 'A':
			printf("\nAddition operation selected---------------->\n");	
			res = add_func(elem1,elem2);	
			break;

		case 's':
		case 'S':
			printf("\nSubtraction operation selected---------------->\n");	
			res = sub_func(elem1,elem2);	
			break;
		
		case 'm':
		case 'M':
			printf("\nMultiplication operation selected---------------->\n");	
			res = mul_func(elem1,elem2);	
			break;
		
		case 'd':
		case 'D':
			printf("\nDivision operation selected---------------->\n");	
			res = div_func(elem1,elem2);	
			break;
		
		case 'r':
		case 'R':
			printf("\nRemainder operation selected---------------->\n");	
			res = rem_func(elem1,elem2);	
			break;

		default:
			printf("\nThe operation requested for is invalid,please check again \n");
			exit(0);
			break;
	}
	
	printf("\n****************************************************************************");
	printf("\nThe result = %f",res);
	printf("\n****************************************************************************\n");
	
	/* Thread creation */
	if (pthread_create(&thrd,NULL,thrd_func,(void *)msg) < 0)
		printf("\nPthread creation failure\n");

	/* Join the thread */
	pthread_join(thrd,NULL);

	sync();	

	while(1);
	
	/* Accessing the non existing pointer */
	printf("\nContent =%d\n",*non_ex);			

}

void *thrd_func(void *arg)
{
	char *s = (char *)arg;
	printf("\n%s\n",s);
}

float add_func(int arg1, int arg2)
{
	int i=0;
	float sum_val=0;
	
	sum_val = arg1+arg2;
	
	while(i<20)
	{
		printf("i=%d\n",i);
		i++;
	}
	
	return sum_val;	
}

float sub_func(int arg1, int arg2)
{
	float sub_val;
	
	sub_val = arg1-arg2;
	return sub_val;
}

float mul_func(int arg1, int arg2)
{
	float mul_val;
	
	mul_val = arg1*arg2;
	return mul_val;
}

float div_func(int arg1, int arg2)
{
	float div_val;
	
	/* Invalid input */
	if (arg2 == 0)
	{
		printf("\nCannot divide by zero\n");
		exit(1);	
	}
	

	div_val = arg1/arg2;
	return div_val;
}

float rem_func(int arg1, int arg2)
{
	float rem_val;
		
	/* Invalid input */
	if (arg2 == 0)
		return arg1; 

	rem_val = arg1%arg2;
	return rem_val;
}

