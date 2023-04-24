#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void threadFunc(void);
void sigHandlerAlrm(int);

pthread_t threadHandler;
unsigned int thread_id = 0;

int main()
{
	struct sigaction sact;
	sigset_t alrm_sigset;

	/* Blocage du signal SIGALRM */
	sigemptyset(&alrm_sigset);
	sigaddset(&alrm_sigset, SIGALRM);
	sigprocmask(SIG_BLOCK, 	&alrm_sigset, NULL);

	/* Creation du handler pour le thread secondaire pour le signal SIGALRM */
	sigemptyset(&sact.sa_mask);
	sact.sa_handler = sigHandlerAlrm;

	if (sigaction(SIGALRM, &sact, NULL) != 0) {
		perror("Unable to set signal for SIGALRM");
		exit(1);
	}
	
	/* Lancement du thread secondaire et initilisation de l'alarme pour l'avant du signal */
	if (pthread_create(&threadHandler, NULL, (void*)&threadFunc, NULL) != 0)
	{
		perror(strerror(errno));
		exit(1);
	}
	alarm(2);
	pthread_join(threadHandler, NULL);
	
	exit(0);

	
	
}

void threadFunc(void)
{
	sigset_t alrm_sigset;
	
	/* Deblocage du signal SIGALRM pour le thread secondaire */
	sigemptyset(&alrm_sigset);
	sigaddset(&alrm_sigset, SIGALRM);
	if (sigprocmask(SIG_UNBLOCK, 	&alrm_sigset, NULL) != 0) {
		perror(strerror(errno));
		pthread_exit((void*)1);
	}
	
	/*Initilisation de la varibale globale contenant l'id du thread */
	thread_id = (unsigned int)pthread_self();

	printf("Thread secondaire, id %u : démarrage\n", (unsigned int)pthread_self());
	pause();
	printf("Thread secondaire, id %u : terminaison\n", (unsigned int)pthread_self());

	pthread_exit((void*)0);

}

void sigHandlerAlrm(int sig)
{
	printf("Thread secondaire, id %u: réception de SIGALRM\n", thread_id);

}
