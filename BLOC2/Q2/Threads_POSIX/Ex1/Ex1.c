#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void threadFunc(int *param);

int main()
{
	pthread_t threadsHandles[4];
	int **threads_args;
	int i;

	threads_args = (int**)malloc(sizeof(int*)*(sizeof(threadsHandles)/sizeof(pthread_t)));
	if (threads_args == NULL) {
		perror(strerror(errno));
	}
	/* Initialisation des arguements alloué dynamiquement */
	for (i = 0; i < sizeof(threadsHandles)/sizeof(pthread_t);i++) {
		threads_args[i] = (int*)malloc(sizeof(int));
		*(threads_args[i]) = i;
	}
	/* Creation des differents threads */
	for(i = 0; i < sizeof(threadsHandles)/sizeof(pthread_t); i++) {
		if (pthread_create(&(threadsHandles[i]), NULL,(void*)&threadFunc , threads_args[i]) != 0)
			perror(strerror(errno));
	}

	/* Attente de la terminaison des threads */
	for (i = 0; i < sizeof(threadsHandles)/sizeof(pthread_t); i++) {
		pthread_join(threadsHandles[i], NULL);
	}
	free(threads_args);
	exit(0);	


}

void threadFunc(int *param)
{
	int thread_num = *param;

	struct timespec temps;
	temps.tv_sec = 1;
	temps.tv_nsec = 700000000;
	printf("Thread %d, id %u : démarrage\n", (*param) + 1, (unsigned int)pthread_self());
	nanosleep(&temps, NULL);
	free(param);
	printf("Thread %d, id %u : Terminaison\n", thread_num + 1, (unsigned int)pthread_self());
	pthread_exit(0);

}
