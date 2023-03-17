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

void printSuiviPiece(void);
void* FctMouvement(void *);
void* FctAffichage(void*);	


int fd_petra_in, fd_petra_out;

main()
{
	pthread_t thread_mvmt;
	pthread_t thread_affichage;
	
	int rc, cpt, ret;

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


	ret = pthread_create(&thread_mvmt, NULL, FctMouvement, NULL);
	if (ret != 0) {
		perror("Erreur de creation du thread de lecture de capteurs !\n");
		return -1;
	}

	ret = pthread_join(thread_mvmt, NULL);
	if (ret != 0) {
		perror("Erreur de synchronisation de thread !\n");
		return -1;
	}
	
}


/* Tu prefere avoir un truc genre comme ca : 

	Piece au debut du charriot []
	Piece au debut du convoyeur 1 []
	piece au mileu du convoyeur 1 []
	Piece à la fin du convoyeur 1 [*]
	Piece au debut du convoyeur 2 []
	piece au mileu du convoyeur 2 []
	Piece à la fin du convoyeur 2 []
	Piece dans le bac de destination []
*/
void printSuiviPiece(void)
{

	printf("Pièce au début du chariot\t[   ]\n");
	printf("Pièce au début du convoyeur 1\t[   ]\n");
	printf("Pièce au milieu du convoyeur 1\t[   ] \n");
	printf("Pièce à la fin du convoyeur 1\t[   ]\n");
	printf("Pièce au début du convoyeur 2\t[   ]\n");
	printf("Pièce au milieu du convoyeur 2\t[   ]\n");
	printf("Pièce à la fin du convoyeur 2\t[   ]\n");
	printf("Pièce dans le bac\t\t[   ]\n");

	fflush(stdout);
}


void* FctMouvement(void* p)
{

	int rc, compteur_slot;
	struct CAPTEURS previous_capteurs_struct;
	unsigned char previous_capteurs_byte;
	

	read(fd_petra_in, &u_capt.byte, 1);

	while (1)
	{

		compteur_slot = 0; // Pour plus tard pour l'etat pour slot

		previous_capteurs_byte = u_capt.byte;
		/* Tant que l'etat des capteurs a pas change, on ne fait rien */
		u_act.act.PV = 0;		
		u_act.act.CP = 0; // Le plongeur est en position 0 initialement
		rc = write(fd_petra_out, &u_act.byte, 1);
		if (rc <= 0)
		{
			perror("Erreur d'ecriture : ");
		}

		read(fd_petra_in, &u_capt.byte, 1);

		/* Tant que pas au debut on attend*/
		while(u_capt.capt.CS == 1)
			;
		

		read(fd_petra_in, &u_capt.byte, 1);

		if (u_capt.capt.DE == 0)
		{
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
			while (u_capt.capt.PP == 1){
					read(fd_petra_in, &u_capt.byte, 1);
					}
						
			u_act.act.CP = 1;
			rc = write(fd_petra_out, &u_act.byte, 1);
			if (rc <= 0)
			{
				perror("Erreur d'ecriture : ");
			}
			sleep(1); // Teporisation pour capteur
			read(fd_petra_in, &u_capt.byte, 1);
			/* Tant que en mouvement, on fait rien */
			while(u_capt.capt.CS == 1)
					read(fd_petra_in, &u_capt.byte, 1);
					
			/* On lache la piece sur le convoyeur 1*/
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

			read(fd_petra_in, &u_capt.byte, 1);
			while (u_capt.capt.S == 1) {
				read(fd_petra_in, &u_capt.byte, 1);
				nanosleep(10000);
				while (u_capt.capt.S == 0 && compteur_slot != 1)
				{
					compteur_slot = 1;
				}
			}

			int finis = 0;
			while (!finis) {
				read(fd_petra_in, &u_capt.byte, 1);

				if (u_capt.capt.S == 0) 
				{
					// Demarrage timer
					while( !finis)
					{

					}
					read(fd_petra_in, &u_capt.byte, 1);
					if (u_capt.capt.S == 1)
					{
						compteur_slot = 1;
					}
					else
						compteur_slot = 0;
				}
			}

			/*
while (previous_capteurs_byte != u_capt.byte)
{

	if (u_capt.capt.S != previous_capteurs_struct.S)
	{

	}

	if(u_capt.capt.L1 != previous_capteurs_struct.L1)
		;
	// A completer
}
*/


		}
		

		/* Si un capteur change, on regarde lequel a changer d'etat */

		
		/*
		u_act.byte = 0; // Debut du tour de boucle
		previous_capteurs_byte = 0

		
		u_act.act.CP = 0; // Le plongeur est en position 0
		rc = write(fd_petra_out, &u_act.byte, 1);
		if (rc <= 0)
		{
			perror("Erreur d'ecriture : ");
		}
		while (u_capt.capt.L1 != 0)
			;
		
		while(u_capt.capt.S != 0)
			;
		while (u_capt.)
		if (u_capt.capt.)
			u_act.act.AA = 0;
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
		sleep(1);
		u_act.act.PA = 0;
		rc = write(fd_petra_out, &u_act.byte, 1);
		if (rc <= 0)
		{
			perror("Erreur d'ecriture : ");
		}
		sleep(2);
		u_act.act.CP = 1;//Le plongeur est en position 0
		rc = write(fd_petra_out, &u_act.byte, 1);
		if (rc <= 0)
		{
			perror("Erreur d'eccriture : ");
		}
		sleep(4);
		u_act.act.PV = 0;
		u_act.act.C1 = 1;
		rc = write(fd_petra_out, &u_act.byte, 1);
		if (rc <= 0)
		{
			perror("Erreur d'ecriture : ");
		}
		sleep(9);
		u_act.act.C1 = 0;
		u_act.act.GA = 1;
		rc = write(fd_petra_out, &u_act.byte, 1);
		if (rc <= 0)
		{
			perror("Erreur d'ecriture : ");
		}
		sleep(1);
		u_act.act.AA = 1;
		rc = write(fd_petra_out, &u_act.byte, 1);
		if (rc <= 0)
		{
			perror("Erreur d'ecriture : ");
		}
		sleep(3);
		u_act.act.C2 = 1;
		u_act.act.GA = 0;
		rc = write(fd_petra_out, &u_act.byte, 1);
		if (rc <= 0)
		{
			perror("Erreur d'ecriture : ");
		}
		sleep(9);
		u_act.act.C2 = 0;
		rc = write(fd_petra_out, &u_act.byte, 1);
		if (rc <= 0)
		{
			perror("Erreur d'ecriture : ");
		}
		*/


	}

}