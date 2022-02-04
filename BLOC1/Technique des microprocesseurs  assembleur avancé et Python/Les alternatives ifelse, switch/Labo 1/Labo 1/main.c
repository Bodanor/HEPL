#include <stdio.h>

/* Ici, je décide de creer des variable globale pour faire la meme chose que dans le cours. Si c'était des varibales local au "main", 
 * Les instructions aurait du changée comme écrit dans le PDF
 * Par ailleurs, il fait écrit que dans les exos, les varibale pour l'affichage, saisies et alternatives doivent etres des entiers signés.
 * Pour l'exercice 1 et 2, on peux passer par des flottants pour les calculs. Donc uen fois les calculs fait, il faut afficher en entiers signés.
 * Pour finir, on ne peux pas affciher de "float" car avec visual, le '%f' dans le printf n'existse pas c'est pourquoi, on utilise des "double".
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
		// Affichage de msg1 

		push offset msg
		call dword ptr printf
		add esp, 4

		// Scanf pour celsius

		lea eax, celsius
		push eax
		push offset printFormat
		call dword ptr scanf
		add esp, 8

		// Conversion en double

		cvtsi2sd xmm0, celsius
		mov eax, 9
		cvtsi2sd xmm1, eax
		mulsd xmm0, xmm1

		// calcul en fahrenheidt avec la constante 5

		mov eax, 5
		cvtsi2sd xmm1, eax
		divsd xmm0, xmm1

		// calcul en fahrenheidt avec la constante 32

		mov eax, 32
		cvtsi2sd xmm1, eax
		addsd xmm0, xmm1
		movsd fahrenheidt, xmm0

		// Reconversion en entiers signe et affichage de la reponse avec printf

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

/* 3. Saisir la taille des 3 côtés d'un triangle. Afficher si ce triangle est équilatéral (= les 3 côtes
* ont la même taille) ou non.
*/

/*
const char msg[] = "Entrez la taille des 3 cote d'un triangle : ";
const char printFormat[] = "%d %d %d";
const char msg1[] = "\nCe triangle est equilateral";
const char msg2[] = "\nCe triangle n'est pas equilateral";
int a, b, c;

void main()
{
	_asm
	{
		// Affichage de msg

		push offset msg
		call dword ptr printf
		add esp, 4

		// Push des 3 variables pour les cotes + le format pour scanf

		lea eax, c
		push eax
		lea eax, b
		push eax
		lea eax, a
		push eax
		push offset printFormat
		call dword ptr scanf
		add esp, 16

		mov eax, a 
		cmp eax, b // Comparaison de a avec b
		jne equiFalse // Si pa égal alors on jump au label "Equifalse" qui va afficher msg2 à l'ecran. Sinon, on continue l'execution
		cmp eax, c // Plus qu'a tester a avec c
		jne equiFalse // Meme chose qu'avec le précédent jne

		// Si a, b, c sont égaux alors on arrive ici et on va affciher  msg1

		push offset msg1
		call dword ptr printf
		add esp, 4

		jmp finif // Ne pas oublier de jump vers finif sinon, equiFalse va etre executer aussi ce qui n'est pas le but.

	// Affichage si  a, b, c ne sont pas égaux
	equiFalse:
		push offset msg2
		call dword ptr printf
		add esp, 4
		jmp finif // Pas obligatoire puisque finif ce trouve juste en dessous, il va quand meme etre éxécuter à part si on veux gaspiller un cycle d'horloge...


	finif:

	}

}
*/

/* 4. Saisir la taille pour les côtés a, b et c d’un triangle et afficher si ce triangle est rectangle ou
* non, c’est-à-dire s'il satisfait le théorème de Pythagore ou non (par exemple, quand a = 3,
* b = 4 et c = 5, alors le triangle est rectangle).
*/

/*
const char msg[] = "Entrez la taille pour les 3 cote d'un triangle : ";
const char printFormat[] = "%d %d %d";
const char msg1[] = "\nTriangle rectangle !\n";
const char msg2[] = "\nPas un triangle rectangle !\n";
int a, b, c;

void main()
{
	_asm
	{
		// Affichage de msg

		push offset msg
		call dword ptr printf
		add esp, 4

		// Scanf pour les 3 cote du triangle

		lea eax, a
		push eax
		lea eax, b
		push eax
		lea eax, c
		push eax
		push offset printFormat
		call dword ptr scanf
		add esp, 16

		// On va dabord determiner ou est l'hypotenuse donc, le cote le plus grand

		// comparaison d'abord avec a et b
		mov eax, a
		cmp eax, b
		jl compb // Si a plus petit que b alors on jump
		cmp eax, c // Si a plus petit que c alors on jump
		jl compc

		// Si on arrive ici, c'est que "a" est l'hypotenuse. Suffit d'appliquer le theorème de pythagore
		imul eax, eax
		mov ebx, b
		imul ebx, ebx
		mov ecx, c
		imul ecx, ecx
		add ebx, ecx
		cmp eax, ebx
		je recTrue // Si hypotenuse au carre egal somme des deux autres coté au carre alors on jmp pour dire que c'est un triangle rectangle

		// Sinon, on arrive ici et on affiche que c'est pas un triangle rectangle
		jmp recFalse


	compb:
		// ici, on sait deja que "a" est plusque "b" donc inutile de tester
		mov eax, b
		cmp eax, c
		jl compc //Si b plus petit que c alors on jmp 
		
		// Si on arrive ici, c'est que "b" est l'hypotenuse. Suffit d'appliquer le theorème de pythagore
		imul eax, eax
		mov ebx, a
		imul ebx, ebx
		mov ecx, c
		imul ecx, ecx
		add ebx, ecx
		cmp eax, ebx
		je recTrue // Si hypotenuse au carre egal somme des deux autres coté au carre alors on jmp pour dire que c'est un triangle rectangle

		// Sinon, on arrive ici et on affiche que c'est pas un triangle rectangle
		jmp recFalse
		
	compc:

		// ici, on sait que C est l'hypotenuse car on a tester tout les cas possible précédemment. Donc application de pythagore
		mov eax, c

		imul eax, eax
		mov ebx, a
		imul ebx, ebx
		mov ecx, b
		imul ecx, ecx
		add ebx, ecx
		cmp eax, ebx
		je recTrue // Si hypotenuse au carre egal somme des deux autres coté au carre alors on jmp pour dire que c'est un triangle rectangle

		// Sinon, on arrive ici et on affiche que c'est pas un triangle rectangle
		jmp recFalse
	
	// Affichage de si le triangle est rectangle
	recTrue:
		push offset msg1
		call dword ptr printf
		add esp, 4
		jmp end // Pour eviter d'executer le label : "recFalse"

	// Affichage de si le triangle n'est pas rectangle
	recFalse:
		push offset msg2
		call dword ptr printf
		add esp, 4
		jmp end

	end:
		// Tout s'est bien passé 


	}
	
}
*/