#include <stdio.h>

/* Ici, je d�cide de creer des variable globale pour faire la meme chose que dans le cours. Si c'�tait des varibales local au "main", 
 * Les instructions aurait du chang�e comme �crit dans le PDF
 */

/* 1. Saisir une temp�rature en degr�s Celsius et l�afficher en degr�s Fahrenheit. La formule de
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