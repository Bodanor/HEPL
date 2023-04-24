/* ************************************************************

    TEST ELEMENTAIRE

    POUR LA COMMANDE DU PETRA.


    IN.PR.E.S.
    LABORATOIRE D'INFORMATIQUE INDUSTRIELLE.

    POSIX - DIGITAL UNIX POSIX 1003.1 ET 1003.1b

   ************************************************************ */

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#define NOMBRE_PIECE 2

struct ACTUATEURS
{
    unsigned CP : 2; // Carrier Position
    unsigned C1 : 1; // Conveyor 1
    unsigned C2 : 1;
    unsigned PV : 1; // Plunger Vacuum
    unsigned PA : 1; // Plunger Activate
    unsigned AA : 1; // Arm Activate
    unsigned GA : 1; // Grapple Activate
};
union
{
    struct ACTUATEURS act;
    unsigned char byte;
} u_act;

struct CAPTEURS
{
    unsigned L1 : 1; // Length 1
    unsigned L2 : 1; // Length 2
    unsigned T : 1;  /* cabl*/
    unsigned S : 1;  // Slot
    unsigned CS : 1; // Carrier Stable
    unsigned AP : 1; // Arm Position
    unsigned PP : 1; // Plunger Position
    unsigned DE : 1; // Dispenser Empty
};

union
{
    struct CAPTEURS capt;
    unsigned char byte;
} u_capt;

int fd_petra_in, fd_petra_out;
int slotTab[NOMBRE_PIECE];
pthread_t thread_seek_piece;
pthread_t thread_detect_slot;
pthread_t thread_bras;
pthread_t thread_convoyeur2;
pthread_t thread_bac_piece;

void *FonctionSeekPiece(void *);
void *FonctionDetectSlot(void *);
void *FonctionBras(void *);
void *FonctionConvoyeur2(void *);
void *FonctionBacPiece(void *);
void HANDLERSIGALARM(int);

unsigned int test_seek = 0;
unsigned int test_slot = 0;
unsigned int test_bras = 0;
unsigned int test_convoyeur2 = 0;
unsigned int test_bacpiece = 0;

pthread_mutex_t mutex_seek;
pthread_mutex_t mutex_slot;
pthread_mutex_t mutex_bras;
pthread_mutex_t mutex_convoyeur2;
pthread_mutex_t mutex_bacpiece;

pthread_cond_t cond_seek;
pthread_cond_t cond_slot;
pthread_cond_t cond_bras;
pthread_cond_t cond_convoyeur2;
pthread_cond_t cond_bacpiece; 


int main()
{

    int cpt, ret;

    unsigned int c;

    u_act.byte = 0x00;
    printf("actuateurs : %x \n\r", u_act.byte);

    u_act.act.PV = 1;
    printf("actuateurs : %x \n\r", u_act.byte);

    fd_petra_out = open("/dev/actuateursPETRA", O_WRONLY);
    if (fd_petra_in == -1)
    {
        perror("MAIN : Erreur ouverture PETRA_OUT");
        // return 1;
    }
    else
        printf("MAIN: PETRA_OUT opened\n");

    fd_petra_in = open("/dev/capteursPETRA", O_RDONLY);
    if (fd_petra_in == -1)
    {
        perror("MAIN : Erreur ouverture PETRA_IN");
        // return 1;
    }
    else
        printf("MAIN: PETRA_IN opened\n");

    /* Lancement des 5 threads principaux */

    pthread_cond_init(&cond_seek, NULL);
    pthread_cond_init(&cond_slot, NULL);
    pthread_cond_init(&cond_bras, NULL);
    pthread_cond_init(&cond_convoyeur2, NULL);
    pthread_cond_init(&cond_bacpiece, NULL);

    ret = pthread_create(&thread_seek_piece, NULL, FonctionSeekPiece, NULL);
    if (ret != 0)
    {
        perror("Erreur de creation du thread de lecture de capteurs !\n");
        return -1;
    }

    ret = pthread_create(&thread_detect_slot, NULL, FonctionDetectSlot, NULL);
    if (ret != 0)
    {
        perror("Erreur de creation du thread de lecture de capteurs !\n");
        return -1;
    }

    ret = pthread_create(&thread_bras, NULL, FonctionBras, NULL);
    if (ret != 0)
    {
        perror("Erreur de creation du thread de lecture de capteurs !\n");
        return -1;
    }

    ret = pthread_create(&thread_convoyeur2, NULL, FonctionConvoyeur2, NULL);
    if (ret != 0)
    {
        perror("Erreur de creation du thread de lecture de capteurs !\n");
        return -1;
    }

    ret = pthread_create(&thread_bac_piece, NULL, FonctionBacPiece, NULL);
    if (ret != 0)
    {
        perror("Erreur de creation du thread de lecture de capteurs !\n");
        return -1;
    }


    /* On ne retournera jamais ici !*/
    
    pthread_join(thread_detect_slot, NULL);
}

