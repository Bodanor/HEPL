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
	unsigned L2 : 1; // Lengchristh 2
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

void printMenu();
void printCapteurs(struct CAPTEURS);

main()
{
	int fd_petra_in, fd_petra_out;
	int rc, cpt;
	struct CAPTEURS previous;
	
	unsigned int c;
	fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
	u_act.byte = 0x00;
	printf("actuateurs : %x \n\r", u_act.byte);

	u_act.act.PV = 1;
	printf("actuateurs : %x \n\r", u_act.byte);

	fd_petra_out = open("/dev/actuateursPETRA", O_WRONLY);
	if (fd_petra_in == -1)
	{
		perror("MAIN : Erreur ouverture PETRA_OUT");
		//return 1;
	}
	else
		printf("MAIN: PETRA_OUT opened\n");

	fd_petra_in = open("/dev/capteursPETRA", O_RDONLY);
	if (fd_petra_in == -1)
	{
		perror("MAIN : Erreur ouverture PETRA_IN");
		//return 1;
	}
	else
		printf("MAIN: PETRA_IN opened\n");

	printMenu();

	
	read(fd_petra_in, &previous,  sizeof(previous));
	printCapteurs(previous);
	while (1)
	{
		/* Un caractere est en attente d'etre lu */
		
		if((c = tcischars(0))> 0)
		{
			c = getchar();
			c -= 0x30;
			switch (c)
			{
				case 0:
					u_act.act.CP = 0;
					break;
				case 1:
					u_act.act.CP = 1;
					break;
				case 2:
					u_act.act.CP = 2;
					break;
				case 3 : 
					u_act.act.CP = 3;
					break;
				case 4:
					u_act.act.C1 = (u_act.act.C1 == 1) ? 0 : 1;
					break;
				case 5:
					u_act.act.C2 = (u_act.act.C2 == 1) ? 0 : 1;
					break;
				case 6:
					u_act.act.PV = (u_act.act.PV == 1) ? 0 : 1;
					break;
				case 7:
					u_act.act.PA = (u_act.act.PA == 1) ? 0 : 1;
					break;
				case 8 : 
					u_act.act.AA = (u_act.act.AA == 1) ? 0 : 1;
					break;
				case 9 : 
					u_act.act.GA = (u_act.act.GA == 1) ? 0 : 1;
					break;
			}
			write(fd_petra_out, &u_act.byte, 1);	
		}

		previous = u_capt.capt;
		read(fd_petra_in, &u_capt.byte, 1);

			
			if (previous.L1 != u_capt.capt.L1)
			{
				printf("\033[16;5H");
				printf("%c", u_capt.capt.L1 + 0x30);

			}

			if (previous.L2 != u_capt.capt.L2)
			{
				printf("\033[17;5H");
				printf("%c", u_capt.capt.L2  + 0x30);

			}
			if (previous.T != u_capt.capt.T)
			{
				printf("\033[18;5H");
				printf("%c", u_capt.capt.T + 0x30);

			}
			if (previous.S != u_capt.capt.S)
			{
				printf("\033[19;5H");
				printf("%c", u_capt.capt.S + 0x30);

			}
			if (previous.CS != u_capt.capt.CS)
			{
				printf("\033[20;5H");
				printf("%c", u_capt.capt.CS + 0x30);

			}
			if (previous.AP != u_capt.capt.AP)
			{
				printf("\033[21;5H");
				printf("%c", u_capt.capt.AP + 0x30);

			}
			if (previous.PP != u_capt.capt.PP)
			{
				printf("\033[22;5H");
				printf("%c", u_capt.capt.PP + 0x30);

			}
			if (previous.DE != u_capt.capt.DE)
			{
				printf("\033[23;5H");
				printf("%c", u_capt.capt.DE + 0x30);

			}
			
		
		printf("\033[24;9H");

	}
	
	close(fd_petra_in);
	close(fd_petra_out);
}
void printMenu()
{
	/*
	unsigned CP : 2; // Carrier Position
	unsigned C1 : 1; // Conveyor 1
	unsigned C2 : 1;
	unsigned PV : 1; // Plunger Vacuum
	unsigned PA : 1; // Plunger Activate
	unsigned AA : 1; // Arm Activate
	unsigned GA : 1; // Grapple Activate
	*/

	printf("\033[2J"); // Clean de l'ecran
	printf("---Affichage du menu ---\n\n");
	printf("0-> Carrier position 0 (au niveau des plaquettes)\n");
	printf("1-> Carrier position 1 (au niveau des plaquettes)\n");
	printf("2-> Carrier position 2 (au niveau du convoyeur 1)\n");
	printf("3-> Carrier position 3 (au niveau du convoyeur 2)\n");
	printf("4-> Mise en route du conveyeur 1\n");
	printf("5-> Mise en route du conveyeur 2\n");
	printf("6-> Activation du piston \n");
	printf("7-> Descente de la pompe \n");
	printf("8-> Activation du bras \n");
	printf("9-> Activation du grappin \n\n");
	printf("CAPTEUR : \n\n");

	printf("L1 : \n");
	printf("L2 : \n");
	printf("T : \n");
	printf("S : \n");
	printf("CS : \n");
	printf("AP : \n");
	printf("PP : \n");
	printf("DE : \n\n");

	printf("CHOIX : ");
	fflush(stdout);

}

void printCapteurs(struct CAPTEURS previous)
{
	printf("\033[16;5H");
	printf("%c", previous.L1 + 0x30);

	printf("\033[17;5H");
	printf("%c", previous.L2 + 0x30);


	printf("\033[18;5H");
	printf("%c", previous.T + 0x30);


	printf("\033[19;5H");
	printf("%c", previous.S  + 0x30);


	printf("\033[20;5H");
	printf("%c", previous.CS + 0x30);


	printf("\033[21;5H");
	printf("%c", previous.AP + 0x30);


	printf("\033[22;5H");
	printf("%c", previous.PP  + 0x30);


	printf("\033[23;5H");
	printf("%c", previous.DE  + 0x30);

	fflush(stdout);


}