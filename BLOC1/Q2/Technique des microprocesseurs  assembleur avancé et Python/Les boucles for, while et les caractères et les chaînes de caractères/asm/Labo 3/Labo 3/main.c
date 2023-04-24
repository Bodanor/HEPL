#include <stdio.h>
#include <stdlib.h>

/* 1. Afficher le contenu d’un vecteur de doubles.

double vect[5] = { 5.0, 3.4, 98.3764, 874.847, 437.874 };
const char printFormat[] = "%lf ";
int i;

i = 0;
int main()
{
	_asm
	{
	debutwhile:
		cmp i, 5
		jge finwhile	// Si i >= a 5 alors on saute
		
		mov eax, i		//Eax stocke I
		mov ebx, offset vect	// EBX contient l'adresse de vect double
		movsd xmm0, qword ptr[ebx + eax*8]	//XMM0, ebx(adresse) + eax(i) + 8 (double = 8 octets)
		sub esp, 8	// On ne peux pas push xmm0, donc on soustrait 8 a esp
		movsd qword ptr[esp], xmm0	// On deplace xmm0 a esp
		push offset printFormat		// on place le format pour printf dans la pile
		call dword ptr printf		// call printf
		add esp, 12		// Rajouter 12 a esp, pour détruire le push (xmm0 + formatprintf)
			
		inc i	// Incrementer i a chaque boucle
		jmp debutwhile
	finwhile:

	}

}
*/

/* 2. Copier dans un vecteur de doubles uniquement les valeurs négatives figurant dans un
vecteur d’entiers (par exemple, si VecEntiers contient [-9, 4, 8, -2, -7, 5], alors on aura dans
VecDoubles [-9, -2, -7]).

int vecentiers[6] = {-9, 4, 8, -2, -7, 5};
double vecdouble[6];
int i = 0, b = 0;
int main()
{
	_asm
	{
	debutwhile:
		mov eax, i	// EAX, contient i (compteur jusque 6)
		cmp eax, 6	// Si eax, >= 6 alors on saute
		jge finwhile

		mov ebx, offset vecentiers	// EBX, adresse vecentiers
		cmp dword ptr[ebx + eax*4], 0	// EBX(adresse) + eax(i) + 4(car des entiers), compare à 0
		jl ajouterdouble		// Si plus petit que zero (donc negatif) alors on saute
		inc i	// Sinon in incremente i et donc on passe a l'entier suivant
		jmp debutwhile	// Rvenir au debut de boucle while

	ajouterdouble:	// Si on est ici c'est qu'on a détécté un nombre négatif
		cvtsi2sd xmm0, qword ptr[ebx + eax*4]	// Convertion du nmb négatif en double dans XMM0
		mov eax, b	// On prend la valeur b (variable qui sert de compteur dans le vecteur de double)
		mov ebx, offset vecdouble	//EBX contient l'adresse du vecdouble
		movsd qword ptr[ebx + eax*8], xmm0	// Deplacement de XMM0, dans le vecteur de double (8 car double)
		inc b	// Ne pas oublier d'incrementer b
		inc i	// Pareil ici puisque après on jump au debut de boucle 
		jmp debutwhile	// Jump début de boucle

	finwhile:	// Sert à sortir de boucle
	}
}
*/

/* 3. Insérer une valeur saisie au clavier au bon endroit dans un vecteur d’entiers dont les valeurs
sont déjà ordonnées dans un ordre croissant (par exemple, si VecEntiers contient [2, 8, 11,
15, 20] et que la valeur à insérer est 10, alors on aura dans VecEntiers [2, 8, 10, 11, 15, 20]).

int VecEntiers[5] = { 2, 8, 11, 15, 20 };
int valeur;
char scanfFormat[] = "%d";
void main()
{
	_asm
	{
		mov eax, offset valeur
		push eax
		push offset scanfFormat


	}


}
*/



/* 2. Échanger 2 à 2 les caractères dans une chaîne de caractères (par exemple, pour la chaîne
"bonjour", on aura "objnuor"). */

/*
char string[] = "bonjour";

void main()
{
	_asm
	{
		mov eax, offset string
		debutwhile :

		cmp byte ptr[eax], 0
			je finwhile

			cmp byte ptr[eax + 1], 0
			je finwhile

			mov bl, byte ptr[eax + 1]
			xchg bl, byte ptr[eax]
			mov byte ptr[eax + 1], bl

			add eax, 2
			jmp debutwhile

		finwhile:
	}
}
*/
