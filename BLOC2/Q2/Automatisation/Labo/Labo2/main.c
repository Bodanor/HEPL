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
	unsigned T : 1;	 /* cabl*/
	unsigned S : 1;	 // Slot
	unsigned CS : 1; // Carrier Stable
	unsigned AP : 1; // Arm Position
	unsigned PP : 1; // Plunger Position
	unsigned DE : 1; // Dispenser Empty
					 /*                 unsigned H1 : 1;
									  unsigned H2 : 1;
									  unsigned H3 : 1;
									  unsigned H4 : 1;
									  unsigned H5 : 1;
									  unsigned H6 : 1;
									  unsigned    : 2;	*/
};

union
{
	struct CAPTEURS capt;
	unsigned char byte;
} u_capt;

void printSuiviPiece(int);
void *FctMouvement(void *);
void *FctAffichage(void *);
void *FctCapteurs(void *);

int fd_petra_in, fd_petra_out;

main()
{
	pthread_t thread_mvmt;

	int rc, cpt, ret;

	unsigned int c;

	u_act.byte = 0x00;

	u_act.act.PV = 1;
	
	
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

	

	/* Affichage générale */
	printf("\033[2J");
	fflush(stdout);
	printf("Pièce au début du chariot\t[   ]\n");
	printf("Pièce au début du convoyeur 1\t[   ]\n");
	printf("Pièce au milieu du convoyeur 1\t[   ] \n");
	printf("Pièce à la fin du convoyeur 1\t[   ]\n");
	printf("Pièce au début du convoyeur 2\t[   ]\n");
	printf("Pièce au milieu du convoyeur 2\t[   ]\n");
	printf("Pièce à la fin du convoyeur 2\t[   ]\n");
	printf("Pièce dans le bac\t\t[   ]\n");

	fflush(stdout);

	ret = pthread_create(&thread_mvmt, NULL, FctMouvement, NULL);
	if (ret != 0)
	{
		perror("Erreur de creation du thread de lecture de capteurs !\n");
		return -1;
	}


	ret = pthread_join(thread_mvmt, NULL);
	if (ret != 0)
	{
		perror("Erreur de synchronisation de thread !\n");
		return -1;
	}

}

void printSuiviPiece(int suivis)
{
	/* Suppression des précédents états*/

	printf("\033[2;35H");
	printf(" ");
	printf("\033[3;35H");
	printf(" ");
	printf("\033[4;35H");
	printf(" ");
	printf("\033[5;35H");
	printf(" ");
	printf("\033[6;35H");
	printf(" ");
	printf("\033[7;35H");
	printf(" ");
	printf("\033[8;35H");
	printf(" ");
	printf("\033[9;35H");
	printf(" ");

	switch (suivis)
	{
	case 0:
		printf("\033[2;35H");
		printf("X");
		break;
	case 1:
		printf("\033[3;35H");
		printf("X");
		break;
	case 2:
		printf("\033[4;35H");
		printf("X");
		break;
	
	case 3:
		printf("\033[5;35H");
		printf("X");
		break;
	
	case 4:
		printf("\033[6;35H");
		printf("X");
		break;

	case 5:
		printf("\033[7;35H");
		printf("X");
		break;
	
	case 6:
		printf("\033[8;35H");
		printf("X");
		break;
	
	case 7:
		printf("\033[9;35H");
		printf("X");
		break;
	
	default:
		break;
	}
	fflush(stdout);

}

