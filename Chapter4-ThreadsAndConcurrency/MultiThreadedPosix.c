#include<pthread.h>
#include<stdio.h>

#include<stdlib.h>

#define NUM_THREADS 10
int sum; // this data is shared by the threads 
void *runner(void *param); /* thread call this functions */



int main(int argc, char *argv[])
{
	pthread_t tid; /* the thread identifier */
	pthread_t workers[NUM_THREADS];
	pthread_attr_t attr; /* set of thread attributes */

	/* set the default attributes of the thread */
	pthread_attr_init(&attr);
	/* create the thread */
	pthread_create(&tid, &attr, runner, argv[1]);
	/* wait for the thread to exit */
	//pthread_join(tid, NULL);
	for(int i = 0; i < NUM_THREADS; i++)
		pthread_join(workers[i], NULL);
	printf("sum = %d\n", sum);
}

/* The thread will execute in this function */
void *runner(void *param)
{
	int i, upper = atoi(param);
	sum = 0;

	for(i = 1; i <= upper; i++)
		sum+=i;
	pthread_exit(0);
}
