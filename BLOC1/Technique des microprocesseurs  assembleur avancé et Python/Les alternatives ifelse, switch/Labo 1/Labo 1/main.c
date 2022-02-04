#include <stdio.h>

/* Ici, je décide de creer des variable globale pour faire la meme chose que dans le cours. Si c'était des varibales local au "main", 
 * Les instructions aurait du changée comme écrit dans le PDF
 * Par ailleurs, il fait écrit que dans les exos, les varibale pour l'affichage, saisies et alternatives doivent etres des entiers signés.
 * Pour l'exercice 1 et 2, on peux passer par des flottants pour les calculs. Donc uen fois les calculs fait, il faut afficher en entiers signés.
 */

/* 1. Saisir une température en degrés Celsius et l’afficher en degrés Fahrenheit. La formule de
 * conversion est F = C * 9 / 5 + 32
 */

/*
const char msg[] = "Entrez une temperature en celsius : ";
const char printFormat[] = "%d";
const char msg1[] = "\nLa temperature en Fahrenheidt vaut : %d";
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

		cvttsd2si eax, xmm0
		push eax
		push offset msg1
		call dword ptr printf
		add esp, 8

	}

}
*/

/* 2. Saisir la distance (en kilomètres) et la durée d’un trajet (en heures et minutes). Afficher la
 * vitesse moyenne du trajet (par exemple, pour un trajet de 200 km effectué en 2 heures et 30
 * minutes, on a une vitesse moyenne de 80 km/h).
 */

/*
const char msg[] = "Entrez la distance en kilometres : ";
const char msg1[] = "Entrez la duree du trajet en heures et minutes : ";
const char printFormatdistance[] = "%d";
const char printFormatDuree[] = "%d %d";
const char msg2[] = "\nLa vitesse moyenne est de : %d km/h";

int distance, heures, minutes;

void main()
{
	_asm
	{
		push offset msg
		call dword ptr printf
		add esp, 4

		lea eax, distance
		push eax
		push offset printFormatdistance
		call dword ptr scanf
		add esp, 8

		push offset msg1
		call dword ptr printf
		add esp, 4

		lea eax, minutes
		push eax
		lea eax, heures
		push eax
		push offset printFormatDuree
		call dword ptr scanf
		add esp,12

		// Conversion des valeurs en double
		cvtsi2sd xmm0, heures
		cvtsi2sd xmm1, minutes
		mov eax, 60
		cvtsi2sd xmm2, eax
		divsd xmm1, xmm2
		addsd xmm0, xmm1

		cvtsi2sd xmm1, distance
		divsd xmm1, xmm0

		cvttsd2si eax, xmm1

		push eax
		push offset msg2
		call dword ptr printf
		add esp, 8

	}

}
*/