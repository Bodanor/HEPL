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
		nop
	debutwhile:
		mov eax, i
		cmp eax, 6
		jge finwhile

		mov ebx, offset vecentiers
		cmp dword ptr[ebx + eax*4], 0
		jl ajouterdouble
		inc i
		jmp debutwhile

	ajouterdouble:
		cvtsi2sd xmm0, qword ptr[ebx + eax*4]
		mov eax, b
		mov ebx, offset vecdouble
		movsd qword ptr[ebx + eax*8], xmm0
		inc b
		inc i
		jmp debutwhile

	finwhile:
	}
}
*/