void *FonctionSeekPiece(void *p)
{
    int rc;
    int signal_envoyer = 0;
    struct timespec temps;
    
    while (1)
    {
        /* Le plongeur est en position 0 initialement */
        u_act.act.PV = 0;
        u_act.act.CP = 0;
        rc = write(fd_petra_out, &u_act.byte, 1);
        if (rc <= 0)
            perror("Erreur d'ecriture : ");
        /* Temporisation avant que le Petra detecte un mouvement dans le capteur */
        temps.tv_nsec = 500000000;
        temps.tv_sec = 0;
        nanosleep(&temps, NULL);
        /* Tant que le chariot bouge, on attend la fin du mouvement */
        read(fd_petra_in, &u_capt.byte, 1);
        while (u_capt.capt.CS == 1)
            read(fd_petra_in, &u_capt.byte, 1);

        /* Si pièce dispible */
        if (u_capt.capt.DE == 0)
        {
            /* Abaissement du bras*/
            u_act.act.PA = 1;
            rc = write(fd_petra_out, &u_act.byte, 1);
            if (rc <= 0)
            {
                perror("Erreur d'ecriture : ");
            }
            sleep(2); // Attente de l'abaissement du bras

            /* Activation de la pompe */
            u_act.act.PV = 1;
            rc = write(fd_petra_out, &u_act.byte, 1);
            if (rc <= 0)
            {
                perror("Erreur d'ecriture : ");
            }
          
            /* On remonte le bras */
            u_act.act.PA = 0;
            rc = write(fd_petra_out, &u_act.byte, 1);
            if (rc <= 0)
            {
                perror("Erreur d'ecriture : ");
            }

            /* Attent que le bras remonte */
            read(fd_petra_in, &u_capt.byte, 1);
            while (u_capt.capt.PP == 1)
            {
                read(fd_petra_in, &u_capt.byte, 1);
            }

            /* Le bras se deplace au dessus du convoyeur 1 */
            u_act.act.CP = 1;
            rc = write(fd_petra_out, &u_act.byte, 1);
            if (rc <= 0)
            {
                perror("Erreur d'ecriture : ");
            }

            /* Temporisation avant que le Petra detecte un mouvement dans le capteur */
            nanosleep(&temps, NULL);

            /* Tant que en mouvement, on fait rien */
            read(fd_petra_in, &u_capt.byte, 1);
            while (u_capt.capt.CS == 1)
                read(fd_petra_in, &u_capt.byte, 1);

            /* On lache la piece sur le convoyeur 1*/
            u_act.act.PV = 0;
            u_act.act.C1 = 1;
            rc = write(fd_petra_out, &u_act.byte, 1);
            if (rc <= 0)
            {
                perror("Erreur d'ecriture : ");
            }
            /* Signal sur varibable */

            pthread_mutex_lock(&mutex_slot);
            test_slot = 1;
            pthread_mutex_unlock(&mutex_slot);
            pthread_cond_signal(&cond_slot);
        }
    }
}
void *FonctionDetectSlot(void *p)
{
    int i;
    int *pi = &slotTab[0];
    clock_t debut_capt_s, fin_capt_s;
    double temps_piece;
	struct timespec temps;
    pthread_mutex_lock(&mutex_slot);
    while (test_slot == 0)
        pthread_cond_wait(&cond_slot, &mutex_slot);
    pthread_mutex_unlock(&mutex_slot);

    printf("Thread Detect Slot démarre\n");

    while (1)
    {
        for (i = 0; i < NOMBRE_PIECE; i++)
        {
        	
        	read(fd_petra_in, &u_capt.byte, 1);
        	while (u_capt.capt.S == 0)
                read(fd_petra_in, &u_capt.byte, 1);
  
            /* Debut de la clock*/
            debut_capt_s = clock();
            /* Detection de changement d'état */
            read(fd_petra_in, &u_capt.byte, 1);
            while (u_capt.capt.S == 1)
                read(fd_petra_in, &u_capt.byte, 1);
            /* Fin de la clock */
            fin_capt_s = clock();
            /* calcul du temps que la pièce prend pour passer le capteur S */
            temps_piece = ((double)(fin_capt_s - debut_capt_s)) / CLOCKS_PER_SEC;

            /* Pièce sans slot */
            if (temps_piece >= 0.05)
            {
                *(pi + i) = 0;
                printf("Piece sans slot\n");
            	temps.tv_sec = 2;
            	temps.tv_nsec = 200000000;
            	nanosleep(&temps, NULL);    
            }
            /* Piece avec slot donc temps d'attente plus long */
            else
            {
                *(pi + i) = 1;
                printf("Piece avec slot\n");
                temps.tv_sec = 2;
                temps.tv_nsec = 900000000;
                nanosleep(&temps, NULL);
           }

            pthread_mutex_lock(&mutex_bras);
            test_bras = 1;
            pthread_mutex_unlock(&mutex_bras);
            pthread_cond_signal(&cond_bras);

        }
    }
}

