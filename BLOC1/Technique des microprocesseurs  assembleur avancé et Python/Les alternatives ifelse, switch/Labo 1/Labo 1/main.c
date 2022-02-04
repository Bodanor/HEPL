#include <stdio.h>

/* Ici, je décide de creer des variable globale pour faire la meme chose que dans le cours. Si c'était des varibales local au "main", 
 * Les instructions aurait du changée comme écrit dans le PDF
 */

/* 1. Saisir une température en degrés Celsius et l’afficher en degrés Fahrenheit. La formule de
conversion est F = C * 9 / 5 + 32 */

/*
const char msg[] = "Entrez une temperature en celsius : ";
const char printFormat[] = "%d";
const char msg1[] = "\nLa temperature en Fahrenheidt vaut : %lf";
int celsius;
double fahrenheidt;
void main()
{
	_asm
	{
		push offset msg
		call dword ptr printf
		add esp, 4

		lea eax, celsius
		push eax
		push offset printFormat
		call dword ptr scanf
		add esp, 8

		cvtsi2sd xmm0, celsius
		mov eax, 9
		cvtsi2sd xmm1, eax
		mulsd xmm0, xmm1

		mov eax, 5
		cvtsi2sd xmm1, eax
		divsd xmm0, xmm1

		mov eax, 32
		cvtsi2sd xmm1, eax
		addsd xmm0, xmm1
		movsd fahrenheidt, xmm0

		push fahrenheidt + 4
		push fahrenheidt
		push offset msg1
		call dword ptr printf
		add esp, 12

	}

}
*/