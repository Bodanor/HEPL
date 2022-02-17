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