void *FctMouvement(void *p)
{

	int rc, compteur_slot;
	struct CAPTEURS previous_capteurs_struct;
	unsigned char previous_capteurs_byte;
	clock_t previous_clock, end;
	int slot = 0;
	double temps_piece;
	struct timespec temps;


	while (1)
	{
		read(fd_petra_in, &u_capt.byte, 1); // We read the state of all sensors

		compteur_slot = 0;

		previous_capteurs_byte = u_capt.byte;
		/* While the state of the sensors has not changes, we do nothing */
		u_act.act.PV = 0;
		u_act.act.CP = 0;
		rc = write(fd_petra_out, &u_act.byte, 1);
		if (rc <= 0)
		{
			perror("Erreur d'ecriture : ");
		}

		read(fd_petra_in, &u_capt.byte, 1);
		while (u_capt.capt.CS == 1) /* While the arm is not at the right position, we wait */
			read(fd_petra_in, &u_capt.byte, 1);

		
		if (u_capt.capt.DE == 0) /* If they are piece to grab, we enter here*/
		{
			
			printSuiviPiece(0);
			/* We tell the PETRA to activate the plunger in order to grab pieces */
			u_act.act.PA = 1;
			rc = write(fd_petra_out, &u_act.byte, 1); 
			if (rc <= 0)
			{
				perror("Erreur d'ecriture : ");
			}
			sleep(2); /* Waiting two seconds for the plunger to reach the pieces */
			
			/* We tell the PETRA to enable the vaccum to hold the piece when the plunger goes up */
			u_act.act.PV = 1;
			rc = write(fd_petra_out, &u_act.byte, 1);
			if (rc <= 0)
			{
				perror("Erreur d'ecriture : ");
			}

			/* The plunger goes up from here */
			u_act.act.PA = 0;
			rc = write(fd_petra_out, &u_act.byte, 1);
			if (rc <= 0)
			{
				perror("Erreur d'ecriture : ");
			}

			read(fd_petra_in, &u_capt.byte, 1);
			while (u_capt.capt.PP == 1) /* We wait for the plunger to reach the top of the arm */
				read(fd_petra_in, &u_capt.byte, 1);
			
			/* We move the arm that holds the piece to the first position (right above the convoyer 1) */
			u_act.act.CP = 1;
			rc = write(fd_petra_out, &u_act.byte, 1);
			if (rc <= 0)
			{
				perror("Erreur d'ecriture : ");
			}
			sleep(1); /* We wait for the arm to be in position */

			/* While the arm is moving we wait */
			read(fd_petra_in, &u_capt.byte, 1);
			while (u_capt.capt.CS == 1)
				read(fd_petra_in, &u_capt.byte, 1);

			printSuiviPiece(1);
			/* We drop the piece on the first convoyer */
			u_act.act.PV = 0;
			u_act.act.C1 = 1;
			rc = write(fd_petra_out, &u_act.byte, 1);
			if (rc <= 0)
			{
				perror("Erreur d'ecriture : ");
			}

			read(fd_petra_in, &u_capt.byte, 1);
			while (u_capt.capt.S == 0)
				read(fd_petra_in, &u_capt.byte, 1);

			/* Piece au debut du capteur S a partir d'ici*/
			previous_clock = clock();

			read(fd_petra_in, &u_capt.byte, 1);
			while (u_capt.capt.S == 1)
				read(fd_petra_in, &u_capt.byte, 1);

			end = clock();

			temps_piece = ((double)(end - previous_clock)) / CLOCKS_PER_SEC;

			/* Si une piece sans slot*/
			if (temps_piece >= 0.05)
			{
				temps.tv_sec = 0;
				temps.tv_nsec = 800000000;
				slot = 0;
				nanosleep(&temps, NULL);
			}
			/* Piece avec slot donc temps d'attente plus long */
			else
			{
				temps.tv_sec = 2;
				temps.tv_nsec = 0;
				nanosleep(&temps, NULL);
				slot = 1;
			}

			/* Stop du convoyeur 1 et activation du verrou du bras */
			u_act.act.C1 = 0;
			u_act.act.GA = 1;
			rc = write(fd_petra_out, &u_act.byte, 1);
			if (rc <= 0)
			{
				perror("Erreur d'ecriture : ");
			}
			temps.tv_sec = 1;
			temps.tv_nsec = 0;
			nanosleep(&temps, NULL);

			/* Activation du convoyeur 2 et basculement du bras */
			u_act.act.AA = 1;
			u_act.act.C2 = 1;
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

			read(fd_petra_in, &u_capt.byte, 1);
			while (u_capt.capt.L2 == 0)
				read(fd_petra_in, &u_capt.byte, 1);

			read(fd_petra_in, &u_capt.byte, 1);
			while (u_capt.capt.L2 == 1)
				read(fd_petra_in, &u_capt.byte, 1);
			temps.tv_sec = 0;
			temps.tv_nsec = 650000000;
			nanosleep(&temps, NULL);

			/* Stop du convoyeur 2*/
			u_act.act.C2 = 0;
			rc = write(fd_petra_out, &u_act.byte, 1);
			if (rc <= 0)
			{
				perror("Erreur d'ecriture : ");
			}

			/* Si slot alors on active le convoyeur 2 pour que la piece tombe dans le bac puis stop du convoyeur 2 */
			if (slot == 1)
			{
				u_act.act.C2 = 1;
				rc = write(fd_petra_out, &u_act.byte, 1);
				if (rc <= 0)
				{
					perror("Erreur d'ecriture : ");
				}
				temps.tv_sec = 2;
				temps.tv_nsec = 0;
				nanosleep(&temps, NULL);
				u_act.act.C2 = 0;
				rc = write(fd_petra_out, &u_act.byte, 1);
				if (rc <= 0)
				{
					perror("Erreur d'ecriture : ");
				}
			}
			/* Si pas de slot alors mouvement du plongeur en position 1 puis lachement de la piece */
			else
			{
				u_act.act.CP = 3;
				rc = write(fd_petra_out, &u_act.byte, 1);
				if (rc <= 0)
				{
					perror("Erreur d'ecriture : ");
				}
				temps.tv_sec = 0;
				temps.tv_nsec = 500000000;
				nanosleep(&temps, NULL);
				
				/* Tant que en mouvement, on fait rien */
				read(fd_petra_in, &u_capt.byte, 1);
				while (u_capt.capt.CS == 1)
					read(fd_petra_in, &u_capt.byte, 1);

				u_act.act.PA = 1;
				rc = write(fd_petra_out, &u_act.byte, 1);
				if (rc <= 0)
				{
					perror("Erreur d'ecriture : ");
				}
				sleep(2);
				u_act.act.PV = 1;
				rc = write(fd_petra_out, &u_act.byte, 1);
				if (rc <= 0)
				{
					perror("Erreur d'ecriture : ");
				}
				u_act.act.PA = 0;
				rc = write(fd_petra_out, &u_act.byte, 1);
				if (rc <= 0)
				{
					perror("Erreur d'ecriture : ");
				}

				read(fd_petra_in, &u_capt.byte, 1);
				while (u_capt.capt.PP == 1)
					read(fd_petra_in, &u_capt.byte, 1);

				u_act.act.CP = 2;
				rc = write(fd_petra_out, &u_act.byte, 1);
				if (rc <= 0)
				{
					perror("Erreur d'ecriture : ");
				}
				temps.tv_sec = 0;
				temps.tv_nsec = 500000000;
				nanosleep(&temps, NULL);
			
				/* Tant que en mouvement, on fait rien */
				read(fd_petra_in, &u_capt.byte, 1);
				while (u_capt.capt.CS == 1)
					read(fd_petra_in, &u_capt.byte, 1);

				u_act.act.PV = 0;
				rc = write(fd_petra_out, &u_act.byte, 1);
				if (rc <= 0)
				{
					perror("Erreur d'ecriture : ");
				}
			}
		}
	}
}
