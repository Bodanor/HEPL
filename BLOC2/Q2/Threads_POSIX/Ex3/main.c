#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>

void sigHandlerSig(int);
void ThreadFunc1(void);
void ThreadFunc2(void);
void ThreadFunc3(void);
int main()
{
	pthread_t threadsHandles[3];
	sigset_t mask;
	struct sigaction sact;
	struct timespec temps;
	int i;

	sigemptyset(&mask);
	sigaddset(&mask, SIGALRM);
	sigaddset(&mask, SIGUSR1);
	sigaddset(&mask, SIGUSR2);
	sigprocmask(SIG_BLOCK, &mask, NULL);

	sigemptyset(&sact.sa_mask);
	sact.sa_handler = sigHandlerSig;
	sact.sa_flags = 0;
	
	temps.tv_sec = 2;
	temps.tv_nsec = 0;

	if (sigaction(SIGALRM, &sact, NULL) != 0) {
		perror("Unable to set signal for SIGALRM");
		exit(1);
	}
	if (sigaction(SIGUSR1, &sact, NULL) != 0) {
		perror("Unable to set signal for SIGALRM");
		exit(1);
	}
	if (sigaction(SIGUSR2, &sact, NULL) != 0) {
		perror("Unable to set signal for SIGALRM");
		exit(1);
	}

	if (pthread_create(&(threadsHandles[0]), NULL, (void*)&ThreadFunc1, NULL) != 0)
		perror(strerror(errno));

	if (pthread_create(&(threadsHandles[1]), NULL, (void*)&ThreadFunc2, NULL) != 0)
		perror(strerror(errno));

	if (pthread_create(&(threadsHandles[2]), NULL, (void*)&ThreadFunc3, NULL) != 0)
		perror(strerror(errno));

	nanosleep(&temps, NULL);
	pthread_kill(threadsHandles[1], SIGUSR1);
	pthread_kill(threadsHandles[2], SIGUSR2);

	for (i = 0; i < 3; i++) {
		pthread_join(threadsHandles[i], NULL);
	}
	exit(0);
}

void ThreadFunc1(void)
{
	sigset_t alrm_sigset;
	
	/* Deblocage du signal SIGALRM pour le thread secondaire */
	sigemptyset(&alrm_sigset);
	sigaddset(&alrm_sigset, SIGALRM);
	if (sigprocmask(SIG_UNBLOCK, 	&alrm_sigset, NULL) != 0) {
		perror(strerror(errno));
		pthread_exit((void*)1);
	}
	
	printf("Thread secondaire, id %u : démarrage\n", (unsigned int)pthread_self());
	alarm(5);
	pause();
	printf("Thread secondaire, id %u : terminaison\n", (unsigned int)pthread_self());
	pthread_exit(0);
}


void ThreadFunc2(void)
{

	sigset_t mask;
	
	/* Deblocage du signal SIGALRM pour le thread secondaire */
	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	if (sigprocmask(SIG_UNBLOCK, 	&mask, NULL) != 0) {
		perror(strerror(errno));
		pthread_exit((void*)1);
	}

	printf("Thread secondaire, id %u : démarrage\n", (unsigned int)pthread_self());
	pause();
	printf("Thread secondaire, id %u : terminaison\n", (unsigned int)pthread_self());
	pthread_exit(0);
}
void ThreadFunc3(void)
{

	sigset_t mask;
	
	/* Deblocage du signal SIGALRM pour le thread secondaire */
	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR2);
	if (sigprocmask(SIG_UNBLOCK, 	&mask, NULL) != 0) {
		perror(strerror(errno));
		pthread_exit((void*)1);
	}
	printf("Thread secondaire, id %u : démarrage\n", (unsigned int)pthread_self());
	pause();
	printf("Thread secondaire, id %u : terminaison\n", (unsigned int)pthread_self());
	pthread_exit(0);
}

void sigHandlerSig(int sig)
{
	printf("Thread secondaire, id %u: réception du signal %s\n", (unsigned int)pthread_self(), strsignal(sig));

}

