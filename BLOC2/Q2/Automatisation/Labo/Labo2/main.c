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
void *FctCapteur(void *);
void *FctMouvement(void *);

struct CAPTEURS previous_capteurs; // Global pour le thread de lecture de capteurs
int fd_petra_in, fd_petra_out;

main()
{
	pthread_t thread_capteur;
	pthread_t thread_mvmt;

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
	if (ret != 0)
	{
		perror("Erreur de creation du thread de lecture de capteurs !\n");
		return -1;
	}
	ret = pthread_create(&thread_capteur, NULL, FctCapteur, NULL);
	if (ret != 0)
	{
		perror("Erreur de creation du thread de lecture de capteurs !\n");
		return -1;
	}

	/*
	ret = pthread_join(&thread_mvmt, NULL);
	if (ret != 0) {
		perrot("Erreur de synchronisation de thread !\n");
		return -1;
	}
	*/
	ret = pthread_join(thread_capteur, NULL);
	if (ret != 0)
	{
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

void *FctCapteur(void *p1)
{
	printf("\033[2J"); // Clear screen
	printf("\033[0;0H"); // Workaround car les printf continuent après les logs, donc il suffit de placer le curseur au début du terminal !
	printf("\e[?25l"); // Permet de cacher le curseur
	printSuiviPiece();

	while (1)
	{
		read(fd_petra_in, &u_capt.byte, 1);

		// La pièce se trouve au debut du convoyeur 1
		if (u_capt.capt.L1)
		{
			printf("\033[1;35H");
			printf("*");
		}
		else
		{
			printf("\033[1;32H");
			printf(" ");
		}

		// La pièce se trouve au debut du convoyeur 2
		if (u_capt.capt.L2)
		{
			printf("\033[5;35H");
			printf("*");
		}
		else
		{
			printf("\033[5;35H");
			printf(" ");
		}


		/*
		if (previous_capteurs.T != u_capt.capt.T)
		{
			printf("\033[3;5H");
			printf("%c", u_capt.capt.T + 0x30);
		}
		if (previous_capteurs.S != u_capt.capt.S)
		{
			printf("\033[4;5H");
			printf("%c", u_capt.capt.S + 0x30);
		}
		if (previous_capteurs.CS != u_capt.capt.CS)
		{
			printf("\033[5;5H");
			printf("%c", u_capt.capt.CS + 0x30);
		}
		if (previous_capteurs.AP != u_capt.capt.AP)
		{
			printf("\033[6;5H");
			printf("%c", u_capt.capt.AP + 0x30);
		}
		if (previous_capteurs.PP != u_capt.capt.PP)
		{
			printf("\033[7;5H");
			printf("%c", u_capt.capt.PP + 0x30);
		}
		if (previous_capteurs.DE != u_capt.capt.DE)
		{
			printf("\033[8;5H");
			printf("%c", u_capt.capt.DE + 0x30);
		}
		*/
	}
}

void *FctMouvement(void *p)
{

	/* 	struct ACTUATEURS
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
	} u_act; */

	int rc;

	u_act.byte = 0;
	while (1)
	{

		sleep(2);
		u_act.act.AA = 0; // Le plongeur est en position 0
		rc = write(fd_petra_out, &u_act.byte, 1);
		if (rc <= 0)
		{
			perror("Erreur d'ecriture : ");
		}
		sleep(4); // Attente pour que le plongeur soit bel et bien en position 0

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
		sleep(2);
		u_act.act.PA = 0;
		rc = write(fd_petra_out, &u_act.byte, 1);
		if (rc <= 0)
		{
			perror("Erreur d'ecriture : ");
		}
		sleep(2);
		u_act.act.AA = 1; // Le plongeur est en position 0
		rc = write(fd_petra_out, &u_act.byte, 1);
		if (rc <= 0)
		{
			perror("Erreur d'eccriture : ");
		}
		sleep(1);
		u_act.act.PV = 1;
		u_act.act.C1 = 1;
		rc = write(fd_petra_out, &u_act.byte, 1);
		if (rc <= 0)
		{
			perror("Erreur d'ecriture : ");
		}
		sleep(10);
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
		sleep(7);
		u_act.act.C2 = 0;
		rc = write(fd_petra_out, &u_act.byte, 1);
		if (rc <= 0)
		{
			perror("Erreur d'ecriture : ");
		}
	}
}