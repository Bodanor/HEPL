#include <stdio.h>

/*
 * 1. Saisir les valeurs pour R et I et afficher la valeur pour U. La loi d'Ohm est : la tension U
 * (en volts) aux bornes d'une résistance R (en ohms) est proportionnelle à l'intensité du
 * courant électrique I (en ampères) qui la traverse.
*/

/*

const char msg[] = "Entrez la valeur de R (ohms): ";
const char msg1[] = "Entrez la valeur de I (Ampere): ";
const char msg2[] = "La valeur de U vaut : %lf volts\n";
const char formatSaisie[] = "%lf";
double R, I, U;

void main()
{
	_asm
	{
		push offset msg
		call dword ptr printf
		add esp, 4

		lea eax, R
		push eax
		push offset formatSaisie
		call dword ptr scanf
		add esp, 8

		push offset msg1
		call dword ptr printf
		add esp, 4

		lea eax, I
		push eax
		push offset formatSaisie
		call dword ptr scanf
		add esp, 8

		movsd xmm0, I
		mulsd xmm0, R
		movsd U, xmm0

		push U + 4
		push U
		push offset msg2
		call dword ptr printf
		add esp, 12
	}
}
*/

/* 2. Saisir le rayon R d’un cercle et afficher le périmètre de ce cercle. Formule du périmètre :
 * P = 2 π R, où π correspond à 3.14 (nombre pi).
 */

/*

const char msg[] = "Entrez le rayon R d'un cercle : ";
const char msg1[] = "Le perimetre du cercle vaut : %lf ";
const char formatSaisie[] = "%lf";
const double pi = 3.14159;

double peri;
double rayon;

void main()
{
	_asm
	{
		push offset msg
		call dword ptr printf
		add esp, 4

		lea eax, rayon
		push eax
		push offset formatSaisie
		call dword ptr scanf
		add esp, 8

		movsd xmm0, rayon
		mov eax, 2
		cvtsi2sd xmm1, eax
		mulsd xmm0, xmm1
		mulsd xmm0, pi
		movsd peri, xmm0

		push peri + 4
		push peri
		push offset msg1
		call dword ptr printf
		add esp, 12
	}
}

*/
/*
	3. Entrer 2 valeurs et saisir l'opération à réaliser sur ces 2 valeurs parmi : 1 pour +, 2 pour -, 3 pour * et 4 pour /, 
	puis afficher le résultat de l’opération. 
*/

/*

const char msgA[] = "Entrez la valeur de a :";
const char msgB[] = "Entrez la valeur de b :";
const char msgChoix[] = "Entrez l'operation a effectuer :\n1) Addition\n2) Soustraction\n3) Multiplication\n4) Division\n\nChoix :";
const char formatSaisie[] = "%d";

int operation, a, b;

void main()
{
	_asm
	{
		push offset msgA
		call dword ptr printf
		add esp, 4

		lea eax, a
		push eax
		push offset formatSaisie
		call dword ptr scanf
		add esp, 8

		push offset msgB
		call dword ptr printf
		add esp, 4

		lea eax, b
		push eax
		push offset formatSaisie
		call dword ptr scanf
		add esp, 8

		push offset msgChoix
		call dword ptr printf
		add esp, 4

		lea eax, operation
		push eax
		push offset formatSaisie
		call dword ptr scanf
		add esp, 8

		mov eax, a
		mov ebx, b

		cmp operation, 1
		je addition

		cmp operation, 2
		je soustraction

		cmp operation, 3
		je multiplication

		cmp operation, 4
		je division

	addition:
		add eax, ebx
		jmp afficherResultat

	soustraction:
		sub eax, ebx
		jmp afficherResultat

	multiplication:
		imul eax, ebx
		jmp afficherResultat

	division:
		cdq
		idiv ebx

	afficherResultat:
		push eax
		push offset formatSaisie
		call dword ptr printf
		add esp, 8
	}
}
*/

/*
	4. Entrer la taille pour les côtés a, b, c et d d'un quadrilatère. Afficher si ce quadrilatère est un
	losange (a = b = c = d), un parallélogramme (a = c et b = d) ou une autre forme.
/*

/*

double a, b, c, d;
const char msg[] = "Entrez la taille de chaque cote d'un quadrilatere (separerer par un espace): ";
const char formatsaisie[] = "%lf %lf %lf %lf";
const char msglosange[] = "C'est un losange !\n";
const char msgPara[] = "C'est un parallelogramme !\n";
const char msgAutre[] = "C'est une autre forme !\n";

void main()
{
	_asm
	{
		push offset msg
		call dword ptr printf
		add esp, 4

		lea eax, d
		push eax
		lea eax, c
		push eax
		lea eax, b
		push eax
		lea eax, a
		push eax
		push offset formatsaisie
		call dword ptr scanf
		add esp, 20

		movsd xmm0, a
		comisd xmm0, b
		jne compareother

		comisd xmm0, c
		jne compareother

		comisd xmm0, d
		jne compareother

		push offset msglosange
		call dword ptr printf
		add esp, 4
		jmp fin

	compareother:
		comisd xmm0, c
		jne autreForme

		movsd xmm0, b
		comisd xmm0, d
		jne autreForme

		push offset msgPara
		call dword ptr printf
		add esp, 4

		jmp fin

	autreForme:
		push offset msgAutre
		call dword ptr printf
		add esp, 4

	fin:
	}
}
*/