void *FonctionBras(void *p)
{
    int rc;
    struct timespec temps;

    while (1)
    {
        printf("Osti que c'est bon\n");
        pthread_mutex_lock(&mutex_bras);
        while (test_bras == 0)
            pthread_cond_wait(&cond_bras, &mutex_bras);
        pthread_mutex_unlock(&mutex_bras);
        printf("TABARNAK DE CALISSE Recu d'un signal sur condition pour bras \n");

			u_act.act.GA = 1;
			rc = write(fd_petra_out, &u_act.byte, 1);
			if (rc <= 0)
			{
				perror("Erreur d'ecriture : ");
			}
			
			pthread_mutex_lock(&mutex_convoyeur2);
            test_convoyeur2 = 1;
            pthread_mutex_unlock(&mutex_convoyeur2);
            pthread_cond_signal(&cond_convoyeur2);

			
			temps.tv_sec = 1;
			temps.tv_nsec = 0;
			nanosleep(&temps, NULL);

			u_act.act.AA = 1;
			rc = write(fd_petra_out, &u_act.byte, 1);
			if (rc <= 0)
			{
				perror("Erreur d'ecriture : ");
			}

			temps.tv_sec = 1;
			temps.tv_nsec = 200000000;
			nanosleep(&temps, NULL);

			/* On lache le verrou du convoyeur 2 */
			u_act.act.GA = 0;

			rc = write(fd_petra_out, &u_act.byte, 1);
			if (rc <= 0)
			{
				perror("Erreur d'ecriture : ");
			}
			

            printf("Checkez moi ca la rafallllllllllllle\n");
			 pthread_mutex_lock(&mutex_bras);
            test_bras = 0;
            pthread_mutex_unlock(&mutex_bras);
            pthread_cond_signal(&cond_bras);
            
            u_act.act.AA = 0;
			rc = write(fd_petra_out, &u_act.byte, 1);
			if (rc <= 0)
			{
				perror("Erreur d'ecriture : ");
			}
    }

}
void *FonctionConvoyeur2(void *p)
{
	int rc;
	
	printf("CHECKEZ MON PICK-UP\n");	
 	pthread_mutex_lock(&mutex_convoyeur2);
    while (test_convoyeur2 == 0)
    	pthread_cond_wait(&cond_bras, &mutex_convoyeur2);
    pthread_mutex_unlock(&mutex_convoyeur2);
	printf("CRISS DE SAINT SIBOUER\n");
	
	u_act.act.C2 = 1;
	rc = write(fd_petra_out, &u_act.byte, 1);
	if (rc <= 0)
	{
		perror("Erreur d'ecriture : ");
	}
	printf("NORMQNLEMENT LE CONVOYEUR 2 SE LANCE\n");
}
void *FonctionBacPiece(void *p)
{
}

void HANDLERSIGALARM(int sig)
{
    printf("Je suis passé dans le handler de sigalrm ;) \n");
}