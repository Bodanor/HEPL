#include <stdio.h>

/* Ici, je d�cide de creer des variable globale pour faire la meme chose que dans le cours. Si c'�tait des varibales local au "main", 
 * Les instructions aurait du chang�e comme �crit dans le PDF
 * Par ailleurs, il fait �crit que dans les exos, les varibale pour l'affichage, saisies et alternatives doivent etres des entiers sign�s.
 * Pour l'exercice 1 et 2, on peux passer par des flottants pour les calculs. Donc uen fois les calculs fait, il faut afficher en entiers sign�s.
 */

/* 1. Saisir une temp�rature en degr�s Celsius et l�afficher en degr�s Fahrenheit. La formule de
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

/* 2. Saisir la distance (en kilom�tres) et la dur�e d�un trajet (en heures et minutes). Afficher la
 * vitesse moyenne du trajet (par exemple, pour un trajet de 200 km effectu� en 2 heures et 30
 * minutes, on a une vitesse moyenne de 80 km/h).
 */
